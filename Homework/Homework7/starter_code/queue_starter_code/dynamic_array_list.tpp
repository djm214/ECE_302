#include "dynamic_array_list.h"

#include <algorithm>
#include <stdexcept>

#include <iostream>

template <typename T>
DynamicArrayList<T>::DynamicArrayList()
{
  size = 0; //size of the current array
  capacity = 2; //sets the initial capacity

  data = new T[capacity]; //allocates enough memory for an array of capacity
}
  
template <typename T>
DynamicArrayList<T>::DynamicArrayList(const DynamicArrayList<T>& x)
{
  size = x.size;
  capacity = x.capacity; //copy size and capacity

  data = new T[capacity]; //allocate an array of size capacity

  for(int i = 0; i < size; i++)
  {
    data[i] = x.data[i]; //copies values from x into main
  }
}
    
template <typename T>
DynamicArrayList<T>::~DynamicArrayList()
{
  std::clog << "DynamicArrayList Destructor called." << std::endl;
  clear(); //call clear function
}

template <typename T>
DynamicArrayList<T>& DynamicArrayList<T>::operator=(DynamicArrayList<T> x)
{
  size = x.size;
  capacity = x.capacity; //copy size and capacity

  data = new T[capacity]; //allocate an array of size capacity

  for(int i = 0; i < size; i++)
  {
    data[i] = x.data[i]; //copies values from x into main
  }
  return *this;
}

template <typename T>
void DynamicArrayList<T>::swap(DynamicArrayList<T>& y)
{
  DynamicArrayList<T> temp(y);//create a copy of the passed in variable

  y.size = size;
  y.capacity = capacity; //copy over size and capacity

  delete [] y.data; //de-allocate previous data allocation for y

  y.data = new T[y.capacity]; //new allocation

  for(int i = 0; i < y.size; i++)
  {
    y.data[i] = data[i]; //copies over data items
  } //end y swap
  //begin current swap

  size = temp.size;
  capacity = temp.capacity; //copy over size and capacity

  delete [] data; //de-allocate data memory

  data = new T[capacity]; //new allocation

  for(int i = 0; i < size; i++)
  {
    data[i] = temp.data[i]; //copies over data
  } //end swap
}

template <typename T>
bool DynamicArrayList<T>::isEmpty()
{
  return (size == 0); //if size is 0, return true
}

template <typename T>
std::size_t DynamicArrayList<T>::getLength()
{
  return size;
}

template <typename T>
void DynamicArrayList<T>::insert(std::size_t position, const T& item)
{
  if(position >= capacity)
  {
    T* temp = new T[capacity*2]; //doubles capacity

    for(int i = 0; i < capacity; i++)
    {
      temp[i] = data[i]; //copies all data to temp
    }

    temp[position] = item; //the index position set to item
    delete [] data; //de-allocate data variable

    data = temp; //set data equal to temp
    size++; //increase size
  }
  else
  {
    data[position] = item; //set index position to item
    size++; //increase size of data
  }
}

template <typename T>
void DynamicArrayList<T>::remove(std::size_t position)
{
  if(position < capacity)
  {
    for(int i = position; i <= size; i++)
    {
      data[i] = data[i + 1]; //skips only the item at position
    }
    size--;
  }
}

template <typename T>
void DynamicArrayList<T>::clear()
{
  delete [] data; //de-allocates data
  size = 0;
  capacity = 2; //reset to default values
}

template <typename T>
T DynamicArrayList<T>::getEntry(std::size_t position)
{
  if(position < capacity)
  {
    return data[position]; //return item at position
  }
  else
  {
    throw(std::range_error("error in range"));
  }
}

template <typename T>
void DynamicArrayList<T>::setEntry(std::size_t position, const T& newValue)
{
  if(position < size)
  {
    data[position] = newValue; //return item at position
  }
  else
  {
    T* temp = new T[capacity*2]; //doubles capacity

    for(int i = 0; i < capacity; i++)
    {
      temp[i] = data[i]; //copies all data to temp
    }

    temp[position] = newValue; //the index position set to item
    delete [] data; //de-allocate data variable

    data = temp; //set data equal to temp
    size++; //increase size
  }
}
