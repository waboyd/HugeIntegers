#include "UnsignedHugeInt.h"

// ToDo: Set the max_word_value in UnsignedHugeInt and HugeIntWord.
unsigned long long UnsignedHugeInt::max_word_value = 999999999;
unsigned long long UnsignedHugeInt::word_base = UnsignedHugeInt::max_word_value + 1;

UnsignedHugeInt::UnsignedHugeInt() {
    // ToDo: Set maximum word value.
    HugeIntWord *newWord = new HugeIntWord(0);
    this->mostSigWord = newWord;
    this->leastSigWord = newWord;
}

UnsignedHugeInt::UnsignedHugeInt(const unsigned long long value) {
    // ToDo: Set maximum word value.
    HugeIntWord *newWord = new HugeIntWord(0);
    this->leastSigWord = newWord;
    this->mostSigWord = newWord->add_value(value);
}

UnsignedHugeInt::UnsignedHugeInt(std::string integer_string) {
    // ToDo: handle bases that are not a power of 10.
    std::string thisWordString;
    char thisWordChar[MAX_DIGITS_PER_WORD + 1];
    unsigned long long thisWordValue;
    unsigned long long thisWordIndex = integer_string.length();
    HugeIntWord *thisWordObject = new HugeIntWord(0);
    HugeIntWord *newWordObject;
    this->leastSigWord = thisWordObject;
    
    // Add words for the least significant words.
    while (thisWordIndex > MAX_DIGITS_PER_WORD) {
        thisWordIndex -= MAX_DIGITS_PER_WORD;
        thisWordString = integer_string.substr(thisWordIndex, MAX_DIGITS_PER_WORD);
        strcpy(thisWordChar, thisWordString.c_str());
        thisWordValue = strtoul(thisWordChar, NULL, 10);
        thisWordObject->add_value(thisWordValue);
        newWordObject = new HugeIntWord(0, thisWordObject);
        thisWordObject = newWordObject;
    }
    
    // 
    thisWordString = integer_string.substr(0, thisWordIndex);
    strcpy(thisWordChar, thisWordString.c_str());
    thisWordValue = strtoul(thisWordChar, NULL, 10);
    this->mostSigWord = thisWordObject->add_value(thisWordValue);
}

UnsignedHugeInt::UnsignedHugeInt(const UnsignedHugeInt& orig) {
    // ToDo: Complete this method.
}

UnsignedHugeInt::~UnsignedHugeInt() {
    HugeIntWord *thisWord = this->mostSigWord;
    HugeIntWord *wordToDelete, *nextWord;
    while (thisWord != NULL) {
        wordToDelete = thisWord;
        
        nextWord = thisWord->get_next_lower_sig_word();
        delete(wordToDelete);
        thisWord = nextWord;
    }
}

short UnsignedHugeInt::compare(const UnsignedHugeInt& numberA, const UnsignedHugeInt& numberB) {

//    if (numberA == NULL || numberB == NULL) {
//        throw std::invalid_argument("A null value was compared.");
//    }

    unsigned long long numWordsA = numberA.num_words();
    unsigned long long numWordsB = numberB.num_words();
    HugeIntWord *thisWordA, *thisWordB;
    unsigned long long wordValueA, wordValueB;
    
    thisWordA = numberA.get_most_significant_word();
    thisWordB = numberB.get_most_significant_word();
    
    if (numWordsA > numWordsB && thisWordA->get_value() > 0)
        return 1;
    else if (numWordsA < numWordsB && thisWordB->get_value() > 0)
        return -1;
        
    while (thisWordA != NULL && thisWordB != NULL) {
        wordValueA = thisWordA->get_value();
        wordValueB = thisWordB->get_value();
        if (wordValueA > wordValueB)
            return 1;
        else if (wordValueA < wordValueB)
            return -1;
        thisWordA = thisWordA->get_next_lower_sig_word();
        thisWordB = thisWordB->get_next_lower_sig_word();
    }
    
    if ((thisWordA == NULL && thisWordB != NULL) || (thisWordA != NULL && thisWordB == NULL)) {
        throw std::logic_error("A problem occurred involving the number of words in an UnsignedHugeInt.");
    }
    
    return 0;   // The numbers are equal.
}

