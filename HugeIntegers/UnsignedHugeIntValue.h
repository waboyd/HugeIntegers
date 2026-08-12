#pragma once

#include <cstdint>
#include <fstream>
#include <iostream>
#include <string.h>
#include <sstream>
#include <sys/stat.h>
#include <vector>

class UnsignedHugeIntValue {
    friend class UnsignedHugeInt;
public:
    // Public Methods

    /**
     * @brief Creates a new UnsignedHugeIntValue object with a value of 0.
     */
    UnsignedHugeIntValue();

    /**
     * @brief Creates a new UnsignedHugeIntValue object with the value given in the parameter.
     * The parameter must be an unsigned integer that can be managed by the computer. If the integer is too large to
     * use as an argument, a string parameter should be used instead.
     * @param value Unsigned integer value for the initial value of the UnsignedHugeIntValue object.
     */
    UnsignedHugeIntValue(const unsigned long long value);

    /**
     * @brief Creates a new UnsignedHugeIntValue object with the value given in the parameter.
     * The string parameter should have only the digits of the integer value.
     * @param integer_string Initial value of the UnsignedHugeIntValue object as a string of digits.
     */
    UnsignedHugeIntValue(const std::string integer_string);

    /**
     * @brief Creates a new UnsignedHugeIntValue object with the value given in the parameter.
     * The string parameter should have only the digits of the integer value.
     * @param integer_string Initial value of the UnsignedHugeIntValue object as a string of digits.
     */
    UnsignedHugeIntValue(const char* integer_string);

    /**
     * @brief Creates a new UnsignedHugeIntValue object as a copy of the argument.
     * @param orig Object whose value is to be copied.
     */
    UnsignedHugeIntValue(const UnsignedHugeIntValue& orig);

    /**
     * @brief Creates a new UnsignedHugeIntValue object as a copy of the object referred to by the argument.
     * @param orig Pointer to the object whose value is to be copied.
     */
    UnsignedHugeIntValue(const UnsignedHugeIntValue* orig);

    /**
     * @brief Creates a new UnsignedHugeIntValue object with a value moved from the argument.
     * The value does not not exist in the original argument object after this operation.
     * @param orig Object whose value will be moved.
     */
    UnsignedHugeIntValue(UnsignedHugeIntValue&& orig) noexcept;

    /**
     * @brief Deletes the UnsignedHugeIntValue object completely.
     */
    virtual ~UnsignedHugeIntValue();

    /**
     * @brief Returns the number of base 10 digits in the value.
     * @return The number of base 10 digits in the value.
     */
    UnsignedHugeIntValue number_of_digits() const;

    /**
     * @brief Sets the value of this UnsignedHugeIntValue object to the integer in the text file.
     * The file should contain digits for only a single integer, as the entire file is scanned to
     * set the value of this object.
     * @param file_path The path of a file containing an unsigned integer value.
     */
    void read_from_text_file(std::string file_path);

    /**
     * @brief Sets the value of this UnsignedHugeIntValue object to the integer in the text file.
     * The file should contain digits for only a single integer, as the entire file is scanned to
     * set the value of this object.
     * @param integer_file A file pointer, with read permission, to the file to be read.
     */
    void read_from_text_file(FILE* integer_file);

    /**
     * @brief Writes the value from this object to a new text file.
     * The file with the given path must not already exist.
     * @param file_path The destination path, including the file name, of the text file to be written.
     */
    void write_to_text_file(std::string file_path) const;

    /**
     * @brief Writes the value from this object as text to a file.
     * The value will be written to the current file pointer location.
     * @param integer_file A file pointer, with write permission, to the file location where the value will be written.
     */
    void write_to_text_file(FILE* integer_file) const;

    /**
     * @brief Sets the value of this object to the value from a binary file.
     * The file should be one created by the write_to_binary_file method of UnsignedHugeIntValue. Portability of the binary files
     * is not guaranteed.
     * @param file_path The file path, including the file name, of the binary file containing the value of an UnsignedHugeIntValue.
     */
    void read_from_binary_file(std::string file_path);

    /**
     * @brief Writes the value from this object to a new binary file.
     * The file must not already exist. The binary file can be read by the read_from_binary_file method of UnsignedHugeIntValue.
     * Portability of the binary files is not guaranteed.
     * @param file_path
     */
    void write_to_binary_file(std::string file_path) const;

