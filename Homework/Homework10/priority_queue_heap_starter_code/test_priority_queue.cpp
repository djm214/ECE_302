#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "heap_priority_queue.h"

TEST_CASE("Test Construction", "[construction]") {
  HeapPriorityQueue<int>  pq;
  REQUIRE(pq.isEmpty());
}

TEST_CASE("Test add", "[add]") {
  HeapPriorityQueue<int>  pq;
  pq.add(25);

  REQUIRE(!pq.isEmpty());
  REQUIRE(pq.peek() == 25);

  pq.add(1);
  REQUIRE(pq.peek() == 25);

  pq.add(78);
  REQUIRE(pq.peek() == 78);

  pq.add(79);
  REQUIRE(pq.peek() == 79);

  pq.add(10019032);
  REQUIRE(pq.peek() == 10019032);

  pq.add(10019032); //ensuring that the same number can be added twice
  REQUIRE(pq.peek() == 10019032);

  pq.remove();
  REQUIRE(pq.peek() == 10019032);
}

TEST_CASE("Test remove", "[remove]") {
  HeapPriorityQueue<int>  pq;
  pq.add(25);
  REQUIRE(pq.peek() == 25);
  pq.add(1);
  REQUIRE(pq.peek() == 25);
  pq.add(78);

  REQUIRE(pq.peek() == 78);
  pq.remove();
  pq.add(77);
  REQUIRE(pq.peek() == 77);
  pq.remove();
  REQUIRE(pq.peek() == 25);
  pq.remove();
  REQUIRE(pq.peek() == 1);
  pq.remove();
  REQUIRE(pq.isEmpty());
}
