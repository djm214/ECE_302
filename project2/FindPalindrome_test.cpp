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

