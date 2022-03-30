#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "dynamic_array_list.h"
#include "sorted_list.h"
#include "priority_queue.h"

TEST_CASE("Testing Priority Queue", "[priority queue]") {
  typedef SortedList<int, DynamicArrayList<int> > SortedListType;
  typedef PriorityQueue<int, SortedListType>  PriorityQueueType;

  PriorityQueueType pq;

  REQUIRE(pq.isEmpty());

  pq.add(0);
  pq.add(2);
  pq.add(4);
  pq.add(5); //adds 0-5 in a random order
  pq.add(3);
  pq.add(1);

  REQUIRE(pq.isEmpty() == false);

  REQUIRE(pq.peek() == 5); //returns highest priority
  pq.remove(); //removes highest priority
  REQUIRE(pq.peek() == 4); //returns new highest ....
  pq.remove();
  REQUIRE(pq.peek() == 3);
  pq.remove();
  REQUIRE(pq.peek() == 2);
  pq.remove();
  REQUIRE(pq.peek() == 1);
  pq.remove();
  REQUIRE(pq.peek() == 0);
  pq.remove();

  REQUIRE(pq.isEmpty());
  
}
