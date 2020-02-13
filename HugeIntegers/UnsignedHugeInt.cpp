#include "UnsignedHugeInt.h"

// ToDo: Set the max_word_value in UnsignedHugeInt and HugeIntWord.
unsigned long long UnsignedHugeInt::max_word_value = 999999999;
unsigned long long UnsignedHugeInt::word_base = UnsignedHugeInt::max_word_value + 1;
unsigned int UnsignedHugeInt::num_objects_created = 0;
unsigned int UnsignedHugeInt::num_objects_deleted = 0;

UnsignedHugeInt::UnsignedHugeInt() {
    // ToDo: Set maximum word value.
    HugeIntWord *newWord = new HugeIntWord(0);
    this->mostSigWord = newWord;
    this->leastSigWord = newWord;
    this->defined_key_1 = CHECK_VALUE_A;
    this->defined_key_2 = CHECK_VALUE_B;
    ++UnsignedHugeInt::num_objects_created;
}

UnsignedHugeInt::UnsignedHugeInt(const unsigned long long value) {
    // ToDo: Set maximum word value.
    HugeIntWord *newWord = new HugeIntWord(0);
    this->leastSigWord = newWord;
    this->mostSigWord = newWord->add_value(value);
    this->defined_key_1 = CHECK_VALUE_A;
    this->defined_key_2 = CHECK_VALUE_B;
    ++UnsignedHugeInt::num_objects_created;
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
    ++UnsignedHugeInt::num_objects_created;
}

UnsignedHugeInt::UnsignedHugeInt(const UnsignedHugeInt& orig) {
    this->change_to_copy_of(orig);
    this->defined_key_1 = CHECK_VALUE_A;
    this->defined_key_2 = CHECK_VALUE_B;
    ++UnsignedHugeInt::num_objects_created;
}

UnsignedHugeInt::UnsignedHugeInt(const UnsignedHugeInt* orig) {
    this->change_to_copy_of(*orig);
    this->defined_key_1 = CHECK_VALUE_A;
    this->defined_key_2 = CHECK_VALUE_B;
    ++UnsignedHugeInt::num_objects_created;
}

UnsignedHugeInt::~UnsignedHugeInt() {
    if(!this->is_defined()) {
        delete(this->mostSigWord);
        delete(this->leastSigWord);
        std::cout << "Warning: The destructor was called for a non-defined UnsignedHugeInt object.\n";
        return;
    }
    this->delete_all_words();
    this->defined_key_1 = 0;
    this->defined_key_2 = 0;
    ++UnsignedHugeInt::num_objects_deleted;
}

void UnsignedHugeInt::operator=(const UnsignedHugeInt& orig) {
    if (this == &orig)
        return;
    if(this->is_defined()) {
        this->delete_all_words();
        ++UnsignedHugeInt::num_objects_deleted;
    }
    this->change_to_copy_of(orig);
    this->defined_key_1 = CHECK_VALUE_A;
    this->defined_key_2 = CHECK_VALUE_B;
    ++UnsignedHugeInt::num_objects_created;
}

void UnsignedHugeInt::operator=(const UnsignedHugeInt* orig) {
    if (this == orig)
        return;
    if(this->is_defined()) {
        this->delete_all_words();
        ++UnsignedHugeInt::num_objects_deleted;
    }
    this->change_to_copy_of(*orig);
    this->defined_key_1 = CHECK_VALUE_A;
    this->defined_key_2 = CHECK_VALUE_B;
    ++UnsignedHugeInt::num_objects_created;
}

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

bool UnsignedHugeInt::operator<(const UnsignedHugeInt& right_operand) const {
    return UnsignedHugeInt::compare(*this, right_operand) < 0;
}

bool UnsignedHugeInt::operator<(const unsigned long long right_operand) const {
    return UnsignedHugeInt::compare(*this, UnsignedHugeInt(right_operand)) < 0;    
}

