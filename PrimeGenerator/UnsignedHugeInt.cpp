#include "UnsignedHugeInt.h"

    // ToDo: Set the maxWordValmax_word_valuein HugeIntWord.
    unsigned long long UnsignedHugeInt::max_word_value = 999999999;
    unsigned long long UnsignedHugeInt::word_base = UnsignedHugeInt::max_word_value + 1;

UnsignedHugeInt::UnsignedHugeInt() {
    // ToDo: Set maximum word value.
    this->numWords = 1;
    HugeIntWord *newWord = new HugeIntWord(0);
    this->mostSigWord = newWord;
    this->leastSigWord = newWord;
}

UnsignedHugeInt::UnsignedHugeInt(const unsigned long long value) {
    // ToDo: Set maximum word value.
    if (value > UnsignedHugeInt::max_word_value) {
        unsigned long carryValue = value / UnsignedHugeInt::word_base;
        unsigned long long lesserValue = value % UnsignedHugeInt::word_base;
        HugeIntWord *lesserWord, *greaterWord;
        lesserWord = new HugeIntWord(lesserValue);
        greaterWord = new HugeIntWord(carryValue, 1, lesserWord);
        this->mostSigWord = greaterWord;
        this->leastSigWord = lesserWord;
        this->numWords = 2;
    }
    else {
        HugeIntWord *newWord = new HugeIntWord(value);
        this->mostSigWord = newWord;
        this->leastSigWord = newWord;
        this->numWords = 1;
    }
}

UnsignedHugeInt::UnsignedHugeInt(const UnsignedHugeInt& orig) {
    // ToDo: Complete this method.
}

UnsignedHugeInt::~UnsignedHugeInt() {
    HugeIntWord *thisWord = this->mostSigWord;
    HugeIntWord *wordToDelete, *nextWord;
    while (thisWord != NULL) {
        wordToDelete = thisWord;
        
        nextWord = thisWord->get_next_word();
        delete(wordToDelete);
        thisWord = nextWord;
    }
}

UnsignedHugeInt UnsignedHugeInt::operator+(const UnsignedHugeInt& addend) {
    // ToDo: Complete this method.
    UnsignedHugeInt sum;
    
    return sum;
}

UnsignedHugeInt UnsignedHugeInt::operator+(const long long& addend) {
    // ToDo: Complete this method.
    UnsignedHugeInt sum;
    
    std::cout << "First addend: " << this->to_string() << "\n";
    std::cout << "Second addend: " << addend << "\n";
    
    return sum;
}

UnsignedHugeInt UnsignedHugeInt::operator-(UnsignedHugeInt minuend) {
    // ToDo: Complete this method.
    UnsignedHugeInt difference;
    
    return difference;
}

UnsignedHugeInt UnsignedHugeInt::operator-(long long minuend) {
    // ToDo: Complete this method.
    UnsignedHugeInt difference;
    
    return difference;
}

UnsignedHugeInt UnsignedHugeInt::operator*(UnsignedHugeInt factor) {
    // ToDo: Complete this method.
    UnsignedHugeInt product;
    
    return product;
}

UnsignedHugeInt UnsignedHugeInt::operator*(long long factor) {
    // ToDo: Complete this method.
    UnsignedHugeInt product;
    
    return product;
}

UnsignedHugeInt UnsignedHugeInt::operator/(UnsignedHugeInt divisor) {
    // ToDo: Complete this method.
    UnsignedHugeInt quotient;
    
    return quotient;
}

UnsignedHugeInt UnsignedHugeInt::operator/(long long divisor) {
    // ToDo: Complete this method.
    UnsignedHugeInt quotient;
    
    return quotient;
}

long UnsignedHugeInt::num_words() {
    return this->numWords;
}

HugeIntWord* UnsignedHugeInt::remove_most_significant_word() {
    HugeIntWord *oldMostSigWord = this->mostSigWord;
    if (oldMostSigWord == NULL) {
        throw std::logic_error("An UnsignedHugeInt object has no words or value.");
    }
    HugeIntWord *newMostSigWord = oldMostSigWord->get_next_word();
    if (newMostSigWord == NULL) {
        throw std::logic_error("An attempt was made to remove the only word of an UnsignedHugeInt object.");
    }
    newMostSigWord->remove_more_significant_word();
    this->mostSigWord = newMostSigWord;
    --this->numWords;
    delete(oldMostSigWord);
    return newMostSigWord;
}

bool UnsignedHugeInt::is_prime() {
    // ToDo: Complete this method.
    return false;
}

std::string UnsignedHugeInt::to_string() {
    // ToDo: Convert the words to base 10 when forming the string.
    std::string numberString = "", wordString;
    HugeIntWord *thisWord;
    if (this->numWords == 0)
        numberString = "0";
    else {
        thisWord = this->mostSigWord;
        while (thisWord != NULL) {
            wordString = thisWord->to_string();
            numberString += wordString;
            thisWord = thisWord->get_next_word();
        }
    }
    return numberString;
}

HugeIntWord* UnsignedHugeInt::add_word() {
    return this->add_word((unsigned long long)0);
}

HugeIntWord* UnsignedHugeInt::add_word(unsigned long long value) {
    if (value > UnsignedHugeInt::max_word_value) {
        unsigned long carryValue = value / UnsignedHugeInt::word_base;
        unsigned long long lesserValue = value % UnsignedHugeInt::word_base;
        HugeIntWord *lesserWord, *greaterWord;
        lesserWord = new HugeIntWord(lesserValue);
        greaterWord = new HugeIntWord(carryValue, 1, lesserWord);
        this->add_word(lesserWord);
        this->add_word(greaterWord);
        return greaterWord;
    }
    else {
        HugeIntWord *newWord = new HugeIntWord(value);
        this->add_word(newWord);
        return newWord;
    }
}

HugeIntWord* UnsignedHugeInt::add_word(HugeIntWord* new_word) {
    if (new_word == NULL) {
        throw std::invalid_argument("A null word was added to an UnsignedHugeInt.");
    }
    HugeIntWord *oldMostSigWord = this->mostSigWord;
    new_word->set_less_significant_word(oldMostSigWord, this->numWords);
    oldMostSigWord->set_more_significant_word(new_word);
    this->mostSigWord = new_word;
    return new_word;
    ++this->numWords;        
}

void UnsignedHugeInt::throw_warning(std::string message) {
    std::cout << message << "\n";
}
