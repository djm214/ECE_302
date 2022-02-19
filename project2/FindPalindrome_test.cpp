#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include "FindPalindrome.hpp"

// There should be at least one test per FindPalindrome method

#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include "FindPalindrome.hpp"

// There should be at least one test per FindPalindrome method

TEST_CASE( "add string", "[FindPalindrome]" )
{
	INFO("Hint: add a combination of allowable and non-allowable words");

	FindPalindrome b; //creates a FindPalindrome object

	REQUIRE(!b.add("kayak1")); //ensures that numbers cannot be added to the vector
	REQUIRE(b.add("thysndfonSunafndSdF")); //tests that words with a-z and A-Z can be added
	REQUIRE(!b.add("thysndfonSunafndSdF")); //Tests that copies are not allowed

	REQUIRE(b.add("crazy"));
	REQUIRE(!b.add("Crazy")); //these two serve to check that uniqueness is not dependant on case

	REQUIRE(!b.add("Whatz up")); //spaces aren't allowed to be included
}

TEST_CASE("add vector","[FindPalindrome]")
{
	FindPalindrome b; //creates a FindPalindrome object

	std::vector<std::string> stringVector;

	stringVector.push_back("whatsup");
	stringVector.push_back("hello");
	stringVector.push_back("string"); //fills a stringVector with various legal words
	stringVector.push_back("code");
	stringVector.push_back("naan");

	REQUIRE(stringVector.size() == 5);
	REQUIRE(b.add(stringVector)); //require that this is true
	
	b.clear();

	stringVector.push_back("whatsup");
	stringVector.push_back("hello");
	stringVector.push_back("string"); //fills a stringVector with various legal words
	stringVector.push_back("code");
	stringVector.push_back("naan");
	stringVector.push_back("fr3ak"); //add an illegal word

	REQUIRE(!b.add(stringVector)); //require this fails due to the single illegal variable

	b.clear();

	stringVector.push_back("whatsup");
	stringVector.push_back("hello");
	stringVector.push_back("very nice"); //add an illegal word
	stringVector.push_back("string"); //fills a stringVector with various legal words
	stringVector.push_back("code");
	stringVector.push_back("naan");

	REQUIRE(!b.add(stringVector)); //require that this fails due to the illegal addition
	
}

TEST_CASE("Number of Palindromes","[FindPalindromes]")
{
	FindPalindrome b; //creates a FindPalindrome object

	std::vector<std::string> stringVector; //a vector variable that will be used to carry out tests here

	stringVector.push_back("Never");
	stringVector.push_back("Even");
	stringVector.push_back("or"); //fills a stringVector with various legal words
	stringVector.push_back("ODD");

	b.add(stringVector); //call the add vector function

	REQUIRE(b.number() == 1); //should return 1 palindrome

	b.clear(); //clears the vector

	REQUIRE(b.number() == 0); //should be zero after vector is cleared

	b.add("a");
	b.add("Aa"); //fills the vector with 3 words all with the same character with varying case
	b.add("AAA");

	REQUIRE(b.number() == 6); //this should result in 3 factorial possibilities

	b.clear(); //clears the total vector

	b.add("a"); //fils vector of similar characters with differing size chunks/words
	b.add("Aa");

	REQUIRE(b.number() == 2); //this set should result in 2 factorial possibilities

	b.clear(); //clears the total vector

	b.add("a"); //adds one word with one character

	REQUIRE(b.number() == 1); //this set should result in 1 factorial possibilities
}

TEST_CASE("toVector","[FindPalindromes]")
{
	FindPalindrome b; //creates a FindPalindrome object

	std::vector<std::string> stringVector,upReturn;
	std::vector<std::vector<std::string>> returnedValue; //creates variables that will be used to carry out tests in this case
	std::string stringVectorstring,Palindromestring;

	Palindromestring = "NeverODDorEven"; //case preserved expected palindrome in a concatenated string

	stringVector.push_back("Never");
	stringVector.push_back("Even");
	stringVector.push_back("or"); //fills a stringVector with various legal words
	stringVector.push_back("ODD");

	b.add(stringVector); //call the add vector function
	returnedValue = b.toVector(); //get the vector of the palindrome

	upReturn = returnedValue.front(); //set the variable upReturn vector equal to the first vector in the vectorofvectors

	REQUIRE(upReturn.size() == 4); //makes sure the right size vector is obtained

	for(int i = 0; i < upReturn.size(); i++)
	{
		stringVectorstring += upReturn.at(i); //concatenates the first vector of strings
	}

	REQUIRE(stringVectorstring == Palindromestring); //make sure that the output is exactly what is expected, case preserved
}