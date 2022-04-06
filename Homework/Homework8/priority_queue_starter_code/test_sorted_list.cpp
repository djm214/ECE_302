#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "dynamic_array_list.h"
#include "sorted_list.h"

TEST_CASE("Testing Insert", "[sorted list]") {
  typedef SortedList<int, DynamicArrayList<int> > slst;
  
  slst list;

  list.insert(2);
  list.insert(8);
  list.insert(1);
  list.insert(3);
  list.insert(5);
  list.insert(4);
  list.insert(7);
  list.insert(6);
  list.insert(0);

  REQUIRE(list.getLength() == 9); //ensuring size gets updated

  for(int i = 0; i < list.getLength(); i++)
  {
    REQUIRE(list.getEntry(i) == i); //tests to see if it is inserted IN ORDER
  }
}

TEST_CASE("Testing Remove", "[sorted list]") {
  typedef SortedList<int, DynamicArrayList<int> > slst;
  
  slst list;

  CHECK_THROWS_AS(list.remove(0), std::range_error); //should fail if list is empty

  list.insert(2);
  list.insert(8);
  list.insert(1);
  list.insert(3);
  list.insert(5); //fills an array with 0-8 in random order
  list.insert(4);
  list.insert(7);
  list.insert(6);
  list.insert(0);

  REQUIRE(list.getLength() == 9); //ensuring size gets updated

  list.remove(8);
  list.remove(4);
  list.remove(7);
  list.remove(2);

  REQUIRE(list.getLength() == 5); //ensuring size gets decreased accordingly

  REQUIRE(list.getEntry(0) == 0); 
  REQUIRE(list.getEntry(1) == 1); 
  REQUIRE(list.getEntry(2) == 3); //tests to see order maintained
  REQUIRE(list.getEntry(3) == 5); 
  REQUIRE(list.getEntry(4) == 6); 

  CHECK_THROWS_AS(list.remove(10), std::range_error); //check the error throws
  CHECK_THROWS_AS(list.remove(-1), std::range_error);
}

TEST_CASE("Testing getPosition", "[sorted list]") {
  typedef SortedList<int, DynamicArrayList<int> > slst;
  
  slst list;

  list.insert(2);
  list.insert(8);
  list.insert(1);
  list.insert(3);
  list.insert(5);
  list.insert(4);
  list.insert(7);
  list.insert(6);
  list.insert(0);

  REQUIRE(list.getLength() == 9); //ensuring size gets updated

  for(int i = 0; i < 9; i++)
  {
    REQUIRE(list.getPosition(i) == i); //should equal the first occurence of the item
  }

  for(int i = 9; i < 15; i++)
  {
    REQUIRE(list.getPosition(i) == 9); //ensures that anything larger than all items return the size
  }

  REQUIRE(list.getPosition(-1) == 0); //should be appended to the beginning

  list.remove(5); //remove an element
  REQUIRE(list.getPosition(5) == 5); //the position that it SHOULD be added back to must equal what it was previously
}