bool operator<(const unsigned long long left_operand, const UnsignedHugeInt& right_operand) {
    return UnsignedHugeInt::compare(UnsignedHugeInt(left_operand), right_operand) < 0;
}

bool UnsignedHugeInt::operator<=(const UnsignedHugeInt& right_operand) const {
    return UnsignedHugeInt::compare(*this, right_operand) <= 0;
}

bool UnsignedHugeInt::operator<=(const unsigned long long right_operand) const {
    return UnsignedHugeInt::compare(*this, UnsignedHugeInt(right_operand)) <= 0;    
}

bool operator<=(const unsigned long long left_operand, const UnsignedHugeInt& right_operand) {
    return UnsignedHugeInt::compare(UnsignedHugeInt(left_operand), right_operand) <= 0;
}

bool UnsignedHugeInt::operator>(const UnsignedHugeInt& right_operand) const {
    return UnsignedHugeInt::compare(*this, right_operand) > 0;
}

bool UnsignedHugeInt::operator>(const unsigned long long right_operand) const {
    return UnsignedHugeInt::compare(*this, UnsignedHugeInt(right_operand)) > 0;    
}

bool operator>(const unsigned long long left_operand, const UnsignedHugeInt& right_operand) {
    return UnsignedHugeInt::compare(UnsignedHugeInt(left_operand), right_operand) > 0;
}

bool UnsignedHugeInt::operator>=(const UnsignedHugeInt& right_operand) const {
    return UnsignedHugeInt::compare(*this, right_operand) >= 0;
}

bool UnsignedHugeInt::operator>=(const unsigned long long right_operand) const {
    return UnsignedHugeInt::compare(*this, UnsignedHugeInt(right_operand)) >= 0;    
}

bool operator>=(const unsigned long long left_operand, const UnsignedHugeInt& right_operand) {
    return UnsignedHugeInt::compare(UnsignedHugeInt(left_operand), right_operand) >= 0;
}

bool UnsignedHugeInt::operator==(const UnsignedHugeInt& right_operand) const {
    return UnsignedHugeInt::compare(*this, right_operand) == 0;
}

bool UnsignedHugeInt::operator==(const unsigned long long right_operand) const {
    return UnsignedHugeInt::compare(*this, UnsignedHugeInt(right_operand)) == 0;    
}

bool operator==(const unsigned long long left_operand, const UnsignedHugeInt& right_operand) {
    return UnsignedHugeInt::compare(UnsignedHugeInt(left_operand), right_operand) == 0;
}

bool UnsignedHugeInt::operator!=(const UnsignedHugeInt& right_operand) const {
    return UnsignedHugeInt::compare(*this, right_operand) != 0;
}

bool UnsignedHugeInt::operator!=(const unsigned long long right_operand) const {
    return UnsignedHugeInt::compare(*this, UnsignedHugeInt(right_operand)) != 0;    
}

bool operator!=(const unsigned long long left_operand, const UnsignedHugeInt& right_operand) {
    return UnsignedHugeInt::compare(UnsignedHugeInt(left_operand), right_operand) != 0;
}

UnsignedHugeInt UnsignedHugeInt::sum_of(const UnsignedHugeInt& addendA, const UnsignedHugeInt& addendB) {
    if(!addendA.is_defined() || !addendB.is_defined()) {
        throw std::invalid_argument("One of the numbers of the addition operation is not defined.");
    }
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
    UnsignedHugeInt sum((unsigned long long)0);
    sumWord = sum.get_least_significant_word();
    sumMostSigWord = sum.get_most_significant_word();
    
    while (lesserAddendWord != NULL) {
        thisWordSum = greaterAddendWord->get_value() + lesserAddendWord->get_value() + carryValue;
        carryValue = thisWordSum / UnsignedHugeInt::word_base;
        thisWordSum = thisWordSum % UnsignedHugeInt::word_base;
        
        if (sumWord == NULL) {
            sumWord = sum.add_word(thisWordSum);
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
            sumWord = sum.add_word(thisWordSum);
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
            sumWord = sum.add_word(thisWordSum);
            sumMostSigWord = sumWord;
        }
        else {
            sumMostSigWord = sumWord->add_value(thisWordSum);
        }
        sumWord = sumWord->get_next_more_sig_word();        
    }
    sum.mostSigWord = sumMostSigWord;
    return sum;
}


