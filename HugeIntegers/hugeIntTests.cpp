#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "UnsignedHugeInt.h"

//#include <iostream>

//TEST_CASE("Test Testing Framework", "Verify that the unit testing framework is working correctly.") {
//    std::cout << "Start of \"Test Testing Framework.\"\n";
//    REQUIRE(true);
//}

TEST_CASE("Blank Number", "Instantiate an UnsignedHugeInt with an unspecified value. Its value should be 0 before modification.") {
    UnsignedHugeInt newNumber;
    std::string valueString = newNumber.to_string();
    REQUIRE(valueString == "0");
}

TEST_CASE("Read Small Integer", "Instantiate an UnsignedHugeInt from an integer.") {
    int valueInt = 83;
//    std::string expectedString = std::to_string(valueInt);
    std::string expectedString = "83";
    UnsignedHugeInt *newNumber = new UnsignedHugeInt(valueInt);
    CHECK(expectedString == newNumber->to_string());
    delete(newNumber);
}

TEST_CASE("Read Large Integer", "Instantiate an UnsignedHugeInt from a long long integer.") {
    long long valueInt = 174506700476973203;
//    std::string expectedString = std::to_string(valueInt);
    std::string expectedString = "174506700476973203";
    UnsignedHugeInt *newNumber = new UnsignedHugeInt(valueInt);
    CHECK(expectedString == newNumber->to_string());
    delete(newNumber);
}

TEST_CASE("Read Zero String", "Instantiate an UnsignedHugeInt with a value of 0 from a string.") {
    std::string valueString = "0";
    UnsignedHugeInt *newNumber = new UnsignedHugeInt(valueString);
    CHECK(valueString == newNumber->to_string());
    delete(newNumber);
}

TEST_CASE("Read And Display Middle Zeros", "Instantiate an UnsignedHugeInt with many consecutive zeros in the middle place values.") {
    std::string valueString = "457760375299030000000000000000000000000000000000000000000589200347000000000000000000000000013";
    UnsignedHugeInt *newNumber = new UnsignedHugeInt(valueString);
    CHECK(valueString == newNumber->to_string());
    delete(newNumber);    
}

TEST_CASE("Read String With Extra Leading Zeros", "Instantiate an UnsignedHugeInt from a string with many extra leading zeros.") {
    std::string valueString = "8790582006700000";
    std::string inputString = "0000000000000000000000000000000" + valueString;
    UnsignedHugeInt *newNumber = new UnsignedHugeInt(inputString);
    CHECK(valueString == newNumber->to_string());
    delete(newNumber);
}

TEST_CASE("Read Very Long Number String", "Instantiate an UnsignedHugeInt from a number string with more than 500 digits.") {
//    std::string testString = "123" "456" "789";
//    std::cout << testString << "\n";
    std::string valueString =
        "76987112145678580852966410509967726809179346411100046467164386844187379451136687874455113894146219846543798465435145"
        "35416798604610498654654135410584968904546541034836489940997401132480551322222222222224087487063549840687353337884814"
        "78108987000000000084765409846543496841513456897745313143684968704137663878416467441222684981656754864201798465654218"
        "79879412318976854163875333325489416878951877788151651981310091894080519879851326687877212464561115154654876489733216"
        "54689774131655944513216456351356786745313256879121406150489018970913379894465478841213548462112121854943101546078631"
        "4984122697451005654";
    UnsignedHugeInt *newNumber = new UnsignedHugeInt(valueString);
    CHECK(valueString == newNumber->to_string());
    delete(newNumber);    
}

TEST_CASE("Copy UnsignedHugeInt From Object",
        "Make a copy of a multiple word UnsignedHugeInt. Check that the original is not changed after the copy.") {
    std::string valueString = "5035049874131000489735174198161536841357152630403";
    UnsignedHugeInt *origNumber = new UnsignedHugeInt(valueString);
    UnsignedHugeInt *copy = new UnsignedHugeInt(*origNumber);
    CHECK(valueString == copy->to_string());
    delete(copy);
    CHECK(valueString == origNumber->to_string());
    delete(origNumber);
}

TEST_CASE("Copy UnsignedHugeInt From Pointer",
        "Make a copy of a multiple word UnsignedHugeInt. Check that the original is not changed after the copy.") {
    std::string valueString = "4168768142106540151010354068402543681008084368374123086404534984";
    UnsignedHugeInt *origNumber = new UnsignedHugeInt(valueString);
    UnsignedHugeInt *copy = new UnsignedHugeInt(origNumber);
    CHECK(valueString == copy->to_string());
    delete(copy);
    CHECK(valueString == origNumber->to_string());
    delete(origNumber);
}

TEST_CASE("Multi-word Addition", "Add two multi-word integers instantiated in different ways.") {
    UnsignedHugeInt *numA = new UnsignedHugeInt("547890553345398741");
    UnsignedHugeInt numB(852109446654601259);
    std::string expectedSum = "1400000000000000000";
    UnsignedHugeInt *sumA;
    sumA = *numA + numB;
    REQUIRE(expectedSum == sumA->to_string());
    delete(numA);
    delete(sumA);
}

TEST_CASE("Add UnsignedHugeInt to Int", "Add an UnsignedHugeInt and an integer, with carry necessary between words.") {
    UnsignedHugeInt *numA = new UnsignedHugeInt("999999999999999962");
    int numB = 7539;
    std::string expectedSum = "1000000000000007501";
    UnsignedHugeInt *sum = *numA + numB;
    CHECK(expectedSum == sum->to_string());
    CHECK(3 == sum->num_words());   // For nine-digit words.
    delete(numA);
    delete(sum);
}

// ToDo: Add a method to add an int to an UnsignedHugeInt.
TEST_CASE("Add Int to UnsignedHugeInt", "Add an integer and an UnsignedHugeInt, with no carry necessary between words.") {
    int numA = 3644562;
    UnsignedHugeInt *numB = new UnsignedHugeInt("5480628615623433244512");
    std::string expectedSum = "5480628615623436889074";
    UnsignedHugeInt *sum = numA + *numB;
    CHECK(expectedSum == sum->to_string());
    CHECK(3 == sum->num_words());   // For nine-digit words.
    delete(numB);
    delete(sum);
}

