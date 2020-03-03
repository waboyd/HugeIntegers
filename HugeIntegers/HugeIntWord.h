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
    HugeIntWord(unsigned long value);
    HugeIntWord(unsigned long value, HugeIntWord* lowerSignificantWord);
    ~HugeIntWord();
    
    unsigned long get_value() const;
    unsigned long long get_word_number() const;
    /**
     * @brief Return the next less significant word (segment) of the number.
     * @return The next less significant word (segment) of the number.
     */
//    void set_more_significant_word(HugeIntWord* next_word);
    std::string to_string();
    
protected:
    
private:
    static unsigned long max_value;
    static unsigned long base_value;
    void set_more_significant_word(HugeIntWord* next_word);
    HugeIntWord *lessSigWord, *moreSigWord;
    unsigned long value;
    unsigned long long place_value;  // Location of this word in the number. 0 is least significant place.
    HugeIntWord* get_next_lower_sig_word() const;
    HugeIntWord* get_next_more_sig_word() const;
    void set_less_significant_word(HugeIntWord* next_word);
    void remove_more_significant_word();
    
    /**
     * @brief Add a value to this word.
     * @param addend Value to add to the word.
     * @return Pointer to most significant word of the addition operation.
     */
    HugeIntWord* add_value(unsigned long long addend);
    
    // ToDo: Remove the following variables after development.
    static unsigned int num_objects_created;
    static unsigned int num_objects_deleted;
};