UnsignedHugeInt UnsignedHugeInt::sum_of(const UnsignedHugeInt& addendA, const unsigned long long addendB) {
    if(!addendA.is_defined()) {
        throw std::invalid_argument("One of the numbers of the addition operation is not defined.");
    }
    unsigned long long thisWordSum;
    unsigned long long thisCarryValue = 0;
    HugeIntWord *thisAddendWord = addendA.get_least_significant_word();
    
    thisWordSum = addendB % UnsignedHugeInt::word_base;
    thisCarryValue = addendB / UnsignedHugeInt::word_base;
    thisWordSum += thisAddendWord->get_value();
    thisCarryValue += thisWordSum / UnsignedHugeInt::word_base;
    thisWordSum = thisWordSum % UnsignedHugeInt::word_base;
    UnsignedHugeInt sum(thisWordSum);
    
    thisAddendWord = thisAddendWord->get_next_more_sig_word();
    
    while (thisAddendWord != NULL || thisCarryValue > 0) {
        thisWordSum = thisCarryValue;
        if (thisAddendWord != NULL) {
            thisWordSum += thisAddendWord->get_value();
            thisAddendWord = thisAddendWord->get_next_more_sig_word();
        }
        thisCarryValue = thisWordSum / UnsignedHugeInt::word_base;
        thisWordSum = thisWordSum % UnsignedHugeInt::word_base;
        sum.add_word(thisWordSum);
    }
    return sum;
}

UnsignedHugeInt UnsignedHugeInt::operator+(const UnsignedHugeInt& addend) const {
    return UnsignedHugeInt::sum_of(*this, addend);
}

UnsignedHugeInt UnsignedHugeInt::operator+(const unsigned long long addend) const {
    return UnsignedHugeInt::sum_of(this, addend);
}

UnsignedHugeInt operator+(const unsigned long long addendA, const UnsignedHugeInt& addendB) {
    return UnsignedHugeInt::sum_of(addendB, addendA);
}

UnsignedHugeInt UnsignedHugeInt::subtract(const UnsignedHugeInt& minuend, const UnsignedHugeInt& subtrahend) {
    if(!minuend.is_defined() || !subtrahend.is_defined()) {
        throw std::invalid_argument("One of the UnsignedHugeInts of the subtraction operation is not defined.");
    }
    if (UnsignedHugeInt::compare(minuend, subtrahend) < 0) {
        throw std::range_error("The subtrahend of an unsigned subtraction operation was greater than the minuend.");
    }
    
    HugeIntWord *minuendWord, *subtrahendWord;
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
    UnsignedHugeInt difference(thisWordDifference);
    difference.get_least_significant_word();
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
        difference.add_word(thisWordDifference);
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
        difference.add_word(thisWordDifference);
        minuendWord = minuendWord->get_next_more_sig_word();
    }
    
    // After carry operations are finished, copy the minuend words to the difference.
    while (minuendWord != NULL) {
        thisMinuendWordValue = minuendWord->get_value();
        difference.add_word(thisMinuendWordValue);
        minuendWord = minuendWord->get_next_more_sig_word();
    }
    difference.remove_extra_leading_words();
    return difference;
}

UnsignedHugeInt UnsignedHugeInt::operator-(const UnsignedHugeInt& subtrahend) const {
    return UnsignedHugeInt::subtract(*this, subtrahend);
}

UnsignedHugeInt UnsignedHugeInt::operator-(const unsigned long long subtrahend) const {
    UnsignedHugeInt subtrahendObject(subtrahend);
    return UnsignedHugeInt::subtract(*this, subtrahendObject);
}

