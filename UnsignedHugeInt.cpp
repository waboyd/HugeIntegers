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
    // ToDo: Complete this method.
}

UnsignedHugeInt::~UnsignedHugeInt() {
    // ToDo: Complete this method.
}

UnsignedHugeInt UnsignedHugeInt::operator+(UnsignedHugeInt addend) {
    // ToDo: Complete this method.
    
}

UnsignedHugeInt UnsignedHugeInt::operator+(long long addend) {
    // ToDo: Complete this method.
    
}

UnsignedHugeInt UnsignedHugeInt::operator-(UnsignedHugeInt minuend) {
    // ToDo: Complete this method.
    
}

UnsignedHugeInt UnsignedHugeInt::operator-(long long minuend) {
    // ToDo: Complete this method.
    
}

UnsignedHugeInt UnsignedHugeInt::operator*(UnsignedHugeInt factor) {
    // ToDo: Complete this method.
    
}

UnsignedHugeInt UnsignedHugeInt::operator*(long long factor) {
    // ToDo: Complete this method.
    
}

UnsignedHugeInt UnsignedHugeInt::operator/(UnsignedHugeInt divisor) {
    // ToDo: Complete this method.
    
}

UnsignedHugeInt UnsignedHugeInt::operator/(long long divisor) {
    // ToDo: Complete this method.
    
}

long UnsignedHugeInt::num_words() {
    return this->numWords;
}

bool UnsignedHugeInt::is_prime() {
    // ToDo: Complete this method.
    return false;
}

std::string UnsignedHugeInt::to_string() {
    // ToDo: Complete this method.
    return NULL;
}
