#include <iostream>
#include <vector>
#include "image.h"
#include "deque.hpp"

struct Vertex
{
  int row;
  int column; //will hold the rows/column values
};

bool BFS(Vertex,Image<Pixel>&);

int main(int argc, char *argv[])
{
  Image<Pixel> input = readFromFile(argv[1]); //reads in the image
  bool success = false; //will determine if BFS failed or succeeded
  bool startingPixelFound = false; //will be used to tell if a red pixel has been read in
  Vertex start; //will hold starting vertex

  //scan the png to find a red pixel
  for(int i = 0; i < input.width();i++)
  {
    for(int j = 0; j < input.height();j++)
    {
      if(input(i,j) == RED && !startingPixelFound)
      {
        start.row = i; //store i and j into the start vertex
        start.column = j;
        startingPixelFound = true; //found one red pixel
      }
      else if(input(i,j) == RED && startingPixelFound)
      {
        //fails if there is another red pixel
        std::cout << "There can only be one RED pixel per image\n";
        return EXIT_FAILURE;
      }

      if(input(i,j) != RED && input(i,j) != WHITE && input(i,j) != BLACK)
      {
        //fails if there is a pixel that is not of red,green,or black
        std::cout << "Only pixels of color red, green, or black allowed\n";
        return EXIT_FAILURE;
      }
    }
  }

  //call Breadth-Field Search
  success = BFS(start,input);

  if(success == false)
  {
    //if breadth for Search fails...
    std::cout << "Solution Not Found\n";
    return EXIT_FAILURE;
  }
  
  writeToFile(input,argv[2]); //write to file if success == true
}

//functions
bool BFS(Vertex start,Image<Pixel>&input)
{
  bool explored[input.width()][input.height()]; //will hold all pixels that have been explored
  
  Deque<Vertex> frontier; //a queue to hold pixels that can be explored
  frontier.pushBack(start); //add the starting vertex to the queue

  explored[start.row][start.column] = true; //set it's explored value to true

  Vertex traversal; //a vertex that will be used below
  while(!frontier.isEmpty())
  {
    traversal = frontier.front(); //set traversal to the front of the queue
    frontier.popFront(); //remove the front of the queue

    int r = traversal.row; 
    int c = traversal.column; //keep track of the rows/columns in variables r/c

    //check for solution
    if(r == 0 || r == input.width()-1 || c == 0 || c == input.height()-1)
    {
      input(r,c) = GREEN; //set pixel to green
      std::cout << "Solution Found\n";
      return true;
    }

    if(input(r-1,c)==WHITE && !explored[r-1][c])
    {
      Vertex temp;
      temp.row = r-1;
      temp.column = c;

      frontier.pushBack(temp); //pushback new vertex
      explored[r-1][c] = true; //set it to explored
    }
    if(input(r+1,c)==WHITE && !explored[r+1][c])
    {
      Vertex temp;
      temp.row = r+1;
      temp.column = c;

      frontier.pushBack(temp); //pushback new vertex
      explored[r+1][c] = true; //set it to explored
    }
    if(input(r,c-1)==WHITE && !explored[r][c-1])
    {
      Vertex temp;
      temp.row = r;
      temp.column = c-1;

      frontier.pushBack(temp); //pushback new vertex
      explored[r][c-1] = true; //set it to explored
    }
    if(input(r,c+1)==WHITE && !explored[r][c+1])
    {
      Vertex temp;
      temp.row = r;
      temp.column = c+1;

      frontier.pushBack(temp); //pushback new vertex
      explored[r][c+1] = true; //set it to explored
    }
  }
  return false; //return false if the function makes it here
}