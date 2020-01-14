#include "HugeIntWord.h"

//HugeIntWord::HugeIntWord()
//{
//    
//}
unsigned long long HugeIntWord::max_value = MAX_VALUE;
unsigned long long HugeIntWord::base_value = max_value + 1;

HugeIntWord::HugeIntWord(unsigned long long value){
    this->value = value;
    this->lessSigWord = NULL;
    this->place_value = 0;
    this->moreSigWord = NULL;
}

HugeIntWord::HugeIntWord(unsigned long long value, HugeIntWord* lowerSignificantWord){
    this->value = value;
    this->lessSigWord = lowerSignificantWord;
    this->place_value = lowerSignificantWord->get_word_number() + 1;
    this->moreSigWord = NULL;
    lowerSignificantWord->set_more_significant_word(this);
}

HugeIntWord::~HugeIntWord()
{
}

unsigned long long HugeIntWord::get_value() const {
    return this->value;
}

unsigned long long HugeIntWord::get_word_number() const {
    return this->place_value;
}

HugeIntWord* HugeIntWord::get_next_lower_sig_word() {
    return this->lessSigWord;
}

HugeIntWord* HugeIntWord::get_next_more_sig_word() {
    return this->moreSigWord;
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
    this->place_value = next_word->get_word_number() + 1;
}

void HugeIntWord::set_less_significant_word(HugeIntWord* next_word) {
    if (this->lessSigWord != NULL) {
        throw std::logic_error("An attempt was made to attach a word to replace an existing word.");
    }
    
    if (next_word == NULL) {
        std::cout << "WARNING: An attempt was made to attach a null object to a word.\n";
        return;
    }
    
    this->lessSigWord = next_word;
    this->place_value = next_word->get_word_number() + 1;
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
    std::string formattedNumberString;
    unsigned short numLeadingZeros;
    numberToStringStream << this->value;
    numberString = numberToStringStream.str();
    if (this->moreSigWord != NULL) {
        numLeadingZeros = MAX_NUMBER_OF_DIGITS - numberString.length();
        formattedNumberString = std::string(numLeadingZeros, '0') + numberString;
    }
    else {
        formattedNumberString = numberString;
    }
    return formattedNumberString;
}

bool HugeIntWord::add_value(unsigned long long addend) {
    unsigned long long thisNewValue;
    unsigned long long carryValue;
    if (addend <= HugeIntWord::max_value) {
        thisNewValue = this->value + addend;
        if (thisNewValue > HugeIntWord::max_value) {
            carryValue = thisNewValue / HugeIntWord::base_value;
            thisNewValue = thisNewValue % HugeIntWord::base_value;
            this->value = thisNewValue;
            if (this->moreSigWord == NULL) {
                this->moreSigWord = new HugeIntWord(carryValue, this);
                // ToDo: Change the most significant word of the integer.
            }
            else {
                this->moreSigWord->add_value(carryValue);
            }
            return true;
        }
        else {
            this->value = thisNewValue;
            return false;
        }
    }
    else {
        thisNewValue = (addend % HugeIntWord::base_value) + this->value;
        carryValue = (addend / HugeIntWord::base_value) + (thisNewValue / HugeIntWord::base_value);
        thisNewValue = thisNewValue % HugeIntWord::base_value;
        this->value = thisNewValue;
        if (this->moreSigWord == NULL) {
            this->moreSigWord = new HugeIntWord(carryValue, this);
        }
        else {
            this->moreSigWord->add_value(carryValue);
        }
        return true;        
    }
}