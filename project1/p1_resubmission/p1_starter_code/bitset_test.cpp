#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "bitset.hpp"

// THIS IS JUST AN EXAMPLE
// There should be at least one test per Bitset method

TEST_CASE( "Test bitset construction", "[bitset]" ) 
{
    Bitset b;  
    REQUIRE(b.size() == 8);
    REQUIRE(b.good());
    REQUIRE(b.asString() == "00000000");

    Bitset a(20);
    REQUIRE(a.size() == 20);
    REQUIRE(a.good());
    REQUIRE(a.asString() == "00000000000000000000");

    Bitset c("1011");
    REQUIRE(c.size() == 4);
    REQUIRE(c.good());
    REQUIRE(c.asString() == "1011");
}

TEST_CASE("size", "[bitset]")
{
    Bitset b(10000);
    REQUIRE(b.size() == 10000);
    REQUIRE(b.good());

    Bitset c;
    REQUIRE(c.size() == 8);
    REQUIRE(c.good());

    Bitset d("1011101");
    REQUIRE(d.size() == 7);
    REQUIRE(d.good());
}

TEST_CASE("good", "[bitset]")
{
    Bitset b("10001");
    REQUIRE(b.good());

    Bitset c("1000300001");
    REQUIRE(c.good() == false); //fails by way of having a non 1/0 (3)

    b.set(0);
    REQUIRE(b.good());
    b.set(5);
    REQUIRE(b.good() == false);

    Bitset d(0);
    REQUIRE(d.good() == false);

    Bitset e;
    REQUIRE(e.good());

    e.reset(7);
    REQUIRE(e.good());
    e.reset(8);
    REQUIRE(e.good() == false);

    Bitset f;
    REQUIRE(f.good());

    f.set(7);
    REQUIRE(f.good());
    f.set(8);
    REQUIRE(f.good() == false);

    Bitset g;
    REQUIRE(g.good());

    g.toggle(7);
    REQUIRE(g.good());
    g.toggle(8);
    REQUIRE(g.good() == false);
}

TEST_CASE("set", "[bitset]")
{
    Bitset b;
    REQUIRE(b.good());
    REQUIRE(b.size() == 8);
    REQUIRE(b.asString() == "00000000");

    b.set(0);
    REQUIRE(b.asString() == "10000000");
    REQUIRE(b.good());
    b.set(1);
    REQUIRE(b.asString() == "11000000");
    REQUIRE(b.good());
    b.set(2);
    REQUIRE(b.asString() == "11100000");
    REQUIRE(b.good());
    b.set(3);
    REQUIRE(b.asString() == "11110000");
    REQUIRE(b.good());
    b.set(4);
    REQUIRE(b.asString() == "11111000");
    REQUIRE(b.good());
    b.set(5);
    REQUIRE(b.asString() == "11111100");
    REQUIRE(b.good());
    b.set(6);
    REQUIRE(b.asString() == "11111110");
    REQUIRE(b.good());
    b.set(7);
    REQUIRE(b.asString() == "11111111");
    REQUIRE(b.good());

    b.set(8);
    REQUIRE(b.good() == false);
}

TEST_CASE("reset", "[bitset]")
{
    Bitset b("11111111");
    REQUIRE(b.good());
    REQUIRE(b.size() == 8);
    REQUIRE(b.asString() == "11111111");

    b.reset(0);
    REQUIRE(b.asString() == "01111111");
    REQUIRE(b.good());
    b.reset(1);
    REQUIRE(b.asString() == "00111111");
    REQUIRE(b.good());
    b.reset(2);
    REQUIRE(b.asString() == "00011111");
    REQUIRE(b.good());
    b.reset(3);
    REQUIRE(b.asString() == "00001111");
    REQUIRE(b.good());
    b.reset(4);
    REQUIRE(b.asString() == "00000111");
    REQUIRE(b.good());
    b.reset(5);
    REQUIRE(b.asString() == "00000011");
    REQUIRE(b.good());
    b.reset(6);
    REQUIRE(b.asString() == "00000001");
    REQUIRE(b.good());
    b.reset(7);
    REQUIRE(b.asString() == "00000000");
    REQUIRE(b.good());

    b.reset(8);
    REQUIRE(b.good() == false);
}

TEST_CASE("toggle", "[bitset]")
{
    Bitset b("11110000");
    REQUIRE(b.good());
    REQUIRE(b.size() == 8);
    REQUIRE(b.asString() == "11110000");

    b.toggle(0);
    b.toggle(1);
    b.toggle(2);
    b.toggle(3);
    b.toggle(4);
    b.toggle(5);
    b.toggle(6);
    b.toggle(7);
    REQUIRE(b.good());

    REQUIRE(b.asString() == "00001111");

    b.toggle(8);
    REQUIRE(b.good() == false);
}

TEST_CASE("test", "[bitset]")
{
    Bitset b("11110000");

    for(intmax_t i = 0; i < 4; i++)
    {
        REQUIRE(b.test(i));
    }

    for(intmax_t i = 4; i < 8; i++)
    {
        REQUIRE(b.test(i) == false);
    }
}

TEST_CASE("asString", "[bitset]")
{
    Bitset b("1000000000000001000000001011010100100100001110010");
    REQUIRE(b.asString() == "1000000000000001000000001011010100100100001110010");

    Bitset c;
    REQUIRE(c.asString() == "00000000");

    Bitset d(13);
    REQUIRE(d.asString() == "0000000000000");
}

