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

TEST_CASE("cutTest1","[FindPalindromes]")
{
	FindPalindrome b; //creates a FindPalindrome object

	std::vector<std::string> testvect; //creates a vector that will be used in the tests below

	testvect.push_back("a");
	testvect.push_back("aa"); //fills the vector with basic words with 2 character type (a and b)
	testvect.push_back("aaa");
	testvect.push_back("b");

	REQUIRE(b.cutTest1(testvect)); //there is a b once which is odd and 6 a's which is even

	testvect.push_back("c"); //adds another character that only appears once

	REQUIRE(!b.cutTest1(testvect)); //if two characters are odd, the test should fail

	testvect.push_back("BBB"); //makes the occurance of b even (4)
							   //also serves to make sure b = B in the functions eyes

	REQUIRE(b.cutTest1(testvect)); //once b is even, cutTest1 should be true again

	testvect.push_back("ZZZZ"); //testing capitalization implementation

	REQUIRE(b.cutTest1(testvect)); //should evaluate true since there are 4 Z's
}

TEST_CASE("cutTest2", "[FindPalindromes]")
{
	FindPalindrome b; //creates a FindPalindrome object

	std::vector<std::string> vect1, vect2, vect3, vect4; //these string vectors will be used in the below tests

	vect1.push_back("a");
	vect1.push_back("b"); //vect 1 {a b c}
	vect1.push_back("c");

	vect2.push_back("a");
	vect2.push_back("b");
	vect2.push_back("e"); //vect 2 {a b e f c}
	vect2.push_back("f");
	vect2.push_back("c");


	REQUIRE(b.cutTest2(vect1,vect2)); //the larger contains at least one copy of each small vector character

	vect3.push_back("a");
	vect3.push_back("b"); // vect 3 {a b y}
	vect3.push_back("y");

	REQUIRE(!b.cutTest2(vect3,vect2)); //should fail since the smaller one (vect 3) contains y which is not in the larger vector (vect 4)

	vect4.push_back("aby"); //this tests with a smaller vector size, but a larger character count
	vect4.push_back("gfrty"); //vect 4 {aby gfrty}

	REQUIRE(b.cutTest2(vect3,vect4)); //should be true even though 4 has a smaller vector size than 3

}

TEST_CASE("recursive call function", "[FindPalindromes]")
{
	FindPalindrome b; //creates a FindPalindrome object

	std::vector<std::string> testvect; //creates a vector of strings that will be used below in tests

	testvect.push_back("a");
	testvect.push_back("aa"); //testvect {a aa aaa}
	testvect.push_back("aaa");

	b.add(testvect); //adds a vector with the three a values the add function calls the recursive function

	REQUIRE(b.number() == 6); //should find N! palindromes since all characters ar a, which means every combination is a palindrome

	b.add("aaaa"); //adds a vector with the three a values the add function calls the recursive function

	REQUIRE(b.number() == 24); //should equal 4 factorial now

	b.add("aaaaa"); 

	REQUIRE(b.number() == 120); //should equal 5 factorial now

	//assuming these work, this means the function works since it shows the function iterates th vect.size() factorial
}