UnsignedHugeInt operator-(const unsigned long long minuend, const UnsignedHugeInt& subtrahend) {
    UnsignedHugeInt minuendObject(minuend);
    return UnsignedHugeInt::subtract(minuendObject, subtrahend);
}

UnsignedHugeInt UnsignedHugeInt::multiply(const UnsignedHugeInt& factorA, const UnsignedHugeInt& factorB) {
    // ToDo: Possibly apply multithreading to this method.
    if(!factorA.is_defined() || !factorB.is_defined()) {
        throw std::invalid_argument("One of the numbers of the multiplication operation is not defined.");
    }
    // Find the product of the least significant word of each factor.
    HugeIntWord *startWordA = factorA.get_least_significant_word(); // Starting words when finding a partial product.
    HugeIntWord *startWordB = factorB.get_least_significant_word();
    if ((startWordA == NULL) || (startWordB == NULL))
        return *(new UnsignedHugeInt(((unsigned long long)0)));    
    UnsignedHugeInt totalProduct(startWordA->get_value() * startWordB->get_value());
    HugeIntWord *totalCalcWord = totalProduct.get_least_significant_word();
    UnsignedHugeInt partialProduct;
    
    // Find partial products while changing startWordA.
    startWordA = startWordA->get_next_more_sig_word();
    while (startWordA != NULL) {
        totalCalcWord = totalCalcWord->get_next_more_sig_word();
        partialProduct = UnsignedHugeInt::find_multiplication_subtotal(startWordA, startWordB);
        totalCalcWord = totalProduct.add_value_at_word(totalCalcWord, partialProduct);
        startWordA = startWordA->get_next_more_sig_word();
    }
    startWordA = factorA.get_most_significant_word();
    
    // Find partial products while changing startWordB.
    startWordB= startWordB->get_next_more_sig_word();
    while (startWordB != NULL) {
        totalCalcWord = totalCalcWord->get_next_more_sig_word();
        partialProduct = UnsignedHugeInt::find_multiplication_subtotal(startWordA, startWordB);
        totalCalcWord = totalProduct.add_value_at_word(totalCalcWord, partialProduct);
        startWordB = startWordB->get_next_more_sig_word();
    }
    
    // Remove leading 0 words.
    totalProduct.remove_extra_leading_words();
    
    return totalProduct;
}

UnsignedHugeInt UnsignedHugeInt::operator*(const UnsignedHugeInt& factor) const {
    return UnsignedHugeInt::multiply(*this, factor);
}

UnsignedHugeInt UnsignedHugeInt::operator*(const unsigned long long factor) const {
    UnsignedHugeInt factorObject(factor);
    return UnsignedHugeInt::multiply(*this, factorObject);
}

UnsignedHugeInt operator*(const unsigned long long factorA, const UnsignedHugeInt& factorB) {
    UnsignedHugeInt factorAObject(factorA);
    return UnsignedHugeInt::multiply(factorAObject, factorB);
}

