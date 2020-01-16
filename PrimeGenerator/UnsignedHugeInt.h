#pragma once

/* 
 * File:   UnsignedHugeInt.h
 * Author: William Boyd
 *
 * Created on December 26, 2019, 11:54 AM
 */

//#include <bits/stdc++.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

//#include <iomanip>
//#include <locale>
//#include <sstream>
//#include <ostream>

//#include <string>
//#include <cstring>

#include "HugeIntWord.h"

//#define MAXNUMWORDS 100000
#define MAX_DIGITS_PER_WORD 9

class UnsignedHugeInt {
public:
    // Public Methods
    
    UnsignedHugeInt();
    UnsignedHugeInt(const unsigned long long value);
    UnsignedHugeInt(std::string integer_string);
    UnsignedHugeInt(const UnsignedHugeInt& orig);
    virtual ~UnsignedHugeInt();
    
    /**
     * @brief Determine which of the two numbers is greater.
     * @param numberA One of the numbers to compare.
     * @param numberB One of the numbers to compare.
     * @return 1 if numberA is greater; 0 if the numbers are equal; -1 if numberB is greater.
     */
    static short compare(const UnsignedHugeInt& numberA, const UnsignedHugeInt& numberB);
    static UnsignedHugeInt* sum_of(const UnsignedHugeInt& addendA, const UnsignedHugeInt& addendB);
    UnsignedHugeInt* operator+(const UnsignedHugeInt& addend) const;
    UnsignedHugeInt* operator+(const long long addend) const;
    UnsignedHugeInt operator-(UnsignedHugeInt minuend) const;
    UnsignedHugeInt operator-(long long minuend) const;
    UnsignedHugeInt operator*(UnsignedHugeInt factor) const;
    UnsignedHugeInt operator*(long long factor) const;
    UnsignedHugeInt operator/(UnsignedHugeInt divisor) const;
    UnsignedHugeInt operator/(long long divisor) const;
    
    long num_words() const;
    HugeIntWord* get_most_significant_word() const;
    HugeIntWord* get_least_significant_word() const;
    HugeIntWord* remove_most_significant_word();
    bool is_prime();
    std::string to_string() const;
    
protected:
//    void set_number_of_words_to(unsigned long long number_of_words);
    
private:
    static unsigned long long max_word_value;
    static unsigned long long word_base;
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
