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