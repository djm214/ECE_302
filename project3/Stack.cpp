//  Adapated from Frank M. Carrano and Timothy M. Henry.

/** ADT Stack implementation.
    @file Stack.cpp */

#include <iostream>
#include <cstddef>
#include "Stack.hpp"
#include "Node.hpp"

// TODO: Implement the constructor here
template<class ItemType>
Stack<ItemType>::Stack() 
{
	headPtr = nullptr; //initializes the headPtr to null
	currentSize = 0; //sets the current size of the list to zero
}  // end default constructor

// TODO: Implement the destructor here
template<class ItemType>
Stack<ItemType>::~Stack()
{
}  // end destructor

// TODO: Implement the isEmpty method here
template<class ItemType>
bool Stack<ItemType>::isEmpty() const
{
	if(currentSize == 0)
	{
		return true; //if the currentSize variable is zero, then the stack is empty
	}
	return false; //returns false for any value other than zero
}  // end isEmpty

// TODO: Implement the size method here
template<class ItemType>
int Stack<ItemType>::size() const
{
	return currentSize; //returns the current size vector
}  // end size

// TODO: Implement the push method here
template<class ItemType>
bool Stack<ItemType>::push(const ItemType& newItem)
{
	Node<ItemType>* currentPointer = headPtr; //creates a stand in variable for the current node pointer

	for(int i = 0; i < currentSize; i++)
	{
		if((currentPointer->getNext()) == nullptr)
		{
			currentPointer = currentPointer; //if the next node is nullptr, do not update the currentpointer
		}
		else
		{
			currentPointer = currentPointer->getNext(); //traverses the list, getting the next node pointers
		}
	}

	currentPointer->setNext(currentPointer->getNext()); //adds a next node
	currentPointer = currentPointer->getNext(); //sets the next node pointer equal to current pointer
	currentPointer->setItem(newItem); //sets the value of that node

	return true;
}  // end push

// TODO: Implement the peek method here
template<class ItemType>
ItemType Stack<ItemType>::peek() const throw(logic_error)
{
	ItemType returnItem;
	return returnItem;
}  // end peek

// TODO: Implement the pop method here
template<class ItemType>
bool Stack<ItemType>::pop() 
{
	return false;
}  // end pop

// TODO: Implement the clear method here
template<class ItemType>
void Stack<ItemType>::clear()
{
}  // end clear

