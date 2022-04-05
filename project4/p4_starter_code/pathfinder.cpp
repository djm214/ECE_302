#include <iostream>

#include "image.h"
#include "deque.hpp"

int main(int argc, char *argv[])
{
  Image<Pixel> input = readFromFile(argv[1]); //reads in the image
  Image<Pixel> output = readFromFile(argv[2]); //what soln wil be written to
  Pixel s; //will hold the starting position

  //The following loops will be responsible for locating the starting state
  for(int i = 0; i < input.width();i++)
  {
    for(int j = 0; j < input.height();j++)
    {
      if(input(i,j) == RED)
      {
        //cases of if the pixel is on the outter edge of the maze already
        if(i == 0 || i == (input.width()-1))
        {
          input(i,j) = GREEN; //write that one pixel to green
          std::cout<< "Solution found";
          return EXIT_SUCCESS;
        }
        else if(j == 0 || j == (input.height()-1))
        {
          input(i,j) = GREEN; //write that one pixel to green
          std::cout<< "Solution found";
          return EXIT_SUCCESS;
        }
        else
        {
          s = input(i,j); //case of solution not equal to goal
        }
      }
    }
  }

  Deque<Pixel> frontier; //will hold all non-explored pixels
  frontier.pushBack(s); //push the starting state onto queue

  Deque<Pixel> explored; //will keep track of which pixels have been explored

  while(1)
  {
    if(frontier.isEmpty())
    {
      std::cout << "No Soultion Found";
      return EXIT_FAILURE;
    }

    s = frontier.back(); //set s equal to the front of the queue
    frontier.popBack(); //pop the back of the queue

    explored.pushBack(s); //add s to explored

  }

}

