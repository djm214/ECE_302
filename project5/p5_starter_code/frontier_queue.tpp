#include "frontier_queue.hpp"

// TODO implement the member functions here

template <typename T>
State<T> frontier_queue<T>::pop() 
{
  //This works, however, it doesn't have O(log n)
  /*
  std::vector<State<T>> temp;
  temp.push_back(queue[0]);

  queue.erase(queue.begin());
  return temp[0]; //return the front of the queue
  */

  std::vector<State<T>> temp;
  
  temp.push_back(queue[0]); //hold the original root
  queue[0] = queue[queue.size()-1]; //set root to last
  queue.pop_back(); //remove last node

  int replaced = 0;
  bool correctSpot = false;

  while(!correctSpot && (replaced+1) < queue.size())
  {
    if(queue[replaced+1].getFCost() >= queue[replaced].getFCost())
    {
      correctSpot = true; //this is where pop should be
    }
    else
    {
      temp.push_back(queue[replaced]); //pushback the raplaced

      //swapping
      queue[replaced] = queue[replaced+1]; 
      queue[replaced+1] = temp[1]; //get the second element as the first holds the original root

      temp.pop_back(); //remove the last element
      replaced++; //traverse replaced
    }
  }
  return temp[0];
}

template <typename T>
void frontier_queue<T>::push(const T &p, std::size_t cost, std::size_t heur) 
{
  queue.push_back(State<T>(p,cost,heur)); //add the state to the end of the queue

  std::vector<State<T>> temp;
  int parentIndex;
  int insertionIndex = queue.size()-1; //holds the end of the queue
  bool rightSpot = false; //initialize bool to false

  while(!rightSpot && (insertionIndex >= 0))
  {
    parentIndex = (insertionIndex)/2;
    if(queue[insertionIndex].getFCost() >= queue[parentIndex].getFCost())
    {
      rightSpot = true;
    }
    else //bubble up process
    {
      temp.push_back(queue[parentIndex]);

      //swapping process
      queue[parentIndex] = queue[insertionIndex];
      queue[insertionIndex] = temp[0];

      //remove the temp vector
      temp.pop_back();
      insertionIndex = parentIndex;
    }
  }
}

template <typename T>
bool frontier_queue<T>::empty() 
{
  return (queue.size() == 0); //return true if the queue is empty
}

template <typename T> 
bool frontier_queue<T>::contains(const T &p) 
{
  for(int i = 0; i < queue.size(); i++)
  {
    if(p == queue[i].getValue())
    {
      return true; //return true if there is a match
    }
  }
  return false; //return false if there is no match
}

template <typename T>
void frontier_queue<T>::replaceif(const T &p, std::size_t cost) 
{
  //traverse the list
  for(int i = 0; i < queue.size(); i++)
  {
    //if the value is found
    if(p == queue[i].getValue())
    {
      //if the cost parameter is less than the cost of the variable in the list's cost
      if(cost < queue[i].getFCost())
      {
        queue[i].updatePathCost(cost); //replace if cost < queue value cost
      }
    }
  }
}