UnsignedHugeInt* UnsignedHugeInt::sum_of(const UnsignedHugeInt& addendA, const UnsignedHugeInt& addendB) {
    UnsignedHugeInt *sum;
    HugeIntWord *greaterAddendWord, *lesserAddendWord;
    HugeIntWord *sumWord, *sumMostSigWord;
    unsigned long long thisWordSum, carryValue = 0;
    
    if (addendB.num_words() > addendA.num_words()) {
        greaterAddendWord = addendB.get_least_significant_word();
        lesserAddendWord = addendA.get_least_significant_word();
    }
    else {
        greaterAddendWord = addendA.get_least_significant_word();
        lesserAddendWord = addendB.get_least_significant_word();
    }
    sum = new UnsignedHugeInt;
    sumWord = sum->get_least_significant_word();
    sumMostSigWord = sum->get_most_significant_word();
    
    while (lesserAddendWord != NULL) {
        thisWordSum = greaterAddendWord->get_value() + lesserAddendWord->get_value() + carryValue;
        carryValue = thisWordSum / UnsignedHugeInt::word_base;
        thisWordSum = thisWordSum % UnsignedHugeInt::word_base;
        
        if (sumWord == NULL) {
            sumWord = sum->add_word(thisWordSum);
            sumMostSigWord = sumWord;
        }
        else {
            sumMostSigWord = sumWord->add_value(thisWordSum);
        }
        greaterAddendWord = greaterAddendWord->get_next_more_sig_word();
        lesserAddendWord = lesserAddendWord->get_next_more_sig_word();
        sumWord = sumWord->get_next_more_sig_word();
    }
    
    while (greaterAddendWord != NULL) {
        thisWordSum = greaterAddendWord->get_value() + carryValue;
        carryValue = thisWordSum / UnsignedHugeInt::word_base;
        thisWordSum = thisWordSum % UnsignedHugeInt::word_base;
        
        if (sumWord == NULL) {
            sumWord = sum->add_word(thisWordSum);
            sumMostSigWord = sumWord;
        }
        else {
            sumMostSigWord = sumWord->add_value(thisWordSum);
        }
        greaterAddendWord = greaterAddendWord->get_next_more_sig_word();
        sumWord = sumWord->get_next_more_sig_word();
    }
    
    while (carryValue > 0) {
        thisWordSum = carryValue % UnsignedHugeInt::word_base;
        carryValue = carryValue / UnsignedHugeInt::word_base;
        
        if (sumWord == NULL) {
            sumWord = sum->add_word(thisWordSum);
            sumMostSigWord = sumWord;
        }
        else {
            sumMostSigWord = sumWord->add_value(thisWordSum);
        }
        sumWord = sumWord->get_next_more_sig_word();        
    }
    sum->mostSigWord = sumMostSigWord;
    return sum;
}

UnsignedHugeInt* UnsignedHugeInt::operator+(const UnsignedHugeInt& addend) const {
    UnsignedHugeInt *sum;
    
    // ToDo: Remove these print statements.
    std::cout << "First addend: " << this->to_string() << "\n";
    std::cout << "Second addend: " << addend.to_string() << "\n";
    
    sum = UnsignedHugeInt::sum_of(*this, addend);
//    unsigned long long numSumWords = 0;
//    unsigned long long thisWordSum;
//    unsigned long long thisCarryValue = 0;
//    HugeIntWord *thisAddendWordA = this->leastSigWord;
//    HugeIntWord *thisAddendWordB = addend.
    
//    thisWordSum = addend % UnsignedHugeInt::word_base;
//    thisCarryValue = addend / UnsignedHugeInt::word_base;
//    thisWordSum += thisAddendWordA->get_value();
//    thisCarryValue += thisWordSum / UnsignedHugeInt::word_base;
//    thisWordSum = thisWordSum % UnsignedHugeInt::word_base;
//    sum = new UnsignedHugeInt(thisWordSum);
//    
//    thisAddendWordA = thisAddendWordA->get_next_more_sig_word();
//    
//    while (thisAddendWordA != NULL || thisCarryValue > 0) {
//        thisWordSum = thisCarryValue;
//        if (thisAddendWordA != NULL) {
//            thisWordSum += thisAddendWordA->get_value();
//            thisAddendWordA = thisAddendWordA->get_next_more_sig_word();
//        }
//        thisCarryValue = thisWordSum / UnsignedHugeInt::word_base;
//        thisWordSum = thisWordSum % UnsignedHugeInt::word_base;
//        sum->add_word(thisWordSum);
//    }
    return sum;
}

