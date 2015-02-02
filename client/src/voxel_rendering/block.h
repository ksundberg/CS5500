#ifndef BLOCK_H
#define BLOCK_H

enum BlockType
{
	BlockTypeDefault
};

class Block
{
	public:
		Block();
		~Block();

		bool IsActive();
		void SetActive(bool active);

	private:
		bool mActive;

		BlockType mBlockType;
};

#endif