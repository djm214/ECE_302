#include "deque.hpp"

template <typename T>
Deque<T>::Deque()
{
  obj = new LinkedList<T>; //allocate memory for the object
}

template <typename T>
Deque<T>::~Deque()
{
  obj->clear(); //clears the list
}

template <typename T>
bool Deque<T>::isEmpty() const noexcept
{
  return obj->isEmpty(); //returns isEmpty bool from linked list
}

template <typename T>
void Deque<T>::pushFront(const T & item)
{
  obj->insert(1,item); //inserts item at the front of the list
}

template <typename T>
void Deque<T>::popFront()
{
  if(isEmpty())
  {
    throw(std::runtime_error("deque is empty")); //throw a runtime error if the deque is empty
  }
  obj->remove(1); //removes item at the front of the list
}

template <typename T>
T Deque<T>::front() const
{
  if(isEmpty())
  {
    throw(std::runtime_error("deque is empty")); //throw a runtime error if the deque is empty
  }
  return obj->getEntry(1); //return the first item
}

template <typename T>
void Deque<T>::pushBack(const T & item)
{
  obj->insert(obj->getLength(),item); //inserts item at the back of the list
}

template <typename T>
void Deque<T>::popBack()
{
  if(isEmpty())
  {
    throw(std::runtime_error("deque is empty")); //throw a runtime error if the deque is empty
  }
  obj->remove(obj->getLength()); //removes item at the back of the list
}

template <typename T>
T Deque<T>::back() const
{
  if(isEmpty())
  {
    throw(std::runtime_error("deque is empty")); //throw a runtime error if the deque is empty
  }
  return obj->getEntry(obj->getLength()); //return the last item
}