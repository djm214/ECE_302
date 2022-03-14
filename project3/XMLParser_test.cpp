#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include <iostream>
#include "catch.hpp"
#include "XMLParser.hpp"

using namespace std;

//--------------------------------------------------------------------------------------------------------------------------------------
//Begin Stack tests
//--------------------------------------------------------------------------------------------------------------------------------------

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

TEST_CASE( "Test Stack clear", "[XMLParser]" )
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

	intStack.clear(); //call the clear function

	REQUIRE(intStack.isEmpty()); //ensures that the stack is now empty
	REQUIRE(intStack.pop() == false);
}

TEST_CASE( "Test Stack isEmpty", "[XMLParser]" )
{
	// Create a Stack to hold ints
	Stack<int> intStack;
	int testSize = 5;
	int stackSize; //holds the stack size
	bool success; //testing bool

	REQUIRE(intStack.isEmpty());

	for (int i=0; i<testSize; i++) 
	{
		intStack.push(i); //assuming that the push function works, fill the stack with ints
		REQUIRE(intStack.isEmpty() == false); //once things are pushed onto the stack and the size is no longer 0, isEmpty should fail
	}

	REQUIRE(intStack.isEmpty() == false);

	intStack.clear(); //clear the stack and reset size to zero

	REQUIRE(intStack.isEmpty()); //should evaluate to true since the stack was cleared
}


//--------------------------------------------------------------------------------------------------------------------------------------
//Begin XML tests
//--------------------------------------------------------------------------------------------------------------------------------------

TEST_CASE( "Test XMLParser tokenizeInputString", "[XMLParser]" )
{
	   INFO("Hint: tokenize single element test of XMLParse");
		// Create an instance of XMLParse
		XMLParser myXMLParser;
		string testString = "<test>stuff</test>";
		bool success;
		success = myXMLParser.tokenizeInputString(testString);
		REQUIRE(success);
}

TEST_CASE( "Test Stack handout-0", "[XMLParser]" )
{
		// Create a Stack to hold ints
		Stack<int> intStack;
		int testSize = 10;
		int stackSize;
		bool success = false;
		for (int i=0; i<testSize; i++) {
			intStack.push(i);
			stackSize = intStack.size();
			success = (stackSize == (i+1));
			REQUIRE(success);
		}
		for (int i = testSize-1; i>=0; i--) {
			REQUIRE(intStack.isEmpty() == false);
            int elem = intStack.peek();
			REQUIRE(elem == i);
            REQUIRE(intStack.isEmpty() == false);
			intStack.pop();
		}
        REQUIRE(intStack.isEmpty() == true);
}

TEST_CASE( "Test Stack handout-1", "[XMLParser]" )
{
	   Stack<char> charStack;
       std::string s("Hello world");
       int i = 1;
       for (auto c:s) {
           charStack.push(c);
           REQUIRE(charStack.size() == i);
           i++;
       }
       for (i = 0; i < 5; i++) {
           REQUIRE(charStack.isEmpty() == false);
           char c = charStack.peek();
           REQUIRE(c == s[s.length()-1-i]);
           REQUIRE(charStack.isEmpty() == false);
           charStack.pop();
       }
       REQUIRE(charStack.size() == 6);
       charStack.clear();
       REQUIRE(charStack.isEmpty() == true);      
}

// You can assume that the beginning and the end of CONTENT will not be filled with whitespace
TEST_CASE( "Test XMLParser tokenizeInputString Handout-0", "[XMLParser]" )
{
	   INFO("Hint: tokenize single element test of XMLParse");
		// Create an instance of XMLParse
		XMLParser myXMLParser;
		string testString = "<test>stuff</test>";
		bool success;
		success = myXMLParser.tokenizeInputString(testString);
		REQUIRE(success);
		std::vector<TokenStruct> result = {TokenStruct{StringTokenType::START_TAG, std::string("test")},
											TokenStruct{StringTokenType::CONTENT, std::string("stuff")},
											TokenStruct{StringTokenType::END_TAG, std::string("test")}};
		std::vector<TokenStruct> output = myXMLParser.returnTokenizedInput();
		REQUIRE(result.size() == output.size());
		for (int i = 0; i < result.size(); i++) {
			REQUIRE(result[i].tokenType == output[i].tokenType);
			REQUIRE(result[i].tokenString.compare(output[i].tokenString) == 0);
		}
}


