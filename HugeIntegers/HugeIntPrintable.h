#pragma once

#include <cstdint>
#include <fstream>
#include <iostream>
#include <string.h>
#include <sys/stat.h>
#include <vector>

// Holds a huge integer in a form that is easy to print as a string in base 10.
// Changing the value of an object after it is created is not supported.
class HugeIntPrintable {
    friend class UnsignedHugeIntValue;
public:
    /**
     * @brief Creates a new object with the value given in the parameter.
     * The string parameter should have only the digits of the integer value.
     * @param integer_string Value for the new object as a string of digits.
     */
    HugeIntPrintable(const std::string integer_string);

    /**
     * @brief Creates a new object with the value given in the parameter.
     * The string parameter should have only the digits of the integer value.
     * @param integer_string Value for the new object as a string of digits.
     */
    HugeIntPrintable(const char* integer_string);

    /**
     * @brief Creates a copy of the given printable integer.
     * @param orig Object to be copied.
     */
    HugeIntPrintable(const HugeIntPrintable& orig);

    /**
     * @brief Creates a new object with a value moved from the argument.
     * The value does not not exist in the original argument object after this operation.
     * @param orig Object whose value will be moved.
     */
    HugeIntPrintable(HugeIntPrintable&& orig) noexcept;

    /**
     * @brief Deletes the HugeIntPrintable object completely.
     */
    virtual ~HugeIntPrintable();

    /**
     * @brief Returns the number of base 10 digits in the value.
     * @return The number of base 10 digits in the value.
     */
    unsigned long long number_of_digits() const;

    /**
     * @brief Returns the number of base 10 digits in the value.
     * @return The number of base 10 digits in the value.
     */
    unsigned long long length() const;

    /**
     * @brief Creates a HugeIntPrintable object from the integer in the text file.
     * The file should contain digits for only a single integer, as the
     * entire file is scanned to set the value of this object.
     * @param file_path The path of a file containing an integer value.
     * @return A new object with the value of the integer in the text file.
     */
    static HugeIntPrintable read_from_text_file(std::string file_path);

    /**
     * @brief Creates a HugeIntPrintable object from the integer in the text file.
     * The file should contain digits for only a single integer, as the
     * entire file is scanned to set the value of this object.
     * @param file_path The path of a file containing an integer value.
     * @return A new object with the value of the integer in the text file.
     */
    static HugeIntPrintable read_from_text_file(FILE* integer_file);

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
     * @brief Reads and recreates a HugeIntPrintable object from a binary file.
     * The file should be one created by the write_to_binary_file method
     * of HugeIntPrintable. Portability of the binary files is not guaranteed.
     * @param file_path The file path, including the file name, of the binary file containing a HugeIntPrintable object.
     * @return A HugeIntPrintable object read from the binary file.
     */
    static HugeIntPrintable read_from_binary_file(std::string file_path);

    /**
     * @brief Writes the value from this object to a new binary file.
     * The file must not already exist. The binary file can be read by the read_from_binary_file method of HugeIntPrintable.
     * Portability of the binary files is not guaranteed.
     * @param file_path The destination path, including the file name, of the binary file to be written.
     */
    void write_to_binary_file(std::string file_path) const;

    /**
     * @brief Converts the value of this object to a C++ string.
     */
    operator std::string() const;


protected:
    // The type used for the word (segment) values in a huge integer.
    using WordType = uint32_t;

    // The number of digits stored in each word of an object.
    static constexpr unsigned int digits_per_word = 9;

    // The base value for the words of HugeIntPrintable.
    // This value must be 10 raised to the power of digits_per_word.
    static constexpr WordType word_base_value = 1000000000;

    // The largest possible value of one word of a HugeIntPrintable value.
    // This value must be one less than word_base_value.
    static constexpr WordType max_word_value = 999999999;

    // Protected Methods

    /**
     * @brief Creates a HugeIntPrintable object with a blank value.
     * This constructor should normally not be used.
     */
    HugeIntPrintable();

    /**
     * @brief Creates a new HugeIntPrintable object with the provided word values.
     * The provided vector should have nonzero length.
     * This constructor is intended for use within functions of friend classes.
     * This constructor avoids use of a default vector object.
     * @param word_values_vector Heap-allocated non-null vector of word values.
     */
    HugeIntPrintable(std::vector<WordType>* word_values_vector);

private:
    // Holds all of the word (value segment) values.
    std::vector<WordType> *word_values;

    // Determines whether this is a negative integer.
    bool is_negative = false;
};

// Operators involving HugeIntPrintable, but not considered part of HugeIntPrintable by the compiler.

/**
 * @brief Outputs the value of the HugeIntPrintable object to the stream as a string.
 * @param out_stream The stream that receives the string form of the HugeIntPrintable object.
 * @param huge_int_object The object whose value is output to the stream.
 */
std::ostream& operator<<(std::ostream& out_stream, const HugeIntPrintable& huge_int_object);
