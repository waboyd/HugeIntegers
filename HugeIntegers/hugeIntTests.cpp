#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "UnsignedHugeInt.h"

//#include <iostream>

//TEST_CASE("Test Testing Framework", "Verify that the unit testing framework is working correctly.") {
//    std::cout << "Start of \"Test Testing Framework.\"\n";
//    REQUIRE(true);
//}

TEST_CASE("New Number", "Instantiate an UnsignedHugeInt with an unspecified value. Its value should be 0 before modification.") {
    UnsignedHugeInt newNumber;
    std::string valueString = newNumber.to_string();
    REQUIRE(valueString == "0");
}