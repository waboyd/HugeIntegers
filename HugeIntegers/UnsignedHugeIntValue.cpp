#include "UnsignedHugeIntValue.h"
#include "UnsignedHugeIntValue.h"

// ToDo: Set the max_word_value in UnsignedHugeIntValue and HugeIntWord.
unsigned long UnsignedHugeIntValue::max_word_value = 999999999;
unsigned long long UnsignedHugeIntValue::word_base = UnsignedHugeIntValue::max_word_value + 1;

UnsignedHugeIntValue::UnsignedHugeIntValue() {
    // ToDo: Set maximum word value.
    HugeIntWord *newWord = new HugeIntWord(0);
    this->mostSigWord = newWord;
    this->leastSigWord = newWord;
    this->defined_key_1 = CHECK_VALUE_A;
    this->defined_key_2 = CHECK_VALUE_B;
}

UnsignedHugeIntValue::UnsignedHugeIntValue(const unsigned long long value) {
    // ToDo: Set maximum word value.
    HugeIntWord *newWord = new HugeIntWord(0);
    this->leastSigWord = newWord;
    this->mostSigWord = newWord->add_value(value);
    this->defined_key_1 = CHECK_VALUE_A;
    this->defined_key_2 = CHECK_VALUE_B;
}

UnsignedHugeIntValue::UnsignedHugeIntValue(const std::string integer_string) {
    this->set_value_from_string(integer_string);
    this->defined_key_1 = CHECK_VALUE_A;
    this->defined_key_2 = CHECK_VALUE_B;
}

UnsignedHugeIntValue::UnsignedHugeIntValue(const char* integer_string) {
    std::string cppString(integer_string);
    this->set_value_from_string(cppString);
    this->defined_key_1 = CHECK_VALUE_A;
    this->defined_key_2 = CHECK_VALUE_B;
}

UnsignedHugeIntValue::UnsignedHugeIntValue(const UnsignedHugeIntValue& orig) {
    this->change_to_copy_of(orig);
    this->defined_key_1 = orig.defined_key_1;
    this->defined_key_2 = orig.defined_key_2;
}

UnsignedHugeIntValue::UnsignedHugeIntValue(const UnsignedHugeIntValue* orig) {
    this->change_to_copy_of(*orig);
    this->defined_key_1 = orig->defined_key_1;
    this->defined_key_2 = orig->defined_key_2;
}

UnsignedHugeIntValue::UnsignedHugeIntValue(UnsignedHugeIntValue&& orig) {
    this->mostSigWord = orig.mostSigWord;
    this->leastSigWord = orig.leastSigWord;
    this->defined_key_1 = orig.defined_key_1;
    this->defined_key_2 = orig.defined_key_2;
    orig.mostSigWord = orig.leastSigWord = NULL;
}

UnsignedHugeIntValue UnsignedHugeIntValue::number_of_digits() const {
    // This implementation assumes the word base is a power of 10.
    if (this->mostSigWord == NULL)
        return UnsignedHugeIntValue(1);
    UnsignedHugeIntValue totalNumDigits(UnsignedHugeIntValue::multiply(
            this->mostSigWord->get_word_number(), MAX_DIGITS_PER_WORD)
    );
    unsigned long upperBoundary = 10;
    unsigned long mostSigValue = this->mostSigWord->get_value();
    unsigned short numMostSigDigits = 1;
    while (mostSigValue >= upperBoundary) {
        ++numMostSigDigits;
        upperBoundary *= 10;
    }
    totalNumDigits += numMostSigDigits;
    return totalNumDigits;
}

UnsignedHugeIntValue::~UnsignedHugeIntValue() {
    if(!this->is_defined()) {
        delete(this->mostSigWord);
        delete(this->leastSigWord);
        std::cout << "Warning: The destructor was called for a non-defined UnsignedHugeIntValue object.\n";
        return;
    }
    this->delete_all_words();
    this->defined_key_1 = 0;
    this->defined_key_2 = 0;
}

