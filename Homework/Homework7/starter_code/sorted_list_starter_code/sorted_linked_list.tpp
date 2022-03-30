#include "sorted_linked_list.hpp"
#include <stdexcept>

template <typename T>
SortedLinkedList<T>::SortedLinkedList(): LinkedList<T>()
{
}

template <typename T>
SortedLinkedList<T>::SortedLinkedList(const SortedLinkedList<T> & x):
  LinkedList<T>(x)
{
}

template <typename T>
SortedLinkedList<T>& SortedLinkedList<T>::operator=(const SortedLinkedList<T>& x)
{
  LinkedList<T>::operator=(x);
  return *this;
}

template <typename T>
SortedLinkedList<T>::~SortedLinkedList()
{
  // base destructor gets called automatically
}

template <typename T>
bool SortedLinkedList<T>::isEmpty()
{
  return LinkedList<T>::isEmpty();
}

template <typename T>
std::size_t SortedLinkedList<T>::getLength()
{
  return LinkedList<T>::getLength();
}

template <typename T>
void SortedLinkedList<T>::insert(const T& item)
{
  int index = 0;
  if(getLength() == 0)
  {
    LinkedList<T>::insert(1,item); //insert the item into the first position
  }
  else
  {
    for(int i = 1; i < getLength(); i++)
    {
      index = i; //keep updating 
      if(getEntry(i-1) >= item && i != getLength() -1)
      {
        continue; //break out of the loop
      }
      else if(i == getLength() -1)
      {
        break;
      }
    }
    LinkedList<T>::insert(index+2,item); //insert the item
  }
}

template <typename T>
void SortedLinkedList<T>::remove(const T& item)
{
  if(isEmpty()) throw std::range_error("empty list in remove");
  int prevIndex = 0; //will hold the previous node index
  
  for(int i = 0; i < getLength(); i++)
  {
    if(getEntry(i) == item)
    {
      break; //break from the for loop
    }
    else
    {
      prevIndex = i; //set the index variable
    }
  }

  if(getEntry(prevIndex+1) != item)
  {
    throw std::logic_error("item not found in list"); //thow an error if item prev index is incorrect
  }

  LinkedList<T>::remove(prevIndex + 2); //remove the item
  
}

template <typename T>
void SortedLinkedList<T>::removeAt(std::size_t position)
{
  if(isEmpty()) throw std::range_error("empty list in removeAt");
  
  LinkedList<T>::remove(position + 1); //assuming this is 1 based and my linked list was 0 based
}

template <typename T>
void SortedLinkedList<T>::clear()
{
  LinkedList<T>::clear();
}

template <typename T>
T SortedLinkedList<T>::getEntry(std::size_t position)
{
  return LinkedList<T>::getEntry(position+1);
}

template <typename T>
long int SortedLinkedList<T>::getPosition(const T& newValue)
{
  int index = 0; //an index variable

  for(int i = 0; i < getLength(); i++)
  {
    if(getEntry(i) == newValue) //first instance of newValue
    {
      index = i;
      return index+1; //add 1 for 1 based indexing
    }
    else if(getEntry(i) > newValue) //where the value should be inserted
    {
      index = i;
      return index; //should be correct based off of 1 based indexing
    }
  }
}
