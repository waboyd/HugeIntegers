# HugeIntegers Library for C++

This is the source code and static library for a new C++ class named UnsignedHugeInt. The class is designed to be used as an integer type that allows exact values to be stored for integers with many digits.

The class does not have an inherent limit on the size of the integers used or the number of digits per integer, but size limits can still occur from restrictions in the programming environment or available memory. Positive integers with millions of digits can be stored or used in computations as objects of UnsignedHugeInt. The class is not intended to store or perform operations using negative integers. Use of negative values with the operations UnsignedHugeInt will result in unexpected and incorrect values.

This library, excluding the file catch.hpp, was created entirely by William A. Boyd Jr. This library is distributed under the MIT License. This software may be used or modified freely, but please name me as the creator of the original version of this library in the credits of the applicable product(s). If you have questions or comments, please send me an email at bwilliam@hotmail.com, and include the name of the library in the subject line. I would be happy to hear if this software was useful.

The file catch.hpp is the Catch2 test framework, which was used for class testing. The file catch.hpp is separate from the compiled library and is present for testing purposes. Catch2 is Copyright (c) 2019 Two Blue Cubes Ltd, distributed under the Boost Software License, Version 1.0. It was obtained from https://github.com/catchorg/Catch2.


## Setup
The library is precompiled as a static library for a 64-bit Windows environment in the folder named StaticLibrary. Your compiler will need access to the header file UnsignedHugeInt.h, and your linker will need the file libUnsignedHugeInt.lib.

If the UnsignedHugeInt class will be used on a system other than 64-bit Windows, it may be necessary to compile the source code for your particular environment. The required source files are:

* UnsignedHugeInt.h
* UnsignedHugeInt.cpp
* UnsingedHugeIntValue.h
* UnsignedHugeIntValue.cpp
* HugeIntWord.h
* HugeIntWord.cpp

Of these, only UnsignedHugeInt.h should be included by external software. Some constants in the header files may need to be adjusted. The `MAX_VALUE` constant should be one less than a power of 10. The system must be able to store the value of `MAX_VALUE` squared in a single variable of type `unsigned long long`. The `MAX_NUMBER_OF_DIGITS` and `MAX_DIGITS_PER_WORD` constants should be the number of digits in `MAX_VALUE`.

If the installation was successful, the following lines should be compilable without problems.

    #include "UnsignedHugeInt.h"

    int main(int argc, char **argv)
    {
        UnsignedHugeInt x = "847650900928374678345345346987947984989091384";
        ++x;
        std::cout << "Value of x: " << x << "\n";
    }

This should assign the value to x, increment it, and print its new value.

## Instantiation and Initialization

Include the UnsingedHugeInt.h as a header file to allow the use of UnsignedHugeInt as a type.

    #include "UnsignedHugeInt.h"

Variables of UnsignedHugeInt can be declared and initialized with the same syntax used for other C++ integer types. Unlike the primitive int types, variables of UnsignedHugeInt that are not initialized are given a value of 0.

    UnsignedHugeInt a;		// Initializes a to 0.
    UnsignedHugeInt b(5542);	// Initializes b to 5542.
    UnsignedHugeInt c = 478;	// Initializes c to 478.
    int x = 73l;
    UnsignedHugeInt d = x;		// Initializes d to 731 (value of x).

If an integer is too large for the native C++ environment to process, you will not be able to assign the value as a literal integer value. For example, UnsignedHugeInt can hold a value of 1234567890098765432101, but the compiler does not understand the number 1234567890098765432101 because it is too large.

    UnsignedHugeInt a = 1234567890098765432101; // Does not work. Do not do this!

For this reason, strings (char* or std::string) of digits can be used to assign a value to an UnsignedHugeInt. The string must contain only digits for the integer. Values can also be copied from existing UnsignedHugeInt or nonnegative integer variables.

    UnsignedHugeInt a = "1234567890098765432101";	// This will give the correct value to the variable.
    UnsignedHugeInt b(a);		// Copies the value 1234567890098765432101 to the new variable b.
    UnsignedHugeInt c = a;		// Copies the value 1234567890098765432101 to the new variable c.


## Output

The UnsignedHugeInt method to_string() returns the value of the variable as a std::string. An object of UnsignedHugeInt can also be cast a std::string to give the same result. The value of an UnsignedHugeInt can be output directly to a stream.

    UnsignedHugeInt d = "56748962340197409876098734777769112230553";
    std::string intString1, intString2;
    intString1 = d.to_string();
    intString2 = (std::string)d;
    std::cout << "intString1: " << intString1 << "\n";
    std::cout << "intString2: " << intString2 << "\n";
    std::cout << "d: " << d << "\n";

Result:

    intString1: 56748962340197409876098734777769112230553
    intString2: 56748962340197409876098734777769112230553
    d: 56748962340197409876098734777769112230553


## Arithmetic Operators

UnsignedHugeInt supports the following arithmetic operators, which behave the same way as the operators for the native C++ integer types.

	+	-	*	/	%
	+=	-=	*=	/=	%=
	++ (prefix or suffix)
	-- (prefix or suffix)
