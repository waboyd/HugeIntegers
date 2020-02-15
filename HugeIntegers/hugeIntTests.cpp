#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "UnsignedHugeInt.h"

//#include <iostclTabCtrlream>

//TEST_CASE("Test Testing Framework", "Verify that the unit testing framework is working correctly.") {
////    std::cout << "Start of \"Test Testing Framework.\"\n";
////    REQUIRE(true);
////    UnsignedHugeInt x(((long)12345));
////    x = x + 1;
//
//    std::string divisorString = "";
//    std::string quotientString = "";
//    std::string remainderString = "";
//    UnsignedHugeInt divisor(divisorString), quotient(quotientString), remainder(remainderString);
//    UnsignedHugeInt dividend = (divisor * quotient) + remainder;
//    std::cout << "------------------------------------------------------------------------------------------------\n";
//    std::cout << "dividend: " << dividend.to_string() << "\n";
//    std::cout << "divisor: " << divisor.to_string() << "\n";
//    std::cout << "quotient: " << quotient.to_string() << "\n";
//    std::cout << "remainder: " << remainder.to_string() << "\n";
//    std::cout << "------------------------------------------------------------------------------------------------\n";

//    int a(5);
//    int b = ++a;
//    int c = a++;
//    std::cout << "a: " << a << "\n";
//    std::cout << "b: " << b << "\n";
//    std::cout << "c: " << c << "\n";
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

TEST_CASE("Change Value Using int Assignment", "Declare an UnsignedHugeInt object, then change the value by setting it to an int.") {
    UnsignedHugeInt x("107096857973904791587293709587456899847878969002071");
    x = 884951;
    std::string expectedValueString = "884951";
    CHECK(expectedValueString == x.to_string());
}

TEST_CASE("Set Equal to String", "Change the value of an UnsignedHugeInt object by using the assignment to string operation.") {
    std::string value1 = "354064900797000673870687196";
    std::string value2 = "77987000354400898674339870116476073540893968707325846";
    std::string value3 = "7893404410970";
    UnsignedHugeInt x;
    x = value1;
    CHECK(value1 == x.to_string());
    x = value2;
    CHECK(value2 == x.to_string());
    x = value3;
    CHECK(value3 == x.to_string());
}

TEST_CASE("Compare With One Operand Much Greater",
        "Perform all comparson operations for a pair of UnsignedHugeInt objects when one object has more words.") {
    UnsignedHugeInt numberA("3265874619983746598176589680046549820036879412136564499741138444077167");
    UnsignedHugeInt numberB("709484635419812491349815318909401294408");
    CHECK_FALSE(numberA < numberB);
    CHECK_FALSE(numberA <= numberB);
    CHECK(numberA > numberB);
    CHECK(numberA >= numberB);
    CHECK_FALSE(numberA == numberB);
    CHECK(numberA != numberB);
    CHECK(numberB < numberA);
    CHECK(numberB <= numberA);
    CHECK_FALSE(numberB > numberA);
    CHECK_FALSE(numberB >= numberA);
    CHECK_FALSE(numberB == numberA);
    CHECK(numberB != numberA);    
}

TEST_CASE("Compare Objects With Same Number of Words",
        "Perform all comparson operations for a pair of UnsignedHugeInt objects with the same number of words.") {
    UnsignedHugeInt numberA("37109534108409873540189307182681");
    UnsignedHugeInt numberB("817438108799000000000706371072");
    CHECK_FALSE(numberA < numberB);
    CHECK_FALSE(numberA <= numberB);
    CHECK(numberA > numberB);
    CHECK(numberA >= numberB);
    CHECK_FALSE(numberA == numberB);
    CHECK(numberA != numberB);
    CHECK(numberB < numberA);
    CHECK(numberB <= numberA);
    CHECK_FALSE(numberB > numberA);
    CHECK_FALSE(numberB >= numberA);
    CHECK_FALSE(numberB == numberA);
    CHECK(numberB != numberA);    
}

