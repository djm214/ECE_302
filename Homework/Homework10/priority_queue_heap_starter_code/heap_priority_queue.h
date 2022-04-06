
#ifndef _HEAP_PRIORITY_QUEUE_H_
#define _HEAP_PRIORITY_QUEUE_H_

#include "abstract_priority_queue.h"
#include "dynamic_array_list.h"

template <typename T>
class HeapPriorityQueue: public AbstractPriorityQueue<T>
{
public:
    
    // return true if the priority queue is empty
    bool isEmpty();
    
    // insert item into the queue
    void add(const T& item);
    
    // remove highest priority item from the queue
    void remove();
    
    // get the item with the highest priority from the queue
    T peek();
    
private:
    
    DynamicArrayList<T> lst;
};

template <typename T>
bool HeapPriorityQueue<T>::isEmpty()
{
    return lst.isEmpty();
}

template <typename T>
void HeapPriorityQueue<T>::add(const T& item)
{
    lst.insert(lst.getLength(),item); //insert at the bottom of the tree
    
    int temp; //will be used for swapping purposes
    int parentIndex; //will keep track of the parent of the insertion
    int insertionIndex = lst.getLength()-1; //keep track of index
    bool correctSpot = false; //initializes exit statement to false
  
    while(!correctSpot && (insertionIndex >= 0))
    {
    	parentIndex = (insertionIndex)/2;
    	if(lst.getEntry(insertionIndex) <= lst.getEntry(parentIndex))
    	{
    		correctSpot = true; //this is where insertion SHOULD be
    	}
    	else
    	{
    		//swap items at parent and insertion indexes
    		temp = lst.getEntry(parentIndex);
    		lst.setEntry(parentIndex,lst.getEntry(insertionIndex));
    		lst.setEntry(insertionIndex,temp);
    		
    		insertionIndex = parentIndex;
    	}
    }
}

template <typename T>
void HeapPriorityQueue<T>::remove()
{
    //replace the root with the last object
    lst.setEntry(0,lst.getEntry(lst.getLength()-1));
    lst.remove(lst.getLength()-1);
    
    //trickle the object down intil its in the right spot again
    int temp; //will be used for swapping purposes
    int replaced = 0; //the index of the replaced root
    bool correctSpot = false; //initialized to incorrect spot
    while(!correctSpot && (replaced+1) < lst.getLength())
    {	
    	if(lst.getEntry(replaced+1) <= lst.getEntry(replaced))
    	{
		correctSpot = true; //this is where it should be
    	}
    	else
    	{
    		//swap replaced and CMP if above for loop is false
    		temp = lst.getEntry(replaced);
    		lst.setEntry(replaced,lst.getEntry(replaced+1));
    		lst.setEntry(replaced+1,temp);
    		
    		replaced++; //traverse the array by 1
    	}
    }
    
}

template <typename T>
T HeapPriorityQueue<T>::peek()
{
    return lst.getEntry(0);
}


#endif // _HEAP_PRIORITY_QUEUE_H_