UnsignedHugeIntValue::operator std::string() const {
    return this->to_string();
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator=(const UnsignedHugeIntValue& orig) {
    if (this == &orig)
        return *this;
    if(this->is_defined()) {
        this->delete_all_words();
    }
    this->change_to_copy_of(orig);
    this->defined_key_1 = orig.defined_key_1;
    this->defined_key_2 = orig.defined_key_2;
    return *this;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator=(const UnsignedHugeIntValue* orig) {
    if (this == orig)
        return *this;
    if(this->is_defined()) {
        this->delete_all_words();
    }
    this->change_to_copy_of(*orig);
    this->defined_key_1 = orig->defined_key_1;
    this->defined_key_2 = orig->defined_key_2;
    return *this;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator=(UnsignedHugeIntValue&& orig) {
    if (this == &orig)
        return *this;
    if(this->is_defined()) {
        this->delete_all_words();
    }
    this->mostSigWord = orig.mostSigWord;
    this->leastSigWord = orig.leastSigWord;
    this->defined_key_1 = orig.defined_key_1;
    this->defined_key_2 = orig.defined_key_2;
    orig.mostSigWord = orig.leastSigWord = NULL;
    return *this;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator=(const unsigned long long value) {
    if(this->is_defined()) {
        this->delete_all_words();
    }
    HugeIntWord *newWord = new HugeIntWord(0);
    this->leastSigWord = newWord;
    this->mostSigWord = newWord->add_value(value);
    this->defined_key_1 = CHECK_VALUE_A;
    this->defined_key_2 = CHECK_VALUE_B;
    return *this;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator=(const std::string value_string) {
    if(this->is_defined()) {
        this->delete_all_words();
    }
    this->set_value_from_string(value_string);
    return *this;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator=(const char* value_string) {
    if(this->is_defined()) {
        this->delete_all_words();
    }
    std::string cppStringValue(value_string);
    this->set_value_from_string(cppStringValue);
    return *this;
}

short UnsignedHugeIntValue::compare(const UnsignedHugeIntValue& numberA, const UnsignedHugeIntValue& numberB) {
    if(!numberA.is_defined() || !numberB.is_defined()) {
        throw std::invalid_argument("One of the numbers of the comparison operation is not defined.");
    }
    unsigned long long numWordsA = numberA.num_words();
    unsigned long long numWordsB = numberB.num_words();
    HugeIntWord *thisWordA, *thisWordB;
    unsigned long wordValueA, wordValueB;
    
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
        throw std::logic_error("A problem occurred involving the number of words in an UnsignedHugeIntValue.");
    }
    
    return 0;   // The numbers are equal.
}

UnsignedHugeIntValue UnsignedHugeIntValue::sum_of(const UnsignedHugeIntValue& addendA, const UnsignedHugeIntValue& addendB) {
    if(!addendA.is_defined() || !addendB.is_defined()) {
        throw std::invalid_argument("One of the numbers of the addition operation is not defined.");
    }
    HugeIntWord *greaterAddendWord, *lesserAddendWord;
    HugeIntWord *sumWord, *sumMostSigWord;
    unsigned long long thisWordSum;
    unsigned long carryValue = 0;
    
    if (addendB.num_words() > addendA.num_words()) {
        greaterAddendWord = addendB.get_least_significant_word();
        lesserAddendWord = addendA.get_least_significant_word();
    }
    else {
        greaterAddendWord = addendA.get_least_significant_word();
        lesserAddendWord = addendB.get_least_significant_word();
    }
    UnsignedHugeIntValue sum((unsigned long long)0);
    sumWord = sum.get_least_significant_word();
    sumMostSigWord = sum.get_most_significant_word();
    
    while (lesserAddendWord != NULL) {
        thisWordSum = greaterAddendWord->get_value() + lesserAddendWord->get_value() + carryValue;
        carryValue = thisWordSum / UnsignedHugeIntValue::word_base;
        thisWordSum = thisWordSum % UnsignedHugeIntValue::word_base;
        
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
        carryValue = thisWordSum / UnsignedHugeIntValue::word_base;
        thisWordSum = thisWordSum % UnsignedHugeIntValue::word_base;
        
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
        thisWordSum = carryValue % UnsignedHugeIntValue::word_base;
        carryValue = carryValue / UnsignedHugeIntValue::word_base;
        
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


UnsignedHugeIntValue UnsignedHugeIntValue::sum_of(const UnsignedHugeIntValue& addendA, const unsigned long long addendB) {
    if(!addendA.is_defined()) {
        throw std::invalid_argument("One of the numbers of the addition operation is not defined.");
    }
    unsigned long long thisWordSum;
    unsigned long thisCarryValue = 0;
    HugeIntWord *thisAddendWord = addendA.get_least_significant_word();
    
    thisWordSum = addendB % UnsignedHugeIntValue::word_base;
    thisCarryValue = addendB / UnsignedHugeIntValue::word_base;
    thisWordSum += thisAddendWord->get_value();
    thisCarryValue += thisWordSum / UnsignedHugeIntValue::word_base;
    thisWordSum = thisWordSum % UnsignedHugeIntValue::word_base;
    UnsignedHugeIntValue sum(thisWordSum);
    
    thisAddendWord = thisAddendWord->get_next_more_sig_word();
    
    while (thisAddendWord != NULL || thisCarryValue > 0) {
        thisWordSum = thisCarryValue;
        if (thisAddendWord != NULL) {
            thisWordSum += thisAddendWord->get_value();
            thisAddendWord = thisAddendWord->get_next_more_sig_word();
        }
        thisCarryValue = thisWordSum / UnsignedHugeIntValue::word_base;
        thisWordSum = thisWordSum % UnsignedHugeIntValue::word_base;
        sum.add_word(thisWordSum);
    }
    return sum;
}

UnsignedHugeIntValue UnsignedHugeIntValue::subtract(const UnsignedHugeIntValue& minuend, const UnsignedHugeIntValue& subtrahend) {
    if(!minuend.is_defined() || !subtrahend.is_defined()) {
        throw std::invalid_argument("One of the UnsignedHugeIntValues of the subtraction operation is not defined.");
    }
    if (UnsignedHugeIntValue::compare(minuend, subtrahend) < 0) {
        throw std::range_error("The subtrahend of an unsigned subtraction operation was greater than the minuend.");
    }
    
    HugeIntWord *minuendWord, *subtrahendWord;
    unsigned long long thisMinuendWordValue;
    unsigned long thisWordDifference, thisSubtrahendWordValue, carryValue;
    
    // Determine the least significant word of the difference.
    minuendWord = minuend.get_least_significant_word();
    if (minuendWord == NULL)
        return UnsignedHugeIntValue((unsigned long long)0);
    subtrahendWord = subtrahend.get_least_significant_word();
    if (subtrahendWord == NULL)
        return UnsignedHugeIntValue(minuend);
    thisMinuendWordValue = minuendWord->get_value();
    thisSubtrahendWordValue = subtrahendWord->get_value();
    if (thisMinuendWordValue < thisSubtrahendWordValue) {
        carryValue = 1;
        thisWordDifference = (UnsignedHugeIntValue::word_base + thisMinuendWordValue) - thisSubtrahendWordValue;
    }
    else {
        carryValue = 0;
        thisWordDifference = thisMinuendWordValue - thisSubtrahendWordValue;
    }        
    UnsignedHugeIntValue difference(thisWordDifference);
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

UnsignedHugeIntValue UnsignedHugeIntValue::multiply(const UnsignedHugeIntValue& factorA, const UnsignedHugeIntValue& factorB) {
    // ToDo: Possibly apply multithreading to this method.
    if(!factorA.is_defined() || !factorB.is_defined()) {
        throw std::invalid_argument("One of the numbers of the multiplication operation is not defined.");
    }
    // Find the product of the least significant word of each factor.
    HugeIntWord *startWordA = factorA.get_least_significant_word(); // Starting words when finding a partial product.
    HugeIntWord *startWordB = factorB.get_least_significant_word();
    if ((startWordA == NULL) || (startWordB == NULL))
        return UnsignedHugeIntValue((unsigned long long)0);    
    UnsignedHugeIntValue totalProduct((unsigned long long)startWordA->get_value() * startWordB->get_value());
    HugeIntWord *totalCalcWord = totalProduct.get_least_significant_word();
    UnsignedHugeIntValue partialProduct;
    
    // Find partial products while changing startWordA.
    startWordA = startWordA->get_next_more_sig_word();
    while (startWordA != NULL) {
        totalCalcWord = totalCalcWord->get_next_more_sig_word();
        partialProduct = UnsignedHugeIntValue::find_multiplication_subtotal(startWordA, startWordB);
        totalCalcWord = totalProduct.add_value_at_word(totalCalcWord, partialProduct);
        startWordA = startWordA->get_next_more_sig_word();
    }
    startWordA = factorA.get_most_significant_word();
    
    // Find partial products while changing startWordB.
    startWordB= startWordB->get_next_more_sig_word();
    while (startWordB != NULL) {
        totalCalcWord = totalCalcWord->get_next_more_sig_word();
        partialProduct = UnsignedHugeIntValue::find_multiplication_subtotal(startWordA, startWordB);
        totalCalcWord = totalProduct.add_value_at_word(totalCalcWord, partialProduct);
        startWordB = startWordB->get_next_more_sig_word();
    }
    
    // Remove leading 0 words.
    totalProduct.remove_extra_leading_words();
    
    return totalProduct;
}

UnsignedHugeIntValue UnsignedHugeIntValue::multiply_by_int(const unsigned long long factor) const {
    // If factor is small enough to fit in one word of an UnsignedHugeIntValue object, use the faster multiplication function.
    if (factor < UnsignedHugeIntValue::word_base)
        return UnsignedHugeIntValue::multiply_single_word(*this, factor);
    UnsignedHugeIntValue factorObject(factor);
    return UnsignedHugeIntValue::multiply(*this, factorObject);
}

UnsignedHugeIntValue UnsignedHugeIntValue::multiply_single_word(const UnsignedHugeIntValue& large_factor, const unsigned long long small_factor) {
    if(!large_factor.is_defined()) {
        throw std::invalid_argument("The UnsignedHugeIntValue object of the multiplication operation is not defined.");
    }

    HugeIntWord *factorWord, *productWord;
    unsigned long long productValue, carryValue;
    factorWord = large_factor.get_least_significant_word();
    if ((factorWord == NULL) || (small_factor == 0) || ((large_factor.num_words() < 2) && (factorWord->value == 0)))
        return UnsignedHugeIntValue((unsigned long long)0);
    
    // Set the first word of the product.
    productValue = factorWord->value * small_factor;
    carryValue = productValue / UnsignedHugeIntValue::word_base;
    productValue = productValue % UnsignedHugeIntValue::word_base;
    UnsignedHugeIntValue resultProduct(productValue);
    productWord = resultProduct.get_least_significant_word();
    factorWord = factorWord->get_next_more_sig_word();
    
    // Multiply the other words of the UnsignedHugeIntValue factor.
    while (factorWord != NULL) {
        productValue = factorWord->value * small_factor + carryValue;
        carryValue = productValue / UnsignedHugeIntValue::word_base;
        productValue = productValue % UnsignedHugeIntValue::word_base;
        productWord = new HugeIntWord(productValue, productWord);
        factorWord = factorWord->get_next_more_sig_word();
    }
    
    // Set the most significant word of the product from the carry value.
    if (carryValue > 0)
        resultProduct.mostSigWord = new HugeIntWord(carryValue, productWord);
    else
        resultProduct.mostSigWord = productWord;
    return resultProduct;
}

std::pair<UnsignedHugeIntValue, UnsignedHugeIntValue> UnsignedHugeIntValue::divide(const UnsignedHugeIntValue& dividend, const UnsignedHugeIntValue& divisor) {
    if (!dividend.is_defined() || !divisor.is_defined()) {
        throw std::invalid_argument("One of the UnsignedHugeIntValues of the divide operation is not defined.");
    }
    std::pair<UnsignedHugeIntValue, UnsignedHugeIntValue> divisionResults;
    unsigned long long dividendNumWords = dividend.num_words();
    unsigned long long divisorNumWords = divisor.num_words();
    unsigned long long remainderNumWords;
    UnsignedHugeIntValue quotient((unsigned long long)0);
    HugeIntWord *quotientCalcWord = quotient.get_least_significant_word();
    HugeIntWord *remainderEstimateWord, *dividendNextWord, *divisorEstimateWord;
    double dividendLowerEstimate, divisorUpperEstimate;
    unsigned long long quotientWordEstimate;
    
    if (divisorNumWords == 0 || (divisorNumWords == 1 && divisor.get_least_significant_word()->get_value() == 0)) {
        throw std::invalid_argument("An attempt was made to divide by zero.");
    }
    if (compare(dividend, divisor) < 0) {
        divisionResults.first = quotient;
        divisionResults.second = UnsignedHugeIntValue(dividend);
        return divisionResults;
    }
    // Add words to the quotient.
    dividendNextWord = dividend.get_least_significant_word();
    unsigned long long quotientNumWords = dividendNumWords - divisorNumWords + 1;
    for (unsigned long long wordNumber = 1; wordNumber < quotientNumWords; ++wordNumber) {
        quotientCalcWord = quotient.add_word((unsigned long long)0);
        dividendNextWord = dividendNextWord->get_next_more_sig_word();
    }
    UnsignedHugeIntValue subRemainder = integer_with_least_significant_word(dividendNextWord);
    
    // Set the most significant word of the quotient.
        // Give a lower estimate of the quotient word.
        divisorEstimateWord = divisor.get_most_significant_word();
        remainderEstimateWord = subRemainder.get_most_significant_word();
        if (divisorEstimateWord->get_next_lower_sig_word() != NULL) {
            divisorUpperEstimate = divisorEstimateWord->get_value() +
                (((double)divisorEstimateWord->get_next_lower_sig_word()->get_value() + 1) / UnsignedHugeIntValue::word_base);
            dividendLowerEstimate = remainderEstimateWord->get_value() +
                (((double)remainderEstimateWord->get_next_lower_sig_word()->get_value()) / UnsignedHugeIntValue::word_base);
        }
        else {
            divisorUpperEstimate = divisorEstimateWord->get_value();
            dividendLowerEstimate = remainderEstimateWord->get_value();
        }
        quotientWordEstimate = (unsigned long long)(dividendLowerEstimate / divisorUpperEstimate);

        // Multiply the quotient word by the divisor, and subtract the product from the remainder.
        subRemainder = UnsignedHugeIntValue::subtract(subRemainder, UnsignedHugeIntValue::multiply_single_word(divisor, quotientWordEstimate));
        // Increase the quotient word until it is the correct value.
        while (UnsignedHugeIntValue::compare(subRemainder, divisor) >= 0) {
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
            dividendLowerEstimate = (UnsignedHugeIntValue::word_base * remainderEstimateWord->get_value()) +
                remainderEstimateWord->get_next_lower_sig_word()->get_value();
        }
        else if (remainderNumWords < divisorNumWords) {
            dividendLowerEstimate = 0;
        }
        else if (remainderEstimateWord->get_next_lower_sig_word() != NULL)
            dividendLowerEstimate = remainderEstimateWord->get_value() +
                (((double)remainderEstimateWord->get_next_lower_sig_word()->get_value()) / UnsignedHugeIntValue::word_base);
        else
            dividendLowerEstimate = remainderEstimateWord->get_value();
        quotientWordEstimate = (unsigned long)(dividendLowerEstimate / divisorUpperEstimate);

        // Multiply the quotient word by the divisor, and subtract the product from the remainder.
        subRemainder = UnsignedHugeIntValue::subtract(subRemainder, UnsignedHugeIntValue::multiply_single_word(divisor, quotientWordEstimate));
        // Increase the quotient word until it is the correct value.
        while (UnsignedHugeIntValue::compare(subRemainder, divisor) >= 0) {
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

UnsignedHugeIntValue& UnsignedHugeIntValue::operator+=(const UnsignedHugeIntValue& addend) {
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

UnsignedHugeIntValue& UnsignedHugeIntValue::operator+=(const unsigned long long addend) {
    if(!this->is_defined()) {
        throw std::invalid_argument("The UnsignedHugeIntValue object was not defined before compound addition.");
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

UnsignedHugeIntValue& UnsignedHugeIntValue::operator-=(const UnsignedHugeIntValue& subtrahend) {
    if(!this->is_defined() || !subtrahend.is_defined()) {
        throw std::invalid_argument("One of the UnsignedHugeIntValue objects of the compound subtraction operation is not defined.");
    }
    if (UnsignedHugeIntValue::compare(*this, subtrahend) < 0) {
        throw std::range_error("The subtrahend of an unsigned compound subtraction operation was greater than the minuend.");
    }
    
    HugeIntWord *minuendWord, *subtrahendWord;
    unsigned long long thisWordDifference, thisMinuendWordValue, thisSubtrahendWordValue, carryValue(0);
    
    minuendWord = this->get_least_significant_word();
    subtrahendWord = subtrahend.get_least_significant_word();

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
        minuendWord->value = thisWordDifference;
        minuendWord = minuendWord->get_next_more_sig_word();
        subtrahendWord = subtrahendWord->get_next_more_sig_word();
    }
    
    // Continue carry operations from the remaining words of the menuend.
    while (carryValue > 0 && minuendWord != NULL) {
        thisMinuendWordValue = minuendWord->get_value();
        if (thisMinuendWordValue < carryValue) {
            thisWordDifference = (HugeIntWord::base_value + thisMinuendWordValue) - carryValue;
            carryValue = 1;
        }
        else {
            thisWordDifference = thisMinuendWordValue - carryValue;
            carryValue = 0;
        }
        minuendWord->value = thisWordDifference;
        minuendWord = minuendWord->get_next_more_sig_word();
    }
    this->remove_extra_leading_words();
    return *this;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator-=(const unsigned long long subtrahend) {
    return *this -= UnsignedHugeIntValue(subtrahend);
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator*=(const UnsignedHugeIntValue& factor) {
    *this = UnsignedHugeIntValue::multiply(*this, factor);
    return *this;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator*=(const unsigned long long factor) {
    // If factor is small enough to fit in one word of an UnsignedHugeIntValue object, use the faster multiplication function.
    if (factor < UnsignedHugeIntValue::word_base) {
        *this = UnsignedHugeIntValue::multiply_single_word(*this, factor);
        return *this;
    }
    *this = UnsignedHugeIntValue::multiply(*this, UnsignedHugeIntValue(factor));
    return *this;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator/=(const UnsignedHugeIntValue& divisor) {
    *this = UnsignedHugeIntValue::divide(*this, divisor).first;
    return *this;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator/=(const unsigned long long divisor) {
    *this = UnsignedHugeIntValue::divide(*this, UnsignedHugeIntValue(divisor)).first;
    return *this;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator%=(const UnsignedHugeIntValue& divisor) {
    *this = UnsignedHugeIntValue::divide(*this, divisor).second;
    return *this;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator%=(const unsigned long long divisor) {
    *this = UnsignedHugeIntValue::divide(*this, UnsignedHugeIntValue(divisor)).second;
    return *this;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator++() {
    if(!this->is_defined()) {
        throw std::invalid_argument("The UnsignedHugeIntValue object was not defined before incrementing.");
    }
    this->leastSigWord->add_value(1);
    // Set the most significant word.
    HugeIntWord *nextWord = this->mostSigWord->get_next_more_sig_word();
    while(nextWord != NULL) {
        this->mostSigWord = nextWord;
        nextWord = nextWord->get_next_more_sig_word();
    }
    return *this;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator--() {
    if(!this->is_defined()) {
        throw std::invalid_argument("The UnsignedHugeIntValue object was not defined before decrementing.");
    }
    if ((this->num_words() <= 1) && (this->leastSigWord->get_value() < 1)) {
        throw std::range_error("An unsigned integer equal to 0 was decremented.");
    }
    HugeIntWord *minuendWord;
    unsigned long long thisMinuendWordValue;
    minuendWord = this->get_least_significant_word();

    // Subtract all the words of the subtrahend.    
    while (minuendWord != NULL) {
        thisMinuendWordValue = minuendWord->get_value();
        if (thisMinuendWordValue < 1) {
            minuendWord->value = HugeIntWord::base_value - 1;
        }
        else {
            minuendWord->value = thisMinuendWordValue - 1;
            break;
        }
        minuendWord = minuendWord->get_next_more_sig_word();
    }
    this->remove_extra_leading_words();
    return *this;
}

void UnsignedHugeIntValue::read_from_text_file(std::string file_path) {
    FILE *readTextFile = fopen(file_path.c_str(), "r");
    if (readTextFile == NULL)
        std::invalid_argument("The file with the given path could not be opened.");
    read_from_text_file(readTextFile);
    fclose(readTextFile);
}

void UnsignedHugeIntValue::read_from_text_file(FILE* integer_file) {
    if (integer_file == NULL)
        throw std::invalid_argument("A null file pointer was given as an argument.");
    this->delete_all_words();
    this->mostSigWord = this->leastSigWord = NULL;
    char readBuffer[READ_BUFFER_SIZE + 1];
    char digitBuffer[READ_BUFFER_SIZE + MAX_DIGITS_PER_WORD + 1];
    char wordString[MAX_DIGITS_PER_WORD + 1] = "\0";
    unsigned int remainderLength = 0;
    unsigned int numCharsRead;
    unsigned int readBufferIndex, digitBufferIndex;
    char thisChar;
    unsigned long long wordValue;
    HugeIntWord *newMostSigWord = this->leastSigWord;
    bool isFirstWordEmpty = true;
    unsigned long long filePositionAfterRead;

    // Check the number of characters in the file.
    fseek(integer_file, 0, SEEK_END);
    unsigned long long numCharsToRead = ftell(integer_file);

    // Read from the file in reverse order.
    wordString[MAX_NUMBER_OF_DIGITS] = '\0';
    while(numCharsToRead > READ_BUFFER_SIZE) {
        numCharsToRead -= READ_BUFFER_SIZE;
        fseek(integer_file, numCharsToRead, SEEK_SET);
        numCharsRead = fread(readBuffer, sizeof(char), READ_BUFFER_SIZE, integer_file);
        filePositionAfterRead = ftell(integer_file);
        numCharsRead -= (filePositionAfterRead - numCharsToRead) - READ_BUFFER_SIZE;    // Ignore characters that were read twice.

        // Take only the digits from the read buffer to create the digit buffer.
        digitBufferIndex = 0;
        for (readBufferIndex = 0; readBufferIndex < numCharsRead; ++readBufferIndex) {
            thisChar = readBuffer[readBufferIndex];
            if (isdigit(thisChar)) {
                digitBuffer[digitBufferIndex] = thisChar;
                ++digitBufferIndex;
            }
        }
        digitBuffer[digitBufferIndex] = '\0';
        // Attach the remaining digits from the previous buffer to this digit buffer.
        strcat(digitBuffer, wordString);
        digitBufferIndex += remainderLength;
        // Set the words of this UnsignedHugeIntValue object from the digit buffer.
        while (digitBufferIndex > MAX_DIGITS_PER_WORD) {
            digitBufferIndex -= MAX_DIGITS_PER_WORD;
            strncpy(wordString, digitBuffer + digitBufferIndex, MAX_DIGITS_PER_WORD);
            wordValue = strtoul(wordString, NULL, 10);
            if (isFirstWordEmpty) {
                newMostSigWord = new HugeIntWord(wordValue);
                this->leastSigWord = newMostSigWord;
                isFirstWordEmpty = false;
            }
            else {
                newMostSigWord = new HugeIntWord(wordValue, newMostSigWord);
            }
        }
        // Save the remaining digits for the next buffer.
        strncpy(wordString, digitBuffer, digitBufferIndex);
        wordString[digitBufferIndex] = '\0';
        remainderLength = digitBufferIndex;
    }

    // Read the most significant digits from the file.
    fseek(integer_file, 0, SEEK_SET);
    numCharsRead = fread(readBuffer, sizeof(char), numCharsToRead, integer_file);
    filePositionAfterRead = ftell(integer_file);
    numCharsRead -= (filePositionAfterRead - numCharsToRead);    // Ignore characters that were read twice.

    // Take only the digits from the read buffer to create the digit buffer.
    digitBufferIndex = 0;
    for (readBufferIndex = 0; readBufferIndex < numCharsRead; ++readBufferIndex) {
        thisChar = readBuffer[readBufferIndex];
        if (isdigit(thisChar)) {
            digitBuffer[digitBufferIndex] = thisChar;
            ++digitBufferIndex;
        }
    }
    digitBuffer[digitBufferIndex] = '\0';
    strcat(digitBuffer, wordString);
    digitBufferIndex += remainderLength;
    
    if (strlen(digitBuffer) == 0) {
        this->mostSigWord = newMostSigWord;
        this->remove_extra_leading_words();
        this->defined_key_1 = CHECK_VALUE_A;
        this->defined_key_2 = CHECK_VALUE_B;
        return;
    }
    // Add the least significant words from the buffer.
    while (digitBufferIndex > MAX_DIGITS_PER_WORD) {
        digitBufferIndex -= MAX_DIGITS_PER_WORD;
        strncpy(wordString, digitBuffer + digitBufferIndex, MAX_DIGITS_PER_WORD);
        wordValue = strtoul(wordString, NULL, 10);
        if (isFirstWordEmpty) {
            newMostSigWord = new HugeIntWord(wordValue);
            this->leastSigWord = newMostSigWord;
            isFirstWordEmpty = false;
        }
        else {
            newMostSigWord = new HugeIntWord(wordValue, newMostSigWord);
        }
    }
    
    // Set the most significant word.
    strncpy(wordString, digitBuffer, digitBufferIndex);
    wordString[digitBufferIndex] = '\0';
    wordValue = strtoul(wordString, NULL, 10);
    if (isFirstWordEmpty) {
        newMostSigWord = new HugeIntWord(wordValue);
        this->leastSigWord = newMostSigWord;
    }
    else {
        newMostSigWord = new HugeIntWord(wordValue, newMostSigWord);
    }
    this->mostSigWord = newMostSigWord;
    this->remove_extra_leading_words();    
    this->defined_key_1 = CHECK_VALUE_A;
    this->defined_key_2 = CHECK_VALUE_B;
}

void UnsignedHugeIntValue::write_to_text_file(std::string file_path) const {
    // Prevent writing to an existing file.
    if (stat(file_path.c_str(), NULL) >= 0)
        std::invalid_argument("An attempt was made to write an UnsignedHugeIntValue value to an existing file.");
    FILE *writeTextFile = fopen(file_path.c_str(), "w");
    this->write_to_text_file(writeTextFile);
    fclose(writeTextFile);
}

void UnsignedHugeIntValue::write_to_text_file(FILE* integer_file) const {
    if (integer_file == NULL)
        throw std::invalid_argument("A null file pointer was given as an argument.");
    if (!this->is_defined()) {
        throw std::invalid_argument("The UnsignedHugeIntValue object was not defined before the command to write to a file.");
    }
    std::string bufferString;
    HugeIntWord *thisWord = this->mostSigWord;
    unsigned int i;
    
    while (thisWord != NULL) {
        bufferString = "";
        for (i = 0; i < BUFFER_NUM_WORDS; ++i) {
            bufferString += thisWord->to_string();
            thisWord = thisWord->get_next_lower_sig_word();
            if (thisWord == NULL) {
                fputs(bufferString.c_str(), integer_file);
                return;
            }
        }
        fputs(bufferString.c_str(), integer_file);
    }
}

void UnsignedHugeIntValue::read_from_binary_file(std::string file_path) {
    this->delete_all_words();
    this->mostSigWord = this->leastSigWord = NULL;
    unsigned long long remainingNumWords;
    unsigned long readBuffer[BUFFER_NUM_WORDS];
    HugeIntWord *thisWord;
    unsigned int bufferSize = sizeof(unsigned long) * BUFFER_NUM_WORDS;
    unsigned int bufferIndex;
    char *readDest = (char*)readBuffer;

    std::ifstream fileReadStream(file_path, std::ios::in | std::ios::binary);
    if (!fileReadStream.is_open()) {
        fileReadStream.close();
        throw std::invalid_argument("The file " + file_path + " could not be opened.");
    }
    fileReadStream >> remainingNumWords;
    
    // Read the first word from the binary file.
    if (remainingNumWords < 1) {
        this->mostSigWord = this->leastSigWord = new HugeIntWord(0);
        fileReadStream.close();
        return;
    }
    fileReadStream.read(readDest, sizeof(unsigned long));
    this->leastSigWord = thisWord = new HugeIntWord(readBuffer[0]);
    --remainingNumWords;
    
    // Read full buffers from the binary file.
    while (remainingNumWords > BUFFER_NUM_WORDS) {
        fileReadStream.read(readDest, bufferSize);
        for (bufferIndex = 0; bufferIndex < BUFFER_NUM_WORDS; ++bufferIndex) {
            thisWord = new HugeIntWord(readBuffer[bufferIndex], thisWord);
        }
        remainingNumWords -= BUFFER_NUM_WORDS;
    }
    
    // Read the last partial buffer from the binary file.
    fileReadStream.read(readDest, sizeof(unsigned long) * remainingNumWords);
    for (bufferIndex = 0; bufferIndex < remainingNumWords; ++bufferIndex) {
        thisWord = new HugeIntWord(readBuffer[bufferIndex], thisWord);
    }
    fileReadStream.close();
    this->mostSigWord = thisWord;
}

void UnsignedHugeIntValue::write_to_binary_file(std::string file_path) const {
    // Prevent writing to an existing file.
    if (stat(file_path.c_str(), NULL) >= 0)
        std::invalid_argument("An attempt was made to write an UnsignedHugeIntValue value to an existing file.");
    if (!this->is_defined()) {
        throw std::invalid_argument("The UnsignedHugeIntValue object was not defined before the command to write to a file.");
    }
    unsigned long writeBuffer[BUFFER_NUM_WORDS];
    char *writeSource = (char*)writeBuffer;
    unsigned int bufferSize = sizeof(unsigned long) * BUFFER_NUM_WORDS;
    unsigned int bufferIndex;
    HugeIntWord *thisWord = this->leastSigWord;
    
    std::ofstream fileWriteStream(file_path, std::ios::out | std::ios::binary);
    if (!fileWriteStream.is_open()) {
        fileWriteStream.close();
        throw std::invalid_argument("The file at " + file_path + " could not be created.");
    }
    // Write the number of words at the start of the file.
    fileWriteStream << this->num_words();
    
    // Write all the word values to the file.
    while (thisWord != NULL) {
        for (bufferIndex = 0; bufferIndex < BUFFER_NUM_WORDS; ++bufferIndex) {
            writeBuffer[bufferIndex] = thisWord->get_value();
            thisWord = thisWord->get_next_more_sig_word();
            if (thisWord == NULL) {
                fileWriteStream.write(writeSource, sizeof(unsigned long) * (bufferIndex + 1));
                fileWriteStream.close();
                return;
            }
        }
        fileWriteStream.write(writeSource, bufferSize);
    }
    fileWriteStream.close();
}

bool UnsignedHugeIntValue::is_defined() const {
    if ((this->defined_key_1 != CHECK_VALUE_A) || (this->defined_key_2 != CHECK_VALUE_B) ||
        ((this->leastSigWord != NULL) && 
        ((this->leastSigWord->get_next_lower_sig_word() != NULL) || (this->mostSigWord->get_next_more_sig_word() != NULL)))) {
//            throw std::invalid_argument("An UnsignedHugeIntValue object was used before it was defined.");
            return false;
    }
    return true;
}

long UnsignedHugeIntValue::num_words() const {
    if (this->mostSigWord == NULL)
        return 0;
    return (this->mostSigWord->get_word_number() + 1);
}

HugeIntWord* UnsignedHugeIntValue::get_most_significant_word() const {
    return this->mostSigWord;
}

HugeIntWord* UnsignedHugeIntValue::get_least_significant_word() const {
    return this->leastSigWord;
}

HugeIntWord* UnsignedHugeIntValue::remove_most_significant_word() {
    if(!this->is_defined()) {
        throw std::invalid_argument("An attempt was made to remove a word from a non-defined number.");
        return NULL;
    }
    HugeIntWord *oldMostSigWord = this->mostSigWord;
    if (oldMostSigWord == NULL) {
        throw std::logic_error("An UnsignedHugeIntValue object has no words or value.");
    }
    HugeIntWord *newMostSigWord = oldMostSigWord->get_next_lower_sig_word();
    if (newMostSigWord == NULL) {
        throw std::logic_error("An attempt was made to remove the only word of an UnsignedHugeIntValue object.");
    }
    newMostSigWord->remove_more_significant_word();
    this->mostSigWord = newMostSigWord;
    delete(oldMostSigWord);
    return newMostSigWord;
}

std::string UnsignedHugeIntValue::to_string() const {
    if(!this->is_defined()) {
        throw std::invalid_argument("An attempt was made to retrieve the value of a non-defined UnsignedHugeIntValue.");
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

void UnsignedHugeIntValue::change_to_copy_of(const UnsignedHugeIntValue& orig) {
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

void UnsignedHugeIntValue::set_value_from_string(std::string integer_string) {
    // ToDo: handle bases that are not a power of 10.
    std::string thisWordString;
    char thisWordChar[MAX_DIGITS_PER_WORD + 1];
    unsigned long long thisWordValue;
    unsigned long long thisWordIndex = integer_string.length();
    HugeIntWord *newWordObject;
    
    // Set the least significant word.
    if (thisWordIndex <= MAX_DIGITS_PER_WORD) {
        thisWordString = integer_string.substr(0, thisWordIndex);
        strcpy(thisWordChar, thisWordString.c_str());
        thisWordValue = strtoul(thisWordChar, NULL, 10);
        this->mostSigWord = this->leastSigWord = new HugeIntWord(thisWordValue);
        return;
    }
    thisWordIndex -= MAX_DIGITS_PER_WORD;
    thisWordString = integer_string.substr(thisWordIndex, MAX_DIGITS_PER_WORD);
    strcpy(thisWordChar, thisWordString.c_str());
    thisWordValue = strtoul(thisWordChar, NULL, 10);
    newWordObject = new HugeIntWord(thisWordValue);
    this->leastSigWord = newWordObject;
    
    // Add the medium significant words.
    while (thisWordIndex > MAX_DIGITS_PER_WORD) {
        thisWordIndex -= MAX_DIGITS_PER_WORD;
        thisWordString = integer_string.substr(thisWordIndex, MAX_DIGITS_PER_WORD);
        strcpy(thisWordChar, thisWordString.c_str());
        thisWordValue = strtoul(thisWordChar, NULL, 10);
        newWordObject = new HugeIntWord(thisWordValue, newWordObject);
    }
    
    // Set the most significant word.
    thisWordString = integer_string.substr(0, thisWordIndex);
    strcpy(thisWordChar, thisWordString.c_str());
    thisWordValue = strtoul(thisWordChar, NULL, 10);
    this->mostSigWord = new HugeIntWord(thisWordValue, newWordObject);
    this->remove_extra_leading_words();
}

void UnsignedHugeIntValue::delete_all_words() {
    HugeIntWord *thisWord = this->mostSigWord;
    HugeIntWord *wordToDelete, *nextWord;
    while (thisWord != NULL) {
        wordToDelete = thisWord;
        
        nextWord = thisWord->get_next_lower_sig_word();
        delete(wordToDelete);
        thisWord = nextWord;
    }    
}

void UnsignedHugeIntValue::remove_extra_leading_words() {
    while ((this->mostSigWord->value == 0) && (this->mostSigWord != this->leastSigWord)) {
        this->mostSigWord = this->mostSigWord->get_next_lower_sig_word();
        this->mostSigWord->remove_more_significant_word();
    }
}

HugeIntWord* UnsignedHugeIntValue::add_word() {
    return this->add_word((unsigned long long)0);
}

HugeIntWord* UnsignedHugeIntValue::add_word(const unsigned long long value) {
    if (value > UnsignedHugeIntValue::max_word_value) {
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

HugeIntWord* UnsignedHugeIntValue::add_word(HugeIntWord* new_word) {
    if (new_word == NULL) {
        throw std::invalid_argument("A null word was added to an UnsignedHugeIntValue.");
    }
    HugeIntWord *oldMostSigWord = this->mostSigWord;
    new_word->set_less_significant_word(oldMostSigWord);
    oldMostSigWord->set_more_significant_word(new_word);
    this->mostSigWord = new_word;
    return new_word;
}

HugeIntWord* UnsignedHugeIntValue::insert_least_significant_word(unsigned long least_significant_value) {
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

HugeIntWord* UnsignedHugeIntValue::add_value_at_word(HugeIntWord* location_to_add, const UnsignedHugeIntValue& value_to_add) {
    HugeIntWord *thisAddLocation;
    const HugeIntWord *thisValueWord = value_to_add.get_least_significant_word();
    HugeIntWord *moreSigWord;
    HugeIntWord *wordToReturn;
    
    if (location_to_add == NULL) {
        thisAddLocation = this->add_word(new HugeIntWord((unsigned long)0));
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

UnsignedHugeIntValue UnsignedHugeIntValue::integer_with_least_significant_word(const HugeIntWord* least_significant_word) {
    UnsignedHugeIntValue newNumber(least_significant_word->get_value());
    HugeIntWord *thisWord = least_significant_word->get_next_more_sig_word();
    while (thisWord != NULL) {
        newNumber.add_word(thisWord->get_value());
        thisWord = thisWord->get_next_more_sig_word();
    }
    return newNumber;
}

UnsignedHugeIntValue UnsignedHugeIntValue::find_multiplication_subtotal(const HugeIntWord* greater_factor_word, const HugeIntWord* lesser_factor_word) {
    UnsignedHugeIntValue resultSubtotal((unsigned long long)0);
    HugeIntWord *resultLeastSigWord = resultSubtotal.get_least_significant_word();
    const HugeIntWord *thisWordA = greater_factor_word, *thisWordB = lesser_factor_word; // thisWordA is taken in descending place values.
    HugeIntWord *newMostSigWord, *nextWord;
    while(thisWordA != NULL && thisWordB != NULL) {
        resultLeastSigWord->add_value((unsigned long long)thisWordA->get_value() * thisWordB->get_value());
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

std::ostream& operator<<(std::ostream& out_stream, const UnsignedHugeIntValue& huge_int_object) {
    out_stream << huge_int_object.to_string();
    return out_stream;
}
