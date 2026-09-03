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

HugeIntPrintable::HugeIntPrintable(std::vector<WordType>* word_values_vector, bool is_negative)
        : word_values(word_values_vector), is_negative(is_negative) {}

HugeIntPrintable::~HugeIntPrintable()
{
    delete this->word_values;
}

HugeIntPrintable& HugeIntPrintable::operator=(const HugeIntPrintable& orig) {
    delete this->word_values;
    this->word_values = new std::vector<WordType>(*orig.word_values);
    this->is_negative = orig.is_negative;
    return *this;
}

HugeIntPrintable& HugeIntPrintable::operator=(HugeIntPrintable&& orig) noexcept {
    delete this->word_values;
    this->word_values = orig.word_values;
    this->is_negative = orig.is_negative;
    orig.word_values = NULL;
    return *this;
}

HugeIntPrintable& HugeIntPrintable::operator=(const std::string value_string) {
    delete this->word_values;
    this->set_value_from_string(value_string);
    return *this;
}

HugeIntPrintable& HugeIntPrintable::operator=(const char* value_string) {
    delete this->word_values;
    this->set_value_from_string(std::string(value_string));
    return *this;
}

unsigned long long HugeIntPrintable::number_of_digits() const {
    if ((this->word_values == NULL) || (this->word_values->size() == 0)) {
        throw std::logic_error("An attempt was made to find the number of digits for an undefined object.");
    }
    unsigned long long totalNumDigits = 1;
    // First, the number of digits in the leading word is found.
    WordType leadingWord = this->word_values->back();
    while (leadingWord > 10) {
        ++totalNumDigits;
        leadingWord /= 10;
    }
    // The number of digits from all of the other words is then found.
    totalNumDigits += (this->word_values->size() - 1) * digits_per_word;
    return totalNumDigits;
}

unsigned long long HugeIntPrintable::length() const {
    return this->number_of_digits();
}

HugeIntPrintable HugeIntPrintable::read_from_text_file(std::string file_path) {
    FILE *readTextFile = fopen(file_path.c_str(), "r");
    if (readTextFile == NULL)
        std::invalid_argument("The file with the given path could not be opened.");
    // The size of the file must be found.
    fseek(readTextFile, 0, SEEK_END);
    unsigned long long fileReadIndex = ftell(readTextFile);
    if (fileReadIndex == 0) {
        fclose(readTextFile);
        std::invalid_argument(
            "An attempt was made to convert an empty file into a HugeIntPrintable object.");
    }
    // Room is allocated to store all digits of the value from the file.
    auto *wordVector = new std::vector<WordType>((fileReadIndex - 1) / digits_per_word + 1, 0);
    std::vector<WordType>::iterator wordIter = wordVector->begin();
    constexpr unsigned int readBufferSize = 504;
    char readBuffer[readBufferSize];
    unsigned int readBufferIndex;
    char wordBuffer[digits_per_word + 1];
    wordBuffer[digits_per_word] = '\0'; // End of the number segment.
    unsigned long long numWordsRead = 0;
    unsigned int wordBufferIndex = digits_per_word - 1;
    char nextChar;

    // The file is read in reverse order.
    while (fileReadIndex > readBufferSize) {
        fileReadIndex -= readBufferSize;
        fseek(readTextFile, fileReadIndex, SEEK_SET);
        fread(readBuffer, sizeof(char), readBufferSize, readTextFile);
        readBufferIndex = readBufferSize;
        do {
            --readBufferIndex;
            nextChar = readBuffer[readBufferIndex];
            // Characters that are not digits will be skipped.
            if (!isdigit(nextChar))
                continue;
            wordBuffer[wordBufferIndex] = nextChar;
            if (wordBufferIndex == 0) {
                *wordIter = (WordType)strtoul(wordBuffer, NULL, 10);
                ++numWordsRead;
                ++wordIter;
                wordBufferIndex = digits_per_word - 1;
            } else {
                --wordBufferIndex;
            }
        } while (readBufferIndex > 0);
    }
    // The last read buffer needs to be read from the file.
    fseek(readTextFile, 0, SEEK_SET);
    fread(readBuffer, sizeof(char), fileReadIndex, readTextFile);
    fclose(readTextFile);
    readBufferIndex = fileReadIndex;
    while (readBufferIndex > 0) {
        --readBufferIndex;
        nextChar = readBuffer[readBufferIndex];
        // Characters that are not digits will be skipped.
        if (!isdigit(nextChar))
            continue;
        wordBuffer[wordBufferIndex] = nextChar;
        if (wordBufferIndex == 0) {
            *wordIter = (WordType)strtoul(wordBuffer, NULL, 10);
            ++numWordsRead;
            ++wordIter;
            wordBufferIndex = digits_per_word - 1;
        } else {
            --wordBufferIndex;
        }
    }
    // The value in the word buffer needs to be stored as the last word value.
    if (wordBufferIndex < digits_per_word - 1) {
        wordBuffer[wordBufferIndex] = '0';
        while (wordBufferIndex > 0) {
            --wordBufferIndex;
            wordBuffer[wordBufferIndex] = '0';
        }
        *wordIter = (WordType)strtoul(wordBuffer, NULL, 10);
        ++numWordsRead;
        ++wordIter;
    }
    // If too many words were reserved, some words need to be deleted.
    --wordIter;
    while ((*wordIter == 0) && (numWordsRead > 1)) {
        --wordIter;
        --numWordsRead;
    }
    wordVector->resize(numWordsRead);
    wordVector->shrink_to_fit();
    return HugeIntPrintable(wordVector, readBuffer[0] == '-');
}

