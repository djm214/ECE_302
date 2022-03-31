#ifndef DEQUE_HPP
#define DEQUE_HPP

#include "abstract_deque.hpp"
#include "linked_list.hpp"

template <typename T>
class Deque: public AbstractDeque<T>{
public:

//Default Constructor
Deque();
//Default Destructor
~Deque();
//returns true if the list is empty
bool isEmpty() const noexcept;
//adds item to the begining of the list
void pushFront(const T & item);
//removes the item at the front of the list
void popFront();
//returns the front variable
T front() const;
//add an item to the back
void pushBack(const T & item);
//remove an item from the back
void popBack();
//returns the item in the back
T back() const;

private:

LinkedList<T> *obj; //pointer to linkedList obj
  
};

#include "deque.tpp"

#endif
