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
	clear(); //calls clear to delete all elements
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
	Node<ItemType>* newNodePointer = new Node<ItemType>(newItem,headPtr); //creates a new node pointer
	headPtr = newNodePointer; //sets the head pointer to the new Node pointer created

	newNodePointer = nullptr; //makes the variable pointer inaccessable

	currentSize++; //increases the ammount of objects in the list

	return true;
}  // end push

// TODO: Implement the peek method here
template<class ItemType>
ItemType Stack<ItemType>::peek() const throw(logic_error)
{
	ItemType returnItem; //what will ultimately be returned from the function

	if(currentSize == 0)
	{
		throw logic_error("The current list is empty, peek cannot execute"); //throw an error if size is zero
	}

	returnItem = headPtr->getItem(); //returns item on the top of the stack

	return returnItem; //returns the returnItem

	
}  // end peek

// TODO: Implement the pop method here
template<class ItemType>
bool Stack<ItemType>::pop() 
{
	if(isEmpty())
	{
		return false; //if the stack is empty, the operation fails
	}

	Node<ItemType>* removingPtr = headPtr; //creates a stand in variable for the pointer of node to be deleted
	headPtr = headPtr->getNext(); //redefines the head ptr now that one is being deleted

	removingPtr->setNext(nullptr); //makes the pointer to be deleted inaccessable
	delete removingPtr; //deletes memory for removingPtr
	removingPtr = nullptr; //sets the pointer to nullptr

	currentSize--; //decreases total size of list

	return true;
}  // end pop

// TODO: Implement the clear method here
template<class ItemType>
void Stack<ItemType>::clear()
{
	while(!isEmpty())
	{
		pop(); //while the stack is not empty, keep popping elements
	}
}  // end clear

