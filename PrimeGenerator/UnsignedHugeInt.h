#pragma once

/* 
 * File:   UnsignedHugeInt.h
 * Author: William Boyd
 *
 * Created on December 26, 2019, 11:54 AM
 */

//#include <bits/stdc++.h>
#include <iostream>

//#include <iomanip>
//#include <locale>
#include <sstream>
//#include <ostream>

//#include <string>
//#include <cstring>
//#define MAXNUMWORDS 100000000
#define MAXNUMWORDS 100000

class UnsignedHugeInt {
public:
    UnsignedHugeInt();
    UnsignedHugeInt(const unsigned long long value);
    UnsignedHugeInt(const UnsignedHugeInt& orig);
    virtual ~UnsignedHugeInt();
    UnsignedHugeInt operator+(UnsignedHugeInt addend);
    UnsignedHugeInt operator+(long long addend);
    UnsignedHugeInt operator-(UnsignedHugeInt minuend);
    UnsignedHugeInt operator-(long long minuend);
    UnsignedHugeInt operator*(UnsignedHugeInt factor);
    UnsignedHugeInt operator*(long long factor);
    UnsignedHugeInt operator/(UnsignedHugeInt divisor);
    UnsignedHugeInt operator/(long long divisor);
    long num_words();
    bool is_prime();
    std::string to_string();
    
private:
    unsigned long numWords;
    unsigned long words[MAXNUMWORDS];
};