    /**
     * @brief Converts the value of this object to a C++ string.
     */
    operator std::string() const;

    /**
     * @brief Assigns a copy of the right-hand value to the object on the left of the assignment operator.
     * This operation does not change the right-hand value or objects.
     * @param orig An UnsignedHugeIntValue object with a value that will be copied.
     * @return Reference to the newly created object.
     */
    UnsignedHugeIntValue& operator=(const UnsignedHugeIntValue& orig);

    /**
     * @brief Assigns a copy of the right-hand value to the object on the left of the assignment operator.
     * This operation does not change the right-hand value or objects.
     * @param orig A pointer to an UnsignedHugeIntValue object with a value that will be copied.
     * @return Reference to the newly created object.
     */
    UnsignedHugeIntValue& operator=(const UnsignedHugeIntValue* orig);

    /**
     * @brief Moves value from the argument to this object, removing the the value from the argument.
     * @param orig Object whose value will be moved.
     * @return Reference to the new object which received the value.
     */
    UnsignedHugeIntValue& operator=(UnsignedHugeIntValue&& orig) noexcept;

    /**
     * @brief Assigns the value from the right-hand side of the assignment operator to the object on the left of the operator.
     * It is assumed that only non-negative value will be assigned. To assign a value that is too large for the
     * unsigned long long type, a numerical string (such as "9874390745") can be used on the right-hand side of the operator.
     * @param value The value to assign to the UnsignedHugeIntValue object.
     * @return Reference to the newly created object.
     */
    UnsignedHugeIntValue& operator=(const unsigned long long value);

    /**
     * @brief Reads a numerical string as an unsigned integer and assigns the value to the UnsignedHugeIntValue object.
     * The string should contain only digits. This assignment operation can be used to assign values that are too
     * large to be processed directly.
     * @param value_string A C++ string of the value to assign to the UnsignedHugeIntValue object.
     * @return Reference to the newly created object.
     */
    UnsignedHugeIntValue& operator=(const std::string value_string);

    /**
     * @brief Reads a numerical string as an unsigned integer and assigns the value to the UnsignedHugeIntValue object.
     * The string should contain only digits. This assignment operation can be used to assign values that are too
     * large to be processed directly.
     * @param value_string A C string of the value to assign to the UnsignedHugeIntValue object.
     * @return Reference to the newly created object.
     */
    UnsignedHugeIntValue& operator=(const char*  value_string);

    /**
     * @brief Determines which of the two numbers is greater.
     * @param numberA One of the numbers to compare.
     * @param numberB One of the numbers to compare.
     * @return 1 if numberA is greater; 0 if the numbers are equal; -1 if numberB is greater.
     */
    static short compare(const UnsignedHugeIntValue& numberA, const UnsignedHugeIntValue& numberB);

    /**
     * @brief Returns the sum of the two unsigned integers.
     * @param addendA One of the two unsigned integers to be added.
     * @param addendB One of the two unsigned integers to be added.
     * @return The result of adding the two arguments.
     */
    static UnsignedHugeIntValue sum_of(const UnsignedHugeIntValue& addendA, const UnsignedHugeIntValue& addendB);

    /**
     * @brief Returns the sum of the two unsigned integers.
     * @param addendA One of the two unsigned integers to be added.
     * @param addendB One of the two unsigned integers to be added.
     * @return The result of adding the two arguments.
     */
    static UnsignedHugeIntValue sum_of(const UnsignedHugeIntValue& addendA, unsigned long long addendB);

    /**
     * @brief Subtracts two unsigned integers to produce an UnsignedHugeIntValue object.
     * The minuend is not permitted to have a lower value than the subtrahend.
     * @param minuend The integer from which a value is subtracted (the larger operand).
     * @param subtrahend The amount that is subtracted from the minuend.
     * @return The result of subtraction as an unsigned integer.
     */
    static UnsignedHugeIntValue subtract(const UnsignedHugeIntValue& minuend, const UnsignedHugeIntValue& subtrahend);