UnsignedHugeInt* UnsignedHugeInt::operator+(const long long addend) const {
    UnsignedHugeInt *sum;
    
//    std::cout << "First addend: " << this->to_string() << "\n";
//    std::cout << "Second addend: " << addend << "\n";
//    
    unsigned long long thisWordSum;
    unsigned long long thisCarryValue = 0;
    HugeIntWord *thisAddendWord = this->leastSigWord;
    
    thisWordSum = addend % UnsignedHugeInt::word_base;
    thisCarryValue = addend / UnsignedHugeInt::word_base;
    thisWordSum += thisAddendWord->get_value();
    thisCarryValue += thisWordSum / UnsignedHugeInt::word_base;
    thisWordSum = thisWordSum % UnsignedHugeInt::word_base;
    sum = new UnsignedHugeInt(thisWordSum);
    
    thisAddendWord = thisAddendWord->get_next_more_sig_word();
    
    while (thisAddendWord != NULL || thisCarryValue > 0) {
        thisWordSum = thisCarryValue;
        if (thisAddendWord != NULL) {
            thisWordSum += thisAddendWord->get_value();
            thisAddendWord = thisAddendWord->get_next_more_sig_word();
        }
        thisCarryValue = thisWordSum / UnsignedHugeInt::word_base;
        thisWordSum = thisWordSum % UnsignedHugeInt::word_base;
        sum->add_word(thisWordSum);
    }
    return sum;

}

UnsignedHugeInt UnsignedHugeInt::operator-(UnsignedHugeInt minuend) const {
    // ToDo: Complete this method.
    UnsignedHugeInt difference;
    
    return difference;
}

UnsignedHugeInt UnsignedHugeInt::operator-(long long minuend) const {
    // ToDo: Complete this method.
    UnsignedHugeInt difference;
    
    return difference;
}

UnsignedHugeInt UnsignedHugeInt::operator*(UnsignedHugeInt factor) const {
    // ToDo: Complete this method.
    UnsignedHugeInt product;
    
    return product;
}

UnsignedHugeInt UnsignedHugeInt::operator*(long long factor) const {
    // ToDo: Complete this method.
    UnsignedHugeInt product;
    
    return product;
}

UnsignedHugeInt UnsignedHugeInt::operator/(UnsignedHugeInt divisor) const {
    // ToDo: Complete this method.
    UnsignedHugeInt quotient;
    
    return quotient;
}

UnsignedHugeInt UnsignedHugeInt::operator/(long long divisor) const {
    // ToDo: Complete this method.
    UnsignedHugeInt quotient;
    
    return quotient;
}

long UnsignedHugeInt::num_words() const {
    return (this->mostSigWord->get_word_number() + 1);
}

HugeIntWord* UnsignedHugeInt::get_most_significant_word() const {
    return this->mostSigWord;
}

HugeIntWord* UnsignedHugeInt::get_least_significant_word() const {
    return this->leastSigWord;
}

HugeIntWord* UnsignedHugeInt::remove_most_significant_word() {
    HugeIntWord *oldMostSigWord = this->mostSigWord;
    if (oldMostSigWord == NULL) {
        throw std::logic_error("An UnsignedHugeInt object has no words or value.");
    }
    HugeIntWord *newMostSigWord = oldMostSigWord->get_next_lower_sig_word();
    if (newMostSigWord == NULL) {
        throw std::logic_error("An attempt was made to remove the only word of an UnsignedHugeInt object.");
    }
    newMostSigWord->remove_more_significant_word();
    this->mostSigWord = newMostSigWord;
    delete(oldMostSigWord);
    return newMostSigWord;
}

bool UnsignedHugeInt::is_prime() {
    // ToDo: Complete this method.
    return false;
}

std::string UnsignedHugeInt::to_string() const {
    // ToDo: Convert the words to base 10 when forming the string.
    std::string numberString = "", wordString;
    HugeIntWord *thisWord;
    if (this->mostSigWord == NULL)
        numberString = "0";
    else {
        thisWord = this->mostSigWord;
        while (thisWord != NULL) {
            wordString = thisWord->to_string();
            numberString += wordString;
            thisWord = thisWord->get_next_lower_sig_word();
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
        greaterWord = new HugeIntWord(carryValue, lesserWord);
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
    new_word->set_less_significant_word(oldMostSigWord);
    oldMostSigWord->set_more_significant_word(new_word);
    this->mostSigWord = new_word;
    return new_word;
}

void UnsignedHugeInt::throw_warning(std::string message) {
    std::cout << message << "\n";
}