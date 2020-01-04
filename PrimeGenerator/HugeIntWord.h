#pragma once

#include <cstddef>
#include <sstream>

#define MAX_VALUE   999999999

class HugeIntWord
{
public:
    HugeIntWord();
    HugeIntWord(unsigned long long value);
    HugeIntWord(unsigned long long value, unsigned long long place_value, HugeIntWord* lowerSignificantWord);
    ~HugeIntWord();
    /**
     * @brief Return the next less significant word (segment) of the number.
     * @return The next less significant word (segment) of the number.
     */
    HugeIntWord* get_next_word();
    std::string to_string();
    
private:
    HugeIntWord *lessSigWord, *moreSigWord;
    unsigned long long value;
    unsigned long long place_value;  // Location of this word in the number. 0 is least significant place.
};

