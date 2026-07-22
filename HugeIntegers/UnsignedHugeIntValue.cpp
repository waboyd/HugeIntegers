#include "UnsignedHugeIntValue.h"

UnsignedHugeIntValue::UnsignedHugeIntValue() {
    this->word_values = new std::vector<uint32_t>(1, 0);
}

UnsignedHugeIntValue::UnsignedHugeIntValue(const unsigned long long value) {
    if (value <= HUGE_INT_MAX_WORD_VALUE) {
        this->word_values = new std::vector<uint32_t>(1, value);
        return;
    }
    this->word_values = new std::vector<uint32_t>(2);
    this->word_values->at(0) = value % HUGE_INT_WORD_BASE;
    unsigned long long quotient = value / HUGE_INT_WORD_BASE;
    this->word_values->at(1) = quotient % HUGE_INT_WORD_BASE;
    for (quotient /= HUGE_INT_WORD_BASE; quotient > 0; quotient /= HUGE_INT_WORD_BASE) {
        this->word_values->push_back(quotient % HUGE_INT_WORD_BASE);
    }
}

UnsignedHugeIntValue::UnsignedHugeIntValue(const std::string integer_string) {
    this->set_value_from_string(integer_string);
    this->word_values = new std::vector<uint32_t>(1, 0);    // ToDo: Delete or change this line. /////////////////////////////////////////////////////////////////////
}

UnsignedHugeIntValue::UnsignedHugeIntValue(const char* integer_string) {
    std::string cppString(integer_string);
    this->set_value_from_string(cppString);
    this->word_values = new std::vector<uint32_t>(1, 0);    // ToDo: Delete or change this line. /////////////////////////////////////////////////////////////////////
}

UnsignedHugeIntValue::UnsignedHugeIntValue(const UnsignedHugeIntValue& orig) {
    this->word_values = new std::vector<uint32_t>(*orig.word_values);
}

UnsignedHugeIntValue::UnsignedHugeIntValue(const UnsignedHugeIntValue* orig) {
    this->word_values = new std::vector<uint32_t>(*orig->word_values);
}

UnsignedHugeIntValue::UnsignedHugeIntValue(UnsignedHugeIntValue&& orig) {
    this->word_values = orig.word_values;
    orig.word_values = NULL;
}

