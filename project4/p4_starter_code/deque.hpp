#ifndef DEQUE_HPP
#define DEQUE_HPP

#include "abstract_deque.hpp"
#include "linked_list.hpp"

template <typename T>
class Deque: public AbstractDeque<T>{

bool isEmpty() const noexcept;
void pushFront(const T & item);
void popFront();
T front() const;
void pushBack(const T & item);
void popBack();
T back() const;

private:
LinkedList<T> *obj; //pointer to linkedList obj
  
};

#include "deque.tpp"

#endif