std::pair<UnsignedHugeInt, UnsignedHugeInt> UnsignedHugeInt::divide(const UnsignedHugeInt& dividend, const UnsignedHugeInt& divisor) {
    if (!dividend.is_defined() || !divisor.is_defined()) {
        throw std::invalid_argument("One of the UnsignedHugeInts of the divide operation is not defined.");
    }
    std::pair<UnsignedHugeInt, UnsignedHugeInt> divisionResults;
    unsigned long long dividendNumWords = dividend.num_words();
    unsigned long long divisorNumWords = divisor.num_words();
    unsigned long long remainderNumWords;
    UnsignedHugeInt quotient((unsigned long long)0);
    HugeIntWord *quotientCalcWord = quotient.get_least_significant_word();
    HugeIntWord *remainderEstimateWord, *dividendNextWord, *divisorEstimateWord;
    double dividendLowerEstimate, divisorUpperEstimate;
    unsigned long long quotientWordEstimate;
    
    if (divisorNumWords == 0 || (divisorNumWords == 1 && divisor.get_least_significant_word()->get_value() == 0)) {
        throw std::invalid_argument("An attempt was made to divide by zero.");
    }
    if (compare(dividend, divisor) < 0) {
        divisionResults.first = quotient;
        divisionResults.second = UnsignedHugeInt(dividend);
        return divisionResults;
    }
    // Add words to the quotient.
    dividendNextWord = dividend.get_least_significant_word();
    unsigned long long quotientNumWords = dividendNumWords - divisorNumWords + 1;
    for (unsigned long long wordNumber = 1; wordNumber < quotientNumWords; ++wordNumber) {
        quotientCalcWord = quotient.add_word((unsigned long long)0);
        dividendNextWord = dividendNextWord->get_next_more_sig_word();
    }
    UnsignedHugeInt subRemainder = integer_with_least_significant_word(dividendNextWord);
    
    // Set the most significant word of the quotient.
        // Give a lower estimate of the quotient word.
        divisorEstimateWord = divisor.get_most_significant_word();
        remainderEstimateWord = subRemainder.get_most_significant_word();
        if (divisorEstimateWord->get_next_lower_sig_word() != NULL) {
            divisorUpperEstimate = divisorEstimateWord->get_value() +
                (((double)divisorEstimateWord->get_next_lower_sig_word()->get_value() + 1) / UnsignedHugeInt::word_base);
            dividendLowerEstimate = remainderEstimateWord->get_value() +
                (((double)remainderEstimateWord->get_next_lower_sig_word()->get_value()) / UnsignedHugeInt::word_base);
        }
        else {
            divisorUpperEstimate = divisorEstimateWord->get_value();
            dividendLowerEstimate = remainderEstimateWord->get_value();
        }
        quotientWordEstimate = (unsigned long long)(dividendLowerEstimate / divisorUpperEstimate);

        // Multiply the quotient word by the divisor, and subtract the product from the remainder.
        subRemainder = UnsignedHugeInt::subtract(subRemainder, UnsignedHugeInt::multiply(divisor, UnsignedHugeInt(quotientWordEstimate)));
        // Increase the quotient word until it is the correct value.
        while (UnsignedHugeInt::compare(subRemainder, divisor) >= 0) {
            ++quotientWordEstimate;
            subRemainder = subtract(subRemainder, divisor);
        }
        // Set the quotient word.
        quotientCalcWord->add_value(quotientWordEstimate);
        // Include the next word in the remainder.
        quotientCalcWord = quotientCalcWord->get_next_lower_sig_word();
        dividendNextWord = dividendNextWord->get_next_lower_sig_word();
    
    // Loop through the dividend's words.
    while (dividendNextWord != NULL) {
        subRemainder.insert_least_significant_word(dividendNextWord->get_value());

        // Give a lower estimate of the quotient word.
        remainderEstimateWord = subRemainder.get_most_significant_word();
        remainderNumWords = subRemainder.num_words();
        if (remainderNumWords > divisorNumWords) {
            dividendLowerEstimate = (UnsignedHugeInt::word_base * remainderEstimateWord->get_value()) +
                remainderEstimateWord->get_next_lower_sig_word()->get_value();
        }
        else if (remainderNumWords < divisorNumWords) {
            dividendLowerEstimate = 0;
        }
        else if (remainderEstimateWord->get_next_lower_sig_word() != NULL)
            dividendLowerEstimate = remainderEstimateWord->get_value() +
                (((double)remainderEstimateWord->get_next_lower_sig_word()->get_value()) / UnsignedHugeInt::word_base);
        else
            dividendLowerEstimate = remainderEstimateWord->get_value();
        quotientWordEstimate = (unsigned long long)(dividendLowerEstimate / divisorUpperEstimate);

        // Multiply the quotient word by the divisor, and subtract the product from the remainder.
        subRemainder = UnsignedHugeInt::subtract(subRemainder, UnsignedHugeInt::multiply(divisor, UnsignedHugeInt(quotientWordEstimate)));
        // Increase the quotient word until it is the correct value.
        while (UnsignedHugeInt::compare(subRemainder, divisor) >= 0) {
            ++quotientWordEstimate;
            subRemainder = subtract(subRemainder, divisor);
        }
        // Set the quotient word.
        quotientCalcWord->add_value(quotientWordEstimate);
        // Include the next word in the remainder.
        quotientCalcWord = quotientCalcWord->get_next_lower_sig_word();
        dividendNextWord = dividendNextWord->get_next_lower_sig_word();
    }
    // Remove leading zeros.
    quotient.remove_extra_leading_words();
    
    divisionResults.first = quotient;
    divisionResults.second = subRemainder;
    return divisionResults;
}

