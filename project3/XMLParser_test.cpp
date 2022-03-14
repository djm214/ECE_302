#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include <iostream>
#include "catch.hpp"
#include "XMLParser.hpp"

using namespace std;

// TODO Implement tests of your Stack class and XMLParser class here

TEST_CASE( "Test Bag add", "[XMLParser]" )
{
	   INFO("Hint: testing Bag add()");
		// Create a Bag to hold ints
		Bag<int> intBag;
		int testSize = 2;
		int bagSize;
		bool success;
		for (int i=0; i<testSize; i++) {
			success = intBag.add(i);
			REQUIRE(success);
			bagSize = intBag.size();
			success = (bagSize == (i+1));
			REQUIRE(success);
		}
}

TEST_CASE( "Test Stack push", "[XMLParser]" )
{
	   INFO("Hint: testing Stack push()");
		// Create a Stack to hold ints
		Stack<int> intStack;
		int testSize = 3;
		int stackSize;
		bool success;

		for (int i=0; i<testSize; i++) {
			success = intStack.push(i);
			REQUIRE(success);
			stackSize = intStack.size();
			success = (stackSize == (i+1));
			REQUIRE(success);
		}
}

TEST_CASE( "Test Stack pop", "[XMLParser]" )
{
	// Create a Stack to hold ints
	Stack<int> intStack;
	int testSize = 5;
	int stackSize; //holds the stack size
	bool success; //testing bool

	for (int i=0; i<testSize; i++) 
	{
		intStack.push(i); //assuming that the push function works, fill the stack with ints
	}

	REQUIRE(intStack.isEmpty() == false); //the stack should no longer be empty

	for (int i=testSize; i>0 ; i--) 
	{
		success = intStack.pop();
		REQUIRE(success); //pop should always be successful in this case
		stackSize = intStack.size();
		success = (stackSize == (i-1)); //the size of the stack should now be one less than before
		REQUIRE(success);
	}

	REQUIRE(intStack.isEmpty()); //the stack should now be empty

	REQUIRE(intStack.pop() == false); //pop should now fail that the stack is empty
}

TEST_CASE( "Test Stack peek", "[XMLParser]" )
{
	Stack<int> intStack;
	int testSize = 5;
	int stackSize; //holds the stack size
	int success; //testing int for return value of peek

	for (int i=0; i<testSize; i++) 
	{
		intStack.push(i); //assuming that the push function works, fill the stack with ints
	}

	for (int i=testSize; i>0 ; i--) 
	{
		success = intStack.peek();
		REQUIRE(success == (i-1)); //peek should always be successful in this case
		intStack.pop(); //pops the last number on the stack
	}
}

TEST_CASE( "Test Stack size", "[XMLParser]" )
{
	// Create a Stack to hold ints
	Stack<int> intStack;
	int testSize = 5;
	int stackSize; //holds the stack size
	bool success; //testing bool

	for (int i=0; i<testSize; i++) 
	{
		intStack.push(i); //assuming that the push function works, fill the stack with ints
		REQUIRE(intStack.size() == (i+1)); //the stack should have a size of 5 after pushing 5 elements onto stack

	}

	for (int i=testSize; i>0 ; i--) 
	{
		success = intStack.pop();
		REQUIRE(success); //pop should always be successful in this case
		stackSize = intStack.size();
		success = (stackSize == (i-1)); //the size of the stack should now be one less than before
		REQUIRE(success);
	}

	REQUIRE(intStack.size() == 0); //the stack should now be empty
}