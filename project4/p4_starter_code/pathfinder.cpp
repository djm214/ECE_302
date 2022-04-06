#include <iostream>
#include <vector>
#include "image.h"
#include "deque.hpp"

struct Vertex
{
  Pixel p; //will contain a pixel
  int row;
  int column; //will hold the rows/column values
};

bool isExplored(Vertex,std::vector<Vertex>);

int main(int argc, char *argv[])
{
  Image<Pixel> input = readFromFile(argv[1]); //reads in the image
  Vertex s; //will hold the starting position

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
          s.p = input(i,j); //case of solution not equal to goal
          s.row = i;
          s.column = j; //holds coordinates for row/column
        }
      }
    }
  }

  Deque<Vertex> frontier; //will hold all non-explored pixels
  frontier.pushBack(s); //push the starting state onto queue

  std::vector<Vertex> explored; //will keep track of which pixels have been explored

  while(!frontier.isEmpty()) //while the fronteir isn't empty
  {
    std::cout << "top of loop\n";
    s = frontier.front(); //set s equal to the front of the queue
    frontier.popFront(); //pop the back of the queue

    int r = s.row;
    int c = s.column;
    Vertex intermediate; //will be used shortly to push onto queue

    if(r == 0 || c == 0 || r == input.width()-1 || c == input.height()-1)
    {
      input(r,c) = GREEN; //color green
      writeToFile(input,argv[2]);
      std::cout << "Solution Found";
      return EXIT_SUCCESS;
    }

    explored.push_back(s); //add s to explored

    if(input(r-1,c) == WHITE)
    {
      intermediate.p = input(r-1,c); //use intermediate in order to push the different row/column vals
      intermediate.row = r-1;
      intermediate.column = c;
      
      if(!isExplored(intermediate,explored))
      {
        std::cout << "added down\n";
        frontier.pushBack(intermediate); //if the vertex wasn't explored before, add it to frontier
      }
    }
    if(input(r+1,c) == WHITE)
    {
      intermediate.p = input(r+1,c); //use intermediate in order to push the different row/column vals
      intermediate.row = r+1;
      intermediate.column = c;
      
      if(!isExplored(intermediate,explored))
      {
        std::cout<< "added up\n";
        frontier.pushBack(intermediate); //if the vertex wasn't explored before, add it to frontier
      }
    }
    if(input(r,c-1) == WHITE)
    {
      intermediate.p = input(r-1,c); //use intermediate in order to push the different row/column vals
      intermediate.row = r;
      intermediate.column = c-1;
      
      if(!isExplored(intermediate,explored))
      {
        std::cout<<"added left\n";
        frontier.pushBack(intermediate); //if the vertex wasn't explored before, add it to frontier
      }
    }
    if(input(r,c+1) == WHITE)
    {
      intermediate.p = input(r-1,c); //use intermediate in order to push the different row/column vals
      intermediate.row = r;
      intermediate.column = c+1;

      if(!isExplored(intermediate,explored))
      {
        std::cout << "added right\n";
        frontier.pushBack(intermediate); //if the vertex wasn't explored before, add it to frontier
      }
    }
  }

  std::cout << "No Soultion Found"; //if the frotier becomes empty, ther is no soln
  return EXIT_FAILURE; //exit with failure

}

//functions
bool isExplored(Vertex TBS,std::vector<Vertex> exp)
{
  Vertex tester;
  for(int i = 0; i < exp.size(); i++)
  {
    Vertex tester;
    tester.p = exp[i].p;
    tester.row = exp[i].row;
    tester.column = exp[i].column; //copies all values into a tester vertex
    if((tester.row == TBS.row) && (tester.column == TBS.column))
    {
      return true; //return true if the pixel has already been explore
    }
  }
  return false; //return false if the pixel has yet to be explored
}