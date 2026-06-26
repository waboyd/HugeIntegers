/*  Test cases for the base 2 implementation of UnsignedHugeInt library.
    These test cases all depend on the Catch2 test framework.
    These test cases were created when the word base was changed from a power
    of 10 to a power of 2. These are created to test for edge cases with the
    changed implementation.
    The older test cases in the file hugeIntTests.cpp should continue to pass.
    The UnsignedHugeInt library and these test cases were created by William Boyd.
*/

#include <random>
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_get_random_seed.hpp>

#define HUGE_INT_WORD_BASE          4294967296
#define HUGE_INT_MAX_WORD_VALUE     4294967295

#include "UnsignedHugeInt.h"

const char test_folder_path[] = "../TestFiles/";

// Creates an UnsignedHugeInt with the specified number of words and a random value.
UnsignedHugeInt randomHugeInt(unsigned long num_words) {
    std::uint32_t catchSeed = Catch::getSeed();
    std::mt19937 randGen(catchSeed);
    std::uniform_int_distribution<unsigned long> longGenerator(0, HUGE_INT_MAX_WORD_VALUE);

    // Setting the most significant word of each addend.
    unsigned long wordValue(longGenerator(randGen));
    if (wordValue == 0)
        wordValue = HUGE_INT_MAX_WORD_VALUE;
    UnsignedHugeInt resultHugeInt(wordValue);

    // Setting the remaining words of each addend.
    for (unsigned long wordNum = 1; wordNum < num_words; ++wordNum) {
        wordValue = longGenerator(randGen);
        resultHugeInt *= HUGE_INT_WORD_BASE;
        resultHugeInt += wordValue;
    }
    return resultHugeInt;
}

TEST_CASE("Instantiate Value With Many Central Zero Bits",
            "Instantiate an UnsignedHugeInt with many consecutive zeros in the middle bits.") {
    std::string valueString = "3246626956972881084445";
    UnsignedHugeInt *newNumber = new UnsignedHugeInt(valueString);
    CHECK(valueString == newNumber->to_string());
    delete(newNumber);
}

TEST_CASE("Write And Read Value With Many Zero Bits",
            "Write a multi-word UnsignedHugeInt to a text file and a binary file, with some words having a value of 0, then read the value from the file.") {
    // Making an UnsignedHugeInt with middle words with value of 0.
    UnsignedHugeInt x(14624);
    x *= HUGE_INT_WORD_BASE;
    x *= HUGE_INT_WORD_BASE;
    x *= HUGE_INT_WORD_BASE;
    x *= HUGE_INT_WORD_BASE;
    x += 17;
    std::string origNumberString = x.to_string();

    char textFilePath[70];
    strcpy(textFilePath, test_folder_path);
    strcat(textFilePath, "tempBinTestFile1.txt");

    // The file will be deleted if it already existed before the test.
    remove(textFilePath);

    // Use the write_to_text_file method to write the number to a text file.'
    x.write_to_text_file(textFilePath);

    // Read the text file and compare its text to the expected string.
    FILE *readTextFile = fopen(textFilePath, "r");
    char readBuffer[101];
    char digitBuffer[101];
    unsigned int numCharsRead;
    unsigned int readCharIndex, digitCharIndex;
    std::string stringFromTextFile = "";
    numCharsRead = fread(readBuffer, sizeof(char), 100, readTextFile);
    while(numCharsRead > 0) {
        // Take only the digits from the read buffer to create the digit buffer.
        digitCharIndex = 0;
        for (readCharIndex = 0; readCharIndex < numCharsRead; ++readCharIndex) {
            if (isdigit(readBuffer[readCharIndex])) {
                digitBuffer[digitCharIndex] = readBuffer[readCharIndex];
                ++digitCharIndex;
            }
        }
        digitBuffer[digitCharIndex] = '\0';
        // Attach the digit buffer to the string from the file.
        stringFromTextFile += std::string(digitBuffer);
        // Read more from the file.
        numCharsRead = fread(readBuffer, sizeof(char), 100, readTextFile);
    }
    fclose(readTextFile);
    REQUIRE(origNumberString == stringFromTextFile);

    // Test of reading the text file using the class function.
    UnsignedHugeInt textFileInt;
    textFileInt.read_from_text_file(textFilePath);
    REQUIRE(origNumberString == textFileInt.to_string());
    remove(textFilePath);

    // Testing writing and reading to a binary file.
    char binFilePath[70];
    strcpy(binFilePath, test_folder_path);
    strcat(binFilePath, "tempBinTestFile1.bin");
    remove(binFilePath);
    x.write_to_binary_file(binFilePath);

    UnsignedHugeInt binFileInt;
    binFileInt.read_from_binary_file(binFilePath);
    REQUIRE(origNumberString == binFileInt.to_string());
    remove(binFilePath);
}