UnsignedHugeInt UnsignedHugeInt::operator/(const UnsignedHugeInt& divisor) const {
    return UnsignedHugeInt::divide(*this, divisor).first;
}

UnsignedHugeInt UnsignedHugeInt::operator/(const unsigned long long divisor) const {
    UnsignedHugeInt divisorObject(divisor);
    return UnsignedHugeInt::divide(*this, divisorObject).first;
}

UnsignedHugeInt operator/(const unsigned long long dividend, const UnsignedHugeInt& divisor) {
    UnsignedHugeInt dividendObject(dividend);
    return UnsignedHugeInt::divide(dividendObject, divisor).first;
}

UnsignedHugeInt UnsignedHugeInt::operator%(const UnsignedHugeInt& divisor) const {
    return UnsignedHugeInt::divide(*this, divisor).second;
}

UnsignedHugeInt UnsignedHugeInt::operator%(const unsigned long long divisor) const {
    UnsignedHugeInt divisorObject(divisor);
    return UnsignedHugeInt::divide(*this, divisorObject).second;
}

UnsignedHugeInt operator%(const unsigned long long dividend, const UnsignedHugeInt& divisor) {
    UnsignedHugeInt dividendObject(dividend);
    return UnsignedHugeInt::divide(dividendObject, divisor).second;
}

UnsignedHugeInt& UnsignedHugeInt::operator+=(const UnsignedHugeInt addend) {
    if(!this->is_defined() || !addend.is_defined()) {
        throw std::invalid_argument("One of the numbers of the compound addition operation is not defined.");
    }
    HugeIntWord *thisWord = this->leastSigWord;
    HugeIntWord *addendWord = addend.get_least_significant_word();
    
    while (addendWord != NULL) {
        if (thisWord != NULL) {
            thisWord->add_value(addendWord->get_value());
        }
        else {
            thisWord = this->add_word(addendWord->get_value());
            this->mostSigWord = thisWord;
        }
        thisWord = thisWord->get_next_more_sig_word();
        addendWord = addendWord->get_next_more_sig_word();
    }
    // Set the most significant word.
    HugeIntWord *nextWord = this->mostSigWord->get_next_more_sig_word();
    while(nextWord != NULL) {
        this->mostSigWord = nextWord;
        nextWord = nextWord->get_next_more_sig_word();
    }
    return *this;
}

UnsignedHugeInt& UnsignedHugeInt::operator+=(const unsigned long long addend) {
    if(!this->is_defined()) {
        throw std::invalid_argument("The UnsignedHugeInt object was not defined before compound addition.");
    }
    this->leastSigWord->add_value(addend);
    // Set the most significant word.
    HugeIntWord *nextWord = this->mostSigWord->get_next_more_sig_word();
    while(nextWord != NULL) {
        this->mostSigWord = nextWord;
        nextWord = nextWord->get_next_more_sig_word();
    }
    return *this;
}

UnsignedHugeInt& UnsignedHugeInt::operator-=(const UnsignedHugeInt subtrahend) {
    // ToDo: Complete this method.
    return *this;
}

