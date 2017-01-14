#include "misc/string_buffer.h"

#include "catch.hpp"

using namespace Lighttpning;

SCENARIO("StringBuffer can be sized and resized") {
    GIVEN("StringBuffer with N items") {
        StringBuffer strbuff(12);

        REQUIRE(strbuff.size() == 0);
        REQUIRE(strbuff.capacity() >= 12);

        WHEN("the size is increased") {
            strbuff.resize(20);
            THEN("the size and capacity change") {
                REQUIRE(strbuff.size() == 20);
                REQUIRE(strbuff.capacity() >= 20);
            }

        }

        WHEN("the size is reduced") {}
        WHEN("the capacity is increased") {}
        WHEN("the capacity is reduced") {}

    }
}
