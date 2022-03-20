#include "ring_buffer.h"

#include <cassert>

template <typename T>
RingBuffer<T>::RingBuffer(std::size_t size)
{
  queueLength = size;
  data.reset(new T[queueLength]);
  front = 0;
  back = queueLength-1;
  count = 0;
}


template <typename T>
bool RingBuffer<T>::enqueue_front(const T& item)
{
  if(count != queueLength)
  {
    if(front == 0)
    {
      std::unique_ptr<T[]> temp;
      temp.reset(new T[queueLength]); //creates a temp array

      for(int i = 0; i < queueLength; i++)
      {
        temp[i] = data[i]; //copy data data into temp
      }
      for(int i = 0; i < queueLength; i++)
      {
        temp[i+1] = temp[i]; //shift elements of temp over by 1
      }

      temp[0] = item; //temp variable now holds the correct item at the front

      for(int i = 0; i < queueLength; i++)
      {
        data[i] = temp[i]; //copy into temp
      }

      ++count; //increase total count
      back++; //increase back
      return true;
    }
    else
    {
      front = (front - 1) % queueLength;
      data[front] = item;
      ++count;
      return true;
    }
  }
  else
  {
    return false; //fail
  }
}


template <typename T>
bool RingBuffer<T>::enqueue_back(const T& item)
{
  if(count != queueLength){
    back = (back + 1) % queueLength;
    data[back] = item;
    ++count;
    return true;
  }
  
  return false;
}

template <typename T>
T RingBuffer<T>::dequeue_front()
{
  assert(count > 0);
  
  T value;
  
  value = data[front];
  front = (front +1) % queueLength;
  --count;
  
  return value;
}


template <typename T>
T RingBuffer<T>::dequeue_back()
{
  assert(count > 0); //ensure that the count is non-zero
  
  T value; //create a T variable to return later
  
  value = data[back]; //hold the value at the back
  back = (back - 1) % queueLength; //decrease back

  --count; //decrement count
  return value; //return the value
}


template <typename T>
long int RingBuffer<T>::getCount()
{
  return count;
}
