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
    if(front != (queueLength - 1))
    {
      front = (front + 1) % queueLength;
      data[queueLength - front] = item; //have to invert fro front
      ++count; //increases total count
      return true;
    }
    else //in this case, modulation originally gives a wrong answer
    {
      front = (front + 1) % queueLength;
      data[front] = item;
      ++count; //increases total count
      return true;
    }
    
  }
  return false; //enqueue front fails
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