UnsignedHugeIntValue::~UnsignedHugeIntValue() {
    delete this->word_values;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator=(const UnsignedHugeIntValue& orig) {
    if (this == &orig)
        return *this;
    delete this->word_values;
    this->word_values = new std::vector<uint32_t>(*orig.word_values);
    return *this;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator=(const UnsignedHugeIntValue* orig) {
    if (this == orig)
        return *this;
    delete this->word_values;
    this->word_values = new std::vector<uint32_t>(*orig->word_values);
    return *this;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator=(UnsignedHugeIntValue&& orig) {
    if (this == &orig)
        return *this;
    delete this->word_values;
    this->word_values = orig.word_values;
    orig.word_values = NULL;
    return *this;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator=(const unsigned long long value) {
    // ToDo: Change this function to remove dependence on HugeIntWord class.
    delete this->word_values;
//    HugeIntWord *newWord = new HugeIntWord(0);
//    this->leastSigWord = newWord;
//    this->mostSigWord = newWord->add_value(value);
    this->word_values = new std::vector<uint32_t>(1, 0);    // ToDo: Delete or change this line. /////////////////////////////////////////////////////////////////////
    return *this;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator=(const std::string value_string) {
    // ToDo: Change this function to remove dependence on HugeIntWord class.
    delete this->word_values;
    this->set_value_from_string(value_string);
    this->word_values = new std::vector<uint32_t>(1, 0);    // ToDo: Delete or change this line. /////////////////////////////////////////////////////////////////////
    return *this;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator=(const char* value_string) {
    // ToDo: Change this function to remove dependence on HugeIntWord class.
    delete this->word_values;
    std::string cppStringValue(value_string);
    this->set_value_from_string(cppStringValue);
    this->word_values = new std::vector<uint32_t>(1, 0);    // ToDo: Delete or change this line. /////////////////////////////////////////////////////////////////////
    return *this;
}

UnsignedHugeIntValue UnsignedHugeIntValue::number_of_digits() const {
    // ToDo: Change this function to remove dependence on HugeIntWord class.
//    if (this->mostSigWord == NULL)
//        return UnsignedHugeIntValue(1);
    UnsignedHugeIntValue totalNumDigits(1);
    UnsignedHugeIntValue quotient(this);

//    // The value can be repeatedly divided by a power of 10 to find the number of digits.
//    uint32_t divisor = 1;
//    for (unsigned short exponent = 1; exponent <= HUGE_INT_NUMBER_OF_BASE_10_DIGITS_PER_WORD; ++exponent) {
//        divisor *= 10;
//    }
//    while (this->compare(quotient, divisor) >= 0) {
//        totalNumDigits += HUGE_INT_NUMBER_OF_BASE_10_DIGITS_PER_WORD;
//        quotient /= UnsignedHugeIntValue(divisor);
//    }
//    while (this->compare(quotient, UnsignedHugeIntValue(10)) >= 0) {
//        totalNumDigits += 1;
//        quotient /= UnsignedHugeIntValue(10);
//    }
    return totalNumDigits;
}

UnsignedHugeIntValue::operator std::string() const {
    return this->to_string();
}

short UnsignedHugeIntValue::compare(const UnsignedHugeIntValue& numberA, const UnsignedHugeIntValue& numberB) {
    // ToDo: Change this function to remove dependence on HugeIntWord class.
//    unsigned long long numWordsA = numberA.num_words();
//    unsigned long long numWordsB = numberB.num_words();
//    HugeIntWord *thisWordA, *thisWordB;
    uint32_t wordValueA, wordValueB;

//    thisWordA = numberA.get_most_significant_word();
//    thisWordB = numberB.get_most_significant_word();
//
//    if (numWordsA > numWordsB && thisWordA->get_value() > 0)
//        return 1;
//    else if (numWordsA < numWordsB && thisWordB->get_value() > 0)
//        return -1;
//
//    while (thisWordA != NULL && thisWordB != NULL) {
//        wordValueA = thisWordA->get_value();
//        wordValueB = thisWordB->get_value();
//        if (wordValueA > wordValueB)
//            return 1;
//        else if (wordValueA < wordValueB)
//            return -1;
//        thisWordA = thisWordA->get_next_lower_sig_word();
//        thisWordB = thisWordB->get_next_lower_sig_word();
//    }
//
//    if (thisWordA != NULL || thisWordB != NULL) {
//        throw std::logic_error("A problem occurred involving the number of words in an UnsignedHugeIntValue.");
//    }

    return 0;   // The numbers are equal.
}

UnsignedHugeIntValue UnsignedHugeIntValue::sum_of(const UnsignedHugeIntValue& addendA, const UnsignedHugeIntValue& addendB) {
    // ToDo: Change this function to remove dependence on HugeIntWord class.
//    HugeIntWord *greaterAddendWord, *lesserAddendWord;
//    HugeIntWord *sumWord, *sumMostSigWord;
    uint64_t thisWordSum;
    uint64_t carryValue = 0;

//    if (addendB.num_words() > addendA.num_words()) {
//        greaterAddendWord = addendB.get_least_significant_word();
//        lesserAddendWord = addendA.get_least_significant_word();
//    }
//    else {
//        greaterAddendWord = addendA.get_least_significant_word();
//        lesserAddendWord = addendB.get_least_significant_word();
//    }
    UnsignedHugeIntValue sum((unsigned long long)0);
//    sumWord = sum.get_least_significant_word();
//    sumMostSigWord = sum.get_most_significant_word();
//
//    while (lesserAddendWord != NULL) {
//        thisWordSum = carryValue + greaterAddendWord->get_value() + lesserAddendWord->get_value();
//        carryValue = thisWordSum / HUGE_INT_WORD_BASE;
//        thisWordSum = thisWordSum % HUGE_INT_WORD_BASE;
//
//        if (sumWord == NULL) {
//            sumWord = sum.add_word(thisWordSum);
//            sumMostSigWord = sumWord;
//        }
//        else {
//            sumMostSigWord = sumWord->add_value(thisWordSum);
//        }
//        greaterAddendWord = greaterAddendWord->get_next_more_sig_word();
//        lesserAddendWord = lesserAddendWord->get_next_more_sig_word();
//        sumWord = sumWord->get_next_more_sig_word();
//    }
//
//    while (greaterAddendWord != NULL) {
//        thisWordSum = greaterAddendWord->get_value() + carryValue;
//        carryValue = thisWordSum / HUGE_INT_WORD_BASE;
//        thisWordSum = thisWordSum % HUGE_INT_WORD_BASE;
//
//        if (sumWord == NULL) {
//            sumWord = sum.add_word(thisWordSum);
//            sumMostSigWord = sumWord;
//        }
//        else {
//            sumMostSigWord = sumWord->add_value(thisWordSum);
//        }
//        greaterAddendWord = greaterAddendWord->get_next_more_sig_word();
//        sumWord = sumWord->get_next_more_sig_word();
//    }
//
//    while (carryValue > 0) {
//        thisWordSum = carryValue % HUGE_INT_WORD_BASE;
//        carryValue = carryValue / HUGE_INT_WORD_BASE;
//
//        if (sumWord == NULL) {
//            sumWord = sum.add_word(thisWordSum);
//            sumMostSigWord = sumWord;
//        }
//        else {
//            sumMostSigWord = sumWord->add_value(thisWordSum);
//        }
//        sumWord = sumWord->get_next_more_sig_word();
//    }
//    sum.mostSigWord = sumMostSigWord;
    return sum;
}


UnsignedHugeIntValue UnsignedHugeIntValue::sum_of(const UnsignedHugeIntValue& addendA, const unsigned long long addendB) {
    // ToDo: Change this function to remove dependence on HugeIntWord class.
    uint64_t thisWordSum;
    unsigned short thisCarryValue = 0;
//    HugeIntWord *thisAddendWord = addendA.get_least_significant_word();

    thisWordSum = addendB % HUGE_INT_WORD_BASE;
    thisCarryValue = addendB / HUGE_INT_WORD_BASE;
//    thisWordSum += thisAddendWord->get_value();
    thisCarryValue += thisWordSum / HUGE_INT_WORD_BASE;
    thisWordSum = thisWordSum % HUGE_INT_WORD_BASE;
    UnsignedHugeIntValue sum(thisWordSum);

//    thisAddendWord = thisAddendWord->get_next_more_sig_word();

//    while (thisAddendWord != NULL || thisCarryValue > 0) {
//        thisWordSum = thisCarryValue;
//        if (thisAddendWord != NULL) {
//            thisWordSum += thisAddendWord->get_value();
//            thisAddendWord = thisAddendWord->get_next_more_sig_word();
//        }
//        thisCarryValue = thisWordSum / HUGE_INT_WORD_BASE;
//        thisWordSum = thisWordSum % HUGE_INT_WORD_BASE;
//        sum.add_word(thisWordSum);
//    }
    return sum;
}

UnsignedHugeIntValue UnsignedHugeIntValue::subtract(const UnsignedHugeIntValue& minuend, const UnsignedHugeIntValue& subtrahend) {
    // ToDo: Change this function to remove dependence on HugeIntWord class.
    if (UnsignedHugeIntValue::compare(minuend, subtrahend) < 0) {
        throw std::range_error("The subtrahend of an unsigned subtraction operation was greater than the minuend.");
    }

//    HugeIntWord *minuendWord, *subtrahendWord;
    uint64_t thisMinuendWordValue;
    uint32_t thisWordDifference, thisSubtrahendWordValue, carryValue;

    // Determine the least significant word of the difference.
//    minuendWord = minuend.get_least_significant_word();
//    if (minuendWord == NULL)
//        return UnsignedHugeIntValue((unsigned long long)0);
//    subtrahendWord = subtrahend.get_least_significant_word();
//    if (subtrahendWord == NULL)
//        return UnsignedHugeIntValue(minuend);
//    thisMinuendWordValue = minuendWord->get_value();
//    thisSubtrahendWordValue = subtrahendWord->get_value();
    if (thisMinuendWordValue < thisSubtrahendWordValue) {
        thisWordDifference = (HUGE_INT_WORD_BASE + thisMinuendWordValue) - thisSubtrahendWordValue;
        carryValue = 1;
    }
    else {
        thisWordDifference = thisMinuendWordValue - thisSubtrahendWordValue;
        carryValue = 0;
    }
    UnsignedHugeIntValue difference(thisWordDifference);
//    difference.get_least_significant_word();
//    minuendWord = minuendWord->get_next_more_sig_word();
//    subtrahendWord = subtrahendWord->get_next_more_sig_word();

    // Subtract all the words of the subtrahend.
//    while (subtrahendWord != NULL) {
//        thisMinuendWordValue = minuendWord->get_value();
//        thisSubtrahendWordValue = subtrahendWord->get_value() + carryValue;
//        if (thisMinuendWordValue < thisSubtrahendWordValue) {
//            thisWordDifference = (HUGE_INT_WORD_BASE + thisMinuendWordValue) - thisSubtrahendWordValue;
//            carryValue = 1;
//        }
//        else {
//            thisWordDifference = thisMinuendWordValue - thisSubtrahendWordValue;
//            carryValue = 0;
//        }
//        difference.add_word(thisWordDifference);
//        minuendWord = minuendWord->get_next_more_sig_word();
//        subtrahendWord = subtrahendWord->get_next_more_sig_word();
//    }

    // Continue carry operations from the remaining words of the menuend.
//    while (minuendWord != NULL && carryValue > 0) {
//        thisMinuendWordValue = minuendWord->get_value();
//        if (thisMinuendWordValue < carryValue) {
//            thisWordDifference = (HUGE_INT_WORD_BASE + thisMinuendWordValue) - carryValue;
//            carryValue = 1;
//        }
//        else {
//            thisWordDifference = thisMinuendWordValue - carryValue;
//            carryValue = 0;
//        }
//        difference.add_word(thisWordDifference);
//        minuendWord = minuendWord->get_next_more_sig_word();
//    }
//
//    // After carry operations are finished, copy the minuend words to the difference.
//    while (minuendWord != NULL) {
//        thisMinuendWordValue = minuendWord->get_value();
//        difference.add_word(thisMinuendWordValue);
//        minuendWord = minuendWord->get_next_more_sig_word();
//    }
//    difference.remove_extra_leading_words();
    return difference;
}

UnsignedHugeIntValue UnsignedHugeIntValue::multiply(const UnsignedHugeIntValue& factorA, const UnsignedHugeIntValue& factorB) {
    // ToDo: Change this function to remove dependence on HugeIntWord class.
    // ToDo: Possibly apply multithreading to this method.
    // Find the product of the least significant word of each factor.
//    HugeIntWord *startWordA = factorA.get_least_significant_word(); // Starting words when finding a partial product.
//    HugeIntWord *startWordB = factorB.get_least_significant_word();
//    if ((startWordA == NULL) || (startWordB == NULL))
//        return UnsignedHugeIntValue((unsigned long long)0);
//    UnsignedHugeIntValue totalProduct((uint64_t)startWordA->get_value() * startWordB->get_value());
//    HugeIntWord *totalCalcWord = totalProduct.get_least_significant_word();
//    UnsignedHugeIntValue partialProduct;

    // Find partial products while changing startWordA.
//    startWordA = startWordA->get_next_more_sig_word();
//    while (startWordA != NULL) {
//        totalCalcWord = totalCalcWord->get_next_more_sig_word();
//        partialProduct = UnsignedHugeIntValue::find_multiplication_subtotal(startWordA, startWordB);
//        totalCalcWord = totalProduct.add_value_at_word(totalCalcWord, partialProduct);
//        startWordA = startWordA->get_next_more_sig_word();
//    }
//    startWordA = factorA.get_most_significant_word();

    // Find partial products while changing startWordB.
//    startWordB= startWordB->get_next_more_sig_word();
//    while (startWordB != NULL) {
//        totalCalcWord = totalCalcWord->get_next_more_sig_word();
//        partialProduct = UnsignedHugeIntValue::find_multiplication_subtotal(startWordA, startWordB);
//        totalCalcWord = totalProduct.add_value_at_word(totalCalcWord, partialProduct);
//        startWordB = startWordB->get_next_more_sig_word();
//    }

    // Remove leading 0 words.
//    totalProduct.remove_extra_leading_words();

//    return totalProduct;
    return UnsignedHugeIntValue(); // ToDo: Delete this line.    ////////////////////////////////////////////////////////////
}

UnsignedHugeIntValue UnsignedHugeIntValue::multiply_by_int(const unsigned long long factor) const {
    // If factor is small enough to fit in one word of an UnsignedHugeIntValue object, use the faster multiplication function.
    if (factor < HUGE_INT_WORD_BASE)
        return UnsignedHugeIntValue::multiply_single_word(*this, factor);
    UnsignedHugeIntValue factorObject(factor);
    return UnsignedHugeIntValue::multiply(*this, factorObject);
}

UnsignedHugeIntValue UnsignedHugeIntValue::multiply_single_word(const UnsignedHugeIntValue& large_factor, const unsigned long long small_factor) {
    // ToDo: Change this function to remove dependence on HugeIntWord class.
//    HugeIntWord *factorWord, *productWord;
    uint64_t productValue, carryValue;
//    factorWord = large_factor.get_least_significant_word();
//    if ((factorWord == NULL) || (small_factor == 0) || ((large_factor.num_words() < 2) && (factorWord->value == 0)))
//        return UnsignedHugeIntValue((unsigned long long)0);

    // Set the first word of the product.
//    productValue = (uint64_t)factorWord->value * (uint64_t)small_factor;
//    carryValue = productValue / HUGE_INT_WORD_BASE;
//    productValue = productValue % HUGE_INT_WORD_BASE;
//    UnsignedHugeIntValue resultProduct(productValue);
//    productWord = resultProduct.get_least_significant_word();
//    factorWord = factorWord->get_next_more_sig_word();

    // Multiply the other words of the UnsignedHugeIntValue factor.
//    while (factorWord != NULL) {
//        productValue = factorWord->value * small_factor + carryValue;
//        carryValue = productValue / HUGE_INT_WORD_BASE;
//        productValue = productValue % HUGE_INT_WORD_BASE;
//        productWord = new HugeIntWord(productValue, productWord);
//        factorWord = factorWord->get_next_more_sig_word();
//    }

    // Set the most significant word of the product from the carry value.
//    if (carryValue > 0)
//        resultProduct.mostSigWord = new HugeIntWord(carryValue, productWord);
//    else
//        resultProduct.mostSigWord = productWord;
//    return resultProduct;
    return UnsignedHugeIntValue();  // ToDo: Delete this line.  ///////////////////////////////////////////////////////////////////////////////////////////
}

std::pair<UnsignedHugeIntValue, UnsignedHugeIntValue> UnsignedHugeIntValue::divide(const UnsignedHugeIntValue& dividend, const UnsignedHugeIntValue& divisor) {
    // ToDo: Change this function to remove dependence on HugeIntWord class.
    std::pair<UnsignedHugeIntValue, UnsignedHugeIntValue> divisionResults;
//    if (divisor.num_words() == 1) {
//        auto quickDivisionResults = UnsignedHugeIntValue::divide_single_word_divisor(dividend, divisor.get_least_significant_word()->get_value());
//        return std::pair(std::move(quickDivisionResults.first), UnsignedHugeIntValue(quickDivisionResults.second));
//    }
    return UnsignedHugeIntValue::divide_many_word_divisor(dividend, divisor);
}

std::pair<UnsignedHugeIntValue, uint32_t> UnsignedHugeIntValue::divide_single_word_divisor(const UnsignedHugeIntValue& dividend, const uint32_t divisor) {
    // ToDo: Change this function to remove dependence on HugeIntWord class.
    if (divisor == 0) {
        throw std::invalid_argument("An attempt was made to divide by zero.");
    }
//    HugeIntWord *thisDividendWord = dividend.get_most_significant_word();
//    uint64_t subRemainder = thisDividendWord->get_value();
//
//    // The most significant word of the quotient is found first.
//    UnsignedHugeIntValue quotient(subRemainder / divisor);
//    subRemainder %= divisor;
//
//    // The quotient word is found for each corresponding dividend word.
//    thisDividendWord = thisDividendWord->get_next_lower_sig_word();
//    while (thisDividendWord != NULL) {
//        subRemainder *= HUGE_INT_WORD_BASE;
//        subRemainder += thisDividendWord->get_value();
//        quotient.insert_least_significant_word(subRemainder / divisor);
//        subRemainder %= divisor;
//        thisDividendWord = thisDividendWord->get_next_lower_sig_word();
//    }
//
//    // Leading words that have 0 stored are removed.
//    quotient.remove_extra_leading_words();
//    return std::pair(std::move(quotient), (unsigned long)subRemainder);
    return std::pair(UnsignedHugeIntValue(), 0);   // ToDo: Delete this line.  /////////////////////////////////////////////////////////////////////////////////
}

std::pair<UnsignedHugeIntValue, UnsignedHugeIntValue> UnsignedHugeIntValue::divide_many_word_divisor(const UnsignedHugeIntValue& dividend, const UnsignedHugeIntValue& divisor) {
    // ToDo: Change this function to remove dependence on HugeIntWord class.
    std::pair<UnsignedHugeIntValue, UnsignedHugeIntValue> divisionResults;
    unsigned long long dividendNumWords = dividend.num_words();
    unsigned long long divisorNumWords = divisor.num_words();
    unsigned long long remainderNumWords;
//    UnsignedHugeIntValue quotient((unsigned long long)0);
//    HugeIntWord *quotientCalcWord = quotient.get_least_significant_word();
//    HugeIntWord *remainderEstimateWord, *dividendNextWord, *divisorEstimateWord;
//    double dividendLowerEstimate, divisorUpperEstimate;
//    uint64_t quotientWordEstimate;
//
//    if (compare(dividend, divisor) < 0) {
//        return std::pair(quotient, UnsignedHugeIntValue(dividend));
//    }
//    // Add words to the quotient.
//    dividendNextWord = dividend.get_least_significant_word();
//    unsigned long long quotientNumWords = dividendNumWords - divisorNumWords + 1;
//    for (unsigned long long wordNumber = 1; wordNumber < quotientNumWords; ++wordNumber) {
//        quotientCalcWord = quotient.add_word((unsigned long long)0);
//        dividendNextWord = dividendNextWord->get_next_more_sig_word();
//    }
//    UnsignedHugeIntValue subRemainder = integer_with_least_significant_word(dividendNextWord);
//
//    // Set the most significant word of the quotient.
//    // Give a lower estimate of the quotient word.
//    divisorEstimateWord = divisor.get_most_significant_word();
//    remainderEstimateWord = subRemainder.get_most_significant_word();
//    divisorUpperEstimate = divisorEstimateWord->get_value() +
//        (((double)divisorEstimateWord->get_next_lower_sig_word()->get_value() + 1) / HUGE_INT_WORD_BASE);
//    dividendLowerEstimate = remainderEstimateWord->get_value() +
//        (((double)remainderEstimateWord->get_next_lower_sig_word()->get_value()) / HUGE_INT_WORD_BASE);
//    quotientWordEstimate = (uint64_t)(dividendLowerEstimate / divisorUpperEstimate);
//
//    // Multiply the quotient word by the divisor, and subtract the product from the remainder.
//    subRemainder = UnsignedHugeIntValue::subtract(subRemainder, UnsignedHugeIntValue::multiply_single_word(divisor, quotientWordEstimate));
//    // Increase the quotient word until it is the correct value.
//    while (UnsignedHugeIntValue::compare(subRemainder, divisor) >= 0) {
//        ++quotientWordEstimate;
//        subRemainder = subtract(subRemainder, divisor);
//    }
//    // Set the quotient word.
//    quotientCalcWord->add_value(quotientWordEstimate);
//    // Include the next word in the remainder.
//    quotientCalcWord = quotientCalcWord->get_next_lower_sig_word();
//    dividendNextWord = dividendNextWord->get_next_lower_sig_word();
//
//    // Loop through the dividend's words.
//    while (dividendNextWord != NULL) {
//        subRemainder.insert_least_significant_word(dividendNextWord->get_value());
//
//        // Give a lower estimate of the quotient word.
//        remainderEstimateWord = subRemainder.get_most_significant_word();
//        remainderNumWords = subRemainder.num_words();
//        if (remainderNumWords > divisorNumWords) {
//            dividendLowerEstimate = (HUGE_INT_WORD_BASE * remainderEstimateWord->get_value()) +
//                remainderEstimateWord->get_next_lower_sig_word()->get_value();
//        }
//        else if (remainderNumWords < divisorNumWords) {
//            dividendLowerEstimate = 0;
//        }
//        else if (remainderEstimateWord->get_next_lower_sig_word() != NULL)
//            dividendLowerEstimate = remainderEstimateWord->get_value() +
//                (((double)remainderEstimateWord->get_next_lower_sig_word()->get_value()) / HUGE_INT_WORD_BASE);
//        else
//            dividendLowerEstimate = remainderEstimateWord->get_value();
//        quotientWordEstimate = (uint32_t)(dividendLowerEstimate / divisorUpperEstimate);
//
//        // Multiply the quotient word by the divisor, and subtract the product from the remainder.
//        subRemainder = UnsignedHugeIntValue::subtract(subRemainder, UnsignedHugeIntValue::multiply_single_word(divisor, quotientWordEstimate));
//        // Increase the quotient word until it is the correct value.
//        while (UnsignedHugeIntValue::compare(subRemainder, divisor) >= 0) {
//            ++quotientWordEstimate;
//            subRemainder = subtract(subRemainder, divisor);
//        }
//        // Set the quotient word.
//        quotientCalcWord->add_value(quotientWordEstimate);
//        // Include the next word in the remainder.
//        quotientCalcWord = quotientCalcWord->get_next_lower_sig_word();
//        dividendNextWord = dividendNextWord->get_next_lower_sig_word();
//    }
//    // Remove leading zeros.
//    quotient.remove_extra_leading_words();
//    return std::pair(std::move(quotient), std::move(subRemainder));
    return divisionResults; // ToDo: Delete this line.  //////////////////////////////////////////////////////////////////////////////////////////
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator+=(const UnsignedHugeIntValue& addend) {
    // ToDo: Change this function to remove dependence on HugeIntWord class.
//    HugeIntWord *thisWord = this->leastSigWord;
//    HugeIntWord *addendWord = addend.get_least_significant_word();
//
//    while (addendWord != NULL) {
//        if (thisWord != NULL) {
//            thisWord->add_value(addendWord->get_value());
//        }
//        else {
//            thisWord = this->add_word(addendWord->get_value());
//            this->mostSigWord = thisWord;
//        }
//        thisWord = thisWord->get_next_more_sig_word();
//        addendWord = addendWord->get_next_more_sig_word();
//    }
//    // Set the most significant word.
//    HugeIntWord *nextWord = this->mostSigWord->get_next_more_sig_word();
//    while(nextWord != NULL) {
//        this->mostSigWord = nextWord;
//        nextWord = nextWord->get_next_more_sig_word();
//    }
    return *this;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator+=(const unsigned long long addend) {
    // ToDo: Change this function to remove dependence on HugeIntWord class.
//    this->leastSigWord->add_value(addend);
//    // Set the most significant word.
//    HugeIntWord *nextWord = this->mostSigWord->get_next_more_sig_word();
//    while(nextWord != NULL) {
//        this->mostSigWord = nextWord;
//        nextWord = nextWord->get_next_more_sig_word();
//    }
    return *this;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator-=(const UnsignedHugeIntValue& subtrahend) {
    // ToDo: Change this function to remove dependence on HugeIntWord class.
    if (UnsignedHugeIntValue::compare(*this, subtrahend) < 0) {
        throw std::range_error("The subtrahend of an unsigned compound subtraction operation was greater than the minuend.");
    }

//    HugeIntWord *minuendWord, *subtrahendWord;
//    uint64_t thisWordDifference, thisMinuendWordValue, thisSubtrahendWordValue, carryValue(0);
//
//    minuendWord = this->get_least_significant_word();
//    subtrahendWord = subtrahend.get_least_significant_word();
//
//    // Subtract all the words of the subtrahend.
//    while (subtrahendWord != NULL) {
//        thisMinuendWordValue = minuendWord->get_value();
//        thisSubtrahendWordValue = subtrahendWord->get_value() + carryValue;
//        if (thisMinuendWordValue < thisSubtrahendWordValue) {
//            carryValue = 1;
//            thisWordDifference = (HUGE_INT_WORD_BASE + thisMinuendWordValue) - thisSubtrahendWordValue;
//        }
//        else {
//            carryValue = 0;
//            thisWordDifference = thisMinuendWordValue - thisSubtrahendWordValue;
//        }
//        minuendWord->value = thisWordDifference;
//        minuendWord = minuendWord->get_next_more_sig_word();
//        subtrahendWord = subtrahendWord->get_next_more_sig_word();
//    }
//
//    // Continue carry operations from the remaining words of the menuend.
//    while (carryValue > 0 && minuendWord != NULL) {
//        thisMinuendWordValue = minuendWord->get_value();
//        if (thisMinuendWordValue < carryValue) {
//            thisWordDifference = (HUGE_INT_WORD_BASE + thisMinuendWordValue) - carryValue;
//            carryValue = 1;
//        }
//        else {
//            thisWordDifference = thisMinuendWordValue - carryValue;
//            carryValue = 0;
//        }
//        minuendWord->value = thisWordDifference;
//        minuendWord = minuendWord->get_next_more_sig_word();
//    }
//    this->remove_extra_leading_words();
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
    if (factor < HUGE_INT_WORD_BASE) {
        *this = UnsignedHugeIntValue::multiply_single_word(*this, factor);
        return *this;
    }
    *this = UnsignedHugeIntValue::multiply(*this, UnsignedHugeIntValue(factor));
    return *this;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator/=(const UnsignedHugeIntValue& divisor) {
    *this = std::move(UnsignedHugeIntValue::divide(*this, divisor).first);
    return *this;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator/=(const unsigned long long divisor) {
    *this = std::move(UnsignedHugeIntValue::divide(*this, UnsignedHugeIntValue(divisor)).first);
    return *this;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator%=(const UnsignedHugeIntValue& divisor) {
    *this = std::move(UnsignedHugeIntValue::divide(*this, divisor).second);
    return *this;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator%=(const unsigned long long divisor) {
    *this = std::move(UnsignedHugeIntValue::divide(*this, UnsignedHugeIntValue(divisor)).second);
    return *this;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator++() {
    // ToDo: Change this function to remove dependence on HugeIntWord class.
//    this->leastSigWord->add_value(1);
//    // Set the most significant word.
//    HugeIntWord *nextWord = this->mostSigWord->get_next_more_sig_word();
//    while(nextWord != NULL) {
//        this->mostSigWord = nextWord;
//        nextWord = nextWord->get_next_more_sig_word();
//    }
    return *this;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator--() {
    // ToDo: Change this function to remove dependence on HugeIntWord class.
//    if ((this->num_words() <= 1) && (this->leastSigWord->get_value() < 1)) {
//        throw std::range_error("An unsigned integer equal to 0 was decremented.");
//    }
//    HugeIntWord *minuendWord;
//    uint64_t thisMinuendWordValue;
//    minuendWord = this->get_least_significant_word();
//
//    // Subtract all the words of the subtrahend.
//    while (minuendWord != NULL) {
//        thisMinuendWordValue = minuendWord->get_value();
//        if (thisMinuendWordValue < 1) {
//            minuendWord->value = HUGE_INT_WORD_BASE - 1;
//        }
//        else {
//            minuendWord->value = thisMinuendWordValue - 1;
//            break;
//        }
//        minuendWord = minuendWord->get_next_more_sig_word();
//    }
//    this->remove_extra_leading_words();
    return *this;
}

UnsignedHugeIntValue UnsignedHugeIntValue::operator&(const UnsignedHugeIntValue& operand) const {
    // ToDo: Change this function to remove dependence on HugeIntWord class.
//    HugeIntWord *greaterOperandWord, *lesserOperandWord;
//    HugeIntWord *resultMostSigWord;
//
//    if (operand.num_words() > this->num_words()) {
//        greaterOperandWord = operand.get_least_significant_word();
//        lesserOperandWord = this->get_least_significant_word();
//    }
//    else {
//        greaterOperandWord = this->get_least_significant_word();
//        lesserOperandWord = operand.get_least_significant_word();
//    }
//    UnsignedHugeIntValue result(greaterOperandWord->get_value() & lesserOperandWord->get_value());
//    resultMostSigWord = result.get_least_significant_word();
//    lesserOperandWord = lesserOperandWord->get_next_more_sig_word();
//    greaterOperandWord = greaterOperandWord->get_next_more_sig_word();
//
//    while (lesserOperandWord != NULL) {
//        resultMostSigWord = result.add_word(greaterOperandWord->get_value() & lesserOperandWord->get_value());
//        greaterOperandWord = greaterOperandWord->get_next_more_sig_word();
//        lesserOperandWord = lesserOperandWord->get_next_more_sig_word();
//    }
//    result.mostSigWord = resultMostSigWord;
//    result.remove_extra_leading_words();
//    return result;
    return UnsignedHugeIntValue();  // ToDo: Delete this line.  //////////////////////////////////////////////////////////////////////////////////
}

UnsignedHugeIntValue UnsignedHugeIntValue::operator&(const unsigned long long operand) const {
    // ToDo: Change this function to remove dependence on HugeIntWord class.
//    HugeIntWord *operandWord = this->get_least_significant_word();
//    uint64_t operandCarry = operand / HUGE_INT_WORD_BASE;
//    UnsignedHugeIntValue result(operandWord->get_value() & (operand % HUGE_INT_WORD_BASE));
//    HugeIntWord *resultMostSigWord = result.get_least_significant_word();
//    operandWord = operandWord->get_next_more_sig_word();
//    while (operandWord != NULL && operandCarry > 0) {
//        resultMostSigWord = result.add_word(operandWord->get_value() & (operandCarry % HUGE_INT_WORD_BASE));
//        operandCarry /= HUGE_INT_WORD_BASE;
//        operandWord = operandWord->get_next_more_sig_word();
//    }
//    result.mostSigWord = resultMostSigWord;
//    result.remove_extra_leading_words();
//    return result;
    return UnsignedHugeIntValue();  // ToDo: Delete this line.  //////////////////////////////////////////////////////////////////////////////////
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator&=(const UnsignedHugeIntValue& operand) {
    // ToDo: Change this function to remove dependence on HugeIntWord class.
//    HugeIntWord *greaterOperandWord, *lesserOperandWord;
//    HugeIntWord *resultMostSigWord;
//
//    if (operand.num_words() > this->num_words()) {
//        greaterOperandWord = operand.get_least_significant_word();
//        lesserOperandWord = this->get_least_significant_word();
//    }
//    else {
//        greaterOperandWord = this->get_least_significant_word();
//        lesserOperandWord = operand.get_least_significant_word();
//    }
//    resultMostSigWord = this->get_least_significant_word();
//    resultMostSigWord->value = greaterOperandWord->get_value() & lesserOperandWord->get_value();
//    lesserOperandWord = lesserOperandWord->get_next_more_sig_word();
//    greaterOperandWord = greaterOperandWord->get_next_more_sig_word();
//
//    while (lesserOperandWord != NULL) {
//        resultMostSigWord = resultMostSigWord->get_next_more_sig_word();
//        resultMostSigWord->value = greaterOperandWord->get_value() & lesserOperandWord->get_value();
//        greaterOperandWord = greaterOperandWord->get_next_more_sig_word();
//        lesserOperandWord = lesserOperandWord->get_next_more_sig_word();
//    }
//
//    // Excess words in the result must be deleted.
//    HugeIntWord *wordToDelete = resultMostSigWord->get_next_more_sig_word();
//    HugeIntWord *nextMoreSigWord;
//    while (wordToDelete != NULL) {
//        nextMoreSigWord = wordToDelete->get_next_more_sig_word();
//        delete(wordToDelete);
//        wordToDelete = nextMoreSigWord;
//    }
//    resultMostSigWord->moreSigWord = NULL;
//    this->mostSigWord = resultMostSigWord;
//    this->remove_extra_leading_words();
    return *this;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator&=(const unsigned long long operand) {
    // ToDo: Change this function to remove dependence on HugeIntWord class.
//    HugeIntWord *operandWord = this->get_least_significant_word();
//    uint64_t operandCarry = operand / HUGE_INT_WORD_BASE;
//    HugeIntWord *resultMostSigWord = this->get_least_significant_word();
//    resultMostSigWord->value &= (operand % HUGE_INT_WORD_BASE);
//    operandWord = operandWord->get_next_more_sig_word();
//    while (operandWord != NULL && operandCarry > 0) {
//        resultMostSigWord = operandWord;
//        resultMostSigWord->value &= (operandCarry % HUGE_INT_WORD_BASE);
//        operandCarry /= HUGE_INT_WORD_BASE;
//        operandWord = operandWord->get_next_more_sig_word();
//    }
//
//    // Excess words in the result must be deleted.
//    HugeIntWord *nextMoreSigWord;
//    while (operandWord != NULL) {
//        nextMoreSigWord = operandWord->get_next_more_sig_word();
//        delete(operandWord);
//        operandWord = nextMoreSigWord;
//    }
//    resultMostSigWord->moreSigWord = NULL;
//    this->mostSigWord = resultMostSigWord;
//    this->remove_extra_leading_words();
    return *this;
}

UnsignedHugeIntValue UnsignedHugeIntValue::operator|(const UnsignedHugeIntValue& operand) const {
    // ToDo: Change this function to remove dependence on HugeIntWord class.
//    HugeIntWord *greaterOperandWord, *lesserOperandWord;
//    HugeIntWord *resultMostSigWord;
//
//    if (operand.num_words() > this->num_words()) {
//        greaterOperandWord = operand.get_least_significant_word();
//        lesserOperandWord = this->get_least_significant_word();
//    }
//    else {
//        greaterOperandWord = this->get_least_significant_word();
//        lesserOperandWord = operand.get_least_significant_word();
//    }
//
//    // Setting up the least significant word of the result.
//    UnsignedHugeIntValue result(greaterOperandWord->get_value() | lesserOperandWord->get_value());
//    resultMostSigWord = result.get_least_significant_word();
//    lesserOperandWord = lesserOperandWord->get_next_more_sig_word();
//    greaterOperandWord = greaterOperandWord->get_next_more_sig_word();
//
//    // Performing OR operations between matching words.
//    while (lesserOperandWord != NULL) {
//        resultMostSigWord = result.add_word(greaterOperandWord->get_value() | lesserOperandWord->get_value());
//        greaterOperandWord = greaterOperandWord->get_next_more_sig_word();
//        lesserOperandWord = lesserOperandWord->get_next_more_sig_word();
//    }
//
//    // Attaching the most significant words of the greater operand to the result.
//    while (greaterOperandWord != NULL) {
//        resultMostSigWord = result.add_word(greaterOperandWord->get_value());
//        greaterOperandWord = greaterOperandWord->get_next_more_sig_word();
//    }
//
//    result.mostSigWord = resultMostSigWord;
//    return result;
    return UnsignedHugeIntValue();  // ToDo: Delete this line.  //////////////////////////////////////////////////////////////////////////////////
}

UnsignedHugeIntValue UnsignedHugeIntValue::operator|(const unsigned long long operand) const {
    // ToDo: Change this function to remove dependence on HugeIntWord class.
//    HugeIntWord *operandWord = this->get_least_significant_word();
//    uint64_t operandCarry = operand / HUGE_INT_WORD_BASE;
//    UnsignedHugeIntValue result(operandWord->get_value() | (operand % HUGE_INT_WORD_BASE));
//    HugeIntWord *resultMostSigWord = result.get_least_significant_word();
//    operandWord = operandWord->get_next_more_sig_word();
//    while (operandWord != NULL) {
//        resultMostSigWord = result.add_word(operandWord->get_value() | (operandCarry % HUGE_INT_WORD_BASE));
//        operandCarry /= HUGE_INT_WORD_BASE;
//        operandWord = operandWord->get_next_more_sig_word();
//    }
//    while (operandCarry > 0) {
//        resultMostSigWord = result.add_word(operandCarry % HUGE_INT_WORD_BASE);
//        operandCarry /= HUGE_INT_WORD_BASE;
//    }
//    result.mostSigWord = resultMostSigWord;
//    return result;
    return UnsignedHugeIntValue();  // ToDo: Delete this line.  //////////////////////////////////////////////////////////////////////////////////
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator|=(const UnsignedHugeIntValue& operand) {
    // ToDo: Change this function to remove dependence on HugeIntWord class.
//    HugeIntWord *thisWord = this->get_least_significant_word();
//    HugeIntWord *operandWord = operand.get_least_significant_word();
//
//    // Performing OR operations between matching words.
//    while (thisWord != NULL && operandWord != NULL) {
//        thisWord->value |= operandWord->get_value();
//        thisWord = thisWord->get_next_more_sig_word();
//        operandWord = operandWord->get_next_more_sig_word();
//    }
//
//    // If the operand argument does not have more words than the original value,
//    // no words need to be added.
//    if (operandWord == NULL) {
//        return *this;
//    }
//
//    // If the operand argument has more words, those words must be added to the result.
//    HugeIntWord *resultMostSigWord;
//    do {
//        resultMostSigWord = this->add_word(operandWord->get_value());
//        operandWord = operandWord->get_next_more_sig_word();
//    } while (operandWord != NULL);
//
//    this->mostSigWord = resultMostSigWord;
    return *this;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator|=(const unsigned long long operand) {
    // ToDo: Change this function to remove dependence on HugeIntWord class.
//    HugeIntWord *thisWord = this->get_least_significant_word();
//    uint64_t operandCarry = operand / HUGE_INT_WORD_BASE;
//    thisWord->value |= (operand % HUGE_INT_WORD_BASE);
//    thisWord = thisWord->get_next_more_sig_word();
//    while (thisWord != NULL && operandCarry > 0) {
//        thisWord->value |= (operandCarry % HUGE_INT_WORD_BASE);
//        operandCarry /= HUGE_INT_WORD_BASE;
//        thisWord = thisWord->get_next_more_sig_word();
//    }
//
//    // If the operand's value has been completely used, no words need to be added to the result.
//    if (operandCarry == 0) {
//        return *this;
//    }
//
//    // If the operand uses more words than the original value, those words must be added to the result.
//    do {
//        thisWord = this->add_word(operandCarry % HUGE_INT_WORD_BASE);
//        operandCarry /= HUGE_INT_WORD_BASE;
//    } while (operandCarry > 0);
//
//    this->mostSigWord = thisWord;
    return *this;
}

UnsignedHugeIntValue UnsignedHugeIntValue::operator^(const UnsignedHugeIntValue& operand) const {
    // ToDo: Change this function to remove dependence on HugeIntWord class.
//    HugeIntWord *greaterOperandWord, *lesserOperandWord;
//    HugeIntWord *resultMostSigWord;
//
//    if (operand.num_words() > this->num_words()) {
//        greaterOperandWord = operand.get_least_significant_word();
//        lesserOperandWord = this->get_least_significant_word();
//    }
//    else {
//        greaterOperandWord = this->get_least_significant_word();
//        lesserOperandWord = operand.get_least_significant_word();
//    }
//
//    // Setting up the least significant word of the result.
//    UnsignedHugeIntValue result(greaterOperandWord->get_value() ^ lesserOperandWord->get_value());
//    resultMostSigWord = result.get_least_significant_word();
//    lesserOperandWord = lesserOperandWord->get_next_more_sig_word();
//    greaterOperandWord = greaterOperandWord->get_next_more_sig_word();
//
//    // Performing XOR operations between matching words.
//    while (lesserOperandWord != NULL) {
//        resultMostSigWord = result.add_word(greaterOperandWord->get_value() ^ lesserOperandWord->get_value());
//        greaterOperandWord = greaterOperandWord->get_next_more_sig_word();
//        lesserOperandWord = lesserOperandWord->get_next_more_sig_word();
//    }
//
//    // Attaching the most significant words of the greater operand to the result.
//    while (greaterOperandWord != NULL) {
//        resultMostSigWord = result.add_word(greaterOperandWord->get_value());
//        greaterOperandWord = greaterOperandWord->get_next_more_sig_word();
//    }
//
//    result.mostSigWord = resultMostSigWord;
//    result.remove_extra_leading_words();
//    return result;
    return UnsignedHugeIntValue();  // ToDo: Delete this line.  //////////////////////////////////////////////////////////////////////////////////
}

UnsignedHugeIntValue UnsignedHugeIntValue::operator^(const unsigned long long operand) const {
    // ToDo: Change this function to remove dependence on HugeIntWord class.
//    HugeIntWord *operandWord = this->get_least_significant_word();
//    uint64_t operandCarry = operand / HUGE_INT_WORD_BASE;
//    UnsignedHugeIntValue result(operandWord->get_value() ^ (operand % HUGE_INT_WORD_BASE));
//    HugeIntWord *resultMostSigWord = result.get_least_significant_word();
//    operandWord = operandWord->get_next_more_sig_word();
//    while (operandWord != NULL) {
//        resultMostSigWord = result.add_word(operandWord->get_value() ^ (operandCarry % HUGE_INT_WORD_BASE));
//        operandCarry /= HUGE_INT_WORD_BASE;
//        operandWord = operandWord->get_next_more_sig_word();
//    }
//    while (operandCarry > 0) {
//        resultMostSigWord = result.add_word(operandCarry % HUGE_INT_WORD_BASE);
//        operandCarry /= HUGE_INT_WORD_BASE;
//    }
//    result.mostSigWord = resultMostSigWord;
//    result.remove_extra_leading_words();
//    return result;
    return UnsignedHugeIntValue();  // ToDo: Delete this line.  //////////////////////////////////////////////////////////////////////////////////
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator^=(const UnsignedHugeIntValue& operand) {
    // ToDo: Change this function to remove dependence on HugeIntWord class.
//    HugeIntWord *thisWord = this->get_least_significant_word();
//    HugeIntWord *operandWord = operand.get_least_significant_word();
//
//    // Performing XOR operations between matching words.
//    while (thisWord != NULL && operandWord != NULL) {
//        thisWord->value ^= operandWord->get_value();
//        thisWord = thisWord->get_next_more_sig_word();
//        operandWord = operandWord->get_next_more_sig_word();
//    }
//
//    // If the operand argument does not have more words than the original value,
//    // no words need to be added.
//    if (operandWord == NULL) {
//        this->remove_extra_leading_words();
//        return *this;
//    }
//
//    // If the operand argument has more words, those words must be added to the result.
//    HugeIntWord *resultMostSigWord;
//    do {
//        resultMostSigWord = this->add_word(operandWord->get_value());
//        operandWord = operandWord->get_next_more_sig_word();
//    } while (operandWord != NULL);
//
//    this->mostSigWord = resultMostSigWord;
//    this->remove_extra_leading_words();
    return *this;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator^=(const unsigned long long operand) {
    // ToDo: Change this function to remove dependence on HugeIntWord class.
//    HugeIntWord *thisWord = this->get_least_significant_word();
//    uint64_t operandCarry = operand / HUGE_INT_WORD_BASE;
//    thisWord->value ^= (operand % HUGE_INT_WORD_BASE);
//    thisWord = thisWord->get_next_more_sig_word();
//    while (thisWord != NULL && operandCarry > 0) {
//        thisWord->value ^= (operandCarry % HUGE_INT_WORD_BASE);
//        operandCarry /= HUGE_INT_WORD_BASE;
//        thisWord = thisWord->get_next_more_sig_word();
//    }
//
//    // If the operand's value has been completely used, no words need to be added to the result.
//    if (operandCarry == 0) {
//        this->remove_extra_leading_words();
//        return *this;
//    }
//
//    // If the operand uses more words than the original value, those words must be added to the result.
//    do {
//        thisWord = this->add_word(operandCarry % HUGE_INT_WORD_BASE);
//        operandCarry /= HUGE_INT_WORD_BASE;
//    } while (operandCarry > 0);
//
//    this->mostSigWord = thisWord;
//    this->remove_extra_leading_words();
    return *this;
}

UnsignedHugeIntValue UnsignedHugeIntValue::bitwise_not(const unsigned long long number_of_bits) const {
    // ToDo: Change this function to remove dependence on HugeIntWord class.
    if (number_of_bits == 0) {
        return UnsignedHugeIntValue();
    }
    const unsigned long long numFullWords = number_of_bits / HUGE_INT_NUMBER_OF_BITS_PER_WORD;
    const int numExtraBits = number_of_bits % HUGE_INT_NUMBER_OF_BITS_PER_WORD;
//    HugeIntWord *origWord = this->get_least_significant_word(); // Word of the original value.
    unsigned long long currentWordNumber;

    // The least significant word of the result is set first.
//    if (numFullWords == 0) {
//        // Mask bits left of the specified number of bits.
//        return UnsignedHugeIntValue((~origWord->get_value()) &
//                                    (HUGE_INT_MAX_WORD_VALUE >> (HUGE_INT_NUMBER_OF_BITS_PER_WORD - numExtraBits)));
//    }
//    UnsignedHugeIntValue resultValue(~origWord->get_value());
//    origWord = origWord->get_next_more_sig_word();
//
//    // The not operation is applied to full words of the original value.
//    for (currentWordNumber = 1; (currentWordNumber < numFullWords) && (origWord != NULL); ++currentWordNumber) {
//        resultValue.add_word(~origWord->get_value());
//        origWord = origWord->get_next_more_sig_word();
//    }
//
//    // If there are no more words in the original value, all remaining result bits should be ones.
//    for (; currentWordNumber < numFullWords; ++currentWordNumber) {
//        resultValue.add_word(HUGE_INT_MAX_WORD_VALUE);
//    }
//
//    // The most significant word of the result is set last.
//    if (numExtraBits == 0) {
//        return resultValue;
//    }
//    if (origWord == NULL) {
//        resultValue.add_word(HUGE_INT_MAX_WORD_VALUE >> (HUGE_INT_NUMBER_OF_BITS_PER_WORD - numExtraBits));
//        return resultValue;
//    }
//    resultValue.add_word((~origWord->get_value()) &
//                          (HUGE_INT_MAX_WORD_VALUE >> (HUGE_INT_NUMBER_OF_BITS_PER_WORD - numExtraBits)));
//    return resultValue;
    return UnsignedHugeIntValue();  // ToDo: Delete this line.  //////////////////////////////////////////////////////////////////////////////////
}

UnsignedHugeIntValue UnsignedHugeIntValue::operator<<(const unsigned long long number_of_bits) const {
    // ToDo: Change this function to remove dependence on HugeIntWord class.
//    if ((this->num_words() == 1) && (this->get_least_significant_word()->get_value() == 0)) {
//        return UnsignedHugeIntValue();
//    }
//    if (number_of_bits == 0) {
//        return UnsignedHugeIntValue(*this);
//    }
//    const unsigned long long numFullWordsShifted = number_of_bits / HUGE_INT_NUMBER_OF_BITS_PER_WORD;
//    const int wordShiftSize = number_of_bits % HUGE_INT_NUMBER_OF_BITS_PER_WORD;
//    const int carryShiftSize = HUGE_INT_NUMBER_OF_BITS_PER_WORD - wordShiftSize;
//    uint32_t origWordValue, carryValue;
//    HugeIntWord *origWord = this->get_least_significant_word(); // Word of the original value.
//
//    UnsignedHugeIntValue resultValue;
//    // Words with value 0 are created for every multiple of a full word that was shifted.
//    for (unsigned long long wordNum = 0; wordNum < numFullWordsShifted; ++wordNum) {
//        resultValue.add_word();
//    }
//
//    // The next word gets its value from shifting the corresponding original word value.
//    origWordValue = origWord->get_value();
//    if (wordShiftSize == 0) {
//        carryValue = 0;
//    } else {
//        carryValue = origWordValue >> carryShiftSize;
//    }
//    resultValue.get_most_significant_word()->value = origWordValue << wordShiftSize;
//    origWord = origWord->get_next_more_sig_word();
//
//    // The next result word values are combined from two words of the original value.
//    while (origWord != NULL) {
//        origWordValue = origWord->get_value();
//        resultValue.add_word((origWordValue << wordShiftSize) | carryValue);
//        if (wordShiftSize > 0) {
//            carryValue = origWordValue >> carryShiftSize;
//        }
//        origWord = origWord->get_next_more_sig_word();
//    }
//
//    // The most significant result word value is created only from the carry value.
//    if (carryValue > 0) {
//        resultValue.add_word(carryValue);
//    }
//    return resultValue;
    return UnsignedHugeIntValue();  // ToDo: Delete this line.  //////////////////////////////////////////////////////////////////////////////////
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator<<=(const unsigned long long number_of_bits) {
    // ToDo: Change this function to remove dependence on HugeIntWord class.
//    if ((this->num_words() == 1) && (this->get_least_significant_word()->get_value() == 0)) {
//        return *this;
//    }
//    if (number_of_bits == 0) {
//        return *this;
//    }
//
//    const unsigned long long numFullWordsShifted = number_of_bits / HUGE_INT_NUMBER_OF_BITS_PER_WORD;
//    const int wordShiftSize = number_of_bits % HUGE_INT_NUMBER_OF_BITS_PER_WORD;
//    const int carryShiftSize = HUGE_INT_NUMBER_OF_BITS_PER_WORD - wordShiftSize;
//    uint32_t readWordValue, carryValue, shiftedWordValue;
//    HugeIntWord *readWord = this->get_most_significant_word(); // Word being read.
//    HugeIntWord *writeWord; // Word being changed.
//
//    // Words are created for every multiple of a full word that was shifted.
//    for (unsigned long long wordNum = 0; wordNum < numFullWordsShifted; ++wordNum) {
//        this->add_word();
//    }
//    writeWord = this->get_most_significant_word();
//
//    // The bits that were shifted left from the most significant word become
//    // the value of the new most significant word.
//    readWordValue = readWord->get_value();
//    carryValue = 0;
//    if (wordShiftSize == 0) {
//        carryValue = 0;
//    } else {
//        carryValue = readWordValue >> carryShiftSize;
//    }
//    if (carryValue > 0) {
//        this->add_word(carryValue);
//    }
//    shiftedWordValue = readWordValue << wordShiftSize;
//    readWord = readWord->get_next_lower_sig_word();
//
//    // The next new word values are combined from two words of the original value.
//    while (readWord != NULL) {
//        readWordValue = readWord->get_value();
//        if (wordShiftSize > 0) {
//            carryValue = readWordValue >> carryShiftSize;
//        }
//        writeWord->value = carryValue | shiftedWordValue;
//        shiftedWordValue = readWordValue << wordShiftSize;
//        writeWord = writeWord->get_next_lower_sig_word();
//        readWord = readWord->get_next_lower_sig_word();
//    }
//
//    // The shifted least significant word of the original value is put into the new value.
//    writeWord->value = shiftedWordValue;
//    writeWord = writeWord->get_next_lower_sig_word();
//
//    // The words that were shifted in from the right should have a value of 0.
//    while (writeWord != NULL) {
//        writeWord->value = 0;
//        writeWord = writeWord->get_next_lower_sig_word();
//    }
    return *this;
}

UnsignedHugeIntValue UnsignedHugeIntValue::operator>>(const unsigned long long number_of_bits) const {
    // ToDo: Change this function to remove dependence on HugeIntWord class.
//    if ((this->num_words() == 1) && (this->get_least_significant_word()->get_value() == 0)) {
//        return UnsignedHugeIntValue();
//    }
//    if (number_of_bits == 0) {
//        return UnsignedHugeIntValue(*this);
//    }
//    const unsigned long long numFullWordsShifted = number_of_bits / HUGE_INT_NUMBER_OF_BITS_PER_WORD;
//    const int wordShiftSize = number_of_bits % HUGE_INT_NUMBER_OF_BITS_PER_WORD;
//    const int carryShiftSize = HUGE_INT_NUMBER_OF_BITS_PER_WORD - wordShiftSize;
//    uint32_t origWordValue, shiftedWordValue, carryValue;
//    HugeIntWord *origWord = this->get_least_significant_word(); // Word of the original value.
//
//    // A word of the original value is ignored for each full word that was shifted.
//    for (unsigned long long wordNum = 0; wordNum < numFullWordsShifted; ++wordNum) {
//        origWord = origWord->get_next_more_sig_word();
//        if (origWord == NULL) {
//            // If the shift was larger than the original value, 0 is returned.
//            return UnsignedHugeIntValue();
//        }
//    }
//
//    // The least significant word for a new result object is set.
//    shiftedWordValue = origWord->get_value() >> wordShiftSize;
//    origWord = origWord->get_next_more_sig_word();
//    if (origWord == NULL) {
//        return UnsignedHugeIntValue(shiftedWordValue);
//    }
//    origWordValue = origWord->get_value();
//    if (wordShiftSize == 0) {
//        carryValue = 0;
//    } else {
//        carryValue = origWordValue << carryShiftSize;
//    }
//    UnsignedHugeIntValue resultValue(carryValue | shiftedWordValue);
//    shiftedWordValue = origWordValue >> wordShiftSize;
//    origWord = origWord->get_next_more_sig_word();
//
//    // The result word values are combined from two words of the original value.
//    while (origWord != NULL) {
//        origWordValue = origWord->get_value();
//        if (wordShiftSize > 0) {
//            carryValue = origWordValue << carryShiftSize;
//        }
//        resultValue.add_word(carryValue | shiftedWordValue);
//        shiftedWordValue = origWordValue >> wordShiftSize;
//        origWord = origWord->get_next_more_sig_word();
//    }
//
//    // The most significant result word value is set from the final shifted value.
//    if (shiftedWordValue > 0) {
//        resultValue.add_word(shiftedWordValue);
//    }
//    return resultValue;
    return UnsignedHugeIntValue();  // ToDo: Delete this line.  //////////////////////////////////////////////////////////////////////////////////
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator>>=(const unsigned long long number_of_bits) {
    // ToDo: Change this function to remove dependence on HugeIntWord class.
//    if ((this->num_words() == 1) && (this->get_least_significant_word()->get_value() == 0)) {
//        return *this;
//    }
//    if (number_of_bits == 0) {
//        return *this;
//    }
//
//    const unsigned long long numFullWordsShifted = number_of_bits / HUGE_INT_NUMBER_OF_BITS_PER_WORD;
//    const int wordShiftSize = number_of_bits % HUGE_INT_NUMBER_OF_BITS_PER_WORD;
//    const int carryShiftSize = HUGE_INT_NUMBER_OF_BITS_PER_WORD - wordShiftSize;
//    uint32_t readWordValue, shiftedWordValue, carryValue;
//    HugeIntWord *readWord = this->get_least_significant_word(); // Word being read.
//    HugeIntWord *writeWord = readWord; // Word being changed.
//    HugeIntWord *wordToDelete;
//
//    // A word of the original value is ignored for each full word that was shifted.
//    for (unsigned long long wordNum = 0; wordNum < numFullWordsShifted; ++wordNum) {
//        readWord = readWord->get_next_more_sig_word();
//        if (readWord == NULL) {
//            // If the shift was larger than the original value, the resulting value is 0.
//            *this = UnsignedHugeIntValue();
//            return *this;
//        }
//    }
//
//    // The result word values are combined from two words of the original value.
//    shiftedWordValue = readWord->get_value() >> wordShiftSize;
//    readWord = readWord->get_next_more_sig_word();
//    carryValue = 0;
//    while (readWord != NULL) {
//        readWordValue = readWord->get_value();
//        if (wordShiftSize > 0) {
//            carryValue = readWordValue << carryShiftSize;
//        }
//        writeWord->value = carryValue | shiftedWordValue;
//        shiftedWordValue = readWordValue >> wordShiftSize;
//        readWord = readWord->get_next_more_sig_word();
//        writeWord = writeWord->get_next_more_sig_word();
//    }
//
//    // The most significant result word value is set from the final shifted value.
//    if ((shiftedWordValue > 0) || (writeWord->get_next_lower_sig_word() == NULL)) {
//        writeWord->value = shiftedWordValue;
//        wordToDelete = writeWord->get_next_more_sig_word();
//    }
//    else {
//        wordToDelete = writeWord;
//        writeWord = writeWord->get_next_lower_sig_word();
//    }
//    this->mostSigWord = writeWord;
//    writeWord->moreSigWord = NULL;
//
//    // Excess words in the result must be deleted.
//    while (wordToDelete != NULL) {
//        writeWord = wordToDelete->get_next_more_sig_word();
//        delete(wordToDelete);
//        wordToDelete = writeWord;
//    }
    return *this;
}

UnsignedHugeIntValue UnsignedHugeIntValue::left_ones_shifted(const unsigned long long number_of_bits) const {
    // ToDo: Change this function to remove dependence on HugeIntWord class.
    if (number_of_bits == 0) {
        return UnsignedHugeIntValue(*this);
    }
    const unsigned long long numFullWordsShifted = number_of_bits / HUGE_INT_NUMBER_OF_BITS_PER_WORD;
    const int wordShiftSize = number_of_bits % HUGE_INT_NUMBER_OF_BITS_PER_WORD;
    const int carryShiftSize = HUGE_INT_NUMBER_OF_BITS_PER_WORD - wordShiftSize;
    uint32_t origWordValue, carryValue, newWordValue;
//    HugeIntWord *origWord = this->get_least_significant_word(); // Word of the original value.

    UnsignedHugeIntValue resultValue(HUGE_INT_MAX_WORD_VALUE);
    // Words with all 1 bits are created for every multiple of a full word that was shifted.
//    for (unsigned long long wordNum = 0; wordNum < numFullWordsShifted; ++wordNum) {
//        resultValue.add_word(HUGE_INT_MAX_WORD_VALUE);
//    }

    // The next word gets its value from shifting the corresponding original word value.
//    origWordValue = origWord->get_value();
//    if (wordShiftSize == 0) {
//        carryValue = 0;
//        newWordValue = origWordValue;
//    } else {
//        carryValue = origWordValue >> carryShiftSize;
//        newWordValue = (origWordValue << wordShiftSize) | (HUGE_INT_MAX_WORD_VALUE >> carryShiftSize);
//    }
//    resultValue.get_most_significant_word()->value = newWordValue;
//    origWord = origWord->get_next_more_sig_word();

    // The next result word values are combined from two words of the original value.
//    while (origWord != NULL) {
//        origWordValue = origWord->get_value();
//        if (wordShiftSize == 0) {
//            newWordValue = origWordValue;
//        } else {
//            newWordValue = (origWordValue << wordShiftSize) | carryValue;
//            carryValue = origWordValue >> carryShiftSize;
//        }
//        resultValue.add_word(newWordValue);
//        origWord = origWord->get_next_more_sig_word();
//    }

    // The most significant result word value is created only from the carry value.
//    if (carryValue > 0) {
//        resultValue.add_word(carryValue);
//    }
    resultValue.remove_extra_leading_words();
    return resultValue;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::left_ones_shift_transform(const unsigned long long number_of_bits) {
    // ToDo: Change this function to remove dependence on HugeIntWord class.
    if (number_of_bits == 0) {
        return *this;
    }

    const unsigned long long numFullWordsShifted = number_of_bits / HUGE_INT_NUMBER_OF_BITS_PER_WORD;
    const int wordShiftSize = number_of_bits % HUGE_INT_NUMBER_OF_BITS_PER_WORD;
    const int carryShiftSize = HUGE_INT_NUMBER_OF_BITS_PER_WORD - wordShiftSize;
    uint32_t readWordValue, carryValue, shiftedWordValue;
//    HugeIntWord *readWord = this->get_most_significant_word(); // Word being read.
//    HugeIntWord *writeWord; // Word being changed.

    // Words are created for every multiple of a full word that was shifted.
//    for (unsigned long long wordNum = 0; wordNum < numFullWordsShifted; ++wordNum) {
//        this->add_word();
//    }
//    writeWord = this->get_most_significant_word();

    // The bits that were shifted left from the most significant word become
    // the value of the new most significant word.
//    readWordValue = readWord->get_value();
//    if (wordShiftSize == 0) {
//        carryValue = 0;
//    } else {
//        carryValue = readWordValue >> carryShiftSize;
//    }
//    if (carryValue > 0) {
//        this->add_word(carryValue);
//    }
//    shiftedWordValue = readWordValue << wordShiftSize;
//    readWord = readWord->get_next_lower_sig_word();

    // The next new word values are combined from two words of the original value.
//    while (readWord != NULL) {
//        readWordValue = readWord->get_value();
//        if (wordShiftSize > 0) {
//            carryValue = readWordValue >> carryShiftSize;
//        }
//        writeWord->value = carryValue | shiftedWordValue;
//        shiftedWordValue = readWordValue << wordShiftSize;
//        writeWord = writeWord->get_next_lower_sig_word();
//        readWord = readWord->get_next_lower_sig_word();
//    }

    // The shifted least significant word of the original value is put into the new value.
//    if (wordShiftSize == 0) {
//        writeWord->value = shiftedWordValue;
//    } else {
//        writeWord->value = shiftedWordValue | (HUGE_INT_MAX_WORD_VALUE >> carryShiftSize);
//    }
//    writeWord = writeWord->get_next_lower_sig_word();
//
//    // The words that were shifted in from the right should have a value of 0.
//    while (writeWord != NULL) {
//        writeWord->value = HUGE_INT_MAX_WORD_VALUE;
//        writeWord = writeWord->get_next_lower_sig_word();
//    }
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
    // ToDo: Change this function to remove dependence on HugeIntWord class.
    if (integer_file == NULL)
        throw std::invalid_argument("A null file pointer was given as an argument.");
    this->delete_all_words();
    char readBuffer[HUGE_INT_NUMBER_OF_BASE_10_DIGITS_PER_WORD+ 1];
    char nextChar;
    uint32_t segmentValue;
    uint32_t multiplier;
    unsigned short placeIndex;
//    this->mostSigWord = this->leastSigWord = new HugeIntWord(0);
//    do {
//        placeIndex = 0;
//        multiplier = 1;
//        // A segment of digits is read at a time and converted to a long integer.
//        while (placeIndex < HUGE_INT_NUMBER_OF_BASE_10_DIGITS_PER_WORD) {
//            nextChar = fgetc(integer_file);
//            // When the end of the file is reached, no more digits are put in the buffer, and
//            // the multiplier keeps its value.
//            if (nextChar == EOF)
//                break;
//            // Characters that are not digits will be skipped.
//            if (isdigit(nextChar)) {
//                readBuffer[placeIndex] = nextChar;
//                ++placeIndex;
//                multiplier *= 10;
//            }
//        }
//        readBuffer[placeIndex] = '\0'; // End of the number segment.
//        // Converts the string to a long integer.
//        segmentValue = strtoul(readBuffer, NULL, 10);
//        *this = UnsignedHugeIntValue::multiply_single_word(*this, multiplier);
//        this->add_value_at_word(this->leastSigWord, segmentValue);
//    } while (nextChar != EOF);
    this->word_values = new std::vector<uint32_t>(1, 0);    // ToDo: Delete or change this line. /////////////////////////////////////////////////////////////////////
}

void UnsignedHugeIntValue::write_to_text_file(std::string file_path) const {
    // Prevent writing to an existing file.
    struct stat placeholder_stat;
    if (stat(file_path.c_str(), &placeholder_stat) >= 0)
        std::invalid_argument("An attempt was made to write an UnsignedHugeIntValue value to an existing file.");
    FILE *writeTextFile = fopen(file_path.c_str(), "w");
    this->write_to_text_file(writeTextFile);
    fclose(writeTextFile);
}

void UnsignedHugeIntValue::write_to_text_file(FILE* integer_file) const {
    // ToDo: Change this function to remove dependence on HugeIntWord class.
    if (integer_file == NULL)
        throw std::invalid_argument("A null file pointer was given as an argument.");
    if (this->num_words() <= 0) {
        throw std::logic_error("An attempt was made to write an undefined value to a file.");
    }
    std::string bufferString;
//    if (this->num_words() == 1) {
//        bufferString = std::to_string(this->leastSigWord->get_value());
//        fputs(bufferString.c_str(), integer_file);
//        return;
//    }
//
//    // The number of digits must be found to determine the size of the output file.
//    unsigned long long numDigits(HUGE_INT_NUMBER_OF_BASE_10_DIGITS_PER_WORD);
//    uint32_t segmentBase = 1;
//    for (unsigned short exponent = 1; exponent <= HUGE_INT_NUMBER_OF_BASE_10_DIGITS_PER_WORD; ++exponent){
//        segmentBase *= 10;
//    }
//    auto divisionResult = UnsignedHugeIntValue::divide_single_word_divisor(this, segmentBase);
//    UnsignedHugeIntValue &quotient = divisionResult.first;
//    uint32_t &remainder = divisionResult.second;
//    while (quotient.num_words() > 1) {
//        divisionResult = UnsignedHugeIntValue::divide_single_word_divisor(quotient, segmentBase);
//        numDigits += HUGE_INT_NUMBER_OF_BASE_10_DIGITS_PER_WORD;
//    }
//    bufferString = std::to_string(quotient.leastSigWord->get_value());
//    numDigits += bufferString.length();
//
//    // The first sets of digits were already found, so they are sent to the output file.
//    fputs(bufferString.c_str(), integer_file);
//    bufferString = std::to_string(remainder);
//    bufferString = std::string(HUGE_INT_NUMBER_OF_BASE_10_DIGITS_PER_WORD - bufferString.length(), '0') + bufferString;
//    fputs(bufferString.c_str(), integer_file);
//
//    // The other output digits are found in segments, in order of least significant segment of digits.
//    divisionResult = UnsignedHugeIntValue::divide_single_word_divisor(this, segmentBase);
//    unsigned long long segmentIndex;
//    for (segmentIndex = numDigits - HUGE_INT_NUMBER_OF_BASE_10_DIGITS_PER_WORD;
//            segmentIndex > HUGE_INT_NUMBER_OF_BASE_10_DIGITS_PER_WORD;
//            segmentIndex -= HUGE_INT_NUMBER_OF_BASE_10_DIGITS_PER_WORD) {
//        bufferString = std::to_string(remainder);
//        bufferString = std::string(HUGE_INT_NUMBER_OF_BASE_10_DIGITS_PER_WORD - bufferString.length(), '0') + bufferString;
//        fseek(integer_file, segmentIndex, SEEK_SET);
//        fputs(bufferString.c_str(), integer_file);
//        divisionResult = UnsignedHugeIntValue::divide_single_word_divisor(quotient, segmentBase);
//    }
}

void UnsignedHugeIntValue::read_from_binary_file(std::string file_path) {
    // ToDo: Change this function to remove dependence on HugeIntWord class.
    this->delete_all_words();
//    this->mostSigWord = this->leastSigWord = NULL;
    unsigned long long remainingNumWords;
    uint32_t readBuffer[BUFFER_NUM_WORDS];
//    HugeIntWord *thisWord;
    unsigned int bufferSize = sizeof(uint32_t) * BUFFER_NUM_WORDS;
    unsigned int bufferIndex;
    char *readDest = (char*)readBuffer;

//    std::ifstream fileReadStream(file_path, std::ios::in | std::ios::binary);
//    if (!fileReadStream.is_open()) {
//        fileReadStream.close();
//        throw std::invalid_argument("The file " + file_path + " could not be opened.");
//    }
//    fileReadStream >> remainingNumWords;

    // Read the first word from the binary file.
//    if (remainingNumWords < 1) {
//        this->mostSigWord = this->leastSigWord = new HugeIntWord(0);
//        fileReadStream.close();
//        return;
//    }
//    fileReadStream.read(readDest, sizeof(uint32_t));
//    this->leastSigWord = thisWord = new HugeIntWord(readBuffer[0]);
//    --remainingNumWords;
//
//    // Read full buffers from the binary file.
//    while (remainingNumWords > BUFFER_NUM_WORDS) {
//        fileReadStream.read(readDest, bufferSize);
//        for (bufferIndex = 0; bufferIndex < BUFFER_NUM_WORDS; ++bufferIndex) {
//            thisWord = new HugeIntWord(readBuffer[bufferIndex], thisWord);
//        }
//        remainingNumWords -= BUFFER_NUM_WORDS;
//    }
//
//    // Read the last partial buffer from the binary file.
//    fileReadStream.read(readDest, sizeof(uint32_t) * remainingNumWords);
//    for (bufferIndex = 0; bufferIndex < remainingNumWords; ++bufferIndex) {
//        thisWord = new HugeIntWord(readBuffer[bufferIndex], thisWord);
//    }
//    fileReadStream.close();
//    this->mostSigWord = thisWord;
    this->word_values = new std::vector<uint32_t>(1, 0);    // ToDo: Delete or change this line. /////////////////////////////////////////////////////////////////////
}

void UnsignedHugeIntValue::write_to_binary_file(std::string file_path) const {
    // ToDo: Change this function to remove dependence on HugeIntWord class.
    // Prevent writing to an existing file.
    struct stat placeholder_stat;
    if (stat(file_path.c_str(), &placeholder_stat) >= 0)
        std::invalid_argument("An attempt was made to write an UnsignedHugeIntValue value to an existing file.");
    uint32_t writeBuffer[BUFFER_NUM_WORDS];
    char *writeSource = (char*)writeBuffer;
    unsigned int bufferSize = sizeof(uint32_t) * BUFFER_NUM_WORDS;
    unsigned int bufferIndex;
//    HugeIntWord *thisWord = this->leastSigWord;

//    std::ofstream fileWriteStream(file_path, std::ios::out | std::ios::binary);
//    if (!fileWriteStream.is_open()) {
//        fileWriteStream.close();
//        throw std::invalid_argument("The file at " + file_path + " could not be created.");
//    }
//    // Write the number of words at the start of the file.
//    fileWriteStream << this->num_words();
//
//    // Write all the word values to the file.
//    while (thisWord != NULL) {
//        for (bufferIndex = 0; bufferIndex < BUFFER_NUM_WORDS; ++bufferIndex) {
//            writeBuffer[bufferIndex] = thisWord->get_value();
//            thisWord = thisWord->get_next_more_sig_word();
//            if (thisWord == NULL) {
//                fileWriteStream.write(writeSource, sizeof(uint32_t) * (bufferIndex + 1));
//                fileWriteStream.close();
//                return;
//            }
//        }
//        fileWriteStream.write(writeSource, bufferSize);
//    }
//    fileWriteStream.close();
}

long UnsignedHugeIntValue::num_words() const {
    return this->word_values->size();
}

HugeIntWord* UnsignedHugeIntValue::get_most_significant_word() const {
    // ToDo: Remove this function to remove dependence on HugeIntWord class.
//    return this->mostSigWord;
    return NULL;
}

HugeIntWord* UnsignedHugeIntValue::get_least_significant_word() const {
    // ToDo: Remove this function to remove dependence on HugeIntWord class.
//    return this->leastSigWord;
    return NULL;
}

HugeIntWord* UnsignedHugeIntValue::remove_most_significant_word() {
    // ToDo: Change or remove this function to remove dependence on HugeIntWord class.
//    HugeIntWord *oldMostSigWord = this->mostSigWord;
//    if (oldMostSigWord == NULL) {
//        throw std::logic_error("An UnsignedHugeIntValue object has no words or value.");
//    }
//    HugeIntWord *newMostSigWord = oldMostSigWord->get_next_lower_sig_word();
//    if (newMostSigWord == NULL) {
//        throw std::logic_error("An attempt was made to remove the only word of an UnsignedHugeIntValue object.");
//    }
//    newMostSigWord->remove_more_significant_word();
//    this->mostSigWord = newMostSigWord;
//    delete(oldMostSigWord);
//    return newMostSigWord;
    return NULL;
}

std::string UnsignedHugeIntValue::to_string() const {
    // ToDo: Change this function to remove dependence on HugeIntWord class.
//    if (this->mostSigWord == NULL)
//        return "0";
//    uint32_t zero_long(0);
//    UnsignedHugeIntValue zero_object(zero_long);
//    if (this->compare(this, zero_long) == 0)
//        return "0";
    std::string fullNumberString;
    unsigned long long allocationSize;
    // The maximum number of digits can be found from the number of bits used.
//    allocationSize = 0.30103 * HUGE_INT_NUMBER_OF_BITS_PER_WORD * this->num_words() + 1;
//    fullNumberString.resize(allocationSize, '0');
//    // The base used for segments is determined by the maximum power of ten that can be stored in a word.
//    uint32_t segmentBase = 1;
//    for (unsigned short exponent = 1; exponent <= HUGE_INT_NUMBER_OF_BASE_10_DIGITS_PER_WORD; ++exponent) {
//        segmentBase *= 10;
//    }
//
//    // Setting the digits of the result string in segments.
//    unsigned long long segmentStart = allocationSize; // index of the start of the current segment in the result string.
//    auto divisionResult = UnsignedHugeIntValue::divide_single_word_divisor(this, segmentBase);
//    UnsignedHugeIntValue &quotient = divisionResult.first;
//    uint32_t &remainder = divisionResult.second;
//
//    while (this->compare(quotient, zero_object) > 0) {
//        segmentStart -= HUGE_INT_NUMBER_OF_BASE_10_DIGITS_PER_WORD;
//        std::string segmentString(std::to_string(remainder));
//        unsigned short numLeadingZeros = HUGE_INT_NUMBER_OF_BASE_10_DIGITS_PER_WORD - segmentString.length();
//        segmentString = std::string(numLeadingZeros, '0') + std::string(segmentString);
//        fullNumberString.replace(segmentStart, HUGE_INT_NUMBER_OF_BASE_10_DIGITS_PER_WORD, segmentString);
//
//        divisionResult = UnsignedHugeIntValue::divide_single_word_divisor(quotient, segmentBase);
//    }
//
//    // Setting the most significant digits of the string.
//    std::string segmentString(std::to_string(remainder));
//    unsigned short numLeadingDigits = segmentString.length();
//    segmentStart -= numLeadingDigits;
//    fullNumberString.replace(segmentStart, numLeadingDigits, segmentString);
//
//    // Remove extra digits at the beginning.
//    fullNumberString.erase(0, segmentStart);
//    fullNumberString.shrink_to_fit();
    return fullNumberString;
}

void UnsignedHugeIntValue::set_value_from_string(std::string integer_string) {
    // ToDo: Change this function to remove dependence on HugeIntWord class.
    unsigned long long numDigits =  integer_string.length();
    if (numDigits == 0) {
        throw std::invalid_argument("An attempt was made to convert an empty string into an UnsignedHugeInt.");
    }

    // Segments are used that fit within one word of UnsignedHugeInt.
    const uint32_t segmentBaseValue = 1000000000;
    const int segmentLength = 9;
    unsigned long long segmentStartIndex = numDigits % segmentLength;
    std::string segmentString;
    uint32_t segmentValue;

    // The most significant digits are read first.
    if (segmentStartIndex == 0) {
        segmentValue = 0;
    }
    else {
        segmentString = integer_string.substr(0, segmentStartIndex);
        segmentValue = std::stol(segmentString);
        if (segmentValue < 0) {
            throw std::invalid_argument("An attempt was made to read a negative value as a string into an UnsignedHugeInt.");
        }
    }
    this->word_values = new std::vector<uint32_t>(1, segmentValue);
//    this->mostSigWord = this->leastSigWord = new HugeIntWord(segmentValue);
//
//    // The remaining digits of the string are read in segments.
//    for (; segmentStartIndex < numDigits; segmentStartIndex += HUGE_INT_NUMBER_OF_BASE_10_DIGITS_PER_WORD) {
//        segmentString = integer_string.substr(segmentStartIndex, HUGE_INT_NUMBER_OF_BASE_10_DIGITS_PER_WORD);
//        segmentValue = std::stol(segmentString);
//        if (segmentValue < 0) {
//            throw std::invalid_argument("A string could not be converted to an UnsignedHugeInt.");
//        }
//        *this = UnsignedHugeIntValue::multiply_single_word(*this, segmentBaseValue);
//        this->add_value_at_word(this->leastSigWord, segmentValue);
//    }
    this->remove_extra_leading_words();
}

void UnsignedHugeIntValue::delete_all_words() {
    // ToDo: Change or remove this function to remove dependence on HugeIntWord class.
//    HugeIntWord *thisWord = this->mostSigWord;
//    HugeIntWord *wordToDelete, *nextWord;
//    while (thisWord != NULL) {
//        wordToDelete = thisWord;
//        nextWord = thisWord->get_next_lower_sig_word();
//        delete(wordToDelete);
//        thisWord = nextWord;
//    }
//    this->mostSigWord = NULL;
//    this->leastSigWord = NULL;

    delete this->word_values;
}

void UnsignedHugeIntValue::remove_extra_leading_words() {
    unsigned long long highest_index = this->word_values->size();
    if (highest_index <= 1)
        return;
    --highest_index;
    while ((this->word_values->at(highest_index) == 0) && (highest_index > 0)) {
        --highest_index;
    }
    this->word_values->resize(highest_index + 1);
    this->word_values->shrink_to_fit();
}

HugeIntWord* UnsignedHugeIntValue::add_word() {
    // ToDo: Change or remove this function to remove dependence on HugeIntWord class.
    return this->add_word((unsigned long long)0);
}

HugeIntWord* UnsignedHugeIntValue::add_word(const unsigned long long value) {
    // ToDo: Change or remove this function to remove dependence on HugeIntWord class.
//    if (value > HUGE_INT_MAX_WORD_VALUE) {
//        HugeIntWord *newLesserWord, *newGreaterWord;
//        newLesserWord = new HugeIntWord((unsigned long long)0);
//        newGreaterWord = newLesserWord->add_value(value);
//        this->add_word(newLesserWord);
//        this->mostSigWord = newGreaterWord;
//        return newGreaterWord;
//    }
//    else {
//        HugeIntWord *newWord = new HugeIntWord(value);
//        this->add_word(newWord);
//        return newWord;
//    }
    return NULL; // ToDo: Delete this line. ////////////////////////////////////////////////////////////////////////////////////////////////
}

HugeIntWord* UnsignedHugeIntValue::add_word(HugeIntWord* new_word) {
    // ToDo: Change or remove this function to remove dependence on HugeIntWord class.
    if (new_word == NULL) {
        throw std::invalid_argument("A null word was added to an UnsignedHugeIntValue.");
    }
//    HugeIntWord *oldMostSigWord = this->mostSigWord;
//    new_word->set_less_significant_word(oldMostSigWord);
//    oldMostSigWord->set_more_significant_word(new_word);
//    this->mostSigWord = new_word;
    return new_word;
}

HugeIntWord* UnsignedHugeIntValue::insert_least_significant_word(unsigned long least_significant_value) {
    // ToDo: Change this function to remove dependence on HugeIntWord class.
//    if (this->mostSigWord->get_word_number() == 0 && this->mostSigWord->get_value() == 0) {
//        return this->leastSigWord->add_value(least_significant_value);
//    }
    HugeIntWord *newWord = new HugeIntWord(least_significant_value);
//    HugeIntWord *oldLeastSigWord = this->leastSigWord;
//    HugeIntWord *thisWord;
//    unsigned long long wordNumber = 2;
//    oldLeastSigWord->set_less_significant_word(newWord);
//    newWord->set_more_significant_word(oldLeastSigWord);
//    this->leastSigWord = newWord;
//    for (thisWord = oldLeastSigWord->get_next_more_sig_word(); thisWord != NULL; thisWord = thisWord->get_next_more_sig_word()) {
//        thisWord->place_value = wordNumber;
//        ++wordNumber;
//    }
    return newWord;
}

HugeIntWord* UnsignedHugeIntValue::add_value_at_word(HugeIntWord* location_to_add, const UnsignedHugeIntValue& value_to_add) {
    // ToDo: Change this function to remove dependence on HugeIntWord class.
//    HugeIntWord *thisAddLocation;
//    const HugeIntWord *thisValueWord = value_to_add.get_least_significant_word();
//    HugeIntWord *moreSigWord;
    HugeIntWord *wordToReturn;

//    if (location_to_add == NULL) {
//        thisAddLocation = this->add_word(new HugeIntWord((unsigned long)0));
//        wordToReturn = thisAddLocation;
//    }
//    else {
//        thisAddLocation = location_to_add;
//        wordToReturn = location_to_add;
//    }
//
//    while (thisValueWord != NULL) {
//        if (thisAddLocation == NULL) {
//            thisAddLocation = this->add_word(thisValueWord->get_value());
//            this->mostSigWord = thisAddLocation;
//        }
//        else {
//            moreSigWord = thisAddLocation->add_value(thisValueWord->get_value());
//            if (moreSigWord->get_next_more_sig_word() == NULL)
//                this->mostSigWord = moreSigWord;
//        }
//
//        thisValueWord = thisValueWord->get_next_more_sig_word();
//        thisAddLocation = thisAddLocation->get_next_more_sig_word();
//    }
//
//    // Set the most significant word.
//    thisAddLocation = this->mostSigWord;
//    moreSigWord = thisAddLocation->get_next_more_sig_word();
//    while (moreSigWord != NULL) {
//        thisAddLocation = moreSigWord;
//        moreSigWord = moreSigWord->get_next_more_sig_word();
//    }
//    this->mostSigWord = thisAddLocation;
//    return wordToReturn;
    return NULL; // ToDo: Delete this line. ////////////////////////////////////////////////////////////////////////////////////////////////
}

UnsignedHugeIntValue UnsignedHugeIntValue::integer_with_least_significant_word(const HugeIntWord* least_significant_word) {
    // ToDo: Change this function to remove dependence on HugeIntWord class.
//    UnsignedHugeIntValue newNumber(least_significant_word->get_value());
//    HugeIntWord *thisWord = least_significant_word->get_next_more_sig_word();
//    while (thisWord != NULL) {
//        newNumber.add_word(thisWord->get_value());
//        thisWord = thisWord->get_next_more_sig_word();
//    }
//    return newNumber;
    return UnsignedHugeIntValue(); // ToDo: Delete this line. //////////////////////////////////////////////////////////////////////////////////////////////////
}

UnsignedHugeIntValue UnsignedHugeIntValue::find_multiplication_subtotal(const HugeIntWord* greater_factor_word, const HugeIntWord* lesser_factor_word) {
    // ToDo: Change this function to remove dependence on HugeIntWord class.
    UnsignedHugeIntValue resultSubtotal((unsigned long long)0);
//    HugeIntWord *resultLeastSigWord = resultSubtotal.get_least_significant_word();
//    const HugeIntWord *thisWordA = greater_factor_word, *thisWordB = lesser_factor_word; // thisWordA is taken in descending place values.
//    HugeIntWord *newMostSigWord, *nextWord;
//    while(thisWordA != NULL && thisWordB != NULL) {
//        resultLeastSigWord->add_value((uint64_t)thisWordA->get_value() * thisWordB->get_value());
//        thisWordA = thisWordA->get_next_lower_sig_word();
//        thisWordB = thisWordB->get_next_more_sig_word();
//    }
//    // Set the most significant word of the subtotal.
//    newMostSigWord = resultSubtotal.get_most_significant_word();
//    nextWord = newMostSigWord->get_next_more_sig_word();
//    while (nextWord != NULL) {
//        newMostSigWord = nextWord;
//        nextWord = nextWord->get_next_more_sig_word();
//    }
//    resultSubtotal.mostSigWord = newMostSigWord;
    return resultSubtotal;
}

std::ostream& operator<<(std::ostream& out_stream, const UnsignedHugeIntValue& huge_int_object) {
    out_stream << huge_int_object.to_string();
    return out_stream;
}