TEST_CASE("Add UnsignedHugeInt to Int With Carry 32Bit", "Add an UnsignedHugeInt and an integer, with carry necessary between words.") {
    UnsignedHugeInt numA("18446744073709547443");
    int numB = 9224;
    std::string expectedSum = "18446744073709556667";
    UnsignedHugeInt sum = numA + numB;
    CHECK(expectedSum == sum.to_string());
}

TEST_CASE("Add Int to UnsignedHugeInt No Carry 32Bit", "Add an integer and an UnsignedHugeInt, with no carry necessary between words.") {
    int numA = 7478923;
    UnsignedHugeInt *numB = new UnsignedHugeInt("7498309386745986236700766201");
    std::string expectedSum = "7498309386745986236708245124";
    UnsignedHugeInt *sum = new UnsignedHugeInt(numA + *numB);
    CHECK(expectedSum == sum->to_string());
    delete(numB);
    delete(sum);
}

TEST_CASE("Add With Varied Numbers of Words 32Bit", "Add two UnsignedHugeInts with different numbers of words and necessary carrying.") {
    UnsignedHugeInt numA("5940276688849732346");
    UnsignedHugeInt numB("340077134980950716124611356782946210985589200856714857618");
    std::string expectedSum = "340077134980950716124611356782946210991529477545564589964";
    UnsignedHugeInt sum = numA + numB;
    std::string resultString = sum.to_string();
    REQUIRE(expectedSum == resultString);
}

TEST_CASE("Subtract Without Carry 32Bit", "Subtract two UnsignedHugeInt objects without carrying or borrowing across words.") {
    UnsignedHugeInt numA("3778406916379603647819349");
    UnsignedHugeInt numB("2098678934016151378793996");
    std::string expectedString = "1679727982363452269025353";
    UnsignedHugeInt difference;
    difference = numA - numB;
    REQUIRE(expectedString == difference.to_string());
}

TEST_CASE("Subtract With Carry 32Bit", "Subtract two UnsignedHugeInt objects with some carrying across words.") {
    UnsignedHugeInt numA("7499874551618242286487271");
    UnsignedHugeInt numB("7400572865197658486766329");
    std::string expectedString = "99301686420583799720942";
    UnsignedHugeInt difference = numA - numB;
    REQUIRE(expectedString == difference.to_string());
}

TEST_CASE("Increment Prefix With New Word Carry 32Bit",
        "Use the ++ prefix operator to increment an UnsignedHugeInt object. A new word needs to be created for the resulting amount.") {
    UnsignedHugeInt x("79228162514264337593543950335");
    std::string expectedResultString = "79228162514264337593543950336";
    UnsignedHugeInt y = ++x;
    REQUIRE(expectedResultString == x.to_string());
    REQUIRE(expectedResultString == y.to_string());
}

TEST_CASE("Increment Suffix With One Word Carry 32Bit",
        "Use the ++ suffix operator to increment an UnsignedHugeInt object. An value must be carried across one word.") {
    std::string origValueString = "93218479788427304747443747872500088831";
    std::string expectedResultString = "93218479788427304747443747872500088832";
    UnsignedHugeInt x(origValueString);
    UnsignedHugeInt y = x++;
    REQUIRE(expectedResultString == x.to_string());
    REQUIRE(origValueString == y.to_string());
}

TEST_CASE("Decrement Prefix With Word Removal 32Bit",
        "Use the -- prefix operator to decrement an UnsignedHugeInt object. A word needs to be removed from the resulting amount.") {
    UnsignedHugeInt x("79228162514264337593543950336");
    std::string expectedResultString = "79228162514264337593543950335";
    UnsignedHugeInt y = --x;
    REQUIRE(expectedResultString == x.to_string());
    REQUIRE(expectedResultString == y.to_string());
}

TEST_CASE("Decrement Suffix With One Word Carry 32Bit",
        "Use the -- suffix operator to decrement an UnsignedHugeInt object. Some regrouping across words is required.") {
    std::string origValueString = "93218479788427304747443747872500088832";
    std::string expectedResultString = "93218479788427304747443747872500088831";
    UnsignedHugeInt x(origValueString);
    UnsignedHugeInt y = x--;
    REQUIRE(expectedResultString == x.to_string());
    REQUIRE(origValueString == y.to_string());
}

