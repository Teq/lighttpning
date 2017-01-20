#include "misc/string_buffer.h"
#include "exceptions/runtime_error.h"

#include "catch.hpp"

using namespace Lighttpning;

//SCENARIO("StringBuffer can be copy/move constructed/assigned and destructed properly") {}

SCENARIO("StringBuffer can change its capacity and size") {

    GIVEN("empty buffer with default (zero) capacity") {

        StringBuffer strbuff;

        REQUIRE(strbuff.size() == 0);
        REQUIRE(strbuff.capacity() == 0);

        WHEN("the size is increased") {

            size_t newSize = strbuff.size() + 1;

            strbuff.resize(newSize);

            THEN("the size increases, the capacity should be no less than size") {
                REQUIRE(strbuff.size() == newSize);
                REQUIRE(strbuff.capacity() >= newSize);
            }
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

    }

    GIVEN("empty buffer with capacity of N items") {

        const size_t N = 12;
        StringBuffer strbuff(N);

        REQUIRE(strbuff.size() == 0);
        REQUIRE(strbuff.capacity() >= N);

        WHEN("the size is increased") {

            AND_WHEN("new size <= capacity") {

                size_t capacity = strbuff.capacity();
                size_t newSize = N - 1;

                strbuff.resize(newSize);

                THEN("the size increases, the capacity stays the same") {
                    REQUIRE(strbuff.size() == newSize);
                    REQUIRE(strbuff.capacity() == capacity);
                }
            }

            AND_WHEN("new size > capacity") {

                size_t newSize = N + 1;

                strbuff.resize(newSize);

                THEN("the size increases, the capacity should be no less than size") {
                    REQUIRE(strbuff.size() == newSize);
                    REQUIRE(strbuff.capacity() >= newSize);
                }

            }

        }

        WHEN("the capacity is increased") {

            size_t newCapacity = N + 1;
            size_t size = strbuff.size();

            strbuff.reserve(newCapacity);

            THEN("the capacity increases, the size stays the same") {
                REQUIRE(strbuff.size() == size);
                REQUIRE(strbuff.capacity() == newCapacity);
            }
        }

        WHEN("the capacity is reduced") {

            size_t newCapacity = N - 1;
            size_t size = strbuff.size();

            strbuff.reserve(newCapacity);

            THEN("the capacity decreases, the size stays the same") {
                REQUIRE(strbuff.size() == size);
                REQUIRE(strbuff.capacity() == newCapacity);
            }

        }

    }

    GIVEN("non-empty buffer with capacity of N items") {

        const size_t N = 32;
        StringBuffer strbuff(N);

        REQUIRE(strbuff.capacity() == N);

        char cStr[] = "Hello world";
        size_t cStrSize = strlen(cStr);
        strbuff += cStr;

        REQUIRE(strbuff.size() == cStrSize);
        REQUIRE(strbuff.capacity() >= cStrSize);

        WHEN("the size is increased") {

            size_t capacity = strbuff.capacity();

            AND_WHEN("new size <= capacity") {

                size_t newSize = capacity - 1;

                strbuff.resize(newSize);

                THEN("the size increases, the capacity stays the same") {
                    REQUIRE(strbuff.size() == newSize);
                    REQUIRE(strbuff.capacity() == capacity);
                }
            }

            AND_WHEN("new size > capacity") {

                size_t newSize = capacity + 1;

                strbuff.resize(newSize);

                THEN("the size and capacity both increases") {
                    REQUIRE(strbuff.size() == newSize);
                    REQUIRE(strbuff.capacity() >= newSize);
                }

            }

        }

        WHEN("the size is reduced") {

            size_t capacity = strbuff.capacity();
            size_t newSize = strbuff.size() - 1;

            strbuff.resize(newSize);

            THEN("the size reduces, the capacity stays the same") {
                REQUIRE(strbuff.size() == newSize);
                REQUIRE(strbuff.capacity() == capacity);
            }

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

            size_t size = strbuff.size();

            AND_WHEN("new capacity >= size") {

                size_t newCapacity = size + 1;

                strbuff.reserve(newCapacity);

                THEN("the capacity decreases, the size stays the same") {
                    REQUIRE(strbuff.size() == size);
                    REQUIRE(strbuff.capacity() == newCapacity);
                }
            }


            AND_WHEN("new capacity < size") {

                size_t newCapacity = size - 1;

                strbuff.reserve(newCapacity);

                THEN("the size and capacity both decreases") {
                    REQUIRE(strbuff.size() == newCapacity);
                    REQUIRE(strbuff.capacity() == newCapacity);
                }
            }

        }

    }

}
