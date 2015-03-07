#include "MiniMapCamera.h"
#include <iostream>

const int z_fixed = 100;

MiniMapCamera::MiniMapCamera(float x, float y, float z)
{
  CameraPosition.x = x;
  CameraPosition.y = y;
  CameraPosition.z = z_fixed;

  CameraRotation = Vector3(0, 0, 0);
  // lack of rotate function intentionally left out due to mini map being
  // constant stable
  // CameraRotation initialized so that chunkManager::Update can be utilized
}

void AskElement()
{
  string requested_element;

  std::cin >> requested_element;
  CheckElementInput(requested_element);
}

void CheckElementInput(element)
{
  struct Test
  {
    bool LettersOnly;
    Test() : LettersOnly(true) {}

    void operator()(char a)
    {
      if (LettersOnly && !((a <= 'z' && a >= 'a') || (a <= 'Z' && a >= 'A')))
        LettersOnly = false;
    }
  }

  Test element;
  for_each(name.begin(), name.end(), element);

  if (element.LettersOnly)
  {
  }
  else
  {
    AskElement();
  }
}
////////////////////////////////////////////////////////
// lamba function --- will return int value of concentration of desired element
//[](string)->(int){return 1;}

// this is where we will recieve a value of density of the requested element and
// provide a gui that is like a heat map
// where darker colors are more concentration of the element
