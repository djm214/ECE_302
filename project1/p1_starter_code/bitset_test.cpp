#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "bitset.hpp"

// THIS IS JUST AN EXAMPLE
// There should be at least one test per Bitset method

TEST_CASE( "Test bitset default construction", "[bitset]" )
{
    Bitset b;  //object definition
    REQUIRE(b.size() == 8); //check to see size is initialized to 8
    REQUIRE(b.good() == true); //check to see if data is valid
}

TEST_CASE( "Test bitset size variable construction", "[bitset]" )
{
    Bitset b(4);  //object declaration with 4 passed as size variable
    REQUIRE(b.size() == 4); //check if size is set to 4
    REQUIRE(b.good() == true); //check validity of data

    Bitset f(-1); //object declaration with supposedly bad data ( N <= 0)
    REQUIRE(f.good() == false); //check to see if validity is false
}

TEST_CASE("Test bitset string variable construction", "[bitset]" )
{
    Bitset b("100101"); //pass this string into the constructor
    REQUIRE(b.size() == 6); //make sure size is read correctly from string
    REQUIRE(b.good() == true); //make sure data returns true for validity

    Bitset f("102"); //pass bad data into constructor
    REQUIRE(f.size() == 3); //still should pass correct size, so use this to double check
    REQUIRE(f.good() == false); //make sure this gives a false validity
}

TEST_CASE( "size function", "[bitset]" )
{
    Bitset b(12); //declare object and pass 12 into size
    REQUIRE(b.size() == 12); //make sure 12 is returned from size function

    Bitset c(2); //repeat two more times for assurance
    REQUIRE(c.size() == 2);

    Bitset d(10);
    REQUIRE(d.size() == 10);
}

TEST_CASE("good function", "[bitset]")
{
    Bitset b; //valid data
    Bitset c(12);
    Bitset d("100001");

    Bitset f(0); //invalid data
    Bitset g("10032");

    REQUIRE(b.good() == true);
    REQUIRE(c.good() == true); //make sure good data returns true
    REQUIRE(d.good() == true);

    REQUIRE(f.good() == false); //make sure bad data returns false
    REQUIRE(g.good() == false);
}

TEST_CASE("set function", "[bitset]")
{
    Bitset b;

    REQUIRE(b.asString() == "00000000"); //progressively start setting entire array to 1's thorugh set function
    b.set(0);
    REQUIRE(b.asString() == "00000001");
    b.set(1);
    REQUIRE(b.asString() == "00000011");
    b.set(2);
    REQUIRE(b.asString() == "00000111");
    b.set(3);
    REQUIRE(b.asString() == "00001111");
    b.set(4);
    REQUIRE(b.asString() == "00011111");
    b.set(5);
    REQUIRE(b.asString() == "00111111");
    b.set(6);
    REQUIRE(b.asString() == "01111111");
    b.set(7);
    REQUIRE(b.asString() == "11111111");
    REQUIRE(b.good() == true); //make sure validity holds through entire array
    b.set(8);
    REQUIRE(b.good() == false); //make sure validity doesn't hold for N-1
}

TEST_CASE("reset function", "[bitset]")
{
    Bitset b("11111111"); //create a bitset of all 1's

    REQUIRE(b.asString() == "11111111"); //slowly set the array to zeros by placement
    b.reset(0);
    REQUIRE(b.asString() == "11111110");
    b.reset(1);
    REQUIRE(b.asString() == "11111100");
    b.reset(2);
    REQUIRE(b.asString() == "11111000");
    b.reset(3);
    REQUIRE(b.asString() == "11110000");
    b.reset(4);
    REQUIRE(b.asString() == "11100000");
    b.reset(5);
    REQUIRE(b.asString() == "11000000");

    REQUIRE(b.good() == true); //evaluate if the validity statement is functional
    b.reset(8);
    REQUIRE(b.good() == false);

}

TEST_CASE("test function", "[bitset]")
{
    Bitset b("000100"); //creates 2 objects, storing "000100" and "010000" string
    Bitset c("010010"); 

    REQUIRE(b.test(0) == false); //tests every bit of given string to make sure only the one spot where there is a one is true
    REQUIRE(b.test(1) == false);
    REQUIRE(b.test(2) == true);
    REQUIRE(b.test(3) == false);
    REQUIRE(b.test(4) == false);
    REQUIRE(b.test(5) == false);

    REQUIRE(c.test(0) == false); //tests every bit of given string to make sure only the two spots where there is a one is true
    REQUIRE(c.test(1) == true);
    REQUIRE(c.test(2) == false);
    REQUIRE(c.test(3) == false);
    REQUIRE(c.test(4) == true);
    REQUIRE(c.test(5) == false);

    REQUIRE(b.good() == true); //checks to ensure the validity statement within the function operates
    b.test(9);
    REQUIRE(b.good() == false);

}

TEST_CASE("Toggle Function")
{
    Bitset b("00000000"); //create an object full of 0's
    Bitset c("11111111"); //create an object full of 1's

    b.toggle(0);
    REQUIRE(b.asString() == "00000001"); //make sure that the 0 bitset toggles 0 bit
    b.toggle(0);
    REQUIRE(b.asString() == "00000000");

    b.toggle(3);
    REQUIRE(b.asString() == "00001000"); //make sure that the 0 bitset toggles a bit other than 0
    b.toggle(3);
    REQUIRE(b.asString() == "00000000");

    c.toggle(0);
    REQUIRE(c.asString() == "11111110"); //make sure that the 1 bitset toggles 0 bit
    c.toggle(0);
    REQUIRE(c.asString() == "11111111");

    c.toggle(3);
    REQUIRE(c.asString() == "11110111"); //make sure that the 1 bitset toggles a bit other than 0
    c.toggle(3);
    REQUIRE(c.asString() == "11111111");

    REQUIRE(b.good() == true); //evaluate if the validity statement works
    b.toggle(8);
    REQUIRE(b.good() == false);

    REQUIRE(c.good() == true);
    c.toggle(8);
    REQUIRE(c.good() == false);

}

TEST_CASE("string conversion function", "[bitset]")
{
    Bitset b("100010101"); //create an object of every different constructor
    Bitset c("1000000000001");
    Bitset d(3);
    Bitset e;

    REQUIRE(b.asString() == "100010101"); //test to make sure their intended values are returned as strings
    REQUIRE(c.asString() == "1000000000001");
    REQUIRE(d.asString() == "000");
    REQUIRE(e.asString() == "00000000");
}