TEST_CASE("Compare Objects With the Same Value",
        "Perform all comparson operations for a pair of UnsignedHugeInt objects with the same value.") {
    std::string numberString = "9494004840979843503518687978991321980948410165190760354984111097365448984139108";
    UnsignedHugeInt numberA(numberString);
    UnsignedHugeInt numberB(numberString);
    CHECK_FALSE(numberA < numberB);
    CHECK(numberA <= numberB);
    CHECK_FALSE(numberA > numberB);
    CHECK(numberA >= numberB);
    CHECK(numberA == numberB);
    CHECK_FALSE(numberA != numberB);
    CHECK_FALSE(numberB < numberA);
    CHECK(numberB <= numberA);
    CHECK_FALSE(numberB > numberA);
    CHECK(numberB >= numberA);
    CHECK(numberB == numberA);
    CHECK_FALSE(numberB != numberA);    
}

TEST_CASE("Compare unsigned long long And Larger UnsignedHugeInt",
        "Perform all comparson operations for an unsigned long long value and a larger UnsignedHugeInt object.") {
    UnsignedHugeInt numberA("6479194068395");
    unsigned long long numberB = 6479194068393;
    CHECK_FALSE(numberA < numberB);
    CHECK_FALSE(numberA <= numberB);
    CHECK(numberA > numberB);
    CHECK(numberA >= numberB);
    CHECK_FALSE(numberA == numberB);
    CHECK(numberA != numberB);
    CHECK(numberB < numberA);
    CHECK(numberB <= numberA);
    CHECK_FALSE(numberB > numberA);
    CHECK_FALSE(numberB >= numberA);
    CHECK_FALSE(numberB == numberA);
    CHECK(numberB != numberA);    
}

TEST_CASE("Compare int And Smaller UnsignedHugeInt",
        "Perform all comparson operations for an int value and an UnsignedHugeInt object with a lower value.") {
    UnsignedHugeInt numberA("8249348");
    int numberB = 8249351;
    CHECK(numberA < numberB);
    CHECK(numberA <= numberB);
    CHECK_FALSE(numberA > numberB);
    CHECK_FALSE(numberA >= numberB);
    CHECK_FALSE(numberA == numberB);
    CHECK(numberA != numberB);
    CHECK_FALSE(numberB < numberA);
    CHECK_FALSE(numberB <= numberA);
    CHECK(numberB > numberA);
    CHECK(numberB >= numberA);
    CHECK_FALSE(numberB == numberA);
    CHECK(numberB != numberA);    
}

