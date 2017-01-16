#include "misc/string_buffer.h"
#include "exceptions/runtime_error.h"

#include "catch.hpp"

using namespace Lighttpning;

//SCENARIO("StringBuffer can be copy/move constructed/assigned and destructed properly") {}

SCENARIO("StringBuffer can change capacity and size") {

    auto CAN_HANDLE_CAPACITY_AND_SIZE_CHANGES = [](StringBuffer& strbuff) {

        REQUIRE(strbuff.size() <= strbuff.capacity());

        WHEN("the size is increased") {

            AND_WHEN("new size <= capacity") {

                size_t capacity = strbuff.capacity();
                size_t newSize = strbuff.size() + 1;

                if (newSize <= capacity) {

                    strbuff.resize(newSize);

                    THEN("the size increases, the capacity stays the same") {
                        REQUIRE(strbuff.size() == newSize);
                        REQUIRE(strbuff.capacity() == capacity);
                    }

                } // else not applicable
            }

            AND_WHEN("new size > capacity") {

                size_t newSize = strbuff.capacity() + 1;

                strbuff.resize(newSize);

                THEN("the size and capacity both increases") {
                    REQUIRE(strbuff.size() == newSize);
                    REQUIRE(strbuff.capacity() >= newSize);
                }

            }

        }

        WHEN("the size is reduced") {

            size_t capacity = strbuff.capacity();
            size_t size = strbuff.size();

            if (size > 0) {

                size_t newSize = size - 1;
                strbuff.resize(newSize);

                THEN("the size reduces, the capacity stays the same") {
                    REQUIRE(strbuff.size() == newSize);
                    REQUIRE(strbuff.capacity() == capacity);
                }

            } // else not applicable

        }

        WHEN("the capacity is increased") {

            size_t newCapacity = strbuff.capacity() + 1;
            size_t size = strbuff.size();

            strbuff.reserve(newCapacity);

            THEN("the capacity increases, the size stays the same") {
                REQUIRE(strbuff.size() == size);
                REQUIRE(strbuff.capacity() == newCapacity);
            }
        }

        WHEN("the capacity is reduced") {

            size_t capacity = strbuff.capacity();
            size_t size = strbuff.size();

            if (capacity > 0) {

                size_t newCapacity = capacity - 1;

                if (newCapacity >= size) {

                    AND_WHEN("new capacity >= size") {

                        strbuff.reserve(newCapacity);

                        THEN("the capacity decreases, the size stays the same") {
                            REQUIRE(strbuff.size() == size);
                            REQUIRE(strbuff.capacity() == newCapacity);
                        }
                    }

                } // else not applicable

                if (size > 0) {

                    newCapacity = size - 1;

                    AND_WHEN("new capacity < size") {

                        strbuff.reserve(newCapacity);

                        THEN("the size and capacity both decreases") {
                            REQUIRE(strbuff.size() == newCapacity);
                            REQUIRE(strbuff.capacity() == newCapacity);
                        }
                    }

                } // else not applicable

            } // else not applicable

        }

    };

    GIVEN("empty buffer with default (zero) capacity") {

        StringBuffer strbuff;

        REQUIRE(strbuff.size() == 0);
        REQUIRE(strbuff.capacity() == 0);
        REQUIRE(strbuff.buff() == nullptr);

        CAN_HANDLE_CAPACITY_AND_SIZE_CHANGES(strbuff);
    }

    GIVEN("empty buffer with capacity of N items") {

        const size_t N = 12;
        StringBuffer strbuff(N);

        REQUIRE(strbuff.size() == 0);
        REQUIRE(strbuff.capacity() >= N);
        REQUIRE(strbuff.buff() != nullptr);

        CAN_HANDLE_CAPACITY_AND_SIZE_CHANGES(strbuff);
    }

    GIVEN("non-empty buffer") {

        StringBuffer strbuff;
        char cStr[] = "Hello world";
        size_t cStrLen = strlen(cStr);
        strbuff += cStr;

        REQUIRE(strbuff.size() == cStrLen);
        REQUIRE(strbuff.capacity() >= cStrLen);
        REQUIRE(strbuff.buff() != nullptr);

        CAN_HANDLE_CAPACITY_AND_SIZE_CHANGES(strbuff);
    }

}