// You can assume that the beginning and the end of CONTENT will not be filled with whitespace
TEST_CASE( "Test XMLParser tokenizeInputString Handout-1", "[XMLParser]" )
{
	   INFO("Hint: tokenize multiple elements test of XMLParse");
		// Create an instance of XMLParse
		XMLParser myXMLParser;
		string testString = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><Note src='gmail'>  <From>Tom</From> <To>Alice</To> </Note>";
		bool success;
		success = myXMLParser.tokenizeInputString(testString);
		REQUIRE(success);
		std::vector<TokenStruct> result = { TokenStruct{StringTokenType::DECLARATION, std::string("xml version=\"1.0\" encoding=\"UTF-8\"")},
									TokenStruct{StringTokenType::START_TAG, std::string("Note")},
									TokenStruct{StringTokenType::START_TAG, std::string("From")},
									TokenStruct{StringTokenType::CONTENT, std::string("Tom")},
									TokenStruct{StringTokenType::END_TAG, std::string("From")},
									TokenStruct{StringTokenType::START_TAG, std::string("To")},
									TokenStruct{StringTokenType::CONTENT, std::string("Alice")},
									TokenStruct{StringTokenType::END_TAG, std::string("To")},
									TokenStruct{StringTokenType::END_TAG, std::string("Note")}};
		std::vector<TokenStruct> output = myXMLParser.returnTokenizedInput();
		REQUIRE(result.size() == output.size());
		for (int i = 0; i < result.size(); i++) {
			REQUIRE(result[i].tokenType == output[i].tokenType);
			REQUIRE(result[i].tokenString.compare(output[i].tokenString) == 0);
		}
}

TEST_CASE( "Test XMLParser parseTokenizedInput Handout-0", "[XMLParser]" )
{
	   INFO("Hint: tokenize single element test of XMLParse");
		// Create an instance of XMLParse
		XMLParser myXMLParser;
		string testString = "<test myattr='abcdef'>stuff<this_is_empty_tag/></test>";
		bool success;
		success = myXMLParser.tokenizeInputString(testString);
		REQUIRE(success);
		std::vector<TokenStruct> result = {TokenStruct{StringTokenType::START_TAG, std::string("test")},
											TokenStruct{StringTokenType::CONTENT, std::string("stuff")},
											TokenStruct{StringTokenType::EMPTY_TAG, std::string("this_is_empty_tag")},
											TokenStruct{StringTokenType::END_TAG, std::string("test")}};
		std::vector<TokenStruct> output = myXMLParser.returnTokenizedInput();
		REQUIRE(result.size() == output.size());
		success = myXMLParser.parseTokenizedInput();
		REQUIRE(success);
		output = myXMLParser.returnTokenizedInput();
		REQUIRE(result.size() == output.size());
		for (int i = 0; i < result.size(); i++) {
			REQUIRE(result[i].tokenType == output[i].tokenType);
			REQUIRE(result[i].tokenString.compare(output[i].tokenString) == 0);
		}
}

TEST_CASE( "Test XMLParser Final Handout-0", "[XMLParser]" )
{
	   INFO("Hint: Product");
		// Create an instance of XMLParse
		XMLParser myXMLParser;
		ifstream myfile ("./TestFile.txt");
		std::string inputString((std::istreambuf_iterator<char>(myfile) ), (std::istreambuf_iterator<char>()) );

		bool success;
		success = myXMLParser.tokenizeInputString(inputString);
		REQUIRE(success);
		success = myXMLParser.parseTokenizedInput();
		REQUIRE(success);
		REQUIRE(myXMLParser.containsElementName("catalog"));
		REQUIRE(myXMLParser.frequencyElementName("catalog") == 1);
		REQUIRE(myXMLParser.containsElementName("product"));
		REQUIRE(myXMLParser.frequencyElementName("product") == 1);
		REQUIRE(myXMLParser.containsElementName("catalog_item"));
		REQUIRE(myXMLParser.frequencyElementName("catalog_item") == 2);
		REQUIRE(myXMLParser.containsElementName("item_number"));
		REQUIRE(myXMLParser.frequencyElementName("item_number") == 2);
		REQUIRE(myXMLParser.containsElementName("size"));
		REQUIRE(myXMLParser.frequencyElementName("size") == 6);
		REQUIRE(myXMLParser.containsElementName("color_swatch"));
		REQUIRE(myXMLParser.frequencyElementName("color_swatch") == 15);
}