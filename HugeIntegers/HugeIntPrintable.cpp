#include "HugeIntPrintable.h"

HugeIntPrintable::HugeIntPrintable()
{
    this->word_values = new std::vector<WordType>();
}

HugeIntPrintable::HugeIntPrintable(const std::string integer_string) {
    this->set_value_from_string(integer_string);
}

HugeIntPrintable::HugeIntPrintable(const char* integer_string) {
    this->set_value_from_string(std::string(integer_string));
}

HugeIntPrintable::HugeIntPrintable(const HugeIntPrintable& orig)
        : word_values(new std::vector<WordType>(*orig.word_values)),
          is_negative(orig.is_negative) {}

HugeIntPrintable::HugeIntPrintable(HugeIntPrintable&& orig) noexcept
        : word_values(orig.word_values),
          is_negative(orig.is_negative) {
    orig.word_values = NULL;
}

HugeIntPrintable::~HugeIntPrintable()
{
    delete this->word_values;
}

std::string HugeIntPrintable::to_string() const {
    if ((this->word_values == NULL) || (this->word_values->size() == 0)) {
        throw std::logic_error("An attempt was made to show the value of an undefined object.");
    }
    const unsigned long long numWords = this->word_values->size();
    if ((numWords == 1) && (this->word_values->front() == 0)) {
        return "0";
    }

    // The maximum number of digits in the value.
    unsigned long long allocationSize = numWords * digits_per_word + 1;
    std::string fullNumberString;
    fullNumberString.reserve(allocationSize);
    if (this->is_negative) {
        fullNumberString += '-';
    }

    // The first digits can be taken directly from the last stored word.
    std::vector<WordType>::const_reverse_iterator wordIter = this->word_values->crbegin();
    fullNumberString += std::to_string(*wordIter);
    // For the following words, zeros may need to be added to the string.
    std::string segmentString;
    unsigned short numLeadingZeros;
    for (unsigned long long wordsRead = 1; wordsRead < numWords; ++wordsRead) {
        ++wordIter;
        segmentString = std::to_string(*wordIter);
        numLeadingZeros = digits_per_word - segmentString.length();
        fullNumberString += std::string(numLeadingZeros, '0') + segmentString;
    }
    fullNumberString.shrink_to_fit();
    return fullNumberString;
}

void HugeIntPrintable::set_value_from_string(std::string integer_string) {
    const unsigned long long numDigits =  integer_string.length();
    if (numDigits == 0) {
        throw std::invalid_argument("An attempt was made to convert an empty string into a HugeIntPrintable object.");
    }
    if (integer_string[0] == '-') {
        this->is_negative = true;
    }
    unsigned long long numWords;
    std::string segmentString;
    WordType segmentValue;
    std::vector<WordType>::reverse_iterator wordIter;
    unsigned long long segmentStartIndex = numDigits % digits_per_word;

    // The most significant (leftmost) digits are read first.
    if (std::isdigit(integer_string[0])) {
        numWords = ((numDigits - 1) / digits_per_word) + 1;
        this->word_values = new std::vector<WordType>(numWords);
        wordIter = this->word_values->rbegin();
        if (segmentStartIndex > 0) {
            segmentString = integer_string.substr(0, segmentStartIndex);
            segmentValue = std::stol(segmentString);
            *wordIter = segmentValue;
            ++wordIter;
        }
    } else {
        if (numDigits < 2) {
            throw std::invalid_argument("An attempt was made to convert a string without digits into a HugeIntPrintable object.");
        }
        // The first character is not a digit, such as '-' or '+'.
        numWords = ((numDigits - 2) / digits_per_word) + 1;
        this->word_values = new std::vector<WordType>(numWords);
        wordIter = this->word_values->rbegin();
        if (segmentStartIndex == 0) {
            segmentStartIndex = digits_per_word;
        }
        if (segmentStartIndex != 1) {
            segmentString = integer_string.substr(1, segmentStartIndex - 1);
            segmentValue = std::stol(segmentString);
            *wordIter = segmentValue;
            ++wordIter;
        }
    }

    // The remaining digits of the string are read in segments.
    for (; segmentStartIndex < numDigits; segmentStartIndex += digits_per_word) {
        segmentString = integer_string.substr(segmentStartIndex, digits_per_word);
        segmentValue = std::stol(segmentString);
        *wordIter = segmentValue;
        ++wordIter;
    }
    // If the leftmost words have a value of 0, those words should be removed.
    wordIter = this->word_values->rbegin();
    unsigned long long wordIndex;
    for (wordIndex = numWords; (*wordIter == 0) && (wordIndex > 1); --wordIndex) {
        ++wordIter;
    }
    if (wordIndex < numWords) {
        this->word_values->resize(wordIndex);
        this->word_values->shrink_to_fit();
    }
}

