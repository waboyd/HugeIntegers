#pragma once

#include <cstddef>
#include <iostream>
#include <sstream>
#include <exception>

#define MAX_VALUE   999999999

class HugeIntWord
{
public:
//    HugeIntWord();
    HugeIntWord(unsigned long long value);
    HugeIntWord(unsigned long long value, unsigned long long place_value, HugeIntWord* lowerSignificantWord);
    ~HugeIntWord();
    
    unsigned long long get_value();
    /**
     * @brief Return the next less significant word (segment) of the number.
     * @return The next less significant word (segment) of the number.
     */
    HugeIntWord* get_next_lower_sig_word();
    HugeIntWord* get_next_more_sig_word();
    void set_more_significant_word(HugeIntWord* next_word);
    void set_less_significant_word(HugeIntWord* next_word, unsigned long long greatest_place_value);
    void remove_more_significant_word();
    std::string to_string();
    
private:
    HugeIntWord *lessSigWord, *moreSigWord;
    unsigned long long value;
    unsigned long long place_value;  // Location of this word in the number. 0 is least significant place.
};

