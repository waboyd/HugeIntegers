#pragma once

#include <iostream>
#include <sstream>

// The largest possible value of one word of an UnsignedHugeInt value.
#define HUGE_INT_MAX_WORD_VALUE     4294967295

// The base value for the words of UnsignedHugeInt.
// This value must always be one more than HUGE_INT_MAX_WORD_VALUE.
#define HUGE_INT_WORD_BASE          4294967296

// The number of bits used to store each word value of an UnsignedHugeInt.
#define HUGE_INT_NUMBER_OF_BITS_PER_WORD    32

// The greatest number of 9 digits in a base 10 integer than can be stored in a single UnsignedHugeInt word.
#define HUGE_INT_NUMBER_OF_BASE_10_DIGITS_PER_WORD  9

class HugeIntWord
{
    friend class UnsignedHugeIntValue;

public:

    /**
     * @brief Creates a new HugeIntWord object with the given value.
     * This method does not check whether the value is too large for one HugeIntWord object.
     * @param value Unsigned integer value that will be used as the initial value for the word.
     */
    HugeIntWord(unsigned long value);

    /**
     * @brief Creates a new HugeIntWord object with the given value, then attaches the argument object as the next less significant word.
     * This method does not check whether the value is too large for one HugeIntWord object. The newly created object
     * is set as the next more significant word of the HugeIntWord object argument.
     * @param value Unsigned integer value that will be used as the initial value for the word.
     * @param lowerSignificantWord Object to be set as the next lower significant word of the newly created object.
     */
    HugeIntWord(unsigned long value, HugeIntWord* lowerSignificantWord);

    /**
     * @brief Return the value held by this HugeIntWord object.
     * @return The value held by this HugeIntWord object.
     */
    unsigned long get_value() const;

    /**
     * @brief Returns the place value of this HugeIntWord object within the integer.
     * The least significant word has a place value of 0, and each word has a place value one higher than the next less
     * significant word.
     */
    unsigned long long get_word_number() const;

    /**
     * @brief Returns the value of this word as a string of digits.
     * If the HugeIntWord object is not the most significant word of the integer, leading zeros are added to the string
     * when appropriate.
     * @return The value of this word as a string of digits.
     */
    std::string to_string();

protected:
    // Link to the next less significant word object.
    HugeIntWord *lessSigWord;

    // Link to the next more significant word object.
    HugeIntWord *moreSigWord;

    // Current numerical value of this word.
    unsigned long value;

    // Location of this word in the number. 0 is least significant place.
    unsigned long long place_value;

    // Protected methods

    /**
     * @brief Returns the next less significant word (segment) of the number.
     * @return The next less significant word (segment) of the number.
     */
    HugeIntWord* get_next_lower_sig_word() const;

    /**
     * @brief Returns the next more significant word (segment) of the number.
     * @return The next more significant word (segment) of the number.
     */
    HugeIntWord* get_next_more_sig_word() const;

private:
    /**
     * @brief Sets the argument as the next more significant word of this word object.
     * @param next_word The next more significant word of this word object.
     */
    void set_more_significant_word(HugeIntWord* next_word);

    /**
     * @brief Sets the argument as the next less significant word of this word object.
     * @param next_word The next less significant word of this word object.
     */
    void set_less_significant_word(HugeIntWord* next_word);

    /**
     * @brief Removes and deletes the next more significant word object, leaving this object as the new most significant word.
     */
    void remove_more_significant_word();

    /**
     * @brief Adds a value to this word.
     * @param addend Value to add to the word.
     * @return Pointer to most significant word of the addition operation.
     */
    HugeIntWord* add_value(unsigned long long addend);
};

