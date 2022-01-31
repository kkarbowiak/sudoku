#include "options.h"

#include "doctest.h"


TEST_CASE("Options initially contains values 1..9")
{
    Options options;

    REQUIRE(options.has(1));
    REQUIRE(options.has(2));
    REQUIRE(options.has(3));
    REQUIRE(options.has(4));
    REQUIRE(options.has(5));
    REQUIRE(options.has(6));
    REQUIRE(options.has(7));
    REQUIRE(options.has(8));
    REQUIRE(options.has(9));
}

TEST_CASE("Fixing a value preserves it")
{
    Options options;

    options.fix(1);

    REQUIRE(options.has(1));
}

TEST_CASE("Fixing a value removes all other options")
{
    Options options;

    options.fix(1);

    REQUIRE(!options.has(2));
    REQUIRE(!options.has(3));
    REQUIRE(!options.has(4));
    REQUIRE(!options.has(5));
    REQUIRE(!options.has(6));
    REQUIRE(!options.has(7));
    REQUIRE(!options.has(8));
    REQUIRE(!options.has(9));
}

TEST_CASE("Removing a value makes it removed")
{
    Options options;

    options.remove(1);

    REQUIRE(!options.has(1));
}

TEST_CASE("Removing a value preserves all other values")
{
    Options options;

    options.remove(1);

    REQUIRE(options.has(2));
    REQUIRE(options.has(3));
    REQUIRE(options.has(4));
    REQUIRE(options.has(5));
    REQUIRE(options.has(6));
    REQUIRE(options.has(7));
    REQUIRE(options.has(8));
    REQUIRE(options.has(9));
}

TEST_CASE("Options is empty after removal of all values")
{
    Options options;

    options.remove(1);
    options.remove(2);
    options.remove(3);
    options.remove(4);
    options.remove(5);
    options.remove(6);
    options.remove(7);
    options.remove(8);
    options.remove(9);

    REQUIRE(options.is_empty());
}

TEST_CASE("Options is fixed when it contains a single value")
{
    Options options;

    options.remove(2);
    options.remove(3);
    options.remove(4);
    options.remove(5);
    options.remove(6);
    options.remove(7);
    options.remove(8);
    options.remove(9);

    REQUIRE(options.is_fixed());
}
