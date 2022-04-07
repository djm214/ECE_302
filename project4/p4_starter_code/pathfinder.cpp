#include <iostream>
#include <vector>
#include "image.h"
#include "deque.hpp"

struct Vertex
{
  int row;
  int column; //will hold the rows/column values
};

Vertex getStartingPosition(Image<Pixel>);
bool isExplored(int,int,std::vector<Vertex>);
bool BFS(Vertex,Image<Pixel>&);

int main(int argc, char *argv[])
{
  Image<Pixel> input = readFromFile(argv[1]); //reads in the image
  Vertex s; //will hold the starting position
  bool success = false;

  //hold starting position in s
  s = getStartingPosition(input);

  //call Breadth-Field Search
  success = BFS(s,input);

  if(success == false)
  {
    std::cout << "Solution Not Found";
    return EXIT_FAILURE;
  }
  
  writeToFile(input,argv[2]);
}

//functions
bool isExplored(int row, int column,std::vector<Vertex> exp)
{
  int tester_r,tester_c;
  for(int i = 0; i < exp.size(); i++)
  {
    tester_r = exp[i].row;
    tester_c = exp[i].column; //copies all values into a tester vertex

    if((tester_r == row) && (tester_c == column))
    {
      return true; //return true if the pixel has already been explored
    }
  }
  return false; //return false if the pixel has yet to be explored
}

Vertex getStartingPosition(Image<Pixel> image)
{
  Vertex start; //starting vertex has i&j rows&columns

  for(int i = 0; i < image.width();i++)
  {
    for(int j = 0; j < image.height();j++)
    {
      if(image(i,j) == RED)
      {
        start.row = i;
        start.column = j;
      }
    }
  }

  return start;
}

bool BFS(Vertex start,Image<Pixel>&input)
{
  bool explored[input.width()][input.height()]; //will hold all pixels that have been explored
  
  Deque<Vertex> frontier;
  frontier.pushBack(start);

  explored[start.row][start.column] = true;

  Vertex traversal;
  while(!frontier.isEmpty())
  {
    traversal = frontier.front();
    frontier.popFront();

    int r = traversal.row;
    int c = traversal.column;

    if(r == 0 || r == input.width()-1 || c == 0 || c == input.height()-1)
    {
      input(r,c) = GREEN; //set pixel to green
      std::cout << "Solution Found";
      return true;
    }

    if(input(r-1,c)==WHITE && !explored[r-1][c])
    {
      Vertex temp;
      temp.row = r-1;
      temp.column = c;

      frontier.pushBack(temp);
      explored[r-1][c] = true;
    }
    if(input(r+1,c)==WHITE && !explored[r+1][c])
    {
      Vertex temp;
      temp.row = r+1;
      temp.column = c;

      frontier.pushBack(temp);
      explored[r+1][c] = true;
    }
    if(input(r,c-1)==WHITE && !explored[r][c-1])
    {
      Vertex temp;
      temp.row = r;
      temp.column = c-1;

      frontier.pushBack(temp);
      explored[r][c-1] = true;
    }
    if(input(r,c+1)==WHITE && !explored[r][c+1])
    {
      Vertex temp;
      temp.row = r;
      temp.column = c+1;

      frontier.pushBack(temp);
      explored[r][c+1] = true;
    }
  }
  return false;
}