TEST_CASE("Bitwise AND Between Huge Integers",
        "Perform a bitwise AND between two UnsignedHugeInt objects.") {
    UnsignedHugeInt x(3086491544);
    x *= 4294967296; x += 2770030562;
    x *= 4294967296; x += 195973469;
    UnsignedHugeInt y(5786902765);
    y *= 4294967296; y += 4109587345;
    y *= 4294967296; y += 1378486781;
    y *= 4294967296; y += 4286056106;

    std::string expectedResultString = "55997536345846770117456166920";
    REQUIRE(expectedResultString == (x & y).to_string());
    REQUIRE(expectedResultString == (y & x).to_string());
    REQUIRE(expectedResultString == (x &= y).to_string());
    REQUIRE(expectedResultString == x.to_string());
}

TEST_CASE("Bitwise AND With a Smaller Integer",
        "Perform a bitwise AND between an UnsignedHugeInt and a literal value.") {
    UnsignedHugeInt x(4064589063);
    x *= 4294967296; x += 3092847650;
    x *= 4294967296; x += 2786128765;
    x *= 4294967296; x += 3006617892;

    std::string expectedResultString = "148742145658917156";
    REQUIRE(expectedResultString == (x & 195749016596722022).to_string());
    REQUIRE(expectedResultString == (195749016596722022 & x).to_string());
    REQUIRE(expectedResultString == (x &= 195749016596722022).to_string());
    REQUIRE(expectedResultString == x.to_string());
}

TEST_CASE("Bitwise AND Between UnsignedHugeInts With Deleted Words",
        "Perform a bitwise AND between two UnsignedHugeInt objects that involves deleting the most significant words.") {
    UnsignedHugeInt x(619283830);
    x *= 4294967296; x += 1167598464;
    x *= 4294967296; x += 3461839506;
    UnsignedHugeInt y(2434157193);
    y *= 4294967296; y += 2988725329;
    y *= 4294967296; y += 2758002789;

    std::string expectedResultString = "2219001856";
    REQUIRE(expectedResultString == (x & y).to_string());
    REQUIRE(expectedResultString == (y & x).to_string());
    REQUIRE(expectedResultString == (x &= y).to_string());
    REQUIRE(expectedResultString == x.to_string());
}

TEST_CASE("Bitwise OR Between Huge Integers",
        "Perform a bitwise OR between two UnsignedHugeInt objects.") {
    UnsignedHugeInt x(4160063942);
    x *= 4294967296; x += 1056963321;
    x *= 4294967296; x += 3057012676;
    UnsignedHugeInt y(37690268);
    y *= 4294967296; y += 2047893631;
    y *= 4294967296; y += 2995471765;
    y *= 4294967296; y += 3077673828;

    std::string expectedResultString = "2986130757526146066064971105272586212";
    REQUIRE(expectedResultString == (x | y).to_string());
    REQUIRE(expectedResultString == (y | x).to_string());
    REQUIRE(expectedResultString == (x |= y).to_string());
    REQUIRE(expectedResultString == x.to_string());
}

TEST_CASE("Bitwise OR With a Smaller Integer",
        "Perform a bitwise OR between an UnsignedHugeInt and a literal value.") {
    UnsignedHugeInt x(1564228508);
    x *= 4294967296; x += 2047183850;
    x *= 4294967296; x += 3028875455;
    x *= 4294967296; x += 1036543592;

    std::string expectedResultString = "123930950479033110078028219340625280622";
    REQUIRE(expectedResultString == (x | 2157749616730429542).to_string());
    REQUIRE(expectedResultString == (2157749616730429542 | x).to_string());
    REQUIRE(expectedResultString == (x |= 2157749616730429542).to_string());
    REQUIRE(expectedResultString == x.to_string());
}

TEST_CASE("Bitwise XOR Between Huge Integers",
        "Perform a bitwise XOR between two UnsignedHugeInt objects.") {
    UnsignedHugeInt x(1371424049);
    x *= 4294967296; x += 4168949941;
    x *= 4294967296; x += 2064789873;
    UnsignedHugeInt y(2582067735);
    y *= 4294967296; y += 2001254484;
    y *= 4294967296; y += 3657213554;
    y *= 4294967296; y += 946751722;

    std::string expectedResultString = "204572482143477446110529366386087328155";
    REQUIRE(expectedResultString == (x ^ y).to_string());
    REQUIRE(expectedResultString == (y ^ x).to_string());
    REQUIRE(expectedResultString == (x ^= y).to_string());
    REQUIRE(expectedResultString == x.to_string());
}

