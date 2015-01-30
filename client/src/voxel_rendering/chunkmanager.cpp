#include "chunkmanager.h"
#include <vector>
#include <math.h>
#include "chunk.h"
#include "vector3f.h"
#include "tbb/parallel_for.h"
#include "tbb/task_scheduler_init.h"

/*
The insert methods have been replaced with a blind write to memory in the future we need to insert error checking to make sure
that the index exists and we need to double check index calculations to make sure that chunks don't overlap each other in these
arrays does not happen doing this assumes that it is safe to overwrite an index.
*/

ChunkManager::ChunkManager()
{
	tbb::task_scheduler_init init;//Initializing the the tbb task scheduler using the automatic thread count
	pCameraPosition = new Vector3f(-(16 * (MAX_CHUNKS_INDEX_X/2)) -1,-(16 * (MAX_CHUNKS_INDEX_Y/2)) -1,-(16 * (MAX_CHUNKS_INDEX_Z/2)) -1);//Initializing the camera to an invalid position to guarantee the Visibility list is generated on entering the world
	pCameraRotation = new Vector3f();
}

void ChunkManager::Update(float /*deltaTime*/, Vector3f cameraPosition, Vector3f cameraRotation)
{
	//Code to designate which chunks should be processed below.
	int numChunksLoaded = 0;

	Vector3f cChunk = translateCameraPositionToChunk(cameraPosition);//Getting which chunk the camera is currently in
	if (pCameraPosition->equals(cameraPosition) == false || pCameraRotation->equals(cameraRotation) == false)//The camera has changed, therefore the Visiblity lists and load/unload lists must be updated
	{
		for(int i = cChunk.getX() - MAX_VIEW_DISTANCE; i < cChunk.getX() - MAX_VIEW_DISTANCE; i++)//i = x, j = y, k = z
		{
			for(int j = cChunk.getY() - MAX_VIEW_DISTANCE; j < cChunk.getY() + MAX_VIEW_DISTANCE; j++)
			{
				tbb::parallel_for(//adds the area around the player to the Chunk Visiblity list
					tbb::blocked_range<int>(cChunk.getZ() - MAX_VIEW_DISTANCE, cChunk.getZ() + MAX_VIEW_DISTANCE),
					[&](const tbb::blocked_range<int>& r)
					{
						for(int k = r.begin(); k < r.end(); k++)
						{
							Chunk *tChunk = new Chunk(i, j, k);
							int l = translatePositionToIndex(*tChunk->getPosition());
							tChunk->setIndex(l);
							nchunkVisibilityList[l] = tChunk;
						}
					}
				);
			}
		}

		tbb::parallel_for(//A parallel for loop that categorizes which loaded chunks need to be unloaded.
			chunkListRange(pChunkVisibilityList.begin(), pChunkVisibilityList.end()),
			[&](chunkListRange& r){
				for(auto i: r)
				{
					Chunk* pChunk = i;
					if (nchunkVisibilityList[i->getIndex()] != NULL)
					{
						chunkUnloadList[pChunk->getIndex()] = pChunk;
					}
				}

		});

		tbb::parallel_for(//A parallel for loop that categorizing which chunks have yet to be loaded
			chunkListRange(nchunkVisibilityList.begin(), nchunkVisibilityList.end()),
			[&](chunkListRange& r){
				for(auto i: r)
				{
					Chunk* pChunk = i;
					if (pChunkVisibilityList[i->getIndex()] == NULL || (!pChunk->IsLoaded() || !pChunk->IsSetup()))
					{
						chunkProcessingList[pChunk->getIndex()] = pChunk;
					}
				}

		});
	}

	tbb::parallel_for(chunkListRange(chunkProcessingList.begin(), chunkProcessingList.end()),//A parallel for loop representing a Map of Sequences to be performed on Chunks within the range of the players that can be safe done concurrently
		[&](chunkListRange& r){//A labmda function with pass by reference, this requires compiling under c++11 standard
			for(auto& i: r){//The parallel for loop for a concurrent vector of Chunks
				//add chunk processing code below
				if(i != NULL)
				{
					Chunk* pChunk = i;

					//Update Load List Sequence
					if(pChunk->IsLoaded() == false)
					{
						if(numChunksLoaded < 20)
						{
							pChunk->load();

							numChunksLoaded++;

							forceVisibilityUpdate = true;
						}
					}

					//Update Setup List Sequence
					if(pChunk->IsLoaded() && pChunk->IsSetup() == false)
					{
						pChunk->setup();

						if(pChunk->IsSetup())
						{
							forceVisibilityUpdate = true;
						}
					}

					//Update Rebuild List
					if(pChunk->IsLoaded() && pChunk->IsSetup() && pChunk->getRebuild())
					{
						if(numChunksLoaded < 20)
						{
							//pChunk->RebuildMesh(); This is commented out until the rendering support is complete

							chunkRebuildList[pChunk->getIndex()] = pChunk;

							//Functional Reduce code for setting the UpdateFlags of neighbouring chunks
							//TODO: Reduce pattern
							//End functional reduce code for mesh building

							numChunksLoaded++;

							forceVisibilityUpdate = true;
						}
					}
				}
			}
		});
	chunkProcessingList.clear();//Clearing the list for reuse on the next update


	//Update Flags List
	//TODO: Update Flags are part the reduce pattern
	chunkRebuildList.clear();//Clearing the list for reuse on the next update

	//Update Unload List
	tbb::parallel_for(chunkListRange(chunkUnloadList.begin(), chunkUnloadList.end()),
		[&](chunkListRange& r){
		for(auto& i: r){//A for loop that removes and unloads chunks
			if(i != NULL)
			{
				Chunk* pChunk = i;
				delete pChunk;//Deletes the chunk to simulate the unload function which will be written after world persistence is handleable
			}
		}
	});
	chunkUnloadList.clear();//clearing the list for reuse on the next update

	//Update RenderList if camera position or rotation has changed since last update
	chunkRenderList = nchunkVisibilityList;//Setting the Render list equal to the Visibility list as a place holder for the reduce function that generates the Render List




	pChunkVisibilityList = nchunkVisibilityList;
	nchunkVisibilityList.clear();

	*pCameraPosition = cameraPosition;//setting the previous camera position to the current camera position for the next updates calculation purposes
	*pCameraRotation = cameraRotation;//setting the previous camera rotation to the current camera rotation for the next updates calculation purposes
}