UnsignedHugeInt& UnsignedHugeInt::operator-=(const unsigned long long subtrahend) {
    // ToDo: Complete this method.
    return *this;
}

UnsignedHugeInt& UnsignedHugeInt::operator*=(const UnsignedHugeInt factor) {
    // ToDo: Complete this method.
    return *this;
}

UnsignedHugeInt& UnsignedHugeInt::operator*=(const unsigned long long factor) {
    // ToDo: Complete this method.
    return *this;
}

UnsignedHugeInt& UnsignedHugeInt::operator/=(const UnsignedHugeInt divisor) {
    // ToDo: Complete this method.
    return *this;
}

UnsignedHugeInt& UnsignedHugeInt::operator/=(const unsigned long long divisor) {
    // ToDo: Complete this method.
    return *this;
}

UnsignedHugeInt& UnsignedHugeInt::operator%=(const UnsignedHugeInt divisor) {
    // ToDo: Complete this method.
    return *this;
}

UnsignedHugeInt& UnsignedHugeInt::operator%=(const unsigned long long divisor) {
    // ToDo: Complete this method.
    return *this;
}

UnsignedHugeInt& UnsignedHugeInt::operator++() {
    // ToDo: Complete this method.
    return *this;
}

UnsignedHugeInt UnsignedHugeInt::operator++(int dummy) {
    // ToDo: Complete this method.
    return *this;
}

UnsignedHugeInt& UnsignedHugeInt::operator--() {
    // ToDo: Complete this method.
    return *this;
}

UnsignedHugeInt UnsignedHugeInt::operator--(int dummy) {
    // ToDo: Complete this method.
    return *this;
}

