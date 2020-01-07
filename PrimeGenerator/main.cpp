//#include <stdio.h>
#include <iostream>
#include "UnsignedHugeInt.h"

int main(int argc, char **argv)
{
//    int longSize;
//    longSize = sizeof(unsigned long);
//    int longLongBits = sizeof(unsigned long long) * 8;
//    unsigned long long part1, part2, part3;
//    ///////
//    part1 = pow(2, 63);
//    part1 -= 1;
//    part1 <<= 1;
//    part1 += 1;
//    part2 = 0;
//    part3 = 0;
////    unsigned long long maxLong = part1 + part2 + part3;
//    std::cout << "Maximum unsigned long: " << part1 << ".\n";
////    cout << "Number of bits: " << longLongBits << ".\n";
    
    std::cout << "Test message.\n";
    
//    UnsignedHugeInt numA(4553345398741);
    UnsignedHugeInt *numA = new UnsignedHugeInt(4553345398741);
    unsigned int intA = 59;
    UnsignedHugeInt numB(1259);
    UnsignedHugeInt *sumA;
    std::cout << "Value of the number: ";
    std::cout << numA->to_string() << ".\n";
    
    sumA = *numA + intA;
    std::cout << "Operation result: " << sumA->to_string() << "\n";
//    *numA + intA;
//    int dummyInt;
//    std::cin >> dummyInt;


    delete(numA);
    return 0;

}
