#include "HugeIntWord.h"

//HugeIntWord::HugeIntWord()
//{
//    
//}

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
    lowerSignificantWord->set_more_significant_word(this);
}

HugeIntWord::~HugeIntWord()
{
}

unsigned long long HugeIntWord::get_value() {
    return this->value;
}

HugeIntWord* HugeIntWord::get_next_word() {
    return this->lessSigWord;
}

void HugeIntWord::set_more_significant_word(HugeIntWord* next_word) {
    if (this->moreSigWord != NULL) {
        throw std::logic_error("An attempt was made to attach a word to replace an existing word.");
    }
    
    if (next_word == NULL) {
        std::cout << "WARNING: An attempt was made to attach a null object to a word.\n";
        return;
    }
    
    this->moreSigWord = next_word;
}

void HugeIntWord::set_less_significant_word(HugeIntWord* next_word, unsigned long long greatest_place_value) {
    if (this->lessSigWord != NULL) {
        throw std::logic_error("An attempt was made to attach a word to replace an existing word.");
    }
    
    if (next_word == NULL) {
        std::cout << "WARNING: An attempt was made to attach a null object to a word.\n";
        return;
    }
    
    this->lessSigWord = next_word;
    this->place_value = greatest_place_value;
}

void HugeIntWord::remove_more_significant_word() {
    if (this->moreSigWord == NULL) {
        std::cout << "WARNING: An attempt was made to remove a null more significant word.\n";
        return;
    }
    this->moreSigWord = NULL;
}

std::string HugeIntWord::to_string() {
    // ToDo: Convert the words to base 10 when forming the string.
    std::ostringstream numberToStringStream;
    std::string numberString;
    numberToStringStream << this->value;
    numberString = numberToStringStream.str();
    return numberString;
}