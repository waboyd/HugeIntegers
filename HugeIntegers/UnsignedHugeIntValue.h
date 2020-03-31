#pragma once

#include <fstream>
#include <string.h>
#include <sys/stat.h>

#include "HugeIntWord.h"

#define MAX_DIGITS_PER_WORD 9
#define CHECK_VALUE_A   84340
#define CHECK_VALUE_B   308424
#define READ_BUFFER_SIZE    144
#define BUFFER_NUM_WORDS    16

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
    UnsignedHugeIntValue(UnsignedHugeIntValue&& orig);
    
    /**
     * @brief Deletes the UnsignedHugeIntValue object completely.
     */
    virtual ~UnsignedHugeIntValue();
    
    /**
     * @brief Returns the number of digits in the value.
     * @return The number of digits in the value.
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
    UnsignedHugeIntValue& operator=(UnsignedHugeIntValue&& orig);

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
    static UnsignedHugeIntValue sum_of(const UnsignedHugeIntValue& addendA, const unsigned long long addendB);

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
     * @brief Returns true only if the object has been defined and is not null.
     * @return True if the object is verified as properly defined.
     */
    bool is_defined() const;
    
    /**
     * @brief Returns the number of words that make up the UnsignedHugeIntValue object.
     * @return The number of words in the object.
     */
    long num_words() const;
    
    /**
     * @brief Returns the most significant word of the UnsignedHugeIntValue object.
     * @return The most significant word of the object.
     */
    HugeIntWord* get_most_significant_word() const;

    /**
     * @brief Returns the least significant word of the UnsignedHugeIntValue object.
     * @return The least significant word of the object.
     */
    HugeIntWord* get_least_significant_word() const;

    /**
     * @brief Removes and deletes the most significant word of the UnsignedHugeIntValue object.
     * @return The most significant word of the object after the change.
     */
    HugeIntWord* remove_most_significant_word();
    
    /**
     * @brief Returns the value of this UnsignedHugeIntValue object as a string.
     * @return The value of this object as a string of digits.
     */
    std::string to_string() const;
    
protected:
    // The maximum value that is permitted in one word of UnsignedHugeIntValue.
    static unsigned long max_word_value;
    
    // The base value for a word of UnsignedHugeIntValue. Each word represents a power of the word base.
    static unsigned long long word_base;

    // Protected Methods
    
    /**
     * @brief Changes this object to a copy of the of the object in the argument.
     * It is assumed that this object does not have any already defined words.
     * @param orig The original object that will be copied.
     */
    void change_to_copy_of(const UnsignedHugeIntValue& orig);
    
    /**
     * @brief Sets the value of this object to the unsigned integer given in the argument.
     * It is assumed that this object does not have any already defined words.
     * @param integer_string A string of the digits that will be converted to an unsigned integer.
     */
    void set_value_from_string(std::string integer_string);
    
    /**
     * @brief Removes and deletes all words from this object.
     */
    void delete_all_words();
    
    /**
     * @brief Removes and deletes the most significant words of this object if the words have a value of 0.
     */
    void remove_extra_leading_words();
    
    /**
     * @brief Adds a new most significant word with a value of 0.
     * @return Pointer to the new word that was added.
     */
    HugeIntWord* add_word();
    
    /**
     * @brief Adds new most significant words with a total value given in the parameter.
     * @return Pointer to the most significant new word that was added.
     */
    HugeIntWord* add_word(const unsigned long long value);

    /**
     * @brief Adds the word given in the parameter as the new most significant word.
     * @return Pointer to the new word that was added.
     */
    HugeIntWord* add_word(HugeIntWord* new_word);
    
    /**
     * @brief Changes this number by inserting a new least significant word with the given value.
     * @param least_significant_value The value of the new least significant word to be added.
     * @return The least significant word of this number.
     */
    HugeIntWord* insert_least_significant_word(unsigned long least_significant_value);

private:
    HugeIntWord *leastSigWord, *mostSigWord;
    
    // Integers that are set to specific values when defined.
    int defined_key_1, defined_key_2;
    
    // Private Methods

    /**
     * @brief Adds a specified value at a specified word of this UnsignedHugeIntValue.
     * @param location_to_add Word at which the value will be added. This word will be changed.
     * @param value_to_add Number that will be added to the specified word.
     * @return The least significant word that was updated.
     */
    HugeIntWord* add_value_at_word(HugeIntWord* location_to_add, const UnsignedHugeIntValue& value_to_add);
    
    /**
     * @brief Creates a new UnsignedHugeIntValue object using the argument and its linked more significant words.
     * @param least_significant_word An existing word that will be copied as the least significant word of the new UnsignedHugeIntValue.
     * @return The new UnsignedHugeIntValue object.
     */
    static UnsignedHugeIntValue integer_with_least_significant_word(const HugeIntWord* least_significant_word);
    
    /**
     * @brief For a multiplication operation, the subtotal from multiplying words toward one word of the product is found.
     * This method is called by the multiply() method to find the value at one word of the product.
     * @param greater_factor_word Most significant word of a scan for the first factor.
     * @param lesser_factor_word Least significant word of a scan for the second factor.
     * @return The subtotal for one word of the product of the two factors.
     */
    static UnsignedHugeIntValue find_multiplication_subtotal(const HugeIntWord* greater_factor_word, const HugeIntWord* lesser_factor_word);
    
    /**
     * @brief Multiplies an UnsignedHugeIntValue object by an unsigned integer that is small enough to fit within one word of UnsignedHugeIntValue.
     * This method does not check the size of the integer. This method is more efficient than the multiply() method
     * for cases in which the small_factor is less than the base of the UnsignedHugeIntValue words.
     * @param large_factor The UnsignedHugeIntValue factor of the multiplication.
     * @param small_factor An unsigned integer factor with a value less than the base of the UnsignedHugeIntValue words.
     * @return The result from multiplying the integers as an UnsignedHugeIntValue object.
     */
    static UnsignedHugeIntValue multiply_single_word(const UnsignedHugeIntValue& large_factor, const unsigned long long small_factor);
};

// Operators involving UnsignedHugeIntValue, but not considered part of UnsignedHugeIntValue by the compiler.

/**
 * @brief Outputs the value of the UnsignedHugeIntValue object to the stream as a string.
 * @param out_stream The stream that receives the string form of the UnsignedHugeIntValue object.
 * @param huge_int_object The object whose value is output to the stream.
 */
std::ostream& operator<<(std::ostream& out_stream, const UnsignedHugeIntValue& huge_int_object);    
