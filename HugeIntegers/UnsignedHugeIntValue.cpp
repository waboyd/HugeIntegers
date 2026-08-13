#include "UnsignedHugeIntValue.h"

UnsignedHugeIntValue::UnsignedHugeIntValue()
        : word_values(new std::vector<WordType>(1, 0)) {}

UnsignedHugeIntValue::UnsignedHugeIntValue(const unsigned long long value) {
    if (value <= max_word_value) {
        this->word_values = new std::vector<WordType>(1, value);
        return;
    }
    this->word_values = new std::vector<WordType>(2);
    this->word_values->at(0) = value % word_base_value;
    unsigned long long carryValue = value / word_base_value;
    this->word_values->at(1) = carryValue % word_base_value;
    for (carryValue /= word_base_value; carryValue > 0; carryValue /= word_base_value) {
        this->word_values->push_back(carryValue % word_base_value);
    }
}

UnsignedHugeIntValue::UnsignedHugeIntValue(const std::string integer_string) {
    this->set_value_from_string(integer_string);
}

UnsignedHugeIntValue::UnsignedHugeIntValue(const char* integer_string) {
    std::string cppString(integer_string);
    this->set_value_from_string(cppString);
}

UnsignedHugeIntValue::UnsignedHugeIntValue(const UnsignedHugeIntValue& orig)
        : word_values(new std::vector<WordType>(*orig.word_values)) {}

UnsignedHugeIntValue::UnsignedHugeIntValue(const UnsignedHugeIntValue* orig)
        : word_values(new std::vector<WordType>(*orig->word_values)) {}

UnsignedHugeIntValue::UnsignedHugeIntValue(UnsignedHugeIntValue&& orig) noexcept
        : word_values(orig.word_values) {
    orig.word_values = NULL;
}

UnsignedHugeIntValue::UnsignedHugeIntValue(std::vector<WordType>* word_values_vector)
        : word_values(word_values_vector) {}