bool UnsignedHugeInt::is_defined() const {
    if ((this->defined_key_1 != CHECK_VALUE_A) || (this->defined_key_2 != CHECK_VALUE_B) ||
        ((this->leastSigWord != NULL) && 
        ((this->leastSigWord->get_next_lower_sig_word() != NULL) || (this->mostSigWord->get_next_more_sig_word() != NULL)))) {
//            throw std::invalid_argument("An UnsignedHugeInt object was used before it was defined.");
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

void UnsignedHugeInt::delete_all_words() {
    HugeIntWord *thisWord = this->mostSigWord;
    HugeIntWord *wordToDelete, *nextWord;
    while (thisWord != NULL) {
        wordToDelete = thisWord;
        
        nextWord = thisWord->get_next_lower_sig_word();
        delete(wordToDelete);
        thisWord = nextWord;
    }    
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

HugeIntWord* UnsignedHugeInt::add_word(const unsigned long long value) {
    if (value > UnsignedHugeInt::max_word_value) {
        HugeIntWord *newLesserWord, *newGreaterWord;
        newLesserWord = new HugeIntWord((unsigned long long)0);
        newGreaterWord = newLesserWord->add_value(value);
        this->add_word(newLesserWord);
        this->mostSigWord = newGreaterWord;
        return newGreaterWord;
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

HugeIntWord* UnsignedHugeInt::insert_least_significant_word(unsigned long long least_significant_value) {
    if (this->mostSigWord->get_word_number() == 0 && this->mostSigWord->get_value() == 0) {
        return this->leastSigWord->add_value(least_significant_value);
    }
    HugeIntWord *newWord = new HugeIntWord(least_significant_value);
    HugeIntWord *oldLeastSigWord = this->leastSigWord;
    HugeIntWord *thisWord;
    unsigned long long wordNumber = 2;
    oldLeastSigWord->set_less_significant_word(newWord);
    newWord->set_more_significant_word(oldLeastSigWord);
    this->leastSigWord = newWord;
    for (thisWord = oldLeastSigWord->get_next_more_sig_word(); thisWord != NULL; thisWord = thisWord->get_next_more_sig_word()) {
        thisWord->place_value = wordNumber;
        ++wordNumber;
    }
    return newWord;
}

HugeIntWord* UnsignedHugeInt::add_value_at_word(HugeIntWord* location_to_add, const UnsignedHugeInt& value_to_add) {
    HugeIntWord *thisAddLocation;
    const HugeIntWord *thisValueWord = value_to_add.get_least_significant_word();
    HugeIntWord *moreSigWord;
    HugeIntWord *wordToReturn;
    
    if (location_to_add == NULL) {
        thisAddLocation = this->add_word(new HugeIntWord((unsigned long long)0));
        wordToReturn = thisAddLocation;
    }
    else {
        thisAddLocation = location_to_add;
        wordToReturn = location_to_add;
    }
    
    while (thisValueWord != NULL) {
        if (thisAddLocation == NULL) {
            thisAddLocation = this->add_word(thisValueWord->get_value());
            this->mostSigWord = thisAddLocation;
        }
        else {
            moreSigWord = thisAddLocation->add_value(thisValueWord->get_value());
            if (moreSigWord->get_next_more_sig_word() == NULL)
                this->mostSigWord = moreSigWord;
        }
        
        thisValueWord = thisValueWord->get_next_more_sig_word();
        thisAddLocation = thisAddLocation->get_next_more_sig_word();
    }
    
    // Set the most significant word.
    thisAddLocation = this->mostSigWord;
    moreSigWord = thisAddLocation->get_next_more_sig_word();
    while (moreSigWord != NULL) {
        thisAddLocation = moreSigWord;
        moreSigWord = moreSigWord->get_next_more_sig_word();
    }
    this->mostSigWord = thisAddLocation;
    return wordToReturn;
}

UnsignedHugeInt UnsignedHugeInt::integer_with_least_significant_word(HugeIntWord* least_significant_word) {
    UnsignedHugeInt newNumber(least_significant_word->get_value());
    HugeIntWord *thisWord = least_significant_word->get_next_more_sig_word();
    while (thisWord != NULL) {
        newNumber.add_word(thisWord->get_value());
        thisWord = thisWord->get_next_more_sig_word();
    }
    return newNumber;
}


void UnsignedHugeInt::throw_warning(std::string message) {
    std::cout << message << "\n";
}

UnsignedHugeInt UnsignedHugeInt::find_multiplication_subtotal(const HugeIntWord* greater_factor_word, const HugeIntWord* lesser_factor_word) {
    UnsignedHugeInt resultSubtotal((unsigned long long)0);
    HugeIntWord *resultLeastSigWord = resultSubtotal.get_least_significant_word();
    const HugeIntWord *thisWordA = greater_factor_word, *thisWordB = lesser_factor_word; // thisWordA is taken in descending place values.
    HugeIntWord *newMostSigWord, *nextWord;
    while(thisWordA != NULL && thisWordB != NULL) {
        resultLeastSigWord->add_value(thisWordA->get_value() * thisWordB->get_value());
        thisWordA = thisWordA->get_next_lower_sig_word();
        thisWordB = thisWordB->get_next_more_sig_word();
    }
    // Set the most significant word of the subtotal.
    newMostSigWord = resultSubtotal.get_most_significant_word();
    nextWord = newMostSigWord->get_next_more_sig_word();
    while (nextWord != NULL) {
        newMostSigWord = nextWord;
        nextWord = nextWord->get_next_more_sig_word();
    }
    resultSubtotal.mostSigWord = newMostSigWord;
    return resultSubtotal;
}





// ToDo: Remove the following after development.
void UnsignedHugeInt::report_number_of_objects() {
    std::cout << "Number of UnsignedHugeInt objects created: " << UnsignedHugeInt::num_objects_created << "\n";
    std::cout << "Number of UnsignedHugeInt objects destroyed: " << UnsignedHugeInt::num_objects_deleted << "\n";
    std::cout << "Number of HugeIntWord objects created: " << HugeIntWord::num_objects_created << "\n";
    std::cout << "Number of HugeIntWord objects destroyed: " << HugeIntWord::num_objects_deleted << "\n";
}