TEST_CASE("Compare unsigned long And UnsignedHugeInt With the Same Value",
        "Perform all comparson operations for an unsigned long value and an UnsignedHugeInt object with the same value.") {
    unsigned long numberA = 3621974892;
    UnsignedHugeInt numberB(numberA);
    CHECK_FALSE(numberA < numberB);
    CHECK(numberA <= numberB);
    CHECK_FALSE(numberA > numberB);
    CHECK(numberA >= numberB);
    CHECK(numberA == numberB);
    CHECK_FALSE(numberA != numberB);
    CHECK_FALSE(numberB < numberA);
    CHECK(numberB <= numberA);
    CHECK_FALSE(numberB > numberA);
    CHECK(numberB >= numberA);
    CHECK(numberB == numberA);
    CHECK_FALSE(numberB != numberA);    
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
    UnsignedHugeInt *sum = new UnsignedHugeInt(numA + *numB);
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
    std::string expectedProductString = "32228950780226974593057211942781390313865679498337616";
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

TEST_CASE("Divide Zero Object by Object", "Divide 0 as an UnsignedHugeInt by another UnsignedHugeInt.") {
    UnsignedHugeInt dividendObject = UnsignedHugeInt((unsigned long long)0);
    std::string divisorString = "91246578687631435345469607980";
    UnsignedHugeInt divisorObject = UnsignedHugeInt(divisorString);
    UnsignedHugeInt quotientObject = dividendObject / divisorObject;
    UnsignedHugeInt remainderObject = dividendObject % divisorObject;
    REQUIRE("0" == quotientObject.to_string());
    REQUIRE("0" == remainderObject.to_string());
}

TEST_CASE("Divide Zero Int by Object", "Divide 0 as an int by an UnsignedHugeInt object.") {
    int dividend = 0;
    UnsignedHugeInt divisor("1256758579846981630625936093846");
    UnsignedHugeInt quotient = dividend / divisor;
    UnsignedHugeInt remainder = dividend % divisor;
    REQUIRE("0" == quotient.to_string());
    REQUIRE("0" == remainder.to_string());
}

TEST_CASE("Divide by 1 Object", "Divide an UnsignedHugeInt by the UnsignedHugeInt version of 1.") {
    std::string dividendString = "96934766113409766070714767322344";
    UnsignedHugeInt dividend(dividendString);
    UnsignedHugeInt divisor("1");
    UnsignedHugeInt quotientObject = dividend / divisor;
    UnsignedHugeInt remainderObject = dividend % divisor;
    REQUIRE(dividendString == quotientObject.to_string());
    REQUIRE("0" == remainderObject.to_string());
}

TEST_CASE("Divide UnsignedHugeInt by 1 Int", "Divide an UnsignedHugeInt object by 1 as an integer.") {
    std::string dividendString = "22567890200060487600000000000000";
    UnsignedHugeInt dividend(dividendString);
    int divisor = 1;
    UnsignedHugeInt quotientObject = dividend / divisor;
    UnsignedHugeInt remainderObject = dividend % divisor;
    REQUIRE(dividendString == quotientObject.to_string());
    REQUIRE("0" == remainderObject.to_string());    
}

TEST_CASE("Divide With same Dividend and Divisor", "Divide two UnsignedHugeInt objects with the same value.") {
    std::string operandString = "198763819403900679545367568744646131676873887094634981386498116873";
    UnsignedHugeInt dividendObject(operandString);
    UnsignedHugeInt divisorObject(operandString);
    UnsignedHugeInt quotientObject = dividendObject / divisorObject;
    UnsignedHugeInt remainderObject = dividendObject % divisorObject;
    REQUIRE("1" == quotientObject.to_string());
    REQUIRE("0" == remainderObject.to_string());
}

TEST_CASE("Divide With 1-Word Quotient and No Remainder", "Divide two 1-word UnsignedHugeInts to produce a 1-word quotient.") {
    UnsignedHugeInt dividend(28673604);
    UnsignedHugeInt divisor(387);
    std::string expectedQuotientString = "74092";
    std::string expectedRemainderString = "0";
    std::string quotientString = (dividend / divisor).to_string();
    std::string remainderString = (dividend % divisor).to_string();
    REQUIRE(expectedQuotientString == quotientString);
    REQUIRE(expectedRemainderString == remainderString);
}

TEST_CASE("Divide 2-Word and 1-Word Objects, No Remainder", "Divide a 2-word UnsignedHugeInt by a 1-word UnsignedHugeInt.") {
    UnsignedHugeInt dividend(269556227516770600);
    UnsignedHugeInt divisor(321205700);
    std::string expectedQuotientString = "839201258";
    std::string expectedRemainderString = "0";
    UnsignedHugeInt quotientObject = dividend / divisor;
    UnsignedHugeInt remainderObject = dividend % divisor;
    REQUIRE(expectedQuotientString == quotientObject.to_string());
    REQUIRE(expectedRemainderString == remainderObject.to_string());
}

TEST_CASE("Divide Multi-Word Objects, No Remainder",
        "Divide a multiple-word UnsignedHugeInt by a multiple-word UnsignedHugeInt, resulting in a one-word quotient with no remainder.") {
    UnsignedHugeInt dividend("12904057307347322110454551495483296564478");
    UnsignedHugeInt divisor("295903006877313987478812358644301");
    std::string expectedQuotientString = "43609078";
    std::string expectedRemainderString = "0";
    UnsignedHugeInt quotientObject = dividend / divisor;
    UnsignedHugeInt remainderObject = dividend % divisor;
    REQUIRE(expectedQuotientString == quotientObject.to_string());
    REQUIRE(expectedRemainderString == remainderObject.to_string());
}

TEST_CASE("Divide With Multiple Words 1, No Remainder",
        "Divide two UnsignedHugeInts with multiple words to give a multiple-word quotient and no remainder.") {
    UnsignedHugeInt dividend("135439923503930452938271612456790115876543210");
    UnsignedHugeInt divisor("33555555555");
    std::string expectedQuotientString = "4036289111111111000000000222222222";
    std::string expectedRemainderString = "0";
    UnsignedHugeInt quotientObject = dividend / divisor;
    UnsignedHugeInt remainderObject = dividend % divisor;
    REQUIRE(expectedQuotientString == quotientObject.to_string());
    REQUIRE(expectedRemainderString == remainderObject.to_string());
}

TEST_CASE("Divide With Multiple Words 2, No Remainder",
        "Divide two UnsignedHugeInts with multiple words to give a multiple-word quotient and no remainder.") {
    UnsignedHugeInt dividend("11111000011111222222222222222222000033333000000000666666666000022222000000000444444444");
    UnsignedHugeInt divisor("11111000000000222222222");
    std::string expectedQuotientString = "1000000001000000000000000000000000003000000000000000000000000002";
    std::string expectedRemainderString = "0";
    UnsignedHugeInt quotientObject = dividend / divisor;
    UnsignedHugeInt remainderObject = dividend % divisor;
    REQUIRE(expectedQuotientString == quotientObject.to_string());
    REQUIRE(expectedRemainderString == remainderObject.to_string());
}

TEST_CASE("Divide With Multiple Words 3, No Remainder",
        "Divide two UnsignedHugeInts with multiple words to give a multiple-word quotient and no remainder.") {
    UnsignedHugeInt dividend("303485162354901996800876009914666695076333848");
    UnsignedHugeInt divisor("3904882108479394735601");
    std::string expectedQuotientString = "77719417366247339025048";
    std::string expectedRemainderString = "0";
    UnsignedHugeInt quotientObject = dividend / divisor;
    UnsignedHugeInt remainderObject = dividend % divisor;
    REQUIRE(expectedQuotientString == quotientObject.to_string());
    REQUIRE(expectedRemainderString == remainderObject.to_string());
}

TEST_CASE("Divide UnsignedHugeInt by int, No Remainder",
        "Divide an UnsignedHugeInt object by an int with no remainder.") {
    UnsignedHugeInt dividend("32228950780226974593057211942781390313865679498337616");
    int divisor = 53;
    std::string expectedQuotientString = "608093410947678765906739847977007364412559990534672";
    std::string expectedRemainderString = "0";
    UnsignedHugeInt quotientObject = dividend / divisor;
    UnsignedHugeInt remainderObject = dividend % divisor;
    REQUIRE(expectedQuotientString == quotientObject.to_string());
    REQUIRE(expectedRemainderString == remainderObject.to_string());
}

TEST_CASE("Divide int by UnsignedHugeInt",
        "Divide an int by an UnsignedHugeInt object with a remainder.") {
    int dividend = 4146809;
    UnsignedHugeInt divisor("5822");
    std::string expectedQuotientString = "712";
    std::string expectedRemainderString = "1545";
    UnsignedHugeInt quotientObject = dividend / divisor;
    UnsignedHugeInt remainderObject = dividend % divisor;
    REQUIRE(expectedQuotientString == quotientObject.to_string());
    REQUIRE(expectedRemainderString == remainderObject.to_string());
}

TEST_CASE("Divide With Larger Divisor Than Dividend",
        "Divide UnsignedHugeInt objects with a dividend that is smaller than the divisor.") {
    std::string dividendString = "33710909407863207838429574";
    UnsignedHugeInt dividendObject(dividendString);
    UnsignedHugeInt divisorObject("20497935407798540156054654045863");
    std::string expectedQuotientString = "0";
    UnsignedHugeInt quotientObject = dividendObject / divisorObject;
    UnsignedHugeInt remainderObject = dividendObject % divisorObject;
    REQUIRE(expectedQuotientString == quotientObject.to_string());
    REQUIRE(dividendString == remainderObject.to_string());
}

TEST_CASE("Divide When Dividend Has Larger Leading Word",
        "Divide two multiple-word numbers when the dividend has a larger most significant word.") {
    UnsignedHugeInt dividend("34439523087848407030863994604698753459391024108814539914893647574670983");
    UnsignedHugeInt divisor("490835769086406957529787032881424");
    std::string expectedQuotientString = "70165063870448401116698903495822728293";
    std::string expectedRemainderString = "98401987043578500698735741751";
    UnsignedHugeInt quotient = dividend / divisor;
    UnsignedHugeInt remainder = dividend % divisor;
    REQUIRE(expectedQuotientString == quotient.to_string());
    REQUIRE(expectedRemainderString == remainder.to_string());
}

TEST_CASE("Divide With Equal Numbers of Words", "Divide when the dividend and divisor have the same number of words.") {
    UnsignedHugeInt dividend("65961407394495106412076083420039946078887226492362236931");
    UnsignedHugeInt divisor("21987135798165035468765405408737987053735409873871798741");
    std::string expectedQuotientString = "3";
    std::string expectedRemainderString = "5779867193825984917680996870746840708";
    UnsignedHugeInt quotient = dividend / divisor;
    UnsignedHugeInt remainder = dividend % divisor;
    REQUIRE(expectedQuotientString == quotient.to_string());
    REQUIRE(expectedRemainderString == remainder.to_string());
}

TEST_CASE("Divide When Dividend Has Smaller Leading Word",
        "Divide two multiple-word numbers when the divisor has a larger most significant word.") {
    
    UnsignedHugeInt dividend("5509821354912032618934356441443044776045079125139752582608797800812931419959231230851725532294994544766478795484040792889795167781390702");
    UnsignedHugeInt divisor("6554312049000133281882220402049873270410072549068031968389704");
    std::string expectedQuotientString = "840640682610246068368403846840542054725039972001140443335770549044287126981";
    std::string expectedRemainderString = "5407986409887025840698752784053370987408949870456968640387078";
    UnsignedHugeInt quotient = dividend / divisor;
    UnsignedHugeInt remainder = dividend % divisor;
    REQUIRE(expectedQuotientString == quotient.to_string());
    REQUIRE(expectedRemainderString == remainder.to_string());
}

TEST_CASE("Compound Addition of UnsignedHugeInt Object", "Use the += operator to add an UnsignedHugeInt object.") {
    UnsignedHugeInt x("453170093496799874983745234209856870938475309870189");
    UnsignedHugeInt y("3475029378098745343984760987340985709384894598731520938476849");
    std::string expectedSumString = "3475029378551915437481560862324730943594751469669996248347038";
    UnsignedHugeInt z = x += y;
    REQUIRE(expectedSumString == x.to_string());
    REQUIRE(expectedSumString == z.to_string());
}

TEST_CASE("Compound Addition of int", "Use the += operator to add an int to an UnsignedHugeInt.") {
    UnsignedHugeInt x("83450480039870687434908999574635");
    int y(824309);
    std::string expectedSumString = "83450480039870687434909000398944";
    UnsignedHugeInt z = x += y;
    REQUIRE(expectedSumString == x.to_string());
    REQUIRE(expectedSumString == z.to_string());    
}

TEST_CASE("Compound Subtraction of UnsignedHugeInt Object", "Use the -= operator to subtract an UnsignedHugeInt object.") {
    UnsignedHugeInt x("3475029378551915437481560862324730943594751469669996248347038");
    UnsignedHugeInt y("3475029378098745343984760987340985709384894598731520938476849");
    std::string expectedDifferenceString = "453170093496799874983745234209856870938475309870189";
    UnsignedHugeInt z = x -= y;
    REQUIRE(expectedDifferenceString == x.to_string());
    REQUIRE(expectedDifferenceString == z.to_string());
}

TEST_CASE("Compound Subtraction of int", "Use the -= operator to subtract an int from an UnsignedHugeInt.") {
    UnsignedHugeInt x("83450480039870687434909000398944");
    int y(824309);
    std::string expectedDifferenceString = "83450480039870687434908999574635";
    UnsignedHugeInt z = x -= y;
    REQUIRE(expectedDifferenceString == x.to_string());
    REQUIRE(expectedDifferenceString == z.to_string());    
}

TEST_CASE("Compound Multiplication of UnsignedHugeInt Object", "Use the *= operator to multiply UnsignedHugeInt objects.") {
    UnsignedHugeInt x("348906840332448298731088632654088404038");
    UnsignedHugeInt y("207340940496987406598409874");
    std::string expectedProductString = "72342672420362048481573680294368720190366115486890872873240671212";
    UnsignedHugeInt z = x *= y;
    REQUIRE(expectedProductString == x.to_string());
    REQUIRE(expectedProductString == z.to_string());
}

TEST_CASE("Compound Multiplication of int", "Use the *= operator to multiply an int by an UnsignedHugeInt.") {
    UnsignedHugeInt x("8071397034440481098522194019338068408749094");
    int y(98407);
    std::string expectedProductString = "794281967968184423462273546861001297899772093258";
    UnsignedHugeInt z = x *= y;
    REQUIRE(expectedProductString == x.to_string());
    REQUIRE(expectedProductString == z.to_string());        
}

TEST_CASE("Compound Integer Division of UnsignedHugeIntObject", "Use the /= operator to divide UnsignedHugeInt objects.") {
    UnsignedHugeInt x("22690029771660997484299435939247602551803671407171961949271");
    UnsignedHugeInt y("464065108316103871012683213940");
    std::string expectedQuotientString = "48894065434036885468779840680";
    UnsignedHugeInt z = x /= y;
    REQUIRE(expectedQuotientString == x.to_string());
    REQUIRE(expectedQuotientString == z.to_string());        
}

TEST_CASE("Compound Modulus Division of UnsignedHugeIntObject", "Use the %= operator to divide UnsignedHugeInt objects.") {
    UnsignedHugeInt x("22690029771660997484299435939247602551803671407171961949271");
    UnsignedHugeInt y("464065108316103871012683213940");
    std::string expectedRemainderString = "99403049840587217068406870071";
    UnsignedHugeInt z = x %= y;
    REQUIRE(expectedRemainderString == x.to_string());
    REQUIRE(expectedRemainderString == z.to_string());        
}

TEST_CASE("Compound Integer Division of int", "Use the /= operator to divide an UnsignedHugeInt object by an int.") {
    UnsignedHugeInt x("13660689041940378671300706945942857495386543");
    int y = 389084;
    std::string expectedQuotientString = "35109870984004427504859379840710122994";
    UnsignedHugeInt z = x /= y;
    REQUIRE(expectedQuotientString == x.to_string());
    REQUIRE(expectedQuotientString == z.to_string());            
}

TEST_CASE("Compound Modulus Division of int", "Use the %= operator to divide an UnsignedHugeInt object by an int.") {
    UnsignedHugeInt x("13660689041940378671300706945942857495386543");
    int y = 389084;
    std::string expectedRemainderString = "389047";
    UnsignedHugeInt z = x %= y;
    REQUIRE(expectedRemainderString == x.to_string());
    REQUIRE(expectedRemainderString == z.to_string());            
}

TEST_CASE("Increment Prefix With New Word Carry",
        "Use the ++ prefix operator to increment an UnsignedHugeInt object. A new word needs to be created for the resulting amount.") {
    UnsignedHugeInt x("999999999999999999999999999");
    std::string expectedResultString = "1000000000000000000000000000";
    UnsignedHugeInt y = ++x;
    REQUIRE(expectedResultString == x.to_string());
    REQUIRE(expectedResultString == y.to_string());
}

TEST_CASE("Increment Suffix With One Word Carry",
        "Use the ++ suffix operator to increment an UnsignedHugeInt object. An value must be carried across one word.") {
    std::string origValueString = "38403540471159079999999999";
    std::string expectedResultString = "38403540471159080000000000";
    UnsignedHugeInt x(origValueString);
    UnsignedHugeInt y = x++;
    REQUIRE(expectedResultString == x.to_string());
    REQUIRE(origValueString == y.to_string());
}

TEST_CASE("Decrement Prefix With Word Removal",
        "Use the -- prefix operator to decrement an UnsignedHugeInt object. A word needs to be removed from the resulting amount.") {
    UnsignedHugeInt x("1000000000000000000000000000");
    std::string expectedResultString = "999999999999999999999999999";
    UnsignedHugeInt y = --x;
    REQUIRE(expectedResultString == x.to_string());
    REQUIRE(x.num_words() == 3);
    REQUIRE(expectedResultString == y.to_string());
}

TEST_CASE("Decrement Suffix With One Word Carry",
        "Use the -- suffix operator to decrement an UnsignedHugeInt object. Some regrouping across words is required.") {
    std::string origValueString = "38403540471159080000000000";
    std::string expectedResultString = "38403540471159079999999999";
    UnsignedHugeInt x(origValueString);
    UnsignedHugeInt y = x--;
    REQUIRE(expectedResultString == x.to_string());
    REQUIRE(origValueString == y.to_string());
}

TEST_CASE("Memory Leak Check",
        "Check that the number of UnsignedHugeInt objects created is the same as the number of objects destroyed.") {
    UnsignedHugeInt::report_number_of_objects();
}