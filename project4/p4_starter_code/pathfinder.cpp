#include <iostream>

#include "image.h"
#include "deque.hpp"

int main(int argc, char *argv[])
{
  Image<Pixel> input = readFromFile(argv[1]); //reads in the image
  Pixel s; //will hold the starting position

  //The following loops will be responsible for locating the starting state
  for(int i = 0; i < input.width();i++)
  {
    for(int j = 0; j < input.height();j++)
    {
      if(input(i,j) == RED)
      {
        s = input(i,j);
      }
    }
  }




}

