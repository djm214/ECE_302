#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "deque.hpp"

TEST_CASE( "Tests", "[deque]" ) 
{
    Deque<int> tester;
    REQUIRE(tester.isEmpty());

    tester.pushFront(2);
    tester.pushFront(1);    //add in 1,2,3
    tester.pushBack(3);

    REQUIRE(tester.front() == 1);
    tester.popFront();
    REQUIRE(tester.front() == 2);   //test the order of 1,2,3
    tester.popFront();
    REQUIRE(tester.front() == 3);
    tester.popFront();

    REQUIRE(tester.isEmpty());

    tester.pushBack(9);
    tester.pushBack(10);
    tester.pushBack(11);

    REQUIRE(tester.front() == 9);
    tester.popFront();
    REQUIRE(tester.front() == 10);  //test the order of 9,10,11
    tester.popFront();
    REQUIRE(tester.front() == 11);
    tester.popFront();

    REQUIRE(tester.isEmpty());

    tester.pushBack(9);
    tester.pushBack(10);
    tester.pushBack(11);
    tester.pushBack(12);
    tester.pushBack(13);
    tester.pushBack(14);

    REQUIRE(tester.back() == 14);
    tester.popBack();
    REQUIRE(tester.back() == 13);
    tester.popBack();
    REQUIRE(tester.back() == 12);
    tester.popBack();
    REQUIRE(tester.back() == 11);
    tester.popBack();
    REQUIRE(tester.back() == 10);
    tester.popBack();
    REQUIRE(tester.back() == 9);
    tester.popBack();


    REQUIRE(tester.isEmpty());
}
