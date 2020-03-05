#pragma once

/* 
 * File:   UnsignedHugeInt.h
 * Author: William Boyd
 *
 * Created on December 26, 2019, 11:54 AM
 */

//#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

//#include <iomanip>
//#include <locale>
//#include <sstream>
//#include <ostream>

//#include <string>
//#include <cstring>

#include "HugeIntWord.h"

//#define MAXNUMWORDS 100000
#define MAX_DIGITS_PER_WORD 9
#define CHECK_VALUE_A   84340
#define CHECK_VALUE_B   308424
#define READ_BUFFER_SIZE    144
#define BUFFER_NUM_WORDS    16

class UnsignedHugeInt {
public:
    // Public Methods
    
    UnsignedHugeInt();
    UnsignedHugeInt(const unsigned long long value);
    UnsignedHugeInt(std::string integer_string);
    UnsignedHugeInt(const UnsignedHugeInt& orig);
    UnsignedHugeInt(const UnsignedHugeInt* orig);
    virtual ~UnsignedHugeInt();
    
    void read_from_text_file(std::string file_path);
    void read_from_text_file(FILE* integer_file);
    void write_to_text_file(std::string file_path) const;
    void write_to_text_file(FILE* integer_file) const;
    void read_from_binary_file(std::string file_path);
    void write_to_binary_file(std::string file_path) const;
    
    operator std::string() const;

    UnsignedHugeInt& operator=(const UnsignedHugeInt& orig);
    UnsignedHugeInt& operator=(const UnsignedHugeInt* orig);
    UnsignedHugeInt& operator=(const unsigned long long value);
    UnsignedHugeInt& operator=(const std::string value_string);
    
    /**
     * @brief Determine which of the two numbers is greater.
     * @param numberA One of the numbers to compare.
     * @param numberB One of the numbers to compare.
     * @return 1 if numberA is greater; 0 if the numbers are equal; -1 if numberB is greater.
     */
    static short compare(const UnsignedHugeInt& numberA, const UnsignedHugeInt& numberB);
    bool operator<(const UnsignedHugeInt& right_operand) const;
    bool operator<(const unsigned long long right_operand) const;
    bool operator<=(const UnsignedHugeInt& right_operand) const;
    bool operator<=(const unsigned long long right_operand) const;
    bool operator>(const UnsignedHugeInt& right_operand) const;
    bool operator>(const unsigned long long right_operand) const;
    bool operator>=(const UnsignedHugeInt& right_operand) const;
    bool operator>=(const unsigned long long right_operand) const;
    bool operator==(const UnsignedHugeInt& right_operand) const;
    bool operator==(const unsigned long long right_operand) const;
    bool operator!=(const UnsignedHugeInt& right_operand) const;
    bool operator!=(const unsigned long long right_operand) const;
    static UnsignedHugeInt sum_of(const UnsignedHugeInt& addendA, const UnsignedHugeInt& addendB);
    static UnsignedHugeInt sum_of(const UnsignedHugeInt& addendA, const unsigned long long addendB);
    UnsignedHugeInt operator+(const UnsignedHugeInt& addend) const;
    UnsignedHugeInt operator+(const unsigned long long addend) const;
    static UnsignedHugeInt subtract(const UnsignedHugeInt& minuend, const UnsignedHugeInt& subtrahend);
    UnsignedHugeInt operator-(const UnsignedHugeInt& subtrahend) const;
    UnsignedHugeInt operator-(const unsigned long long subtrahend) const;
    static UnsignedHugeInt multiply(const UnsignedHugeInt& factorA, const UnsignedHugeInt& factorB);
    UnsignedHugeInt operator*(const UnsignedHugeInt& factor) const;
    UnsignedHugeInt operator*(const unsigned long long factor) const;
    static std::pair<UnsignedHugeInt, UnsignedHugeInt> divide(const UnsignedHugeInt& dividend, const UnsignedHugeInt& divisor);
    UnsignedHugeInt operator/(const UnsignedHugeInt& divisor) const;
    UnsignedHugeInt operator/(const unsigned long long divisor) const;
    UnsignedHugeInt operator%(const UnsignedHugeInt& divisor) const;
    UnsignedHugeInt operator%(const unsigned long long divisor) const;
    UnsignedHugeInt& operator+=(const UnsignedHugeInt& addend);
    UnsignedHugeInt& operator+=(const unsigned long long addend);
    UnsignedHugeInt& operator-=(const UnsignedHugeInt& subtrahend);
    UnsignedHugeInt& operator-=(const unsigned long long subtrahend);
    UnsignedHugeInt& operator*=(const UnsignedHugeInt& factor);
    UnsignedHugeInt& operator*=(const unsigned long long factor);
    UnsignedHugeInt& operator/=(const UnsignedHugeInt& divisor);
    UnsignedHugeInt& operator/=(const unsigned long long divisor);
    UnsignedHugeInt& operator%=(const UnsignedHugeInt& divisor);
    UnsignedHugeInt& operator%=(const unsigned long long divisor);
    UnsignedHugeInt& operator++();
    UnsignedHugeInt operator++(int dummy);
    UnsignedHugeInt& operator--();
    UnsignedHugeInt operator--(int dummy);
        