    /**
     * @brief Multiplies two unsigned integers to produce an UnsignedHugeIntValue object.
     * @param factorA One of the integer factors of the multiplication.
     * @param factorB One of the integer factors of the multiplication.
     * @return The result of multiplication as an unsigned integer.
     */
    static UnsignedHugeIntValue multiply(const UnsignedHugeIntValue& factorA, const UnsignedHugeIntValue& factorB);

    /**
     * @brief Multiplies an UnsignedHugeIntValue by another unsigned integer.
     * @param factor One of the unsigned integer factors of the multiplication
     * @return The result of the multiplication as an unsigned integer.
     */
    UnsignedHugeIntValue multiply_by_int(const unsigned long long factor) const;

    /**
     * @brief Performs integer division on the two unsigned operands, and returns both the quotient and the remainder as a pair.
     * This method is called by both '/' and '%' operators.
     * @param dividend The dividend of the division operation.
     * @param divisor The divisor of the division operation.
     * @return The whole number quotient (first) and remainder (second) results of the division operation.
     */
    static std::pair<UnsignedHugeIntValue, UnsignedHugeIntValue> divide(const UnsignedHugeIntValue& dividend, const UnsignedHugeIntValue& divisor);

    /**
     * @brief Increases the object's value by the specified unsigned integer amount.
     * This operation changes the value of the object itself.
     * @param addend Value that will be added to the object's value.
     * @return Reference to the UnsignedHugeIntValue object after its value is changed.
     */
    UnsignedHugeIntValue& operator+=(const UnsignedHugeIntValue& addend);

    /**
     * @brief Increases the object's value by the specified unsigned integer amount.
     * This operation changes the value of the object itself.
     * @param addend Value that will be added to the object's value.
     * @return Reference to the UnsignedHugeIntValue object after its value is changed.
     */
    UnsignedHugeIntValue& operator+=(const unsigned long long addend);

    /**
     * @brief Decreases the object's value by the specified unsigned integer amount.
     * This operation changes the value of the object itself. A negative result is not permitted.
     * @param subtrahend Value that will be subtracted from the object's value.
     * @return Reference to the UnsignedHugeIntValue object after its value is changed.
     */
    UnsignedHugeIntValue& operator-=(const UnsignedHugeIntValue& subtrahend);

    /**
     * @brief Decreases the object's value by the specified unsigned integer amount.
     * This operation changes the value of the object itself. A negative result is not permitted.
     * @param subtrahend Value that will be subtracted from the object's value.
     * @return Reference to the UnsignedHugeIntValue object after its value is changed.
     */
    UnsignedHugeIntValue& operator-=(const unsigned long long subtrahend);

    /**
     * @brief Multiplies the object's value by the specified unsigned integer factor.
     * This operation changes the value of the object itself.
     * @param factor Factor by which the value will be multiplied.
     * @return Reference to the UnsignedHugeIntValue object after its value is changed.
     */
    UnsignedHugeIntValue& operator*=(const UnsignedHugeIntValue& factor);

    /**
     * @brief Multiplies the object's value by the specified unsigned integer factor.
     * This operation changes the value of the object itself.
     * @param factor Factor by which the value will be multiplied.
     * @return Reference to the UnsignedHugeIntValue object after its value is changed.
     */
    UnsignedHugeIntValue& operator*=(const unsigned long long factor);

    /**
     * @brief Divides the object's value by the specified unsigned integer divisor.
     * This operation changes the value of the object itself. The resulting value is the whole number quotient of
     * the original value divided by the divisor.
     * @param divisor Integer by which the value will be divided.
     * @return Reference to the UnsignedHugeIntValue object after its value is changed.
     */
    UnsignedHugeIntValue& operator/=(const UnsignedHugeIntValue& divisor);

    /**
     * @brief Divides the object's value by the specified unsigned integer divisor.
     * This operation changes the value of the object itself. The resulting value is the whole number quotient of
     * the original value divided by the divisor.
     * @param divisor Integer by which the value will be divided.
     * @return Reference to the UnsignedHugeIntValue object after its value is changed.
     */
    UnsignedHugeIntValue& operator/=(const unsigned long long divisor);

