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
//#include <sstream>
//#include <ostream>

//#include <string>
//#include <cstring>

#include "HugeIntWord.h"

//#define MAXNUMWORDS 100000

class UnsignedHugeInt {
public:
    // Public Methods
    
    UnsignedHugeInt();
    UnsignedHugeInt(const unsigned long long value);
    UnsignedHugeInt(const UnsignedHugeInt& orig);
    virtual ~UnsignedHugeInt();
    UnsignedHugeInt operator+(const UnsignedHugeInt& addend);
    UnsignedHugeInt operator+(const long long& addend);
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
    static unsigned long long max_word_value;
    static unsigned long long word_base;
    unsigned long long numWords;
    HugeIntWord *leastSigWord, *mostSigWord;
    
    // Private Methods
    
    /**
     * @brief Add a new most significant word with a value of 0;
     * @return Pointer to the new word that was added.
     */
    HugeIntWord* add_word();
    /**
     * @brief Add new most significant words with a total value given in the parameter;
     * @return Pointer to the most significant new word that was added.
     */
    HugeIntWord* add_word(unsigned long long value);
    /**
     * @brief Add the word given in the parameter as the new most significant word;
     * @return Pointer to the new word that was added.
     */
    HugeIntWord* add_word(HugeIntWord* new_word);
    void throw_warning(std::string message);
    
};
