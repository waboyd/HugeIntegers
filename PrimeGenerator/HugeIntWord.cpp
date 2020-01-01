#include "HugeIntWord.h"

HugeIntWord::HugeIntWord()
{
    
}

HugeIntWord::HugeIntWord(unsigned long long value){
    this->value = value;
    this->lessSigWord = NULL;
    this->place_value = 0;
    this->moreSigWord = NULL;
}

HugeIntWord::HugeIntWord(unsigned long long value, unsigned long long place_value, HugeIntWord* lowerSignificantWord){
    this->value = value;
    this->lessSigWord = lowerSignificantWord;
    this->place_value = place_value;
    this->moreSigWord = NULL;
}


HugeIntWord::~HugeIntWord()
{
}

