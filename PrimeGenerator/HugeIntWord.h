#pragma once

#include <cstddef>
#include <sstream>

#define MAX_VALUE   1000000000

class HugeIntWord
{
public:
    HugeIntWord();
    HugeIntWord(unsigned long long value);
    HugeIntWord(unsigned long long value, unsigned long long place_value, HugeIntWord* lowerSignificantWord);
    ~HugeIntWord();
    
    HugeIntWord* get_next_word();
    std::string to_string();
    
private:
    HugeIntWord *lessSigWord, *moreSigWord;
    unsigned long long value;
    unsigned long long place_value;  // Location of this word in the number. 0 is least significant place.
};