void HugeIntPrintable::write_to_text_file(std::string file_path) const {
    unsigned long long numWords = this->word_values->size();
    if (numWords == 0) {
        throw std::logic_error("An attempt was made to write an undefined value to a file.");
    }
    std::vector<WordType>::const_reverse_iterator wordIter = this->word_values->crbegin();

    // Writing to an existing file is not permitted.
    struct stat placeholder_stat;
    if (stat(file_path.c_str(), &placeholder_stat) >= 0)
        std::invalid_argument("An attempt was made to write a HugeIntPrintable value to an existing file.");
    FILE *writeTextFile = fopen(file_path.c_str(), "w");
    if (writeTextFile == NULL)
        throw std::runtime_error("A new file could not be opened for writing a HugeIntPrintable value.");

    if (this->is_negative) {
        putc('-', writeTextFile);
    }
    // The first word value can be placed directly into the file.
    std::string bufferString = std::to_string(*wordIter);
    fputs(bufferString.c_str(), writeTextFile);
    // For other word values, leading zeros may need to be added.
    for (unsigned long long wordIndex = 1; wordIndex < numWords; ++wordIndex) {
        ++wordIter;
        bufferString = std::to_string(*wordIter);
        bufferString = std::string(digits_per_word - bufferString.length(), '0') + bufferString;
        fputs(bufferString.c_str(), writeTextFile);
    }
    fclose(writeTextFile);
}

std::string HugeIntPrintable::to_string() const {
    if ((this->word_values == NULL) || (this->word_values->size() == 0)) {
        throw std::logic_error("An attempt was made to show the value of an undefined object.");
    }
    const unsigned long long numWords = this->word_values->size();
    if ((numWords == 1) && (this->word_values->front() == 0)) {
        return "0";
    }

    // Memory is reserved for the entire string.
    unsigned long long numDigits = this->number_of_digits();
    std::string fullNumberString;
    if (this->is_negative) {
        fullNumberString.reserve(numDigits + 2);
        fullNumberString += '-';
    } else {
        fullNumberString.reserve(numDigits + 1);
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
    return fullNumberString;
}

HugeIntPrintable::operator std::string() const {
    return this->to_string();
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