    /**
     * @brief Performs modulus division on the object's value with the given divisor.
     * This operation changes the value of the object itself. The resulting value is the remainder of
     * the original value divided by the divisor.
     * @param divisor Integer by which the value will be divided.
     * @return Reference to the UnsignedHugeIntValue object after its value is changed.
     */
    UnsignedHugeIntValue& operator%=(const UnsignedHugeIntValue& divisor);

    /**
     * @brief Performs modulus division on the object's value with the given divisor.
     * This operation changes the value of the object itself. The resulting value is the remainder of
     * the original value divided by the divisor.
     * @param divisor Integer by which the value will be divided.
     * @return Reference to the UnsignedHugeIntValue object after its value is changed.
     */
    UnsignedHugeIntValue& operator%=(const unsigned long long divisor);

    /**
     * @brief Increments the value of the unsigned integer by 1.
     * This operation changes the value of the object itself.
     * @return Reference to the UnsignedHugeIntValue object after its value is changed.
     */
    UnsignedHugeIntValue& operator++();

    /**
     * @brief Decrements the value of the unsigned integer by 1.
     * This operation changes the value of the object itself.
     * @return Reference to the UnsignedHugeIntValue object after its value is changed.
     */
    UnsignedHugeIntValue& operator--();

    /**
     * @brief Returns the result of a bitwise AND operation between two unsigned integers.
     * @param operand Value that will be used in a bitwise AND operation.
     * @return The result of the bitwise AND between the two arguments.
     */
    UnsignedHugeIntValue operator&(const UnsignedHugeIntValue& operand) const;

    /**
     * @brief Returns the result of a bitwise AND operation between two unsigned integers.
     * @param operand Value that will be used in a bitwise AND operation.
     * @return The result of the bitwise AND between the two arguments.
     */
    UnsignedHugeIntValue operator&(unsigned long long operand) const;

    /**
     * @brief Replaces this value with the result of a bitwise AND operation with the operand.
     * This operation changes the value of the object itself.
     * @param addend Value that will be used in a bitwise AND operation with the original value.
     * @return Reference to the UnsignedHugeIntValue object after its value is changed.
     */
    UnsignedHugeIntValue& operator&=(const UnsignedHugeIntValue& operand);

    /**
     * @brief Replaces this value with the result of a bitwise AND operation with the operand.
     * This operation changes the value of the object itself.
     * @param addend Value that will be used in a bitwise AND operation with the original value.
     * @return Reference to the UnsignedHugeIntValue object after its value is changed.
     */
    UnsignedHugeIntValue& operator&=(unsigned long long operand);

    /**
     * @brief Returns the result of a bitwise OR operation between two unsigned integers.
     * @param operand Value that will be used in a bitwise OR operation.
     * @return The result of the bitwise OR between the two arguments.
     */
    UnsignedHugeIntValue operator|(const UnsignedHugeIntValue& operand) const;

    /**
     * @brief Returns the result of a bitwise OR operation between two unsigned integers.
     * @param operand Value that will be used in a bitwise OR operation.
     * @return The result of the bitwise OR between the two arguments.
     */
    UnsignedHugeIntValue operator|(unsigned long long operand) const;

    /**
     * @brief Replaces this value with the result of a bitwise OR operation with the operand.
     * This operation changes the value of the object itself.
     * @param addend Value that will be used in a bitwise OR operation with the original value.
     * @return Reference to the UnsignedHugeIntValue object after its value is changed.
     */
    UnsignedHugeIntValue& operator|=(const UnsignedHugeIntValue& operand);

    /**
     * @brief Replaces this value with the result of a bitwise OR operation with the operand.
     * This operation changes the value of the object itself.
     * @param addend Value that will be used in a bitwise OR operation with the original value.
     * @return Reference to the UnsignedHugeIntValue object after its value is changed.
     */
    UnsignedHugeIntValue& operator|=(unsigned long long operand);

    /**
     * @brief Returns the result of a bitwise XOR operation between two unsigned integers.
     * @param operand Value that will be used in a bitwise XOR operation.
     * @return The result of the bitwise XOR between the two arguments.
     */
    UnsignedHugeIntValue operator^(const UnsignedHugeIntValue& operand) const;

    /**
     * @brief Returns the result of a bitwise XOR operation between two unsigned integers.
     * @param operand Value that will be used in a bitwise XOR operation.
     * @return The result of the bitwise XOR between the two arguments.
     */
    UnsignedHugeIntValue operator^(unsigned long long operand) const;

