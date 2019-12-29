/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UnsignedHugeInt.h
 * Author: William Boyd
 *
 * Created on December 26, 2019, 11:54 AM
 */

#ifndef UNSIGNEDHUGEINT_H
#define UNSIGNEDHUGEINT_H

#include <iostream>
#define MAXNUMWORDS 1000000000

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

#endif /* UNSIGNEDHUGEINT_H */

