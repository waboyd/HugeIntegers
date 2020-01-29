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
    UnsignedHugeInt sumA;
    sumA = *numA + numB;
    CHECK(expectedSum == sumA.to_string());
    delete(numA);
}

TEST_CASE("Add UnsignedHugeInt to Int", "Add an UnsignedHugeInt and an integer, with carry necessary between words.") {
    UnsignedHugeInt numA("999999999999999962");
    int numB = 7539;
    std::string expectedSum = "1000000000000007501";
    UnsignedHugeInt sum = numA + numB;
    CHECK(expectedSum == sum.to_string());
    CHECK(3 == sum.num_words());   // For nine-digit words.
}

TEST_CASE("Add Int to UnsignedHugeInt", "Add an integer and an UnsignedHugeInt, with no carry necessary between words.") {
    int numA = 3644562;
    UnsignedHugeInt *numB = new UnsignedHugeInt("5480628615623433244512");
    std::string expectedSum = "5480628615623436889074";
    UnsignedHugeInt *sum = &(numA + *numB);
    CHECK(expectedSum == sum->to_string());
    CHECK(3 == sum->num_words());   // For nine-digit words.
    delete(numB);
    delete(sum);
}

TEST_CASE("Add With Varied Numbers of Words", "Add two UnsignedHugeInts with different numbers of words and necessary carrying.") {
    UnsignedHugeInt numA("9463748");
    UnsignedHugeInt numB("65801648904710984337546947096703984713998974374");
    std::string expectedSum = "65801648904710984337546947096703984714008438122";
    UnsignedHugeInt sum = numA + numB;
    std::string resultString = sum.to_string();
    REQUIRE(expectedSum == resultString);
}

TEST_CASE("Subtract Without Carry", "Subtract two UnsignedHugeInt objects without carrying or borrowing across words.") {
    UnsignedHugeInt numA("84403664049843549840495215515");
    UnsignedHugeInt numB("16210648974686451687432164471");
    std::string expectedString = "68193015075157098153063051044";
    UnsignedHugeInt difference;
    difference = numA - numB;
    REQUIRE(expectedString == difference.to_string());
}

TEST_CASE("Subtract With Carry", "Subtract two UnsignedHugeInt objects with some carrying across words.") {
    UnsignedHugeInt numA("5019403549065430584450601215460980497032190");
    UnsignedHugeInt numB("2040654687703684065068703687401144948904977");
    std::string expectedString = "2978748861361746519381897528059835548127213";
    UnsignedHugeInt difference = numA - numB;
    REQUIRE(expectedString == difference.to_string());
}

TEST_CASE("Subtract With Different Numbers of Words",
        "Subtract two UnsignedHugeInt objects with a large difference in the numbers of digits.") {
    UnsignedHugeInt numA("1139879984065103680435106871424205414004504254541");
    UnsignedHugeInt numB("987904190075610");
    std::string expectedString = "1139879984065103680435106871424204426100314178931";
    UnsignedHugeInt difference = numA - numB;
    REQUIRE(expectedString == difference.to_string());
}

TEST_CASE("Subtract Integer From UnsignedHugeInt", "Subtract an UnsignedHugeInt and an integer.") {
    UnsignedHugeInt numA("49804510321988733554126");
    unsigned long long numB = 298743419894698443;
    std::string expectedString = "49804211578568838855683";
    UnsignedHugeInt difference = numA - numB;
    REQUIRE(expectedString == difference.to_string());
}

TEST_CASE("Subtract UnsignedHugeInt from Integer", "Subtract an integer and an UnsignedHugeInt.") {
    unsigned long numA = 964388135;
    UnsignedHugeInt numB("8106354");
    std::string expectedString = "956281781";
    UnsignedHugeInt difference = numA - numB;
    REQUIRE(expectedString == difference.to_string());    
}

TEST_CASE("Multiply by Zero Object", "Multiply an UnsignedHugeInt by the UnsignedHugeInt version of 0.") {
    std::string factorAString = "91246578687631435345469607980";
    UnsignedHugeInt factorA(factorAString);
    UnsignedHugeInt factorB("0");
    UnsignedHugeInt productObject = factorA * factorB;
    REQUIRE("0" == productObject.to_string());
}

TEST_CASE("Multiply by Zero Int", "Multiply an UnsignedHugeInt by the unsigned long long version of 0.") {
    UnsignedHugeInt factorA("1256758579846981630625936093846");
    int factorB = 0;
    UnsignedHugeInt productObject = factorA * factorB;
    REQUIRE("0" == productObject.to_string());
}

