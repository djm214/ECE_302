#include "sorted_list.h"

template <typename T, typename L>
SortedList<T, L>::SortedList()
{
  // nothing to do, plist gets created on the stack
}

template <typename T, typename L>
SortedList<T, L>::SortedList(const SortedList<T, L> & x)
{
  plist = x.plist; // use copy assignment to implement copy construction
}

template <typename T, typename L>
SortedList<T, L>& SortedList<T, L>::operator=(const SortedList<T, L>& x)
{
  plist = x.plist;
  return *this;
}

template <typename T, typename L>
SortedList<T, L>::~SortedList()
{
  // plist destructor gets called automatically
}

template <typename T, typename L>
bool SortedList<T, L>::isEmpty()
{
  return plist.isEmpty();
}

template <typename T, typename L>
std::size_t SortedList<T, L>::getLength()
{
  return plist.getLength();
}

template <typename T, typename L>
void SortedList<T, L>::insert(const T& item)
{
  int count = 0;
  if(isEmpty())
  {
    plist.insert(0,item); //insert at the front
  }
  else if(getEntry((getLength()-1)) < item)
  {
    plist.insert(getLength(),item); //insert at the back
  }
  else
  {
    for(int i = 0; i < getLength(); i++)
    {
      if(getEntry(i) >= item && count == 0)
      {
        plist.insert(i,item); //inserts item in previous position
        count++;
      }
    }
  }
}

template <typename T, typename L>
void SortedList<T, L>::remove(const T& item)
{
  if(isEmpty()) throw std::range_error("The list is empty, so remove cannot function");

  bool found = false;

  for(int i = 0; i < getLength(); i++)
  {
    if(getEntry(i) == item)
    {
      plist.remove(i); //remove the item at position i
      found = true; //set the found bool to true
      break; //escape the for loop
    }
  }

  if(found == false) throw std::range_error("The list doesn't contain the item");
}

template <typename T, typename L>
void SortedList<T, L>::removeAt(std::size_t position)
{
  plist.remove(position);
}

template <typename T, typename L>
void SortedList<T, L>::clear()
{
  plist.clear();
}

template <typename T, typename L>
T SortedList<T, L>::getEntry(std::size_t position)
{
  return plist.getEntry(position);
}

template <typename T, typename L>
long int SortedList<T, L>::getPosition(const T& newValue)
{
  if(getEntry(getLength()-1) < newValue)
  {
    return getLength(); //should be inserted at the end
  }
  else if(isEmpty())
  {
    return 0; //should be inserted at 0, since the list is currently empty
  }
  for(int i = 0; i < getLength(); i++)
  {
    if(getEntry(i) == newValue || getEntry(i) >= newValue)
    {
      return i; //returns the indexing number
    }
  }

  throw std::range_error("something went wrong");
}
