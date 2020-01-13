#pragma once

#include <cstddef>
#include <iostream>
#include <sstream>
#include <exception>

#define MAX_VALUE   999999999
#define MAX_NUMBER_OF_DIGITS    9

class HugeIntWord
{
    
    friend class UnsignedHugeInt;
    
public:
//    HugeIntWord();
    HugeIntWord(unsigned long long value);
    HugeIntWord(unsigned long long value, unsigned long long place_value, HugeIntWord* lowerSignificantWord);
    ~HugeIntWord();
    
    unsigned long long get_value();
    unsigned long long get_word_number();
    /**
     * @brief Return the next less significant word (segment) of the number.
     * @return The next less significant word (segment) of the number.
     */
//    void set_more_significant_word(HugeIntWord* next_word);
    std::string to_string();
    
protected:
    
private:
    static unsigned long long max_value;
    static unsigned long long base_value;
    HugeIntWord* get_next_lower_sig_word();
    HugeIntWord* get_next_more_sig_word();
    void set_more_significant_word(HugeIntWord* next_word);
    HugeIntWord *lessSigWord, *moreSigWord;
    unsigned long long value;
    unsigned long long place_value;  // Location of this word in the number. 0 is least significant place.
    void set_less_significant_word(HugeIntWord* next_word);
    void remove_more_significant_word();
    
    /**
     * @brief Add a value to this word.
     * @param addend Value to add to the word.
     * @return True if an amount was carried to the next word; false if no carry.
     */
    bool add_value(unsigned long long addend);
};