TEST_CASE("Multiply by 1 Object", "Multiply an UnsignedHugeInt by the UnsignedHugeInt version of 1.") {
    std::string factorAString = "96934766113409766070714767322344";
    UnsignedHugeInt factorA(factorAString);
    UnsignedHugeInt factorB("1");
    UnsignedHugeInt productObject = factorA * factorB;
    REQUIRE(factorAString == productObject.to_string());
}

TEST_CASE("Multiply 1 Int by UnsignedHugeInt", "Multiply 1 as an integer by an UnsignedHugeInt object.") {
    std::string factorBString = "22567890200060487600000000000000";
    int factorA = 1;
    UnsignedHugeInt factorB(factorBString);
    UnsignedHugeInt productObject = factorA * factorB;
    REQUIRE(factorBString == productObject.to_string());
    
}

TEST_CASE("Multiply With 1-Word Product", "Multiply two 1-word UnsignedHugeInts to produce a 1-word product.") {
    UnsignedHugeInt factorA(387);
    UnsignedHugeInt factorB(74092);
    std::string expectedProductString = "28673604";
    std::string productString = (factorA * factorB).to_string();
    REQUIRE(expectedProductString == productString);
}

TEST_CASE("Multiply Single-Word UnsignedHugeInts", "Multiply two 1-word UnsignedHugeInts to produce a two-word product.") {
    UnsignedHugeInt factorA(839201258);
    UnsignedHugeInt factorB(321205700);
    std::string expectedProductString = "269556227516770600";
    UnsignedHugeInt productObject = factorA * factorB;
    REQUIRE(expectedProductString == productObject.to_string());
}

TEST_CASE("Multiply With One Multi-Word UnsignedHugeInt",
        "Multiply a single-word UnsignedHugeInt by a multiple-word UnsignedHugeInt.") {
    UnsignedHugeInt factorA(43609078);
    UnsignedHugeInt factorB("295903006877313987478812358644301");
    std::string expectedProductString = "12904057307347322110454551495483296564478";
    UnsignedHugeInt productObject = factorA * factorB;
    REQUIRE(expectedProductString == productObject.to_string());    
}

TEST_CASE("Multiply With Multiple Words 1",
        "Multiply two UnsignedHugeInts with multiple words. The first factor has more words than the second.") {
    UnsignedHugeInt factorA("4036289111111111000000000222222222");
    UnsignedHugeInt factorB("33555555555");
    std::string expectedProductString = "135439923503930452938271612456790115876543210";
    UnsignedHugeInt productObject = factorA * factorB;
    REQUIRE(expectedProductString == productObject.to_string());    
}

TEST_CASE("Multiply With Multiple Words 2",
        "Multiply two UnsignedHugeInts with multiple words. The first factor has fewer words than the second.") {
    UnsignedHugeInt factorA("11111000000000222222222");
    UnsignedHugeInt factorB("1000000001000000000000000000000000003000000000000000000000000002");
    std::string expectedProductString = "11111000011111222222222222222222000033333000000000666666666000022222000000000444444444";
    UnsignedHugeInt productObject = factorA * factorB;
    REQUIRE(expectedProductString == productObject.to_string());
    
}

TEST_CASE("Multiply With Multiple Words 3",
        "Multiply two UnsignedHugeInts with multiple words. The two factors have the same number of words.") {
    UnsignedHugeInt factorA("3904882108479394735601"), factorB("77719417366247339025048");
    UnsignedHugeInt resultProduct;
    std::string expectedProductString = "303485162354901996800876009914666695076333848";
    resultProduct = factorA * factorB;
    REQUIRE(expectedProductString == resultProduct.to_string());
}

TEST_CASE("Multiply Int by UnsignedHugeInt",
        "Multiply with an int as the first factor and an UnsignedHugeInt as the second factor.") {
    int factorA = 53;
    UnsignedHugeInt factorB("608093410947678765906739847977007364412559990534672");
    std::string expectedProductString = "32228950780226974593057211942‬781390313865679498337616";
    UnsignedHugeInt productObject = factorA * factorB;
    REQUIRE(expectedProductString == productObject.to_string());    
}

TEST_CASE("Multiply UnsignedHugeInt by Int",
        "Multiply with an UnsignedHugeInt as the first factor and an int as the second factor.") {
    UnsignedHugeInt factorA("7586700304178956891");
    int factorB = 2739;
    std::string expectedProductString = "20779972133146162924449";
    UnsignedHugeInt productObject = factorA * factorB;
    REQUIRE(expectedProductString == productObject.to_string());        
}
