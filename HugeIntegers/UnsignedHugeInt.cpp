#include "UnsignedHugeInt.h"

// ToDo: Set the max_word_value in UnsignedHugeInt and HugeIntWord.
unsigned long long UnsignedHugeInt::max_word_value = 999999999;
unsigned long long UnsignedHugeInt::word_base = UnsignedHugeInt::max_word_value + 1;

UnsignedHugeInt::UnsignedHugeInt() {
    // ToDo: Set maximum word value.
    HugeIntWord *newWord = new HugeIntWord(0);
    this->mostSigWord = newWord;
    this->leastSigWord = newWord;
    this->defined_key_1 = CHECK_VALUE_A;
    this->defined_key_2 = CHECK_VALUE_B;
}

UnsignedHugeInt::UnsignedHugeInt(const unsigned long long value) {
    // ToDo: Set maximum word value.
    HugeIntWord *newWord = new HugeIntWord(0);
    this->leastSigWord = newWord;
    this->mostSigWord = newWord->add_value(value);
    this->defined_key_1 = CHECK_VALUE_A;
    this->defined_key_2 = CHECK_VALUE_B;
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
    
    // Set the most significant word.
    thisWordString = integer_string.substr(0, thisWordIndex);
    strcpy(thisWordChar, thisWordString.c_str());
    thisWordValue = strtoul(thisWordChar, NULL, 10);
    this->mostSigWord = thisWordObject->add_value(thisWordValue);
    this->remove_extra_leading_words();
    this->defined_key_1 = CHECK_VALUE_A;
    this->defined_key_2 = CHECK_VALUE_B;
}

UnsignedHugeInt::UnsignedHugeInt(const UnsignedHugeInt& orig) {
    this->change_to_copy_of(orig);
    this->defined_key_1 = CHECK_VALUE_A;
    this->defined_key_2 = CHECK_VALUE_B;
}

UnsignedHugeInt::UnsignedHugeInt(const UnsignedHugeInt* orig) {
    this->change_to_copy_of(*orig);
    this->defined_key_1 = CHECK_VALUE_A;
    this->defined_key_2 = CHECK_VALUE_B;
}

UnsignedHugeInt::~UnsignedHugeInt() {
    if(!this->is_defined()) {
        delete(this->mostSigWord);
        delete(this->leastSigWord);
        std::cout << "Warning: The destructor was called for a non-defined UnsignedHugeInt object.\n";
        return;
    }
    HugeIntWord *thisWord = this->mostSigWord;
    HugeIntWord *wordToDelete, *nextWord;
    while (thisWord != NULL) {
        wordToDelete = thisWord;
        
        nextWord = thisWord->get_next_lower_sig_word();
        delete(wordToDelete);
        thisWord = nextWord;
    }
}

