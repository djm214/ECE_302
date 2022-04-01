#include "linked_list.hpp"

template <typename T>
Node<T>* LinkedList<T>::getNodeAt(int position) const
{
  Node<T>* curPtr = headptr; //copy the headptr to bea able to traverse the list
  for(int i = 1; i < position; i++)
  {
    curPtr = curPtr->getNext();
  }

  return curPtr;//will return the node that is at the 1 indexed position
}

template <typename T>
LinkedList<T>::LinkedList()
{
  headptr = nullptr; //set headptr to null ptr initially
  size = 0; //list is initially empty
}

template <typename T>
LinkedList<T>::~LinkedList()
{
  clear(); //call the clear function to remove everything from the list
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& x)
{
  size = x.size; //copy the size variable from x obj
  Node<T>* origPtr = x.headptr; //holds the headptr of x obj

  if(size == 0)
  {
    headptr = nullptr; //only happens if the list is empty
  }
  else
  {
    headptr = new Node<T>(); //allocate memory for a new node obj
    headptr->setItem(origPtr->getItem()); //copy the first node

    Node<T>* standIn = headptr; //create a stand in pointer to copy the rest of the list
    origPtr = origPtr->getNext(); //re-evaluate to progress down the list

    while(origPtr != nullptr) //while not at the end of the list
    {
      T next = origPtr->getItem(); //hold next value in a variable
      Node<T>* standIn = new Node<T>(next); //add node with designated value

      standIn = standIn->getNext(); //progress through list by 1
      origPtr = origPtr->getNext(); //progress down the list by 1
    }
  }
}

template <typename T>
void LinkedList<T>::swap(LinkedList<T>& x, LinkedList<T>& y)
{
  LinkedList<T> intermediate(x); //create an intermediate obj with copy constructor
  x = y; //use of operator overload function to set objs equal
  y = intermediate;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& x)
{
  size = x.size; //copies the size variable
  Node<T>* origPtr = x.headptr; //copies the headptr variable
  
  if(size == 0)
  {
    headptr = nullptr;
  }
  else
  {
    //copy first
    headptr = new Node<T>(); //allocate memory for new Node obj
    headptr ->setItem(origPtr->getItem()); //copy value of x obj node to this node

    //copy rest
    Node<T>* standIn = headptr;
    origPtr = origPtr->getNext(); //progress origptr by one position

    while(origPtr != nullptr)
    {
      T next = origPtr->getItem(); //stores the value of the next node in next variable
      standIn->setNext(next); //set the next node in the list to have a value of next

      standIn = standIn->getNext();
      origPtr = origPtr->getNext(); //progresses the two lsits by a position of 1
    }
  }
  return *this;
}

template <typename T>
bool LinkedList<T>::isEmpty() const
{
  if(size == 0)
  {
    return true; //if size is zero, list is empty
  }
  else
  {
    return false;
  }
  
}

template <typename T>
std::size_t LinkedList<T>::getLength() const
{
  return size; //size keeps track of length
}

template <typename T>
bool LinkedList<T>::insert(std::size_t position, const T& item)
{
  bool validityTest;
  bool ableToAdd = (position >= 1) && (position <= (size+1));
  Node<T>* previous = getNodeAt(position-1); //get the node before the node that should come after node to be inserted

  if(position+1 <= size)
  {
    Node<T>* next = getNodeAt(position + 1); //hold the node that will come after inseted node
    if(position-1 >= 1)
    {
      validityTest = (previous->getItem() < item) && (next->getItem() > item);
    }
    else
    {
      validityTest = (next->getItem() > item);
    }
  }
  else
  {
    validityTest = true;
  }

  if(ableToAdd)
  {
    Node<T>* standIn = new Node<T>(item); //create new Node with value equal to ite entry
    if(position == 1) //case of insertaion at the beginning
    {
      standIn->setNext(headptr); //first node should now come after node to be inserted
      headptr = standIn; //headptr should now point to the node that was inserted
    }
    else
    {
      standIn->setNext(previous->getNext()); //inserted node now points to the node previous WAS pointing to
      previous->setNext(standIn); //previous now points to inserted node
    }
    size++;//increment size
  }
  else
  {
    throw(std::range_error("error in insert range")); //if there was an error in the function throw a range error
  }
  return ableToAdd;
}

template <typename T>
bool LinkedList<T>::remove(std::size_t position)
{
  bool ableToRemove = (position >= 1) && (position <= size);
  if(ableToRemove)
  {
    Node<T>* curPtr = headptr; //copy the headptr to be able to traverse the list

    if(position == 1) //case of removal at first position
    {
      curPtr = headptr;
      headptr = headptr->getNext(); //make headptr point to the next node
    }
    else
    {
      Node<T>* previous = getNodeAt(position-1); //get previous node
      curPtr = previous->getNext(); //holds the node to be removed
      previous->setNext(curPtr->getNext()); //previous now points to the node after curPtr
    }
    //delete the memory for pointer to be removed
    curPtr -> setNext(nullptr);
    delete curPtr;
    curPtr = nullptr;
    size--;
  }
  else
  {
    throw(std::range_error("error in range for remove"));
  }
  return ableToRemove;
}

template <typename T>
void LinkedList<T>::clear()
{
  while(size != 0)
  {
    remove(1); //keep removing items until list is empty
  }
}

template <typename T>
T LinkedList<T>::getEntry(std::size_t position) const
{
  bool ableToGet = (position >= 1) && (position <= size);
  if(ableToGet)
  {
    Node<T>* intermediate = getNodeAt(position);//get the node at position
    return intermediate->getItem(); //return the value of that node
  }
  else
  {
    throw(std::range_error("error in getEntry range"));
  }
}

template <typename T>
void LinkedList<T>::setEntry(std::size_t position, const T& newValue)
{
  bool validityTest;
  bool ableToSet = (position >=1) && (position <= size);
  Node<T>* previous = getNodeAt(position - 1); //get the node beofre the node to be set

  if(position+1 <= size)
  {
    Node<T>* next = getNodeAt(position+1);
    if(position-1 >= 1)
    {
      validityTest = (previous->getItem() < newValue) && (next->getItem());
    }
    else
    {
      validityTest = (next->getItem() > newValue);
    }
  }
  else
  {
    validityTest = true;
  }

  if(ableToSet)
  {
    while(size >= position)
    {
      remove(position);
    }
    insert(position,newValue);
  }
  else
  {
    throw(std::range_error("error in setEntry range"));
  }
}