    /**
     * @brief Replaces this value with the result of a bitwise XOR operation with the operand.
     * This operation changes the value of the object itself.
     * @param addend Value that will be used in a bitwise XOR operation with the original value.
     * @return Reference to the UnsignedHugeIntValue object after its value is changed.
     */
    UnsignedHugeIntValue& operator^=(const UnsignedHugeIntValue& operand);

    /**
     * @brief Replaces this value with the result of a bitwise XOR operation with the operand.
     * This operation changes the value of the object itself.
     * @param addend Value that will be used in a bitwise XOR operation with the original value.
     * @return Reference to the UnsignedHugeIntValue object after its value is changed.
     */
    UnsignedHugeIntValue& operator^=(unsigned long long operand);

    /**
     * @brief Returns the result of a bitwise NOT operation over the specified number of bits.
     * The NOT operation will be applied to the rightmost (least significant) bits of the value,
     * and any bit left of the specified number of bits will be completely ignored.
     * @param number_of_bits The number of bits of the value that are considered.
     * @return The result of the bitwise NOT operation.
     */
    UnsignedHugeIntValue bitwise_not(unsigned long long number_of_bits) const;

    /**
     * @brief Returns the result of a bitwise left shift operation.
     * @param number_of_bits Number of bits by which to shift the value.
     * @return The result of the bitwise left shift operation.
     */
    UnsignedHugeIntValue operator<<(unsigned long long number_of_bits) const;

    /**
     * @brief Replaces this value with the result of a bitwise left shift operation.
     * This operation changes the value of the object itself.
     * @param number_of_bits Number of bits by which to shift the value.
     * @return Reference to the UnsignedHugeIntValue object after its value is changed.
     */
    UnsignedHugeIntValue& operator<<=(unsigned long long number_of_bits);

    /**
     * @brief Returns the result of a bitwise right shift operation.
     * @param number_of_bits Number of bits by which to shift the value.
     * @return The result of the bitwise right shift operation.
     */
    UnsignedHugeIntValue operator>>(unsigned long long number_of_bits) const;

    /**
     * @brief Replaces this value with the result of a bitwise right shift operation.
     * This operation changes the value of the object itself.
     * @param number_of_bits Number of bits by which to shift the value.
     * @return Reference to the UnsignedHugeIntValue object after its value is changed.
     */
    UnsignedHugeIntValue& operator>>=(unsigned long long number_of_bits);

    /**
     * @brief Returns the result of a bitwise left shift operation that inserts 1 bits from the right.
     * @param number_of_bits Number of bits by which to shift the value.
     * @return The result of the bitwise left shift operation.
     */
    UnsignedHugeIntValue left_ones_shifted(unsigned long long number_of_bits) const;

    /**
     * @brief Replaces this value with the result of a bitwise left shift operation that inserts 1 bits from the right.
     * This operation changes the value of the object itself.
     * @param number_of_bits Number of bits by which to shift the value.
     * @return Reference to the UnsignedHugeIntValue object after its value is changed.
     */
    UnsignedHugeIntValue& left_ones_shift_transform(unsigned long long number_of_bits);

    /**
     * @brief Returns the number of words that make up the UnsignedHugeIntValue object.
     * @return The number of words in the object.
     */
    long num_words() const;

    /**
     * @brief Returns the value of this UnsignedHugeIntValue object as a string.
     * @return The value of this object as a string of digits.
     */
    std::string to_string() const;

protected:
    // Protected Methods

    /**
     * @brief Sets the value of this object to the unsigned integer given in the argument.
     * It is assumed that this object does not have any already defined words.
     * @param integer_string A string of the digits that will be converted to an unsigned integer.
     */
    void set_value_from_string(std::string integer_string);

    /**
     * @brief Removes and deletes the most significant words of this object if the words have a value of 0.
     */
    void remove_extra_leading_words();

private:
    // The type used for the word (segment) values in a huge integer.
    using WordType = uint32_t;

    // Holds all of the word (value segment) values.
    std::vector<WordType> *word_values = NULL;

    // The number of bits used to store each word value of an UnsignedHugeInt.
    static constexpr unsigned int bits_per_word = 32;