// ToDo: Check that the object exists as a precondition of the operations.
short UnsignedHugeInt::compare(const UnsignedHugeInt& numberA, const UnsignedHugeInt& numberB) {
    if(!numberA.is_defined() || !numberB.is_defined()) {
        throw std::invalid_argument("One of the numbers of the comparison operation is not defined.");
    }
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

UnsignedHugeInt& UnsignedHugeInt::sum_of(const UnsignedHugeInt& addendA, const UnsignedHugeInt& addendB) {
    if(!addendA.is_defined() || !addendB.is_defined()) {
        throw std::invalid_argument("One of the numbers of the addition operation is not defined.");
    }
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
    return *sum;
}

UnsignedHugeInt& UnsignedHugeInt::sum_of(const UnsignedHugeInt& addendA, const unsigned long long addendB) {
    if(!addendA.is_defined()) {
        throw std::invalid_argument("One of the numbers of the addition operation is not defined.");
    }
    UnsignedHugeInt *sum;
    unsigned long long thisWordSum;
    unsigned long long thisCarryValue = 0;
    HugeIntWord *thisAddendWord = addendA.get_least_significant_word();
    
    thisWordSum = addendB % UnsignedHugeInt::word_base;
    thisCarryValue = addendB / UnsignedHugeInt::word_base;
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
    return *sum;
}

UnsignedHugeInt& UnsignedHugeInt::operator+(const UnsignedHugeInt& addend) const {
    return UnsignedHugeInt::sum_of(*this, addend);
}

UnsignedHugeInt& UnsignedHugeInt::operator+(const long long addend) const {
    return UnsignedHugeInt::sum_of(this, addend);
}

UnsignedHugeInt& operator+(const unsigned long long addendA, const UnsignedHugeInt& addendB) {
    return UnsignedHugeInt::sum_of(addendB, addendA);
}

UnsignedHugeInt& UnsignedHugeInt::subtract(const UnsignedHugeInt& minuend, const UnsignedHugeInt& subtrahend) {
    if(!minuend.is_defined() || !subtrahend.is_defined()) {
        throw std::invalid_argument("One of the UnsignedHugeInts of the subtraction operation is not defined.");
    }
    if (UnsignedHugeInt::compare(minuend, subtrahend) < 0) {
        throw std::range_error("The subtrahend of an unsigned subtraction operation was greater than the minuend.");
    }
    
    UnsignedHugeInt *difference;
    HugeIntWord *minuendWord, *subtrahendWord;
//    HugeIntWord *differenceWord;
    unsigned long long thisWordDifference, thisMinuendWordValue, thisSubtrahendWordValue, carryValue;
    
    // Determine the least significant word of the difference.
    minuendWord = minuend.get_least_significant_word();
    if (minuendWord == NULL)
        return *(new UnsignedHugeInt((unsigned long long)0));
    subtrahendWord = subtrahend.get_least_significant_word();
    if (subtrahendWord == NULL)
        return *(new UnsignedHugeInt(minuend));
    thisMinuendWordValue = minuendWord->get_value();
    thisSubtrahendWordValue = subtrahendWord->get_value();
    if (thisMinuendWordValue < thisSubtrahendWordValue) {
        carryValue = 1;
        thisWordDifference = (UnsignedHugeInt::word_base + thisMinuendWordValue) - thisSubtrahendWordValue;
    }
    else {
        carryValue = 0;
        thisWordDifference = thisMinuendWordValue - thisSubtrahendWordValue;
    }        
    difference = new UnsignedHugeInt(thisWordDifference);
//    differenceWord = difference->get_least_significant_word();
    difference->get_least_significant_word();
    minuendWord = minuendWord->get_next_more_sig_word();
    subtrahendWord = subtrahendWord->get_next_more_sig_word();
    
    // Subtract all the words of the subtrahend.    
    while (subtrahendWord != NULL) {
        thisMinuendWordValue = minuendWord->get_value();
        thisSubtrahendWordValue = subtrahendWord->get_value() + carryValue;
        if (thisMinuendWordValue < thisSubtrahendWordValue) {
            carryValue = 1;
            thisWordDifference = (HugeIntWord::base_value + thisMinuendWordValue) - thisSubtrahendWordValue;
        }
        else {
            carryValue = 0;
            thisWordDifference = thisMinuendWordValue - thisSubtrahendWordValue;
        }
//        differenceWord = difference->add_word(thisWordDifference);
        difference->add_word(thisWordDifference);
        minuendWord = minuendWord->get_next_more_sig_word();
        subtrahendWord = subtrahendWord->get_next_more_sig_word();
    }
    
    // Continue carry operations from the remaining words of the menuend.
    while (minuendWord != NULL && carryValue > 0) {
        thisMinuendWordValue = minuendWord->get_value();
        if (thisMinuendWordValue < carryValue) {
            carryValue = 1;
            thisWordDifference = (HugeIntWord::base_value + thisMinuendWordValue) - carryValue;
        }
        else {
            carryValue = 0;
            thisWordDifference = thisMinuendWordValue - carryValue;
        }
//        differenceWord = difference->add_word(thisWordDifference);
        difference->add_word(thisWordDifference);
        minuendWord = minuendWord->get_next_more_sig_word();
    }
    
    // After carry operations are finished, copy the minuend words to the difference.
    while (minuendWord != NULL) {
        thisMinuendWordValue = minuendWord->get_value();
//        differenceWord = difference->add_word(thisMinuendWordValue);
        difference->add_word(thisMinuendWordValue);
        minuendWord = minuendWord->get_next_more_sig_word();
    }
//    this->mostSigWord = differenceWord;
    difference->remove_extra_leading_words();
    return *difference;
}

UnsignedHugeInt& UnsignedHugeInt::operator-(UnsignedHugeInt& subtrahend) const {
    return UnsignedHugeInt::subtract(*this, subtrahend);
}

UnsignedHugeInt& UnsignedHugeInt::operator-(long long subtrahend) const {
    UnsignedHugeInt subtrahendObject(subtrahend);
    return UnsignedHugeInt::subtract(*this, subtrahendObject);
}

UnsignedHugeInt& operator-(const unsigned long long minuend, const UnsignedHugeInt& subtrahend) {
    UnsignedHugeInt minuendObject(minuend);
    return UnsignedHugeInt::subtract(minuendObject, subtrahend);
}

UnsignedHugeInt& UnsignedHugeInt::multiply(const UnsignedHugeInt& factorA, const UnsignedHugeInt& factorB) {
    if(!factorA.is_defined() || !factorB.is_defined()) {
        throw std::invalid_argument("One of the numbers of the multiplication operation is not defined.");
    }
    
    return *(new UnsignedHugeInt);
}

UnsignedHugeInt& UnsignedHugeInt::operator*(UnsignedHugeInt factor) const {
    // ToDo: Complete this method.
    UnsignedHugeInt *product = new UnsignedHugeInt;
    
    return *product;
}

UnsignedHugeInt& UnsignedHugeInt::operator*(long long factor) const {
    // ToDo: Complete this method.
    UnsignedHugeInt *product = new UnsignedHugeInt;
    
    return *product;
}

UnsignedHugeInt& operator*(const unsigned long long factorA, const UnsignedHugeInt& factorB) {
    // ToDo: Complete this method.
    
    return *(new UnsignedHugeInt);  // Placeholder
}

UnsignedHugeInt& UnsignedHugeInt::operator/(UnsignedHugeInt divisor) const {
    // ToDo: Complete this method.
    UnsignedHugeInt *quotient = new UnsignedHugeInt;
    
    return *quotient;
}

UnsignedHugeInt& UnsignedHugeInt::operator/(long long divisor) const {
    // ToDo: Complete this method.
    UnsignedHugeInt *quotient = new UnsignedHugeInt;
    
    return *quotient;
}

bool UnsignedHugeInt::is_defined() const {
    if ((this->defined_key_1 != CHECK_VALUE_A) || (this->defined_key_2 != CHECK_VALUE_B) ||
        ((this->leastSigWord != NULL) && 
        ((this->leastSigWord->get_next_lower_sig_word() != NULL) || (this->mostSigWord->get_next_more_sig_word() != NULL)))) {
            throw std::invalid_argument("An UnsignedHugeInt object was used before it was defined.");
            return false;
    }
    return true;
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
    if(!this->is_defined()) {
        throw std::invalid_argument("An attempt was made to remove a word from a non-defined number.");
        return NULL;
    }
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
    if(!this->is_defined()) {
        throw std::invalid_argument("An attempt was made to retrieve the value of a non-defined UnsignedHugeInt.");
        return "";
    }
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

void UnsignedHugeInt::change_to_copy_of(const UnsignedHugeInt& orig) {
    HugeIntWord *thisCopyWord, *thisOrigWord;
    thisOrigWord = orig.get_least_significant_word();
    if (thisOrigWord != NULL) {
        thisCopyWord = new HugeIntWord(thisOrigWord->get_value());
        this->leastSigWord = thisCopyWord;
        thisOrigWord = thisOrigWord->get_next_more_sig_word();
    }
    else {
        thisCopyWord = new HugeIntWord(0);
        this->leastSigWord = thisCopyWord;
        this->mostSigWord = thisCopyWord;
        return;
    }
    this->leastSigWord = thisCopyWord;
    while (thisOrigWord != NULL) {
        thisCopyWord = new HugeIntWord(thisOrigWord->get_value(), thisCopyWord);
        thisOrigWord = thisOrigWord->get_next_more_sig_word();
    }
    this->mostSigWord = thisCopyWord;
}

void UnsignedHugeInt::remove_extra_leading_words() {
    while ((this->mostSigWord->value == 0) && (this->mostSigWord != this->leastSigWord)) {
        this->mostSigWord = this->mostSigWord->get_next_lower_sig_word();
        this->mostSigWord->remove_more_significant_word();
    }
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

HugeIntWord* find_multiplication_subtotal(HugeIntWord* greater_factor_word, HugeIntWord* lesser_factor_word) {
    // ToDo: Complete this method.
//    HugeIntWord *thisWordA, *thisWordB; // thisWordA is taken in descending place values.
    
    return new HugeIntWord(0);
}