TEST_CASE("Bitwise XOR With a Smaller Integer",
        "Perform a bitwise XOR between an UnsignedHugeInt and a literal value.") {
    UnsignedHugeInt x(2218065611);
    x *= 4294967296; x += 950024177;
    x *= 4294967296; x += 1332099528;
    x *= 4294967296; x += 3322960329;

    std::string expectedResultString = "175733262713133877041631126895603376573";
    REQUIRE(expectedResultString == (x ^ 1056788256052885620).to_string());
    REQUIRE(expectedResultString == (1056788256052885620 ^ x).to_string());
    REQUIRE(expectedResultString == (x ^= 1056788256052885620).to_string());
    REQUIRE(expectedResultString == x.to_string());
}

TEST_CASE("Bitwise XOR Between UnsignedHugeInts With Deleted Words",
        "Perform a bitwise XOR between two UnsignedHugeInt objects that involves deleting the most significant words.") {
    UnsignedHugeInt x(4077794742);
    x *= 4294967296; x += 3721940497;
    x *= 4294967296; x += 2745172045;
    UnsignedHugeInt y(4077794742);
    y *= 4294967296; y += 3721940497;
    y *= 4294967296; y += 3929910533;

    unsigned long expectedResult = 1235070280;
    REQUIRE(expectedResult == (x ^ y));
    REQUIRE(expectedResult == (y ^ x));
    REQUIRE(expectedResult == (x ^= y));
    REQUIRE(expectedResult == x);
}

TEST_CASE("Bit Shift Left Multiple Words",
        "Do a bitwise left shift that requires the addition of multiple words.") {
    UnsignedHugeInt x(11760445202119584);
    UnsignedHugeInt y = x << 76;
    std::string expectedResultString = "888594115937834459493453944637225959424";
    REQUIRE(expectedResultString == y.to_string());
    REQUIRE(expectedResultString == (x <<= 76).to_string());
    REQUIRE(expectedResultString == x.to_string());
}

TEST_CASE("Bit Shift Left Less Than One Word",
        "Do a left shift by fewer bits than a word size.") {
    UnsignedHugeInt x(3189496001646783569);
    UnsignedHugeInt y = x << 7;
    std::string expectedResultString = "408255488210788296832";
    REQUIRE(expectedResultString == y.to_string());
    REQUIRE(expectedResultString == (x <<= 7).to_string());
    REQUIRE(expectedResultString == x.to_string());
}

TEST_CASE("Bit Shift Right Multiple Words",
        "Do a bitwise right shift that removes multiple words.") {
    UnsignedHugeInt x("38931662892971033006133627835528632298634425");
    UnsignedHugeInt y = x >> 81;
    std::string expectedResultString = "16101758379757878294";
    REQUIRE(expectedResultString == y.to_string());
    REQUIRE(expectedResultString == (x >>= 81).to_string());
    REQUIRE(expectedResultString == x.to_string());
}

TEST_CASE("Bit Shift Right Less Than One Word",
        "Do a right shift by fewer bits than a word size.") {
    UnsignedHugeInt x("5748907273582089237073619775896028165078597");
    UnsignedHugeInt y = x >> 12;
    std::string expectedResultString = "1403541814839377255144926703099616251239";
    REQUIRE(expectedResultString == y.to_string());
    REQUIRE(expectedResultString == (x >>= 12).to_string());
    REQUIRE(expectedResultString == x.to_string());
}

TEST_CASE("Bit Shift Right Past Full Value",
        "Do a bitwise right shift that removes the full original value.") {
    UnsignedHugeInt x("278966265550678759616749606172834569");
    UnsignedHugeInt y = x >> 150;
    REQUIRE(0 == y);
    REQUIRE(0 == (x >>= 150));
    REQUIRE(0 == x);
}

TEST_CASE("Random Add Subtract",
        "Checks consistency for addition and subtraction using random UnsignedHugeInt values.") {
    constexpr unsigned long numWords = 500;
    UnsignedHugeInt addendA = randomHugeInt(numWords);
    UnsignedHugeInt addendB = randomHugeInt(numWords);
    UnsignedHugeInt hugeSum = addendA + addendB;
    REQUIRE(addendA == hugeSum - addendB);
    REQUIRE(addendB == hugeSum - addendA);
}

TEST_CASE("Random Divide Multiply",
        "Checks consistency for multiplication and division using random UnsignedHugeInt values.") {
    UnsignedHugeInt dividendInput = randomHugeInt(1000);
    UnsignedHugeInt divisorInput = randomHugeInt(500);
    auto divisionResult = UnsignedHugeInt::divide(dividendInput, divisorInput);
    REQUIRE(dividendInput == divisionResult.first * divisorInput + divisionResult.second);
}
