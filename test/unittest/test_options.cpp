#include "options.h"

#include "doctest.h"


TEST_CASE("Board has options of 1..9")
{
    Options const options;

    REQUIRE(options.options() == std::array{1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u});
}

TEST_CASE("Options initially contains values 1..9")
{
    Options options;

    REQUIRE(options.has(1u));
    REQUIRE(options.has(2u));
    REQUIRE(options.has(3u));
    REQUIRE(options.has(4u));
    REQUIRE(options.has(5u));
    REQUIRE(options.has(6u));
    REQUIRE(options.has(7u));
    REQUIRE(options.has(8u));
    REQUIRE(options.has(9u));
}

TEST_CASE("Fixing a value preserves it")
{
    Options options;

    options.fix(1u);

    REQUIRE(options.has(1u));
}

TEST_CASE("Fixing a value removes all other options")
{
    Options options;

    options.fix(1u);

    REQUIRE(!options.has(2u));
    REQUIRE(!options.has(3u));
    REQUIRE(!options.has(4u));
    REQUIRE(!options.has(5u));
    REQUIRE(!options.has(6u));
    REQUIRE(!options.has(7u));
    REQUIRE(!options.has(8u));
    REQUIRE(!options.has(9u));
}

TEST_CASE("Removing a value makes it removed")
{
    Options options;

    options.remove(1u);

    REQUIRE(!options.has(1u));
}

TEST_CASE("Removing a value preserves all other values")
{
    Options options;

    options.remove(1u);

    REQUIRE(options.has(2u));
    REQUIRE(options.has(3u));
    REQUIRE(options.has(4u));
    REQUIRE(options.has(5u));
    REQUIRE(options.has(6u));
    REQUIRE(options.has(7u));
    REQUIRE(options.has(8u));
    REQUIRE(options.has(9u));
}

TEST_CASE("Options is empty after removal of all values")
{
    Options options;

    options.remove(1u);
    options.remove(2u);
    options.remove(3u);
    options.remove(4u);
    options.remove(5u);
    options.remove(6u);
    options.remove(7u);
    options.remove(8u);
    options.remove(9u);

    REQUIRE(options.is_empty());
}

TEST_CASE("Options is fixed when it contains a single value")
{
    Options options;

    options.remove(2u);
    options.remove(3u);
    options.remove(4u);
    options.remove(5u);
    options.remove(6u);
    options.remove(7u);
    options.remove(8u);
    options.remove(9u);

    REQUIRE(options.is_fixed());
}
