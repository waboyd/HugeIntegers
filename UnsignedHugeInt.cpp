/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UnsignedHugeInt.cpp
 * Author: William Boyd
 * 
 * Created on December 26, 2019, 11:54 AM
 */

#include "UnsignedHugeInt.h"

UnsignedHugeInt::UnsignedHugeInt() {
    this->numWords = 1;
    this->words[0] = 0;
}

UnsignedHugeInt::UnsignedHugeInt(const unsigned long long value) {
    this->numWords = 1;
    this->words[0] = value;
}

UnsignedHugeInt::UnsignedHugeInt(const UnsignedHugeInt& orig) {
}

UnsignedHugeInt::~UnsignedHugeInt() {
}

