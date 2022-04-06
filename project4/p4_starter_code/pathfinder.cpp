#include <iostream>
#include <vector>
#include "image.h"
#include "deque.hpp"

bool isExplored(Pixel,std::vector<Pixel>);

int main(int argc, char *argv[])
{
  Image<Pixel> input = readFromFile(argv[1]); //reads in the image
  Image<Pixel> output = readFromFile(argv[2]); //what soln wil be written to
  Pixel s; //will hold the starting position
  int r,c;

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
          r = i;
          c = j; //will keep track of the position [Pixel at (r,c)]
        }
      }
    }
  }

  Deque<Pixel> frontier; //will hold all non-explored pixels
  frontier.pushBack(s); //push the starting state onto queue

  std::vector<Pixel> explored; //will keep track of which pixels have been explored

  while(!frontier.isEmpty()) //while the fronteir isn't empty
  {
    s = frontier.front(); //set s equal to the front of the queue
    frontier.popFront(); //pop the back of the queue

    explored.push_back(s); //add s to explored

    if(input(r-1,c) == WHITE && !isExplored(input(r-1,c),explored))
    {
      frontier.pushBack(input(r-1,c));
      r--; //update row value
    }
    if(input(r+1,c) == WHITE && !isExplored(input(r-1,c),explored))
    {
      frontier.pushBack(input(r-1,c));
      r++; //update row value
    }
    if(input(r,c-1) == WHITE && !isExplored(input(r-1,c),explored))
    {
      frontier.pushBack(input(r-1,c));
      c--; //update row value
    }
    if(input(r,c+1) == WHITE && !isExplored(input(r-1,c),explored))
    {
      frontier.pushBack(input(r-1,c));
      c++; //update row value
    }
  }

}

//functions
bool isExplored(Pixel TBS,std::vector<Pixel> exp)
{
  for(int i = 0; i < exp.size(); i++)
  {
    if(exp[i] == TBS)
    {
      return true; //return true if the pixel has already been explore
    }
  }
  return false; //return false if the pixel has yet to be explored
}