    // The base value for the words of UnsignedHugeInt.
    // This value must be 2 raised to the power of BITS_PER_WORD.
    static constexpr uint64_t word_base_value = 4294967296;

    // The largest possible value of one word of an UnsignedHugeInt value.
    // This value must be one less than WORD_BASE_VALUE.
    static constexpr WordType max_word_value = 4294967295;

    // Private Methods

    /**
     * @brief Creates a new UnsignedHugeIntValue object with the provided word values.
     * The provided vector should have nonzero length.
     * This constructor is intended for use within functions of this same class. It avoids use of a default vector object.
     * @param word_values_vector Heap-allocated non-null vector of word values.
     */
    UnsignedHugeIntValue(std::vector<WordType>* word_values_vector);

    /**
     * @brief Adds a specified value at a specified word index of this UnsignedHugeIntValue.
     * The next more significant words of this object may be changed because of carry values.
     * @param location_to_add Iterator to the word at which the value will be added. This word will be changed.
     * @param value_to_add Value that will be added to the specified word.
     */
    void add_value_at_word(std::vector<WordType>::iterator location_to_add, const UnsignedHugeIntValue& value_to_add);

    /**
     * @brief Adds a specified value at a specified word index of this UnsignedHugeIntValue.
     * The next more significant words of this object may be changed because of carry values.
     * @param location_to_add Iterator to the word at which the value will be added. This word will be changed.
     * @param value_to_add Value that will be added to the specified word.
     */
    void add_value_at_word(std::vector<WordType>::iterator location_to_add, unsigned long long value_to_add);

    /**
     * @brief Removes the highest indexed elements of the vector if they have a value of 0.
     * @param word_values Vector of word values that is to be trimmed of extra leading 0 values.
     */
    static void remove_extra_leading_words_from(std::vector<WordType>* word_values);

    /**
     * @brief The subtotal from multiplying words of two factors toward one place value of the product is added at that place value.
     * This is a helper function called by the multiply_many_words() method to find the value at one word of the product.
     * The subproducts are found for corresponding factor words and added directly into the product.
     * It is assumed that the result vector already has a size large enough to hold the full product.
     * @param greater_factor_iterator Iterator to the most significant word of a scan for the first factor.
     * @param lesser_factor_iterator Iterator to the least significant word of a scan for the second factor.
     * @param insert_location Iterator to the place value (word location) where the subproducts are added.
     * @param number_of_multiplications Number of pairs of words that will be multiplied to find this subtotal.
     */
    static void insert_multiplication_subtotal(std::vector<WordType>::const_reverse_iterator greater_factor_iterator,
                                               std::vector<WordType>::const_iterator lesser_factor_iterator,
                                               const std::vector<WordType>::iterator& insert_location,
                                               unsigned long long number_of_multiplications);

    /**
     * @brief Multiplies an UnsignedHugeIntValue object by an unsigned integer that is small enough to fit within one word of UnsignedHugeIntValue.
     * This method does not check the size of the integer. This method is more efficient than the multiply() method
     * for cases in which the small_factor is less than the base of the UnsignedHugeIntValue words.
     * @param large_factor The UnsignedHugeIntValue factor of the multiplication.
     * @param small_factor An unsigned integer factor with a value less than the base of the UnsignedHugeIntValue words.
     * @return The result from multiplying the integers as an UnsignedHugeIntValue object.
     */
    static UnsignedHugeIntValue multiply_single_word(const UnsignedHugeIntValue& large_factor, WordType small_factor);

    /**
     * @brief Multiplies this object by an unsigned integer that is small enough to fit within one word of UnsignedHugeIntValue.
     * The value represented by this object will be changed to the product of its starting value and the provided argument.
     * This method is more efficient than the other muliplication methods of this class for cases in which the small_factor is
     * less than the base of the UnsignedHugeIntValue words.
     * @param small_factor An unsigned integer factor with a value less than the base of the UnsignedHugeIntValue words.
     * @return Reference to this object after the value was changed from the multiplication.
     */
    UnsignedHugeIntValue& multiply_single_word_transform(WordType small_factor);