UnsignedHugeIntValue::~UnsignedHugeIntValue() {
    delete this->word_values;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator=(const UnsignedHugeIntValue& orig) {
    if (this == &orig)
        return *this;
    delete this->word_values;
    this->word_values = new std::vector<WordType>(*orig.word_values);
    return *this;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator=(const UnsignedHugeIntValue* orig) {
    if (this == orig)
        return *this;
    delete this->word_values;
    this->word_values = new std::vector<WordType>(*orig->word_values);
    return *this;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator=(UnsignedHugeIntValue&& orig) noexcept {
    if (this == &orig)
        return *this;
    delete this->word_values;
    this->word_values = orig.word_values;
    orig.word_values = NULL;
    return *this;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator=(const unsigned long long value) {
    delete this->word_values;
    if (value <= max_word_value) {
        this->word_values = new std::vector<WordType>(1, value);
        return *this;
    }
    this->word_values = new std::vector<WordType>(2);
    this->word_values->at(0) = value % word_base_value;
    unsigned long long carryValue = value / word_base_value;
    this->word_values->at(1) = carryValue % word_base_value;
    for (carryValue /= word_base_value; carryValue > 0; carryValue /= word_base_value) {
        this->word_values->push_back(carryValue % word_base_value);
    }
    return *this;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator=(const std::string value_string) {
    delete this->word_values;
    this->set_value_from_string(value_string);
    return *this;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator=(const char* value_string) {
    delete this->word_values;
    std::string cppStringValue(value_string);
    this->set_value_from_string(cppStringValue);
    return *this;
}

UnsignedHugeIntValue UnsignedHugeIntValue::number_of_digits() const {
    if ((this->word_values->size() == 1) && (this->word_values->front() == 0)) {
        return UnsignedHugeIntValue(1);
    }
    UnsignedHugeIntValue totalNumDigits(1);
    UnsignedHugeIntValue quotient(this);

    // The value can be repeatedly divided by a power of 10 to find the number of digits.
    constexpr WordType divisor = 1000000000;
    constexpr unsigned long long digits_per_division = 9;
    while ((quotient.word_values->size() > 1) || (quotient.word_values->front()) > divisor) {
        totalNumDigits += digits_per_division;
        quotient.divide_single_word_divisor_transform(divisor);
    }

    while (quotient.word_values->front() >= 10) {
        ++totalNumDigits;
        quotient.divide_single_word_divisor_transform(10);
    }
    return totalNumDigits;
}

UnsignedHugeIntValue::operator std::string() const {
    return this->to_string();
}

short UnsignedHugeIntValue::compare(const UnsignedHugeIntValue& numberA, const UnsignedHugeIntValue& numberB) {
    unsigned long long numWordsA = numberA.num_words();
    unsigned long long numWordsB = numberB.num_words();
    if (numWordsA > numWordsB)
        return 1;
    else if (numWordsA < numWordsB)
        return -1;

    // The corresponding word values are compared in order, starting with the most significant words.
    std::vector<WordType>::const_reverse_iterator wordIterA = numberA.word_values->crbegin();
    std::vector<WordType>::const_reverse_iterator wordIterB = numberB.word_values->crbegin();
    for (unsigned long long wordPrevIndex = numWordsA; wordPrevIndex > 0; --wordPrevIndex) {
        if (*wordIterA > *wordIterB) {
            return 1;
        } else if (*wordIterA < *wordIterB) {
            return -1;
        }
        ++wordIterA;
        ++wordIterB;
    }

    return 0;   // The numbers are equal.
}

UnsignedHugeIntValue UnsignedHugeIntValue::sum_of(const UnsignedHugeIntValue& addendA, const UnsignedHugeIntValue& addendB) {
    unsigned long long lesserNumWords, greaterNumWords, wordIndex;
    std::vector<WordType>::const_iterator lesserAddendIter, greaterAddendIter;
    std::vector<WordType>::iterator sumIter;

    uint64_t thisWordSum = 0;

    greaterNumWords = addendA.num_words();
    lesserNumWords = addendB.num_words();
    if (lesserNumWords > greaterNumWords) {
        // addendB has more words. The number of words needs to be swapped.
        wordIndex = lesserNumWords;
        lesserNumWords = greaterNumWords;
        greaterNumWords = wordIndex;
        lesserAddendIter = addendA.word_values->cbegin();
        greaterAddendIter = addendB.word_values->cbegin();
    } else {
        // addendB does not have more words than addendA.
        lesserAddendIter = addendB.word_values->cbegin();
        greaterAddendIter = addendA.word_values->cbegin();
    }

    auto *sumWords = new std::vector<WordType>(greaterNumWords + 1);
    sumIter = sumWords->begin();

    // While both addends have words, those words are added together.
    for (wordIndex = 0; wordIndex < lesserNumWords; ++wordIndex) {
        thisWordSum = thisWordSum + *lesserAddendIter + *greaterAddendIter;
        *sumIter = (WordType)(thisWordSum % word_base_value);
        thisWordSum /= word_base_value;
        ++lesserAddendIter;
        ++greaterAddendIter;
        ++sumIter;
    }

    // The words of the greater addend are added to the sum, along with carry values.
    for (; wordIndex < greaterNumWords; ++wordIndex) {
        thisWordSum += *greaterAddendIter;
        *sumIter = (WordType)(thisWordSum % word_base_value);
        thisWordSum /= word_base_value;
        ++greaterAddendIter;
        ++sumIter;
    }

    // If there is still a carry value, it becomes the most significant sum word.
    if (thisWordSum > 0) {
        *sumIter = (WordType)thisWordSum;
    } else {
        sumWords->pop_back();
    }
    return UnsignedHugeIntValue(sumWords);
}


UnsignedHugeIntValue UnsignedHugeIntValue::sum_of(const UnsignedHugeIntValue& addendA, unsigned long long addendB) {
    uint64_t wordSum;
    unsigned long long numAddendWords = addendA.word_values->size();
    unsigned long long wordIndex;
    std::vector<WordType>::const_iterator addendIter = addendA.word_values->cbegin();

    auto *sumWords = new std::vector<WordType>(numAddendWords + 1);
    std::vector<WordType>::iterator sumIter = sumWords->begin();

    // Overflow must be avoided when finding the first word of the sum.
    wordSum = (addendB % word_base_value) + *addendIter;
    *sumIter = (WordType)(wordSum % word_base_value);
    wordSum = (wordSum / word_base_value) + (addendB / word_base_value);
    ++addendIter;
    ++sumIter;

    // While there is a carry value, add it to the next word.
    for (wordIndex = 1; (wordSum > 0) && (wordIndex < numAddendWords); ++wordIndex) {
        wordSum += *addendIter;
        *sumIter = (WordType)(wordSum % word_base_value);
        wordSum /= word_base_value;
        ++addendIter;
        ++sumIter;
    }

    // If the carry value is used up, and there are still more addend words, copy the addend words to the sum.
    for (; wordIndex < numAddendWords; ++wordIndex) {
        *sumIter = *addendIter;
        ++addendIter;
        ++sumIter;
    }

    // After all the addend words have been added, the carry value must be considered.
    if (wordSum > 0) {
        *sumIter = (WordType)(wordSum % word_base_value);
        wordSum /= word_base_value;
    } else {
        sumWords->pop_back();
        return UnsignedHugeIntValue(sumWords);
    }

    // If there is somehow still a carry value, more words must be added to the sum.
    while (wordSum > 0) {
        sumWords->push_back((WordType)(wordSum % word_base_value));
        wordSum /= word_base_value;
    }
    return UnsignedHugeIntValue(sumWords);
}

UnsignedHugeIntValue UnsignedHugeIntValue::subtract(const UnsignedHugeIntValue& minuend, const UnsignedHugeIntValue& subtrahend) {
    if (UnsignedHugeIntValue::compare(minuend, subtrahend) < 0) {
        throw std::range_error("The subtrahend of an unsigned subtraction operation was greater than the minuend.");
    }

    uint64_t minuendWordValue, subtrahendWordValue, carryValue = 0;
    const unsigned long long numMinuendWords = minuend.num_words();
    const unsigned long long numSubtrahendWords = subtrahend.num_words();
    std::vector<WordType>::const_iterator minuendWordIter = minuend.word_values->cbegin();
    std::vector<WordType>::const_iterator subtrahendWordIter = subtrahend.word_values->cbegin();

    // Words are created for a result that has the same number of words as the minuend.
    auto *differenceWords = new std::vector<WordType>(numMinuendWords);
    std::vector<WordType>::iterator differenceWordIter = differenceWords->begin();

    // Subtract all the words of the subtrahend.
    unsigned long long wordIndex;
    for (wordIndex = 0; wordIndex < numSubtrahendWords; ++wordIndex) {
        minuendWordValue = *minuendWordIter;
        subtrahendWordValue = *subtrahendWordIter + carryValue;
        if (minuendWordValue < subtrahendWordValue) {
            // Some of the value must be carried over from the next place value.
            *differenceWordIter = (WordType)(word_base_value + minuendWordValue - subtrahendWordValue);
            carryValue = 1;
        } else {
            *differenceWordIter = (WordType)(minuendWordValue - subtrahendWordValue);
            carryValue = 0;
        }
        ++minuendWordIter;
        ++subtrahendWordIter;
        ++differenceWordIter;
    }

    // Continue carry operations until no values need to be carried over.
    for (; carryValue > 0; ++wordIndex) {
        minuendWordValue = *minuendWordIter;
        if (minuendWordValue < carryValue) {
            // This can only happen if the carry value is 1 and the minuend word value is 0.
            *differenceWordIter = max_word_value;
            carryValue = 1;
        } else {
            *differenceWordIter = (WordType)(minuendWordValue - carryValue);
            carryValue = 0;
        }
        ++minuendWordIter;
        ++differenceWordIter;
    }

    // After carry operations are finished, copy the minuend words to the difference.
    for (; wordIndex < numMinuendWords; ++wordIndex) {
        *differenceWordIter = *minuendWordIter;
        ++minuendWordIter;
        ++differenceWordIter;
    }
    UnsignedHugeIntValue::remove_extra_leading_words_from(differenceWords);
    return UnsignedHugeIntValue(differenceWords);
}

UnsignedHugeIntValue UnsignedHugeIntValue::multiply(const UnsignedHugeIntValue& factorA, const UnsignedHugeIntValue& factorB) {
    if (factorA.num_words() == 1) {
        return UnsignedHugeIntValue::multiply_single_word(factorB, factorA.word_values->front());
    }
    if (factorB.num_words() == 1) {
        return UnsignedHugeIntValue::multiply_single_word(factorA, factorB.word_values->front());
    }
    return UnsignedHugeIntValue::multiply_many_words(factorA, factorB);
}

UnsignedHugeIntValue UnsignedHugeIntValue::multiply_by_int(const unsigned long long factor) const {
    // If factor is small enough to fit in one word of an UnsignedHugeIntValue object, use the faster multiplication function.
    if (factor < word_base_value)
        return UnsignedHugeIntValue::multiply_single_word(*this, factor);
    UnsignedHugeIntValue factorObject(factor);
    return UnsignedHugeIntValue::multiply_many_words(*this, factorObject);
}

UnsignedHugeIntValue UnsignedHugeIntValue::multiply_single_word(const UnsignedHugeIntValue& large_factor, WordType small_factor) {
    if (small_factor == 0) {
        // A result of 0 is returned if a factor is 0.
        return UnsignedHugeIntValue();
    }

    const unsigned long long numFactorWords = large_factor.num_words();
    auto *productWords = new std::vector<WordType>(numFactorWords + 1);
    std::vector<WordType>::const_iterator factorIter = large_factor.word_values->cbegin();
    std::vector<WordType>::iterator productIter = productWords->begin();

    uint64_t productWordValue = 0;
    const uint64_t smallFactorCast = (uint64_t)small_factor; // Used to reduce the number of necessary type casts.

    // All large_factor words are multiplied by the small_factor to get the product.
    for (unsigned long long wordIndex = 0; wordIndex < numFactorWords; ++wordIndex) {
        productWordValue += smallFactorCast * *factorIter;
        *productIter = (WordType)(productWordValue % word_base_value);
        productWordValue /= word_base_value;
        ++factorIter;
        ++productIter;
    }

    // Set the most significant word of the product from the carry value.
    if (productWordValue > 0) {
        *productIter = (WordType)productWordValue;
    } else {
        // If there is no carry value, the product should not have an extra word.
        productWords->pop_back();
    }
    return UnsignedHugeIntValue(productWords);
}

UnsignedHugeIntValue& UnsignedHugeIntValue::multiply_single_word_transform(WordType small_factor) {
    if (small_factor == 0) {
        this->word_values->resize(1);
        this->word_values->at(0) = 0;
        this->word_values->shrink_to_fit();
        return *this;
    }

    unsigned long long numOrigWords = this->word_values->size();
    std::vector<WordType>::iterator wordIter = this->word_values->begin();
    uint64_t productWordValue = 0;
    const uint64_t smallFactorCast = (uint64_t)small_factor; // Used to reduce the number of necessary type casts

    // All large_factor words are multiplied by the small_factor to get the product.
    for (unsigned long long wordIndex = 0; wordIndex < numOrigWords; ++wordIndex) {
        productWordValue += smallFactorCast * *wordIter;
        *wordIter = (WordType)(productWordValue % word_base_value);
        productWordValue /= word_base_value;
        ++wordIter;
    }

    // Set the most significant word of the product from the carry value.
    if (productWordValue > 0) {
        this->word_values->push_back((WordType)productWordValue);
    }
    return *this;
}

UnsignedHugeIntValue UnsignedHugeIntValue::multiply_many_words(const UnsignedHugeIntValue& factorA, const UnsignedHugeIntValue& factorB) {
    // ToDo: Possibly apply multithreading to this method.
    const unsigned long long numWordsA = factorA.num_words();
    const unsigned long long numWordsB = factorB.num_words();
    auto *productWords = new std::vector<WordType>(numWordsA + numWordsB, 0);
    UnsignedHugeIntValue resultProduct(productWords);

    // The subtotals are found by multiplying all pairs of words of the factors whose indexes
    // have the same sum as the product word index.
    std::vector<WordType>::const_reverse_iterator factorAIter = factorA.word_values->crend();
    std::vector<WordType>::const_iterator factorBIter = factorB.word_values->cbegin();
    std::vector<WordType>::iterator productIter = productWords->begin();
    unsigned long long numSubtotalProducts = 1; // Number of pairs of words that multiplied to get the subtotal.
    for (unsigned long long factorALength = 1; factorALength <= numWordsA; ++factorALength) {
        --factorAIter;
        if (factorALength <= numWordsB) {
            numSubtotalProducts = factorALength;
        }
        UnsignedHugeIntValue::insert_multiplication_subtotal(factorAIter, factorBIter, productIter, numSubtotalProducts);
        ++productIter;
    }
    for (unsigned long long factorBLength = numWordsB - 1; factorBLength > 0; --factorBLength) {
        ++factorBIter;
        if (factorBLength < numSubtotalProducts) {
            numSubtotalProducts = factorBLength;
        }
        UnsignedHugeIntValue::insert_multiplication_subtotal(factorAIter, factorBIter, productIter, numSubtotalProducts);
        ++productIter;
    }
    // Remove leading 0 words.
    UnsignedHugeIntValue::remove_extra_leading_words_from(productWords);
    return resultProduct;
}

std::pair<UnsignedHugeIntValue, UnsignedHugeIntValue> UnsignedHugeIntValue::divide(
        const UnsignedHugeIntValue& dividend, const UnsignedHugeIntValue& divisor) {
    std::pair<UnsignedHugeIntValue, UnsignedHugeIntValue> divisionResults;
    if (divisor.num_words() == 1) {
        auto quickDivisionResults = UnsignedHugeIntValue::divide_single_word_divisor(dividend, divisor.word_values->front());
        return std::pair(std::move(quickDivisionResults.first), UnsignedHugeIntValue(quickDivisionResults.second));
    }
    return UnsignedHugeIntValue::divide_many_word_divisor(dividend, divisor);
}

std::pair<UnsignedHugeIntValue, UnsignedHugeIntValue::WordType> UnsignedHugeIntValue::divide_single_word_divisor(
        const UnsignedHugeIntValue& dividend, WordType divisor) {
    if (divisor == 0) {
        throw std::invalid_argument("An attempt was made to divide by zero.");
    }
    std::vector<WordType> *quotientWords;
    const unsigned long long numDividendWords = dividend.word_values->size();
    uint64_t subRemainder;
    if (numDividendWords == 1) {
        subRemainder = dividend.word_values->at(0);
        return std::pair(UnsignedHugeIntValue(subRemainder / divisor), (WordType)(subRemainder % divisor));
    }

    std::vector<WordType>::const_reverse_iterator dividendIter = dividend.word_values->crbegin();
    std::vector<WordType>::reverse_iterator quotientIter;
    subRemainder = *dividendIter;

    // The number of quotient words depends on whether the most significant word value of the dividend
    // is as large as the divisor.
    if (subRemainder >= divisor) {
        quotientWords = new std::vector<WordType>(numDividendWords);
        quotientIter = quotientWords->rbegin();
        *quotientIter = subRemainder / divisor;
        subRemainder %= divisor;
        ++quotientIter;
    } else {
        quotientWords = new std::vector<WordType>(numDividendWords - 1);
        quotientIter = quotientWords->rbegin();
    }
    ++dividendIter;

    // The quotient word is found for each corresponding dividend word.
    for (unsigned long long wordPrevIndex = numDividendWords - 1; wordPrevIndex > 0; --wordPrevIndex) {
        subRemainder *= word_base_value;
        subRemainder += *dividendIter;
        *quotientIter = (WordType)(subRemainder / divisor);
        subRemainder %= divisor;
        ++dividendIter;
        ++quotientIter;
    }
    return std::pair(UnsignedHugeIntValue(quotientWords), (WordType)subRemainder);
}

UnsignedHugeIntValue::WordType UnsignedHugeIntValue::divide_single_word_divisor_transform(WordType divisor) {
    if (divisor == 0) {
        throw std::invalid_argument("An attempt was made to divide by zero.");
    }
    const unsigned long long numWords = this->word_values->size();
    std::vector<WordType>::reverse_iterator wordIter = this->word_values->rbegin();
    uint64_t subRemainder = *wordIter;
    if (numWords == 1) {
        *wordIter = subRemainder / divisor;
        return subRemainder % divisor;
    }

    // The number of quotient words depends on whether the most significant word value of the dividend
    // is as large as the divisor.
    bool isWordToRemove;
    if (subRemainder >= divisor) {
        isWordToRemove = false;
        *wordIter = subRemainder / divisor;
        subRemainder %= divisor;
    } else {
        isWordToRemove = true;
    }
    ++wordIter;

    // The quotient word is found for each corresponding dividend word.
    for (unsigned long long wordPrevIndex = numWords - 1; wordPrevIndex > 0; --wordPrevIndex) {
        subRemainder *= word_base_value;
        subRemainder += *wordIter;
        *wordIter = (WordType)(subRemainder / divisor);
        subRemainder %= divisor;
        ++wordIter;
    }
    if (isWordToRemove) {
        this->word_values->pop_back();
    }
    return (WordType)subRemainder;
}

std::pair<UnsignedHugeIntValue, UnsignedHugeIntValue> UnsignedHugeIntValue::divide_many_word_divisor(const UnsignedHugeIntValue& dividend, const UnsignedHugeIntValue& divisor) {
    if (compare(dividend, divisor) < 0) {
        return std::pair(UnsignedHugeIntValue(), UnsignedHugeIntValue(dividend));
    }
    std::vector<WordType> *divisorWords = divisor.word_values;
    unsigned long long numDividendWords = dividend.num_words();
    unsigned long long numDivisorWords = divisorWords->size();

    auto *quotientWords = new std::vector<WordType>(numDividendWords - numDivisorWords + 1);
    std::vector<WordType>::const_reverse_iterator divisorIter = divisorWords->crbegin();
    std::vector<WordType>::reverse_iterator quotientIter = quotientWords->rbegin();
    // The remainder is interpreted and altered as portions of the dividend. This avoids insertions into the vector.
    auto *remainderWords = new std::vector<WordType>(*dividend.word_values);
    std::vector<WordType>::reverse_iterator remainderLeftIter = remainderWords->rbegin();
    std::vector<WordType>::iterator remainderRightIter = remainderWords->begin() + (numDividendWords - numDivisorWords);
    // The integers are too large to divide in one step, so lower estimates for the quotient are
    // found and increased until the quotient is exactly correct.
    double dividendLowerEstimate, divisorUpperEstimate;
    WordType quotientWordEstimate;

    // The most significant word of the quotient is found separately.
    // A lower estimate of the quotient word is found by dividing a lower estimate of the
    // dividend by an upper estimate of the divisor.
    divisorUpperEstimate = *divisorIter + (((double)(*(divisorIter + 1)) + 1) / word_base_value);
    dividendLowerEstimate = *remainderLeftIter + ((double)(*(remainderLeftIter + 1)) / word_base_value);
    quotientWordEstimate = (WordType)(dividendLowerEstimate / divisorUpperEstimate);
    // The product of the divisor and the quotient word is subtracted from the remainder segment.
    UnsignedHugeIntValue subProduct = UnsignedHugeIntValue::multiply_single_word(divisor, quotientWordEstimate);
    UnsignedHugeIntValue::subtract_from_remainder(remainderRightIter, subProduct);
    // The quotient word is incremented until it is the exact correct value.
    while (UnsignedHugeIntValue::is_remainder_too_large(remainderLeftIter, divisorWords)) {
        ++quotientWordEstimate;
        UnsignedHugeIntValue::subtract_from_remainder(remainderRightIter, divisor);
    }
    // The value found for the quotient word is set in the results.
    if (quotientWordEstimate > 0) {
        quotientIter = quotientWords->rbegin();
        *quotientIter = quotientWordEstimate;
        ++quotientIter;
    } else {
        quotientWords->pop_back();
        quotientIter = quotientWords->rbegin();
    }

    // The remaining quotient word values are found.
    for (unsigned long long numWordsRemaining = numDividendWords - numDivisorWords; numWordsRemaining > 0; --numWordsRemaining) {
        // The next dividend word is appended to the remainder segment.
        --remainderRightIter;
        // A lower estimate of the quotient word is found by dividing a lower estimate of the
        // dividend by an upper estimate of the divisor.
        dividendLowerEstimate = (word_base_value * (double)(*remainderLeftIter))
                                + *(remainderLeftIter + 1)
                                + ((double)(*(remainderLeftIter + 2)) / word_base_value);
        quotientWordEstimate = (WordType)(dividendLowerEstimate / divisorUpperEstimate);
        // The product of the divisor and the quotient word is subtracted from the remainder segment.
        subProduct = UnsignedHugeIntValue::multiply_single_word(divisor, quotientWordEstimate);
        UnsignedHugeIntValue::subtract_from_remainder(remainderRightIter, subProduct);

        // The correct quotient value should cause the leftmost word of the remainder to be 0.
        while (*remainderLeftIter > 0) {
            ++quotientWordEstimate;
            UnsignedHugeIntValue::subtract_from_remainder(remainderRightIter, divisor);
        }
        ++remainderLeftIter;
        // The quotient word is incremented until the remainder is less than the divisor.
        while (UnsignedHugeIntValue::is_remainder_too_large(remainderLeftIter, divisorWords)) {
            ++quotientWordEstimate;
            UnsignedHugeIntValue::subtract_from_remainder(remainderRightIter, divisor);
        }
        // The value found for the quotient word is set in the results.
        *quotientIter = quotientWordEstimate;
        ++quotientIter;
    }
    // The leftmost words with a value of 0 must be removed from the remainder.
    UnsignedHugeIntValue::remove_extra_leading_words_from(remainderWords);
    return std::pair(UnsignedHugeIntValue(quotientWords), UnsignedHugeIntValue(remainderWords));
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator+=(const UnsignedHugeIntValue& addend) {
    this->add_value_at_word(this->word_values->begin(), addend);
    return *this;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator+=(const unsigned long long addend) {
    this->add_value_at_word(this->word_values->begin(), addend);
    return *this;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator-=(const UnsignedHugeIntValue& subtrahend) {
    if (UnsignedHugeIntValue::compare(*this, subtrahend) < 0) {
        throw std::range_error("The subtrahend of an unsigned compound subtraction operation was greater than the minuend.");
    }

    uint64_t minuendWordValue, subtrahendWordValue, carryValue = 0;
    const unsigned long long numSubtrahendWords = subtrahend.num_words();
    std::vector<WordType>::iterator thisWordIter = this->word_values->begin();
    std::vector<WordType>::const_iterator subtrahendWordIter = subtrahend.word_values->cbegin();

    // Subtract all the words of the subtrahend.
    unsigned long long wordIndex;
    for (wordIndex = 0; wordIndex < numSubtrahendWords; ++wordIndex) {
        minuendWordValue = *thisWordIter;
        subtrahendWordValue = *subtrahendWordIter + carryValue;
        if (minuendWordValue < subtrahendWordValue) {
            // Some of the value must be carried over from the next place value.
            *thisWordIter = (WordType)(word_base_value + minuendWordValue - subtrahendWordValue);
            carryValue = 1;
        } else {
            *thisWordIter = (WordType)(minuendWordValue - subtrahendWordValue);
            carryValue = 0;
        }
        ++thisWordIter;
        ++subtrahendWordIter;
    }

    // Continue carry operations until no values need to be carried over.
    for (; carryValue > 0; ++wordIndex) {
        minuendWordValue = *thisWordIter;
        if (minuendWordValue < carryValue) {
            // This can only happen if the carry value is 1 and the minuend word value is 0.
            *thisWordIter = max_word_value;
            carryValue = 1;
        } else {
            *thisWordIter = (WordType)(minuendWordValue - carryValue);
            carryValue = 0;
        }
        ++thisWordIter;
    }

    this->remove_extra_leading_words();
    return *this;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator-=(const unsigned long long subtrahend) {
    return *this -= UnsignedHugeIntValue(subtrahend);
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator*=(const UnsignedHugeIntValue& factor) {
    // If factor is small enough to fit in one word of an UnsignedHugeIntValue object, use the faster multiplication function.
    if (factor.num_words() == 1) {
        return this->multiply_single_word_transform((WordType)factor.word_values->front());
    }
    if (this->num_words() == 1) {
        *this = multiply_single_word(factor, this->word_values->front());
        return *this;
    }
    *this = UnsignedHugeIntValue::multiply_many_words(*this, factor);
    return *this;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator*=(const unsigned long long factor) {
    // If factor is small enough to fit in one word of an UnsignedHugeIntValue object, use the faster multiplication function.
    if (factor < word_base_value) {
        return this->multiply_single_word_transform((WordType)factor);
    }
    *this = UnsignedHugeIntValue::multiply(*this, UnsignedHugeIntValue(factor));
    return *this;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator/=(const UnsignedHugeIntValue& divisor) {
    if (divisor.num_words() == 1) {
        this->divide_single_word_divisor_transform(divisor.word_values->front());
        return *this;
    }
    *this = std::move(UnsignedHugeIntValue::divide_many_word_divisor(*this, divisor).first);
    return *this;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator/=(const unsigned long long divisor) {
    if (divisor <= max_word_value) {
        this->divide_single_word_divisor_transform((WordType)divisor);
        return *this;
    }
    *this = std::move(UnsignedHugeIntValue::divide_many_word_divisor(*this, UnsignedHugeIntValue(divisor)).first);
    return *this;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator%=(const UnsignedHugeIntValue& divisor) {
    if (divisor.num_words() == 1) {
        WordType remainder = this->divide_single_word_divisor_transform(divisor.word_values->front());
        this->word_values->resize(1);
        this->word_values->front() = remainder;
        this->word_values->shrink_to_fit();
        return *this;
    }
    *this = std::move(UnsignedHugeIntValue::divide_many_word_divisor(*this, divisor).second);
    return *this;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator%=(const unsigned long long divisor) {
    if (divisor <= max_word_value) {
        WordType remainder = this->divide_single_word_divisor_transform((WordType)divisor);
        this->word_values->resize(1);
        this->word_values->front() = remainder;
        this->word_values->shrink_to_fit();
        return *this;
    }
    *this = std::move(UnsignedHugeIntValue::divide_many_word_divisor(*this, UnsignedHugeIntValue(divisor)).second);
    return *this;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator++() {
    std::vector<WordType>::iterator wordIter = this->word_values->begin();
    const std::vector<WordType>::iterator endWord = this->word_values->end();
    while (wordIter != endWord) {
        if (*wordIter < max_word_value) {
            ++(*wordIter);
            return *this;
        }
        // If the word value is the maximum word value, the next word must be incremented.
        *wordIter = 0;
        ++wordIter;
    }
    // If all the words had the maximum word value, a word must be added.
    this->word_values->push_back(1);
    return *this;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator--() {
    std::vector<WordType> *thisWordValues = this->word_values;
    if ((thisWordValues->size() <= 1) && (thisWordValues->front() == 0)) {
        throw std::range_error("An unsigned integer equal to 0 was decremented.");
    }
    std::vector<WordType>::iterator wordIter = thisWordValues->begin();
    while (*wordIter == 0) {
        *wordIter = max_word_value;
        ++wordIter;
    }
    --(*wordIter);

    // If a word was decremented to 0, check whether leading 0 words must be removed.
    if (*wordIter == 0) {
        this->remove_extra_leading_words();
    }
    return *this;
}

UnsignedHugeIntValue UnsignedHugeIntValue::operator&(const UnsignedHugeIntValue& operand) const {
    // For a bitwise AND operation, the operation only needs to be performed
    // while both operands have nonzero values.
    unsigned long long lesserNumWords, wordIndex;
    std::vector<WordType>::const_iterator thisIter = this->word_values->cbegin();
    std::vector<WordType>::const_iterator argIter = operand.word_values->cbegin();
    lesserNumWords = operand.num_words();
    wordIndex = this->num_words();
    if (wordIndex < lesserNumWords) {
        lesserNumWords = wordIndex;
    }

    // The words of the resulting value are found by doing AND operations to
    // the corresponding operand values.
    auto *resultWords = new std::vector<WordType>(lesserNumWords);
    std::vector<WordType>::iterator resultIter = resultWords->begin();
    for (wordIndex = 0; wordIndex < lesserNumWords; ++wordIndex) {
        *resultIter = *thisIter & *argIter;
        ++thisIter;
        ++argIter;
        ++resultIter;
    }
    UnsignedHugeIntValue::remove_extra_leading_words_from(resultWords);
    return UnsignedHugeIntValue(resultWords);
}

UnsignedHugeIntValue UnsignedHugeIntValue::operator&(unsigned long long operand) const {
    const unsigned long long thisNumWords = this->word_values->size();
    std::vector<WordType>::const_iterator thisIter = this->word_values->cbegin();

    if ((operand <= max_word_value) || (thisNumWords == 1)) {
        return UnsignedHugeIntValue(new std::vector<WordType>(1,
                (WordType)(*thisIter & operand)));
    }

    // The operand and result should normally not need more than 2 words.
    auto *resultWords = new std::vector<WordType>(2);
    std::vector<WordType>::iterator resultIter = resultWords->begin();
    // First (rightmost) result word.
    *resultIter = (WordType)(*thisIter & (operand % word_base_value));
    operand /= word_base_value;
    ++thisIter;
    ++resultIter;
    // Second result word.
    *resultIter = (WordType)(*thisIter & (operand % word_base_value));
    operand /= word_base_value;

    // Find additional word result word values, if there are any.
    for (unsigned long long wordIndex = 2; (operand > 0) && (wordIndex < thisNumWords); ++wordIndex) {
        ++thisIter;
        resultWords->push_back((WordType)(*thisIter & (operand % word_base_value)));
        operand /= word_base_value;
    }
    UnsignedHugeIntValue::remove_extra_leading_words_from(resultWords);
    return UnsignedHugeIntValue(resultWords);
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator&=(const UnsignedHugeIntValue& operand) {
    unsigned long long lesserNumWords, wordIndex;
    std::vector<WordType>::iterator thisIter = this->word_values->begin();
    std::vector<WordType>::const_iterator argIter = operand.word_values->cbegin();
    lesserNumWords = operand.num_words();
    wordIndex = this->num_words();
    if (wordIndex < lesserNumWords) {
        lesserNumWords = wordIndex;
    }

    // The words of the resulting value are found by doing AND operations to
    // the corresponding operand values.
    for (wordIndex = 0; wordIndex < lesserNumWords; ++wordIndex) {
        *thisIter &= *argIter;
        ++thisIter;
        ++argIter;
    }

    // Excess words in the result must be deleted.
    this->word_values->resize(lesserNumWords);
    this->remove_extra_leading_words();
    return *this;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator&=(unsigned long long operand) {
    const unsigned long long thisNumWords = this->word_values->size();
    std::vector<WordType>::iterator thisIter = this->word_values->begin();

    // First (rightmost) result word.
    *thisIter &= (operand % word_base_value);
    operand /= word_base_value;

    // If the operand takes more than one word, other result words must be found.
    unsigned long long wordIndex;
    for (wordIndex = 1; (operand > 0) && (wordIndex < thisNumWords); ++wordIndex) {
        ++thisIter;
        *thisIter &= (operand % word_base_value);
        operand /= word_base_value;
    }

    // Excess words in the result must be deleted.
    this->word_values->resize(wordIndex);
    this->remove_extra_leading_words();
    return *this;
}

UnsignedHugeIntValue UnsignedHugeIntValue::operator|(const UnsignedHugeIntValue& operand) const {
    // The operands are differentiated based on their numbers of words.
    unsigned long long lesserNumWords, greaterNumWords, wordIndex;
    std::vector<WordType>::const_iterator lesserOperandIter, greaterOperandIter;
    lesserNumWords = operand.num_words();
    greaterNumWords = this->num_words();
    if (lesserNumWords > greaterNumWords) {
        // The operand argument has more words than this object.
        wordIndex = lesserNumWords;
        lesserNumWords = greaterNumWords;
        greaterNumWords = wordIndex;
        lesserOperandIter = this->word_values->begin();
        greaterOperandIter = operand.word_values->begin();
    } else {
        // The operand argument does not have more words than this object.
        lesserOperandIter = operand.word_values->begin();
        greaterOperandIter = this->word_values->begin();
    }

    // The result will have the same number of bits as the greater operand.
    auto *resultWords = new std::vector<WordType>(greaterNumWords);
    std::vector<WordType>::iterator resultIter = resultWords->begin();

    // The words of the resulting value are found by doing OR operations to
    // the corresponding operand values.
    for (wordIndex = 0; wordIndex < lesserNumWords; ++wordIndex) {
        *resultIter = *lesserOperandIter | *greaterOperandIter;
        ++lesserOperandIter;
        ++greaterOperandIter;
        ++resultIter;
    }
    // When one operand runs out of words, copy the word values from the other operand.
    for (; wordIndex < greaterNumWords; ++wordIndex) {
        *resultIter = *greaterOperandIter;
        ++greaterOperandIter;
        ++resultIter;
    }
    return UnsignedHugeIntValue(resultWords);
}

UnsignedHugeIntValue UnsignedHugeIntValue::operator|(unsigned long long operand) const {
    const unsigned long long thisNumWords = this->word_values->size();
    // First, the result words are copied from this object's words.
    auto *resultWords = new std::vector<WordType>(*this->word_values);
    std::vector<WordType>::iterator resultIter = resultWords->begin();

    // The result values are adjusted using OR operations with the argument.
    for (unsigned long long wordIndex = 0; (operand > 0) && (wordIndex < thisNumWords); ++wordIndex) {
        *resultIter |= (operand % word_base_value);
        operand /= word_base_value;
        ++resultIter;
    }
    // If the operand needs more words than this object, those words must be
    // appended to the result.
    while (operand > 0) {
        resultWords->push_back((WordType)(operand % word_base_value));
        operand /= word_base_value;
    }
    return UnsignedHugeIntValue(resultWords);
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator|=(const UnsignedHugeIntValue& operand) {
    const unsigned long long thisNumWords = this->num_words();
    unsigned long long operandNumWords, lesserNumWords, wordIndex;
    std::vector<WordType>::iterator thisIter = this->word_values->begin();
    std::vector<WordType>::iterator argIter = operand.word_values->begin();
    operandNumWords = operand.num_words();
    if (operandNumWords < thisNumWords) {
        lesserNumWords = operandNumWords;
    } else {
        lesserNumWords = thisNumWords;
    }

    // The words of the resulting value are found by doing OR operations to
    // the corresponding operand values.
    for (wordIndex = 0; wordIndex < lesserNumWords; ++wordIndex) {
        *thisIter |= *argIter;
        ++thisIter;
        ++argIter;
    }
    // If the operand argument has more words, those words must be appended
    // to the result.
    if (operandNumWords > thisNumWords) {
        this->word_values->insert(thisIter, argIter, operand.word_values->end());
    }
    // If this object has more words than the argument, those words are
    // already set in the result.
    return *this;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator|=(unsigned long long operand) {
    const unsigned long long thisNumWords = this->num_words();
    std::vector<WordType>::iterator thisIter = this->word_values->begin();

    // The operand is split into word-sized segments for OR operations.
    for (unsigned long long wordIndex = 0; (operand > 0) && (wordIndex < thisNumWords); ++wordIndex) {
        *thisIter |= (operand % word_base_value);
        operand /= word_base_value;
        ++thisIter;
    }
    // If the operand argument still has remaining bits, those must be
    // appended to the result.
    while (operand > 0) {
        this->word_values->push_back((WordType)(operand % word_base_value));
        operand /= word_base_value;
    }
    return *this;
}

UnsignedHugeIntValue UnsignedHugeIntValue::operator^(const UnsignedHugeIntValue& operand) const {
    // The operands are differentiated based on their numbers of words.
    unsigned long long lesserNumWords, greaterNumWords, wordIndex;
    std::vector<WordType>::const_iterator lesserOperandIter, greaterOperandIter;
    lesserNumWords = operand.num_words();
    greaterNumWords = this->num_words();
    if (lesserNumWords > greaterNumWords) {
        // The operand argument has more words than this object.
        wordIndex = lesserNumWords;
        lesserNumWords = greaterNumWords;
        greaterNumWords = wordIndex;
        lesserOperandIter = this->word_values->begin();
        greaterOperandIter = operand.word_values->begin();
    } else {
        // The operand argument does not have more words than this object.
        lesserOperandIter = operand.word_values->begin();
        greaterOperandIter = this->word_values->begin();
    }

    // The result could have the same number of bits as the greater operand.
    auto *resultWords = new std::vector<WordType>(greaterNumWords);
    std::vector<WordType>::iterator resultIter = resultWords->begin();

    // The words of the resulting value are found by doing XOR operations to
    // the corresponding operand values.
    for (wordIndex = 0; wordIndex < lesserNumWords; ++wordIndex) {
        *resultIter = *lesserOperandIter ^ *greaterOperandIter;
        ++lesserOperandIter;
        ++greaterOperandIter;
        ++resultIter;
    }
    // When one operand runs out of words, copy the word values from the other operand.
    for (; wordIndex < greaterNumWords; ++wordIndex) {
        *resultIter = *greaterOperandIter;
        ++greaterOperandIter;
        ++resultIter;
    }
    // It is possible for the result to have extra leading 0 bits.
    UnsignedHugeIntValue::remove_extra_leading_words_from(resultWords);
    return UnsignedHugeIntValue(resultWords);
}

UnsignedHugeIntValue UnsignedHugeIntValue::operator^(unsigned long long operand) const {
    const unsigned long long thisNumWords = this->word_values->size();
    // First, the result words are copied from this object's words.
    auto *resultWords = new std::vector<WordType>(*this->word_values);
    std::vector<WordType>::iterator resultIter = resultWords->begin();

    // The result values are adjusted using XOR operations with the argument.
    for (unsigned long long wordIndex = 0; (operand > 0) && (wordIndex < thisNumWords); ++wordIndex) {
        *resultIter ^= (operand % word_base_value);
        operand /= word_base_value;
        ++resultIter;
    }
    // If the operand needs more words than this object, those words must be
    // appended to the result.
    while (operand > 0) {
        resultWords->push_back((WordType)(operand % word_base_value));
        operand /= word_base_value;
    }
    // It is possible for the result to have extra leading 0 bits.
    UnsignedHugeIntValue::remove_extra_leading_words_from(resultWords);
    return UnsignedHugeIntValue(resultWords);
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator^=(const UnsignedHugeIntValue& operand) {
    const unsigned long long thisNumWords = this->num_words();
    unsigned long long operandNumWords, lesserNumWords, wordIndex;
    std::vector<WordType>::iterator thisIter = this->word_values->begin();
    std::vector<WordType>::iterator argIter = operand.word_values->begin();
    operandNumWords = operand.num_words();
    if (operandNumWords < thisNumWords) {
        lesserNumWords = operandNumWords;
    } else {
        lesserNumWords = thisNumWords;
    }

    // The words of the resulting value are found by doing XOR operations to
    // the corresponding operand values.
    for (wordIndex = 0; wordIndex < lesserNumWords; ++wordIndex) {
        *thisIter ^= *argIter;
        ++thisIter;
        ++argIter;
    }
    // If the operand argument has more words, those words must be appended
    // to the result.
    if (operandNumWords > thisNumWords) {
        this->word_values->insert(thisIter, argIter, operand.word_values->end());
    }
    // If this object has more words than the argument, those words are
    // already set in the result.
    // It is possible for the result to have extra leading 0 bits.
    this->remove_extra_leading_words();
    return *this;
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator^=(unsigned long long operand) {
    const unsigned long long thisNumWords = this->num_words();
    std::vector<WordType>::iterator thisIter = this->word_values->begin();

    // The operand is split into word-sized segments for XOR operations.
    for (unsigned long long wordIndex = 0; (operand > 0) && (wordIndex < thisNumWords); ++wordIndex) {
        *thisIter ^= (operand % word_base_value);
        operand /= word_base_value;
        ++thisIter;
    }
    // If the operand argument still has remaining bits, those must be
    // appended to the result.
    while (operand > 0) {
        this->word_values->push_back((WordType)(operand % word_base_value));
        operand /= word_base_value;
    }
    // It is possible for the result to have extra leading 0 bits.
    this->remove_extra_leading_words();
    return *this;
}

UnsignedHugeIntValue UnsignedHugeIntValue::bitwise_not(unsigned long long number_of_bits) const {
    if (number_of_bits == 0) {
        return UnsignedHugeIntValue();
    }
    const unsigned long long numFullWords = number_of_bits / bits_per_word;
    const int numExtraBits = number_of_bits % bits_per_word;
    auto *resultWords = new std::vector<WordType>(numFullWords + 1);
    std::vector<WordType>::iterator resultIter = resultWords->begin();
    const unsigned long long numOrigWords = this->num_words();
    std::vector<WordType>::const_iterator thisIter = this->word_values->cbegin();
    unsigned long long wordIndex, firstIndexLimit;

    // NOT operations are first performed on full words of the original value.
    if (numOrigWords < numFullWords) {
        firstIndexLimit = numOrigWords;
    } else {
        firstIndexLimit = numFullWords;
    }
    for (wordIndex = 0; wordIndex < firstIndexLimit; ++wordIndex) {
        *resultIter = ~(*thisIter);
        ++thisIter;
        ++resultIter;
    }
    // If the original value runs out of words, the result will have all 1's
    // as the remaining bits.
    for (; wordIndex < numFullWords; ++wordIndex) {
        *resultIter = (WordType)max_word_value;
        ++resultIter;
    }
    // If there are no more bits to set, the output can be returned.
    if (numExtraBits == 0) {
        resultWords->pop_back();
        UnsignedHugeIntValue::remove_extra_leading_words_from(resultWords);
        return UnsignedHugeIntValue(resultWords);
    }
    // If there are more bits to set, the leftmost result word must be set.
    if (numOrigWords > numFullWords) {
        *resultIter =
            ~(*thisIter) & (max_word_value >> (bits_per_word - numExtraBits));
    } else {
        *resultIter = max_word_value >> (bits_per_word - numExtraBits);
    }
    UnsignedHugeIntValue::remove_extra_leading_words_from(resultWords);
    return UnsignedHugeIntValue(resultWords);
}

UnsignedHugeIntValue UnsignedHugeIntValue::operator<<(unsigned long long number_of_bits) const {
    const unsigned long long numOrigWords = this->word_values->size();
    if ((numOrigWords == 1) && (this->word_values->front() == 0)) {
        return UnsignedHugeIntValue();
    }
    if (number_of_bits == 0) {
        return UnsignedHugeIntValue(*this);
    }
    std::vector<WordType>::const_iterator thisIter = this->word_values->cbegin();
    const unsigned long long numFullWordsShifted = number_of_bits / bits_per_word;
    const int wordShiftSize = number_of_bits % bits_per_word;

    // If the shift size is divisible by the word size, word values can be
    // copied from the original value.
    if (wordShiftSize == 0) {
        auto *resultWords = new std::vector<WordType>(numOrigWords + numFullWordsShifted, 0);
        std::vector<WordType>::iterator resultIter = resultWords->begin() + numFullWordsShifted;
        for (unsigned long long wordIndex = 0; wordIndex < numOrigWords; ++wordIndex) {
            *resultIter = *thisIter;
            ++thisIter;
            ++resultIter;
        }
        return UnsignedHugeIntValue(resultWords);
    }

    const int carryShiftSize = bits_per_word - wordShiftSize;
    WordType carryValue;
    auto *resultWords = new std::vector<WordType>(numOrigWords + numFullWordsShifted + 1, 0);
    // 0 values are kept for every full word shifted in from the right.
    std::vector<WordType>::iterator resultIter = resultWords->begin() + numFullWordsShifted;
    // The next word gets its value from shifting the rightmost original word.
    *resultIter = *thisIter << wordShiftSize;
    carryValue = *thisIter >> carryShiftSize;

    // The next result word values are combined from two words of the original value.
    for (unsigned long long wordIndex = 1; wordIndex < numOrigWords; ++wordIndex) {
        ++thisIter;
        ++resultIter;
        *resultIter = (*thisIter << wordShiftSize) | carryValue;
        carryValue = *thisIter >> carryShiftSize;
    }

    // The most significant result word value is created only from the carry value.
    if (carryValue > 0) {
        ++resultIter;
        *resultIter = carryValue;
    } else {
        resultWords->pop_back();
    }
    return UnsignedHugeIntValue(resultWords);
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator<<=(unsigned long long number_of_bits) {
    const unsigned long long numOrigWords = this->word_values->size();
    if ((numOrigWords == 1) && (this->word_values->front() == 0)) {
        return *this;
    }
    if (number_of_bits == 0) {
        return *this;
    }
    const unsigned long long numFullWordsShifted = number_of_bits / bits_per_word;
    const int wordShiftSize = number_of_bits % bits_per_word;

    // If the shift size is divisible by the word size, word values of 0 can
    // be inserted from the right side to determine the result.
    if (wordShiftSize == 0) {
        this->word_values->insert(this->word_values->begin(), numFullWordsShifted, 0);
        return *this;
    }

    const int carryShiftSize = bits_per_word - wordShiftSize;
    // The full 0-value words are inserted from the right.
    this->word_values->insert(this->word_values->begin(), numFullWordsShifted + 1, 0);
    std::vector<WordType>::iterator thisIter = this->word_values->begin() + numFullWordsShifted;
    // The next word gets its value from shifting the rightmost original word.
    *thisIter = *(thisIter + 1) << wordShiftSize;

    // The next result word values are combined from two words of the original value.
    for (unsigned long long wordIndex = 1; wordIndex < numOrigWords; ++wordIndex) {
        ++thisIter;
        *thisIter = (*thisIter >> carryShiftSize) | (*(thisIter + 1) << wordShiftSize);
    }
    // The most significant result word value is created only from the carry value.
    ++thisIter;
    *thisIter >>= carryShiftSize;
    if (*thisIter == 0) {
        this->word_values->pop_back();
    }
    return *this;
}

UnsignedHugeIntValue UnsignedHugeIntValue::operator>>(unsigned long long number_of_bits) const {
    const unsigned long long numOrigWords = this->word_values->size();
    if ((numOrigWords == 1) && (this->word_values->front() == 0)) {
        return UnsignedHugeIntValue();
    }
    if (number_of_bits == 0) {
        return UnsignedHugeIntValue(*this);
    }
    const unsigned long long numFullWordsShifted = number_of_bits / bits_per_word;
    if (numFullWordsShifted >= numOrigWords) {
        // All the original bits were shifted out.
        return UnsignedHugeIntValue();
    }
    const int wordShiftSize = number_of_bits % bits_per_word;

    std::vector<WordType>::const_iterator thisIter = this->word_values->cbegin() + numFullWordsShifted;
    auto *resultWords = new std::vector<WordType>(numOrigWords - numFullWordsShifted);
    std::vector<WordType>::iterator resultIter = resultWords->begin();
    // If the shift size is divisible by the word size, word values can be
    // copied from the original value.
    if (wordShiftSize == 0) {
        for (unsigned long long wordIndex = numFullWordsShifted; wordIndex < numOrigWords; ++wordIndex) {
            *resultIter = *thisIter;
            ++thisIter;
            ++resultIter;
        }
        return UnsignedHugeIntValue(resultWords);
    }

    const int carryShiftSize = bits_per_word - wordShiftSize;
    WordType shiftedValue;
    // The result word values are combined from two words of the original value.
    shiftedValue = *thisIter >> wordShiftSize;
    for (unsigned long long wordIndex = numFullWordsShifted + 1; wordIndex < numOrigWords; ++wordIndex) {
        ++thisIter;
        *resultIter = (*thisIter << carryShiftSize) | shiftedValue;
        shiftedValue = *thisIter >> wordShiftSize;
        ++resultIter;
    }
    // The most significant result word value is created only from the carry value.
    if (shiftedValue > 0) {
        *resultIter = shiftedValue;
    } else {
        resultWords->pop_back();
    }
    return UnsignedHugeIntValue(resultWords);
}

UnsignedHugeIntValue& UnsignedHugeIntValue::operator>>=(unsigned long long number_of_bits) {
    const unsigned long long numOrigWords = this->word_values->size();
    if ((numOrigWords == 1) && (this->word_values->front() == 0)) {
        return *this;
    }
    if (number_of_bits == 0) {
        return *this;
    }
    const unsigned long long numFullWordsShifted = number_of_bits / bits_per_word;
    if (numFullWordsShifted >= numOrigWords) {
        this->word_values->resize(1);
        this->word_values->front() = 0;
        this->word_values->shrink_to_fit();
        return *this;
    }
    // If words are shifted out of the value, they are ignored.
    std::vector<WordType>::const_iterator readIter = this->word_values->cbegin() + numFullWordsShifted;
    std::vector<WordType>::iterator writeIter = this->word_values->begin();
    const int wordShiftSize = number_of_bits % bits_per_word;

    // If the shift size is divisible by the word size, full word values can
    // be copied to positions toward the right.
    if (wordShiftSize == 0) {
        for (unsigned long long wordIndex = numFullWordsShifted; wordIndex < numOrigWords; ++wordIndex) {
            *writeIter = *readIter;
            ++readIter;
            ++writeIter;
        }
        this->word_values->resize(numOrigWords - numFullWordsShifted);
        this->word_values->shrink_to_fit();
        return *this;
    }

    const int carryShiftSize = bits_per_word - wordShiftSize;
    WordType shiftedValue;
    // The result word values are combined from two words of the original value.
    shiftedValue = *readIter >> wordShiftSize;

    for (unsigned long long wordIndex = numFullWordsShifted + 1; wordIndex < numOrigWords; ++wordIndex) {
        ++readIter;
        *writeIter = (*readIter << carryShiftSize) | shiftedValue;
        shiftedValue = *readIter >> wordShiftSize;
        ++writeIter;
    }
    // The most significant result word value is created only from the
    // shifted value.
    if ((shiftedValue > 0) || (numOrigWords - numFullWordsShifted == 1)) {
        *writeIter = shiftedValue;
        this->word_values->resize(numOrigWords - numFullWordsShifted);
    } else {
        this->word_values->resize(numOrigWords - numFullWordsShifted - 1);
    }
    this->word_values->shrink_to_fit();
    return *this;
}

UnsignedHugeIntValue UnsignedHugeIntValue::left_ones_shifted(unsigned long long number_of_bits) const {
    const unsigned long long numOrigWords = this->word_values->size();
    if (number_of_bits == 0) {
        return UnsignedHugeIntValue(*this);
    }
    std::vector<WordType>::const_iterator thisIter = this->word_values->cbegin();
    const unsigned long long numFullWordsShifted = number_of_bits / bits_per_word;
    const int wordShiftSize = number_of_bits % bits_per_word;

    // If the shift size is divisible by the word size, word values can be
    // copied from the original value.
    if (wordShiftSize == 0) {
        if ((numOrigWords == 1) && (this->word_values->front() == 0)) {
            return UnsignedHugeIntValue(new std::vector<WordType>(numFullWordsShifted, max_word_value));
        }
        auto *resultWords = new std::vector<WordType>(numOrigWords + numFullWordsShifted, max_word_value);
        std::vector<WordType>::iterator resultIter = resultWords->begin() + numFullWordsShifted;
        for (unsigned long long wordIndex = 0; wordIndex < numOrigWords; ++wordIndex) {
            *resultIter = *thisIter;
            ++thisIter;
            ++resultIter;
        }
        return UnsignedHugeIntValue(resultWords);
    }

    const int carryShiftSize = bits_per_word - wordShiftSize;
    WordType carryValue;
    auto *resultWords = new std::vector<WordType>(numOrigWords + numFullWordsShifted + 1, max_word_value);
    // All 1 bits are kept for every full word shifted in from the right.
    std::vector<WordType>::iterator resultIter = resultWords->begin() + numFullWordsShifted;

    // The next word gets its value from shifting the rightmost original word.
    *resultIter = (*thisIter << wordShiftSize) | (max_word_value >> carryShiftSize);
    carryValue = *thisIter >> carryShiftSize;
    // The next result word values are combined from two words of the original value.
    for (unsigned long long wordIndex = 1; wordIndex < numOrigWords; ++wordIndex) {
        ++thisIter;
        ++resultIter;
        *resultIter = (*thisIter << wordShiftSize) | carryValue;
        carryValue = *thisIter >> carryShiftSize;
    }
    // The most significant result word value is created only from the carry value.
    if (carryValue > 0) {
        ++resultIter;
        *resultIter = carryValue;
    } else {
        resultWords->pop_back();
    }
    return UnsignedHugeIntValue(resultWords);
}

UnsignedHugeIntValue& UnsignedHugeIntValue::left_ones_shift_transform(unsigned long long number_of_bits) {
    const unsigned long long numOrigWords = this->word_values->size();
    if (number_of_bits == 0) {
        return *this;
    }
    const unsigned long long numFullWordsShifted = number_of_bits / bits_per_word;
    const int wordShiftSize = number_of_bits % bits_per_word;

    // If the shift size is divisible by the word size, word values with all 1
    // bits can be inserted from the right side to determine the result.
    if (wordShiftSize == 0) {
        this->word_values->insert(this->word_values->begin(), numFullWordsShifted, max_word_value);
        if (this->word_values->back() == 0) {
            this->word_values->pop_back();
        }
        return *this;
    }

    const int carryShiftSize = bits_per_word - wordShiftSize;
    // Words with all 1 bits are inserted from the right.
    this->word_values->insert(this->word_values->begin(), numFullWordsShifted + 1, max_word_value);
    std::vector<WordType>::iterator thisIter = this->word_values->begin() + numFullWordsShifted;
    // The next word gets its value from shifting the rightmost original word.
    *thisIter = (*(thisIter + 1) << wordShiftSize) | (max_word_value >> carryShiftSize);

    // The next result word values are combined from two words of the original value.
    for (unsigned long long wordIndex = 1; wordIndex < numOrigWords; ++wordIndex) {
        ++thisIter;
        *thisIter = (*thisIter >> carryShiftSize) | (*(thisIter + 1) << wordShiftSize);
    }
    // The most significant result word value is created only from the carry value.
    ++thisIter;
    *thisIter >>= carryShiftSize;
    if (*thisIter == 0) {
        this->word_values->pop_back();
    }
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
    delete this->word_values;
    constexpr unsigned int digitsPerSegment = 9;
    char readBuffer[digitsPerSegment + 1];
    char nextChar;
    WordType segmentValue;
    WordType multiplier;
    unsigned short placeIndex;
    this->word_values = new std::vector<WordType>(1, 0);
    auto *thisWordValues = this->word_values;
    // Find the size of the file for the vector memory reservation.
    fseek(integer_file, 0, SEEK_END);
    unsigned long long fileSize = ftell(integer_file);
    fseek(integer_file, 0, SEEK_SET);
    thisWordValues->reserve((3.321928096 * fileSize + 1) / bits_per_word + 1);
    do {
        placeIndex = 0;
        multiplier = 1;
        // A segment of digits is read at a time and converted to a long integer.
        while (placeIndex < digitsPerSegment) {
            nextChar = fgetc(integer_file);
            // When the end of the file is reached, no more digits are put in the buffer, and
            // the multiplier keeps its value.
            if (nextChar == EOF)
                break;
            // Characters that are not digits will be skipped.
            if (isdigit(nextChar)) {
                readBuffer[placeIndex] = nextChar;
                ++placeIndex;
                multiplier *= 10;
            }
        }
        readBuffer[placeIndex] = '\0'; // End of the number segment.
        // Converts the string to a long integer.
        segmentValue = strtoul(readBuffer, NULL, 10);
        this->multiply_single_word_transform(multiplier);
        this->add_value_at_word(thisWordValues->begin(), segmentValue);
    } while (nextChar != EOF);
    thisWordValues->shrink_to_fit();
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
    if (integer_file == NULL)
        throw std::invalid_argument("A null file pointer was given as an argument.");
    if (this->num_words() <= 0) {
        throw std::logic_error("An attempt was made to write an undefined value to a file.");
    }
    std::string bufferString;
    if (this->num_words() == 1) {
        bufferString = std::to_string(this->word_values->front());
        fputs(bufferString.c_str(), integer_file);
        return;
    }

    // The number of digits must be found to determine the size of the output file.
    constexpr unsigned long long digitsPerSegment = 9;
    constexpr WordType segmentBase = 1000000000;
    unsigned long long numDigits(digitsPerSegment);
    auto divisionResult = UnsignedHugeIntValue::divide_single_word_divisor(this, segmentBase);
    UnsignedHugeIntValue &quotient = divisionResult.first;
    WordType &remainder = divisionResult.second;
    while (quotient.num_words() > 1) {
        remainder = quotient.divide_single_word_divisor_transform(segmentBase);
        numDigits += digitsPerSegment;
    }
    bufferString = std::to_string(quotient.word_values->front());
    numDigits += bufferString.length();

    // The first sets of digits were already found, so they are sent to the output file.
    fputs(bufferString.c_str(), integer_file);
    bufferString = std::to_string(remainder);
    bufferString = std::string(digitsPerSegment - bufferString.length(), '0') + bufferString;
    fputs(bufferString.c_str(), integer_file);

    // The other output digits are found in segments, in order of least significant segment of digits.
    divisionResult = UnsignedHugeIntValue::divide_single_word_divisor(this, segmentBase);
    unsigned long long segmentIndex;
    for (segmentIndex = numDigits - digitsPerSegment; segmentIndex > digitsPerSegment; segmentIndex -= digitsPerSegment) {
        bufferString = std::to_string(remainder);
        bufferString = std::string(digitsPerSegment - bufferString.length(), '0') + bufferString;
        fseek(integer_file, segmentIndex, SEEK_SET);
        fputs(bufferString.c_str(), integer_file);
        remainder = quotient.divide_single_word_divisor_transform(segmentBase);
    }
}

void UnsignedHugeIntValue::read_from_binary_file(std::string file_path) {
    delete this->word_values;
    std::ifstream fileReadStream(file_path, std::ios::in | std::ios::binary);
    if (!fileReadStream.is_open()) {
        fileReadStream.close();
        throw std::invalid_argument("The file " + file_path + " could not be opened.");
    }
    // The file size is found to determine the number of words.
    fileReadStream.seekg(0, fileReadStream.end);
    unsigned long long fileSize = fileReadStream.tellg();
    fileReadStream.seekg(0, fileReadStream.beg);

    // The file data is put into a new vector.
    this->word_values = new std::vector<WordType>(fileSize / sizeof(WordType));
    fileReadStream.read(reinterpret_cast<char*>(this->word_values->data()), fileSize);
    fileReadStream.close();
}

void UnsignedHugeIntValue::write_to_binary_file(std::string file_path) const {
    // This does not permit writing to an existing file.
    struct stat placeholder_stat;
    if (stat(file_path.c_str(), &placeholder_stat) >= 0)
        std::invalid_argument("An attempt was made to write an UnsignedHugeIntValue value to an existing file.");
    std::ofstream fileWriteStream(file_path, std::ios::out | std::ios::binary);
    if (!fileWriteStream.is_open()) {
        fileWriteStream.close();
        throw std::invalid_argument("The file at " + file_path + " could not be created.");
    }
    // Only the word values from this object need to be written to the file.
    std::vector<WordType> *wordValues = this->word_values;
    fileWriteStream.write(reinterpret_cast<const char*>(wordValues->data()), wordValues->size() * sizeof(WordType));
    fileWriteStream.close();
}

long UnsignedHugeIntValue::num_words() const {
    return this->word_values->size();
}

std::string UnsignedHugeIntValue::to_string() const {
    if (this->word_values == NULL) {
        throw std::logic_error("An attempt was made to show the value of an undefined object.");
    }
    const unsigned long long numWords = this->word_values->size();
    if ((numWords == 1) && (this->word_values->front() == 0)) {
        return "0";
    }

    // The maximum number of digits can be found from the number of bits used.
    unsigned long long allocationSize = 0.30103 * bits_per_word * numWords + 1;
    std::string fullNumberString;
    fullNumberString.resize(allocationSize, '0');

    // A value base for segments is used that can be stored in one word.
    constexpr WordType segmentBase = 1000000000;
    constexpr unsigned short segmentLength = 9;
    // The digits of the result string are set in segments.
    unsigned long long segmentStart = allocationSize; // index of the start of the current segment in the result string.
    auto divisionResult = UnsignedHugeIntValue::divide_single_word_divisor(*this, segmentBase);
    UnsignedHugeIntValue &quotient = divisionResult.first;
    WordType &remainder = divisionResult.second;

    // While the quotient is greater than 0, there will be more segments to add to the string.
    while ((quotient.word_values->size() > 1) || (quotient.word_values->front() > 0)) {
        segmentStart -= segmentLength;
        std::string segmentString(std::to_string(remainder));
        unsigned short numLeadingZeros = segmentLength - segmentString.length();
        segmentString = std::string(numLeadingZeros, '0') + std::string(segmentString);
        fullNumberString.replace(segmentStart, segmentLength, segmentString);
        remainder = quotient.divide_single_word_divisor_transform(segmentBase);
    }

    // The most significant digits of the string are set last.
    std::string segmentString(std::to_string(remainder));
    unsigned short numLeadingDigits = segmentString.length();
    segmentStart -= numLeadingDigits;
    fullNumberString.replace(segmentStart, numLeadingDigits, segmentString);

    // Extra digits at the beginning likely need to be removed.
    fullNumberString.erase(0, segmentStart);
    fullNumberString.shrink_to_fit();
    return fullNumberString;
}

void UnsignedHugeIntValue::set_value_from_string(std::string integer_string) {
    const unsigned long long numDigits =  integer_string.length();
    if (numDigits == 0) {
        throw std::invalid_argument("An attempt was made to convert an empty string into an UnsignedHugeInt.");
    }
    this->word_values = new std::vector<WordType>;
    // Space for the integer is reserved based on the estimated number of bits needed.
    this->word_values->reserve((unsigned long long)(3.321928096 * numDigits + 1) / bits_per_word + 1);

    // Segments are used that fit within one word of UnsignedHugeInt.
    constexpr WordType segmentBaseValue = 1000000000;
    constexpr unsigned long long segmentLength = 9;
    unsigned long long segmentStartIndex = numDigits % segmentLength;
    std::string segmentString;
    WordType segmentValue;

    // The most significant digits are read first.
    if (segmentStartIndex == 0) {
        segmentValue = 0;
    }
    else {
        segmentString = integer_string.substr(0, segmentStartIndex);
        segmentValue = std::stol(segmentString);
    }
    this->word_values->push_back(segmentValue);

    // The remaining digits of the string are read in segments.
    for (; segmentStartIndex < numDigits; segmentStartIndex += segmentLength) {
        segmentString = integer_string.substr(segmentStartIndex, segmentLength);
        segmentValue = std::stol(segmentString);
        this->multiply_single_word_transform(segmentBaseValue);
        this->add_value_at_word(this->word_values->begin(), segmentValue);
    }
    this->remove_extra_leading_words();
}

void UnsignedHugeIntValue::remove_extra_leading_words_from(std::vector<WordType>* word_values) {
    unsigned long long newNumWords = word_values->size();
    if (newNumWords <= 1)
        return;
    std::vector<WordType>::const_reverse_iterator wordIter = word_values->crbegin();
    while ((*wordIter == 0) && (newNumWords > 1)) {
        --newNumWords;
        ++wordIter;
    }
    word_values->resize(newNumWords);
    word_values->shrink_to_fit();
}

void UnsignedHugeIntValue::remove_extra_leading_words() {
    UnsignedHugeIntValue::remove_extra_leading_words_from(this->word_values);
}

void UnsignedHugeIntValue::add_value_at_word(std::vector<WordType>::iterator location_to_add, const UnsignedHugeIntValue& value_to_add) {
    std::vector<WordType>::const_iterator addendWordIter = value_to_add.word_values->cbegin();
    const std::vector<WordType>::iterator thisEndWord = this->word_values->end();
    const std::vector<WordType>::const_iterator addendEndWord = value_to_add.word_values->cend();
    uint64_t remainingValue = 0;

    // Corresponding words are added together.
    while ((addendWordIter != addendEndWord) && (location_to_add != thisEndWord)) {
        remainingValue = remainingValue + *location_to_add + *addendWordIter;
        *location_to_add = (WordType)(remainingValue % word_base_value);
        remainingValue /= word_base_value;
        ++location_to_add;
        ++addendWordIter;
    }

    // All the words of value_to_add must be added.
    while (addendWordIter != addendEndWord) {
        remainingValue += *addendWordIter;
        this->word_values->push_back((WordType)(remainingValue % word_base_value));
        remainingValue /= word_base_value;
        ++addendWordIter;
    }

    // The carry value should be added to the current word of this object.
    while ((remainingValue > 0) && (location_to_add != thisEndWord)) {
        remainingValue += *location_to_add;
        *location_to_add = (WordType)(remainingValue % word_base_value);
        remainingValue /= word_base_value;
        ++location_to_add;
    }

    // If there are no more words of this object, another must be added for the carry value.
    if (remainingValue > 0) {
        this->word_values->push_back((WordType)remainingValue);
    }
}

void UnsignedHugeIntValue::add_value_at_word(std::vector<WordType>::iterator location_to_add, unsigned long long value_to_add) {
    const std::vector<WordType>::iterator thisEndWord = this->word_values->end();
    if (value_to_add == 0)
        return;

    // Overflow must be prevented by dividing value_to_add before adding.
    if (location_to_add != thisEndWord) {
        uint64_t remainderSum = (value_to_add % word_base_value) + *location_to_add;
        *location_to_add = (WordType)(remainderSum % word_base_value);
        value_to_add = (value_to_add / word_base_value) + (remainderSum / word_base_value);
        ++location_to_add;
    }

    // Overflow from the addend value should be carried over to the next word of this object.
    while ((value_to_add > 0) && (location_to_add != thisEndWord)) {
        value_to_add += *location_to_add;
        *location_to_add = (WordType)(value_to_add % word_base_value);
        value_to_add /= word_base_value;
        ++location_to_add;
    }

    // If there are no more words of this object, more must be added for the remainder of the value.
    while (value_to_add > 0) {
        this->word_values->push_back((WordType)(value_to_add % word_base_value));
        value_to_add /= word_base_value;
    }
}

void UnsignedHugeIntValue::insert_multiplication_subtotal(
        std::vector<WordType>::const_reverse_iterator greater_factor_iterator,
        std::vector<WordType>::const_iterator lesser_factor_iterator,
        const std::vector<WordType>::iterator& insert_location,
        unsigned long long number_of_multiplications) {
    std::vector<WordType>::iterator resultIter;
    uint64_t wordProduct;

    // Each product of corresponding words is added to the resulting subtotal.
    for (unsigned long long multCount = 0; multCount < number_of_multiplications; ++multCount) {
        wordProduct = (uint64_t)(*greater_factor_iterator) * *lesser_factor_iterator;
        resultIter = insert_location;
        while(wordProduct > 0) {
            wordProduct += *resultIter;
            *resultIter = (WordType)(wordProduct % word_base_value);
            wordProduct /= word_base_value;
            ++resultIter;
        }
        ++greater_factor_iterator;
        ++lesser_factor_iterator;
    }
}

bool UnsignedHugeIntValue::is_remainder_too_large(std::vector<WordType>::reverse_iterator remainder_iterator,
                                               const std::vector<WordType>* divisor_words) {
    std::vector<WordType>::const_reverse_iterator divisorIter = divisor_words->crbegin();
    for (unsigned long long numWordsRemaining = divisor_words->size(); numWordsRemaining > 0; --numWordsRemaining) {
        if (*remainder_iterator > *divisorIter) {
            return true;
        }
        if (*remainder_iterator < *divisorIter) {
            return false;
        }
        ++remainder_iterator;
        ++divisorIter;
    }
    return true;
}

void UnsignedHugeIntValue::subtract_from_remainder(std::vector<WordType>::iterator remainder_iterator,
                                                 const UnsignedHugeIntValue& subtrahend) {
    std::vector<WordType>::const_iterator subtrahendIter = subtrahend.word_values->cbegin();
    uint64_t remainderWord, subtrahendWord, carryValue = 0;
    for (unsigned long long numWordsRemaining = subtrahend.word_values->size(); numWordsRemaining > 0; --numWordsRemaining) {
        remainderWord = *remainder_iterator;
        subtrahendWord = *subtrahendIter + carryValue;
        if (remainderWord < subtrahendWord) {
            *remainder_iterator = word_base_value + remainderWord - subtrahendWord;
            carryValue = 1;
        } else {
            *remainder_iterator = remainderWord - subtrahendWord;
            carryValue = 0;
        }
        ++remainder_iterator;
        ++subtrahendIter;
    }
}

std::ostream& operator<<(std::ostream& out_stream, const UnsignedHugeIntValue& huge_int_object) {
    out_stream << huge_int_object.to_string();
    return out_stream;
}
