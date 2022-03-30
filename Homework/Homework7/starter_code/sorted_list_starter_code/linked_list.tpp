#include "linked_list.hpp"

//ALL FUNCTIONS GIVEN IN THE HOMEWORK DESCRIPTION ON CANVAS

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
  currentSize = x.currentSize; //copies current size
  Node<T>* origPtr = x.headPtr; //copies headPtr

  if(origPtr == nullptr)
  {
    headPtr = nullptr; //original bag is empty
  }
  else
  {
    headPtr = new Node<T>(); //creates a new empty node
    headPtr->setItem(origPtr->getItem()); //copies value of head pointer

    Node<T>* newPtr = headPtr;
    origPtr = origPtr->getNext();
    while(origPtr != nullptr)
    {
      T nextItem = origPtr->getItem(); //gets item from origPtr
      Node<T>* newNodePtr = new Node<T>(nextItem); //creates a new node with the nextItem variable value
      newPtr->setNext(newPtr); //link to end of chain

      newPtr = newPtr->getNext();
      origPtr = origPtr->getNext();
    }
  }
}

template <typename T>
void LinkedList<T>::swap(LinkedList<T>& x, LinkedList<T>& y)
{
  LinkedList<T> temp(x); //sets a temp varaible equal to x
  x = y; //uses the = operator function to swap the lists
  y = temp; 
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& x)
{
  currentSize = x.currentSize;
  Node<T>* origPtr = x.headPtr;
  
  if (origPtr == nullptr)
  {
    headPtr = nullptr; 
  }
  else 
  {
    //make copy of first node
    headPtr = new Node<T>();
    headPtr -> setItem(origPtr -> getItem());
    //copy remaining nodes
    Node<T>* newPtr = headPtr; 
    origPtr = origPtr -> getNext();
    while (origPtr != nullptr) 
    {
      //get next item in list, and make new node with item, and link
      T nextItem = origPtr -> getItem();
      Node<T>* newNodePtr = new Node<T>(nextItem);
      newPtr -> setNext(newNodePtr);
      //shift pointers
      newPtr = newPtr -> getNext();
      origPtr = origPtr -> getNext();
    }
  } 
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
  bool canInsert = (position >= 1) && (position <= currentSize +1);
  Node<T>* prevPtr = getNodeAt(position - 1);
      
  bool isValid;
  if (position+1 <= currentSize) 
  {
    Node<T>* postPtr = getNodeAt(position + 1);
    if (position-1 >= 1 ) 
    {
      isValid = (prevPtr -> getItem() < item) && (postPtr -> getItem() > item); 
    } 
    else 
    { 
      isValid = (postPtr -> getItem()) > item; 
    } // end if
  } // end if
  else
  {
    isValid = true;
  }
           
  if (canInsert) 
  {
    //new node with entry
    Node<T>* newNodePtr = new Node<T>(item);
    //Link new node to list
    if (position == 1) 
    {
      //put node at beginning of the chain is position is 1
      newNodePtr -> setNext(headPtr);
      headPtr = newNodePtr;
    }
    else 
    {
      //put node after the node at position - 1
      newNodePtr -> setNext( prevPtr -> getNext() );
      prevPtr -> setNext( newNodePtr );
    } //end if
    //increment count
    currentSize++;
    } 
    else 
    {
      throw(std::range_error("error in range"));
  } //end if
  return canInsert; 
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
  }
}

template <typename T>
T LinkedList<T>::getEntry(std::size_t position) const
{
  Node<T>* nodePtr = headPtr; //creates a pointer that will traverse the list

  if(position >= 1 && position <= currentSize+1)
  {
    for(int i = 1; i < position; i++)
    {
      nodePtr = nodePtr->getNext(); //traverses the list
    }
    return nodePtr->getItem(); //returns the current item
  }
  else
  {
    throw(std::range_error("error in range")); //throw an error
  }
}

template <typename T>
void LinkedList<T>::setEntry(std::size_t position, const T& newValue)
{
  Node<T>* nodePtr = headPtr; //creates a pointer that will traverse the list

  if(position >= 1 && position <= currentSize+1)
  {
    for(int i = 1; i < position; i++)
    {
      nodePtr = nodePtr->getNext(); //traverses the list
    }
    nodePtr->setItem(newValue); //sets the current node with the new Item
  }
}

template <typename T>
Node<T>* LinkedList<T>::getNodeAt(int position) const //this is a helper function provided to me
{
  Node<T>* curPtr = headPtr;
  for (std::size_t next = 1; next < position; next++)
    curPtr = curPtr -> getNext();
  return curPtr;
} //end getNodeAt
