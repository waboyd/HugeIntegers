/*  Test cases for the base 2 implementation of UnsignedHugeInt library.
    These test cases all depend on the Catch2 test framework.
    These test cases were created when the word base was changed from a power
    of 10 to a power of 2. These are created to test for edge cases with the
    changed implementation.
    The older test cases in the file hugeIntTests.cpp should continue to pass.
    The UnsignedHugeInt library and these test cases were created by William Boyd.
*/

#include <catch2/catch_test_macros.hpp>

#define HUGE_INT_WORD_BASE          4294967296

#include "UnsignedHugeInt.h"

const char test_folder_path[] = "../TestFiles/";

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