    /**
     * @brief Multiplies two unsigned integers to produce an UnsignedHugeIntValue object.
     * It is assumed that each of the two factors has more than one word.
     * @param factorA One of the integer factors of the multiplication.
     * @param factorB One of the integer factors of the multiplication.
     * @return The result of multiplication as an unsigned integer.
     */
    static UnsignedHugeIntValue multiply_many_words(const UnsignedHugeIntValue& factorA, const UnsignedHugeIntValue& factorB);

    /**
     * @brief Divides an UnsignedHugeIntValue object by an unsigned integer that is small enough to fit within one word of UnsignedHugeIntValue.
     * This method expects a divisor with a value less than the word base value, but it does not check the size of the divisor.
     * If the divisor is greater than the maximum word size, incorrect values may be produced. Division using this method is
     * somewhat simpler and faster than division by an UnsignedHugeIntValue, so this method should be used for division whenever
     * the divisor is small enough.
     * @param dividend The dividend of the division operation.
     * @param divisor The divisor of the division operation, which must be less than the word base value.
     * @return The whole number quotient (first) and remainder (second) results of the division operation.
     */
    static std::pair<UnsignedHugeIntValue, UnsignedHugeIntValue::WordType> divide_single_word_divisor(
            const UnsignedHugeIntValue& dividend, WordType divisor);

    /**
     * @brief Divides this UnsignedHugeIntValue object by an unsigned integer that is small enough to fit within one word of UnsignedHugeIntValue.
     * This method expects a divisor with a value less than the word base value, but it does not check the size of the divisor.
     * If the divisor is greater than the maximum word size, incorrect values may be produced. Division using this method is
     * somewhat simpler and faster than division by an UnsignedHugeIntValue, so this method should be used for division whenever
     * the divisor is small enough.
     * The value represented by this object will be changed to the whole number quotient of its starting value and the provided argument.
     * @param divisor The divisor of the division operation, which must be less than the word base value.
     * @return The remainder of the division operation.
     */
    UnsignedHugeIntValue::WordType divide_single_word_divisor_transform(WordType divisor);

    /**
     * @brief Divides UnsignedHugeIntValue objects, where the divisor is not small enough to fit within one word of UnsignedHugeIntValue.
     * This method expects a divisor with a value greater than the maximum word value, but it does not check the size of the divisor.
     * If the divisor is less than the maximum word base value, incorrect values may be produced.
     * @param dividend The dividend of the division operation.
     * @param divisor The divisor of the division operation, which must be greater than or equal to the word base value.
     * @return The whole number quotient (first) and remainder (second) results of the division operation.
     */
    static std::pair<UnsignedHugeIntValue, UnsignedHugeIntValue> divide_many_word_divisor(const UnsignedHugeIntValue& dividend, const UnsignedHugeIntValue& divisor);

    /**
     * @brief Returns true only if the remainder segment is greater than or equal to the divisor.
     * This is a helper function for divide_many_word_divisor().
     * It is assumed that the remainder segment has the same number of words as the divisor.
     * @param remainder_iterator Points to the most significant word of the remainder to check.
     * @param divisor_words The words of the divisor.
     * @return false if the divisor is less than the remainder, otherwise returns true.
     */
    static bool is_remainder_too_large(std::vector<WordType>::reverse_iterator remainder_iterator,
                                    const std::vector<WordType>* divisor_words);

    /**
     * @brief Subtracts from the cooresponding remainder word values.
     * This is a helper function for divide_many_word_divisor().
     * It is assumed that the subtrahend is less than the remainder segment, and this is not checked.
     * @param remainder_iterator Points to the least significant word of the remainder segment to subtract from.
     * @param subtrahend The value that will be subtracted from the remainder segment.
     */
    static void subtract_from_remainder(std::vector<WordType>::iterator remainder_iterator,
                                      const UnsignedHugeIntValue& subtrahend);
};

// Operators involving UnsignedHugeIntValue, but not considered part of UnsignedHugeIntValue by the compiler.

/**
 * @brief Outputs the value of the UnsignedHugeIntValue object to the stream as a string.
 * @param out_stream The stream that receives the string form of the UnsignedHugeIntValue object.
 * @param huge_int_object The object whose value is output to the stream.
 */
std::ostream& operator<<(std::ostream& out_stream, const UnsignedHugeIntValue& huge_int_object);