int ChunkManager::translatePositionToIndex(Vector3f chunkPosition)//Accepts the X,Y,Z coordinates of a chunk and translates it to and one dimensional index position based upon the size limits of the world
{
	float x = chunkPosition.getX();
	float y = chunkPosition.getY();
	float z = chunkPosition.getZ();
	return (x + (MAX_CHUNKS_INDEX_X/2)) + ((y + (MAX_CHUNKS_INDEX_Y/2)) * MAX_CHUNKS_INDEX_X) + ((z + (MAX_CHUNKS_INDEX_Z/2)) * MAX_CHUNKS_INDEX_X * MAX_CHUNKS_INDEX_Y);//This assumes a zero based index and that
		//the negative range and the non-negative range(this includes 0 as non-negative) are of equal size
}

Vector3f * ChunkManager::translateIndexToPosition(int chunkIndex)//Accepts the one dimensional index position of a Chunk and returns the Vector3f coordinates in the world space.
{
	//Some of the math bellow may require require casting the values to doubles or floats to avoid truncation
//	float cIndex = (double) chunkIndex;
	float ara[3];//This may need to be cast to a constant float
	ara[0] = chunkIndex % MAX_CHUNKS_INDEX_X -(MAX_CHUNKS_INDEX_X / 2); //Calculating the X position of the chunk in the world
	ara[1] = floor((chunkIndex % (MAX_CHUNKS_INDEX_X * MAX_CHUNKS_INDEX_Y)) / MAX_CHUNKS_INDEX_X) - (MAX_CHUNKS_INDEX_Y/2);//Calculating the Y position of the Chunk in the World
	ara[2] = floor(chunkIndex / (MAX_CHUNKS_INDEX_X * MAX_CHUNKS_INDEX_Y)) - (MAX_CHUNKS_INDEX_Z/2);//Calculating the Z position of the Chunk in the World
	return new Vector3f(ara);
}

Vector3f ChunkManager::translateCameraPositionToChunk(Vector3f cameraPosition)
{
	float x_position = floor(cameraPosition.getX() + (16 * (MAX_CHUNKS_INDEX_X / 2)) / 16) - (MAX_CHUNKS_INDEX_X / 2);
	float y_position = floor(cameraPosition.getY() + (16 * (MAX_CHUNKS_INDEX_Y / 2)) / 16) - (MAX_CHUNKS_INDEX_Y / 2);
	float z_posiiton = floor(cameraPosition.getZ() + (16 * (MAX_CHUNKS_INDEX_Z / 2)) / 16) - (MAX_CHUNKS_INDEX_Z / 2);
	Vector3f chunk(x_position, y_position, z_posiiton);
	return chunk;
}