    /**
     * @brief Return true only if the object has been defined and is not null.
     * @return True if the object is verified as properly defined.
     */
    bool is_defined() const;
    long num_words() const;
    HugeIntWord* get_most_significant_word() const;
    HugeIntWord* get_least_significant_word() const;
    HugeIntWord* remove_most_significant_word();
    std::string to_string() const;
    
    // ToDo: Remove the following after development.
    static void report_number_of_objects();
    
protected:
    static unsigned long max_word_value;
    static unsigned long long word_base;

    // Protected Methods
    void change_to_copy_of(const UnsignedHugeInt& orig);
    void set_value_from_string(std::string integer_string);
    void delete_all_words();
    void remove_extra_leading_words();
    /**
     * @brief Add a new most significant word with a value of 0;
     * @return Pointer to the new word that was added.
     */
    HugeIntWord* add_word();
    /**
     * @brief Add new most significant words with a total value given in the parameter;
     * @return Pointer to the most significant new word that was added.
     */
    HugeIntWord* add_word(const unsigned long long value);
    /**
     * @brief Add the word given in the parameter as the new most significant word;
     * @return Pointer to the new word that was added.
     */
    HugeIntWord* add_word(HugeIntWord* new_word);
    /**
     * @brief Change this number by inserting a new least significant word with the given value.
     * @param least_significant_value The value of the new least significant word to be added.
     * @return The least significant word of this number.
     */
    HugeIntWord* insert_least_significant_word(unsigned long least_significant_value);

private:
    HugeIntWord *leastSigWord, *mostSigWord;
    int defined_key_1, defined_key_2;
    
    // Private Methods

    /**
     * @brief Add a specified value at a specified word of this UnsignedHugeInt.
     * @param location_to_add Word at which the value will be added. This word will be changed.
     * @param value_to_add Number that will be added to the specified word.
     * @return The least significant word that was updated.
     */
    HugeIntWord* add_value_at_word(HugeIntWord* location_to_add, const UnsignedHugeInt& value_to_add);
    static UnsignedHugeInt integer_with_least_significant_word(const HugeIntWord* least_significant_word);
    
    static UnsignedHugeInt find_multiplication_subtotal(const HugeIntWord* greater_factor_word, const HugeIntWord* lesser_factor_word);

    // ToDo: Remove the following variables after development.
    static unsigned int num_objects_created;
    static unsigned int num_objects_deleted;
};

// Operators involving UnsignedHugeInt, but not considered part of UnsignedHugeInt by the compiler.
bool operator<(const unsigned long long left_operand, const UnsignedHugeInt& right_operand);
bool operator<=(const unsigned long long left_operand, const UnsignedHugeInt& right_operand);
bool operator>(const unsigned long long left_operand, const UnsignedHugeInt& right_operand);
bool operator>=(const unsigned long long left_operand, const UnsignedHugeInt& right_operand);
bool operator==(const unsigned long long left_operand, const UnsignedHugeInt& right_operand);
bool operator!=(const unsigned long long left_operand, const UnsignedHugeInt& right_operand);
UnsignedHugeInt operator+(const unsigned long long addendA, const UnsignedHugeInt& addendB);
UnsignedHugeInt operator-(const unsigned long long minuend, const UnsignedHugeInt& subtrahend);
UnsignedHugeInt operator*(const unsigned long long factorA, const UnsignedHugeInt& factorB);
UnsignedHugeInt operator/(const unsigned long long dividend, const UnsignedHugeInt& divisor);
UnsignedHugeInt operator%(const unsigned long long dividend, const UnsignedHugeInt& divisor);
std::ostream& operator<<(std::ostream& out_stream, const UnsignedHugeInt& huge_int_object);    
