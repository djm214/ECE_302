#include "linked_list.hpp"

template <typename T>
LinkedList<T>::LinkedList()
{
  headPtr = nullptr; //initializes the headPtr to null
	currentSize = 0; //sets the current size of the list to zero
}

template <typename T>
LinkedList<T>::~LinkedList()
{
  clear(); //clears the list
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& x)
{
}

template <typename T>
void LinkedList<T>::swap(LinkedList<T>& x, LinkedList<T>& y)
{
  //TODO
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& x)
{
  //TODO
  return *this;
}

template <typename T>
bool LinkedList<T>::isEmpty() const
{
  if(currentSize == 0)
	{
		return true; //if the currentSize variable is zero, then the list is empty
	}
	return false; //returns false for any value other than zero
}

template <typename T>
std::size_t LinkedList<T>::getLength() const
{
  return currentSize; //returns the current size variable
}

template <typename T>
bool LinkedList<T>::insert(std::size_t position, const T& item)
{
  if(position != 0 && position <= (currentSize + 1))
  {
    Node<T>* newNodePtr = new Node<T>(item); //creates a pointer that will traverse the list

    if(position == 1)
    {
      newNodePtr->setNext(headPtr); //if the position of insert is 1, setNext as headPtr
      headPtr = newNodePtr; //make the new headPtr the newNodePtr
    }
    else
    {
      Node<T>* prevPtr = headPtr; //this pointer will traverse the list to position-1
      for(int i = 0; i < (position-1); i++)
      {
        prevPtr = prevPtr->getNext(); //traverses the list
      }

      newNodePtr->setNext(prevPtr->getNext());
      prevPtr->setNext(newNodePtr);
    }
    currentSize++; //increments the current size of the list
    return true; //success
  }
  else
  {
    return false; //the insert fails
  }
}

template <typename T>
bool LinkedList<T>::remove(std::size_t position)
{
  if(position >= 1 && (position <= currentSize))
  {
    Node<T>* curPtr = nullptr;
    if(currentSize == 1)
    {
      curPtr = headPtr; //copies the headptr to a new pointer
      headPtr = headPtr->getNext(); //sets head pointer to the next node
    }
    else
    {
      Node<T>* prevPtr = headPtr;
      for(int i = 0; i < (position-1); i++)
      {
        prevPtr = prevPtr->getNext(); //traverses the list
      }

      curPtr = prevPtr->getNext();
      prevPtr->setNext(curPtr->getNext()); //move the next pointer over by 1
    }

    curPtr->setNext(nullptr); 
    delete curPtr;
    curPtr = nullptr; //these steps remove the node
  
    currentSize--; //decrease the total size
    return true;
  }
  else
  {
    return false; //remove fails
  }
}

template <typename T>
void LinkedList<T>::clear()
{
  while(!isEmpty())
  {
    remove(1); //remove the element at position i
    currentSize--;
  }
}

template <typename T>
T LinkedList<T>::getEntry(std::size_t position) const
{
  Node<T>* nodePtr = headPtr; //creates a pointer that will traverse the list

  if(position != 0 && position <= currentSize)
  {
    for(int i = 0; i < position; i++)
    {
      nodePtr = nodePtr->getNext(); //traverses the list
    }
    return nodePtr->getItem(); //returns the current item
  }
}

template <typename T>
void LinkedList<T>::setEntry(std::size_t position, const T& newValue)
{
  Node<T>* nodePtr = headPtr; //creates a pointer that will traverse the list

  if(position != 0 && position <= currentSize)
  {
    for(int i = 0; i < position; i++)
    {
      nodePtr = nodePtr->getNext(); //traverses the list
    }
    nodePtr->setItem(newValue); //sets the current node with the new Item
  }
}