All of these return UnsignedHugeInt objects when one of the arguments is an UnsignedHugeInt. The subtraction and decrement operations throw an exception if the result is negative. Please note that UnsignedHugeInt does not support the shift operators << and >>. Integer values can be used for one side of the operator, but the use of negative values in the operations is not supported.

As an example, this finds the average of the two values.

    UnsignedHugeInt value1("61351980004064111786419867354198035418403537");
    UnsignedHugeInt value2 = "490498411878773549840354840587489112335499309";
    UnsignedHugeInt average;	// Has a value of 0 if not initialized.
    average = (value1 + value2) / 2;
    std::cout << "Average value: " << average << "\n";

The following line is output by this program segment:

    Average value: 275925195941418830813387353970843573876951423


The static UnsignedHugeInt method `divide(const UnsignedHugeInt& dividend, const UnsignedHugeInt& divisor)` returns a pair of UnsignedHugeInt objects: the quotient and remainder of the integer division. This method is recommended whenever the quotient and remainder will both be used, as this avoids repetition of the division process.

    UnsignedHugeInt dividend("57044496378411123084322189436884324008935689407410046875046");
    UnsignedHugeInt divisor("47103549732045657048015699403540");
    UnsignedHugeInt quotient, remainder;
    std::pair<UnsignedHugeInt, UnsignedHugeInt> division_results;
    division_results = UnsignedHugeInt::divide(dividend, divisor);
    quotient = division_results.first;
    remainder = division_results.second;
    std::cout << "Quotient: " << quotient << "\n";
    std::cout << "Remainder: " << remainder << "\n";


Result:

    Quotient: 1211044532798818032951280240
    Remainder: 32876386735422226721762658825446


## Comparison Operators

The standard arithmetic operators are supported for UnsignedHugeInt.

	<	>	==
	<=	>=	!=
These all return a bool value and have the same behavior expected for other integer types. Integer values can be used for one side of the operator, but the use of negative values in the operations is not supported.

## Text File Operations

The value of an UnsignedHugeInt can be written to a text file using the method
`write_to_text_file(std::string file_path)`. The argument should be the path of the file to be written, including the name of the file. The write_to_text_file method can only be used to create a new file containing only digits from the value and newline ('\n') characters. An exception is thrown if the file already exists before the method is called.

The value of an UnsignedHugeInt can be set to a value from a text file via the method `read_from_text_file(std::string file_path)`. The argument should be the path of the file to be read, including the name of the file. The text file is assumed to hold the digits of only one unsigned integer. All non-digit characters in the text file are ignored.


    UnsignedHugeInt x = "380985198723318923069853786";
    UnsignedHugeInt y;
    std::string integer_file_path = "..\\TextFiles\\LargeNumber1.txt";	// The file does not yet exist.
    x.write_to_text_file(integer_file_path);	// Write the value of x to a text file.
    y.read_from_text_file(integer_file_path);	// Set y to the value in the text file.
    std::cout << "Value of y: " << y << "\n";


Result:

    Value of y: 380985198723318923069853786



## Binary File Operations

The value of an UnsignedHugeInt can be written to a binary file using the method
`write_to_binary_file(std::string file_path)`. The use of a binary file is more efficient than a text file for both performance and required disk space. The drawback is that the binary file can only be read by the same library that created the file, in the same environment. The argument should be the path of the file to be written, including the name of the file. The write_to_binary_file() method can only be used to create a new binary file; an exception is thrown if the file already exists before the method is called.

The method `read_from_binary_file(std::string file_path)` reads the value of an UnsignedHugeInt that was previously written to a file by the write_to_binary_file() method. The argument should be the path of the file to be read, including the name of the file. The portability of the binary files across different computers is not guaranteed.


    UnsignedHugeInt x = "296870106117339450400480835217839840";
    UnsignedHugeInt y;
    std::string integer_file_path = "..\\DataFiles\\LargeNumber.bin";	// The file does not yet exist.
    x.write_to_binary_file(integer_file_path);	// Write the value of x to a binary file.
    y.read_from_binary_file(integer_file_path);	// Set y to the value in the binary file.
    std::cout << "Value of y: " << y << "\n";


Result:

    Value of y: 296870106117339450400480835217839840



## Development Notes

This library was developed in 2019-2020 by William A. Boyd Jr. The IDEs NetBeans and CodeLite were used at different stages of development. MinGW was used for its C++ compilation tools. Git was used together with Github for version control and backup. The testing framework Catch2 was used to create test cases, allowing a Test-Driven Development approach to be used for this library. 79 test cases were created, both to define the requirements and verify the functionality of the library. The test cases are available in the Github repository, but they are not compiled into the static library.

No guarantees are made as to whether development will continue for this library. Some features that are not currently implemented but could be useful are listed below.

- Detect the environment settings and adjust the maximum size for the value segments (words) accordingly.
- Allow bases for value segments that are not powers of 10. The output functions would need to be replaced.
- Apply multithreading to the multiplication and/or division operations.
- Implement a related class that supports operations for signed integers with many digits.