/* 
 * File:   UnsignedHugeInt.h
 * Author: William Boyd
 *
 * Created on December 26, 2019, 11:54 AM
 */

#pragma once

#include <iostream>

class UnsignedHugeIntValue;

class UnsignedHugeInt {
public:
    // Public Methods
    
    /**
     * @brief Creates a new UnsignedHugeInt object with a value of 0.
     */
    UnsignedHugeInt();

    /**
     * @brief Creates a new UnsignedHugeInt object with the value given in the parameter.
     * The parameter must be an unsigned integer that can be managed by the computer. If the integer is too large to
     * use as an argument, a string parameter should be used instead.
     * @param value Unsigned integer value for the initial value of the UnsignedHugeInt object.
     */
    UnsignedHugeInt(const unsigned long long value);

    /**
     * @brief Creates a new UnsignedHugeInt object with the value given in the parameter.
     * The string parameter should have only the digits of the integer value.
     * @param integer_string Initial value of the UnsignedHugeInt object as a string of digits.
     */
    UnsignedHugeInt(const std::string integer_string);

    /**
     * @brief Creates a new UnsignedHugeInt object with the value given in the parameter.
     * The string parameter should have only the digits of the integer value.
     * @param integer_string Initial value of the UnsignedHugeInt object as a string of digits.
     */
    UnsignedHugeInt(const char* integer_string);

    /**
     * @brief Creates a new UnsignedHugeInt object as a copy of the argument.
     * @param orig Object whose value is to be copied.
     */
    UnsignedHugeInt(const UnsignedHugeInt& orig);

    /**
     * @brief Creates a new UnsignedHugeInt object as a copy of the object referred to by the argument.
     * @param orig Pointer to the object whose value is to be copied.
     */
    UnsignedHugeInt(const UnsignedHugeInt* orig);
    
    /**
     * @brief Creates a new UnsignedHugeInt object with a value moved from the argument.
     * The value does not not exist in the original argument object after this operation.
     * @param orig Object whose value will be moved.
     */
    UnsignedHugeInt(UnsignedHugeInt&& orig);
    
    /**
     * @brief Deletes the UnsignedHugeInt object completely.
     */
    virtual ~UnsignedHugeInt();
    
    /**
     * @brief Sets the value of this UnsignedHugeInt object to the integer in the text file.
     * The file should contain digits for only a single integer, as the entire file is scanned to 
     * set the value of this object.
     * @param file_path The path of a file containing an unsigned integer value.
     */
    void read_from_text_file(std::string file_path);
    
    /**
     * @brief Sets the value of this UnsignedHugeInt object to the integer in the text file.
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
     * The file should be one created by the write_to_binary_file method of UnsignedHugeInt. Portability of the binary files
     * is not guaranteed.
     * @param file_path The file path, including the file name, of the binary file containing the value of an UnsignedHugeInt.
     */
    void read_from_binary_file(std::string file_path);
    
    /**
     * @brief Writes the value from this object to a new binary file.
     * The file must not already exist. The binary file can be read by the read_from_binary_file method of UnsignedHugeInt.
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
     * @param orig An UnsignedHugeInt object with a value that will be copied.
     * @return Reference to the newly created object.
     */
    UnsignedHugeInt& operator=(const UnsignedHugeInt& orig);

    /**
     * @brief Assigns a copy of the right-hand value to the object on the left of the assignment operator.
     * This operation does not change the right-hand value or objects.
     * @param orig A pointer to an UnsignedHugeInt object with a value that will be copied.
     * @return Reference to the newly created object.
     */
    UnsignedHugeInt& operator=(const UnsignedHugeInt* orig);
    
    /**
     * @brief Moves value from the argument to this object, removing the the value from the argument.
     * @param orig Object whose value will be moved.
     * @return Reference to the new object which received the value.
     */
    UnsignedHugeInt& operator=(UnsignedHugeInt&& orig);

    /**
     * @brief Assigns the value from the right-hand side of the assignment operator to the object on the left of the operator.
     * It is assumed that only non-negative value will be assigned. To assign a value that is too large for the
     * unsigned long long type, a numerical string (such as "9874390745") can be used on the right-hand side of the operator.
     * @param value The value to assign to the UnsignedHugeInt object.
     * @return Reference to the newly created object.
     */
    UnsignedHugeInt& operator=(const unsigned long long value);
    
    /**
     * @brief Reads a numerical string as an unsigned integer and assigns the value to the UnsignedHugeInt object.
     * The string should contain only digits. This assignment operation can be used to assign values that are too
     * large to be processed directly.
     * @param value_string A C++ string of the value to assign to the UnsignedHugeInt object.
     * @return Reference to the newly created object.
     */
    UnsignedHugeInt& operator=(const std::string value_string);
    
    /**
     * @brief Reads a numerical string as an unsigned integer and assigns the value to the UnsignedHugeInt object.
     * The string should contain only digits. This assignment operation can be used to assign values that are too
     * large to be processed directly.
     * @param value_string A C string of the value to assign to the UnsignedHugeInt object.
     * @return Reference to the newly created object.
     */
    UnsignedHugeInt& operator=(const char* value_string);

    /**
     * @brief Determines which of the two numbers is greater.
     * @param numberA One of the numbers to compare.
     * @param numberB One of the numbers to compare.
     * @return 1 if numberA is greater; 0 if the numbers are equal; -1 if numberB is greater.
     */
    static short compare(const UnsignedHugeInt& numberA, const UnsignedHugeInt& numberB);
    
    // Returns true only if the left operand is less than the right operand.
    bool operator<(const UnsignedHugeInt& right_operand) const;

    // Returns true only if the left operand is less than the right operand.
    bool operator<(const unsigned long long right_operand) const;

    // Returns true only if the left operand is less than the right operand.
    friend bool operator<(const unsigned long long left_operand, const UnsignedHugeInt& right_operand);

    // Returns true only if the left operand is less than or equal to the right operand.
    bool operator<=(const UnsignedHugeInt& right_operand) const;

    // Returns true only if the left operand is less than or equal to the right operand.
    bool operator<=(const unsigned long long right_operand) const;

    // Returns true only if the left operand is less than or equal to the right operand.
    friend bool operator<=(const unsigned long long left_operand, const UnsignedHugeInt& right_operand);

    // Returns true only if the left operand is greater than the right operand.
    bool operator>(const UnsignedHugeInt& right_operand) const;

    // Returns true only if the left operand is greater than the right operand.
    bool operator>(const unsigned long long right_operand) const;

    // Returns true only if the left operand is greater than the right operand.
    friend bool operator>(const unsigned long long left_operand, const UnsignedHugeInt& right_operand);

    // Returns true only if the left operand is greater than or equal to the right operand.
    bool operator>=(const UnsignedHugeInt& right_operand) const;

    // Returns true only if the left operand is greater than or equal to the right operand.
    bool operator>=(const unsigned long long right_operand) const;

    // Returns true only if the left operand is greater than or equal to the right operand.
    friend bool operator>=(const unsigned long long left_operand, const UnsignedHugeInt& right_operand);

    // Returns true only if the two operands have the same value.
    bool operator==(const UnsignedHugeInt& right_operand) const;

    // Returns true only if the two operands have the same value.
    bool operator==(const unsigned long long right_operand) const;

    // Returns true only if the two operands have the same value.
    friend bool operator==(const unsigned long long left_operand, const UnsignedHugeInt& right_operand);

    // Returns true only if the two operands do not have the same value.
    bool operator!=(const UnsignedHugeInt& right_operand) const;

    // Returns true only if the two operands do not have the same value.
    bool operator!=(const unsigned long long right_operand) const;

    // Returns true only if the two operands do not have the same value.
    friend bool operator!=(const unsigned long long left_operand, const UnsignedHugeInt& right_operand);

    /**
     * @brief Returns the sum of the two unsigned integers.
     * @param addendA One of the two unsigned integers to be added.
     * @param addendB One of the two unsigned integers to be added.
     * @return The result of adding the two arguments.
     */
    static UnsignedHugeInt sum_of(const UnsignedHugeInt& addendA, const UnsignedHugeInt& addendB);

    /**
     * @brief Returns the sum of the two unsigned integers.
     * @param addendA One of the two unsigned integers to be added.
     * @param addendB One of the two unsigned integers to be added.
     * @return The result of adding the two arguments.
     */
    static UnsignedHugeInt sum_of(const UnsignedHugeInt& addendA, const unsigned long long addendB);

    /**
     * @brief Returns the sum of the two unsigned integers.
     * @param addend The integer on the right-hand side of the '+' operator.
     * @return The result of adding the two integer values.
     */
    UnsignedHugeInt operator+(const UnsignedHugeInt& addend) const;

    /**
     * @brief Returns the sum of the two unsigned integers.
     * @param addend The integer on the right-hand side of the '+' operator.
     * @return The result of adding the two integer values.
     */
    UnsignedHugeInt operator+(const unsigned long long addend) const;

    /**
     * @brief Returns the sum of the two unsigned integers.
     * @param addendA The integer on the left side of the '+' operator.
     * @param addendB The integer on the right-hand side of the '+' operator.
     * @return The result of adding the two integer values.
     */
    friend UnsignedHugeInt operator+(const unsigned long long addendA, const UnsignedHugeInt& addendB);

    /**
     * @brief Subtracts two unsigned integers to produce an UnsignedHugeInt object.
     * The minuend is not permitted to have a lower value than the subtrahend.
     * @param minuend The integer from which a value is subtracted (the larger operand).
     * @param subtrahend The amount that is subtracted from the minuend.
     * @return The result of subtraction as an unsigned integer.
     */
    static UnsignedHugeInt subtract(const UnsignedHugeInt& minuend, const UnsignedHugeInt& subtrahend);

    /**
     * @brief Subtracts two unsigned integers to produce an UnsignedHugeInt object.
     * The minuend is not permitted to have a lower value than the subtrahend.
     * @param subtrahend The integer on the right-hand side of the '-' operator (the smaller operand).
     * @return The result of subtraction as an unsigned integer.
     */
    UnsignedHugeInt operator-(const UnsignedHugeInt& subtrahend) const;

    /**
     * @brief Subtracts two unsigned integers to produce an UnsignedHugeInt object.
     * The minuend is not permitted to have a lower value than the subtrahend.
     * @param subtrahend The integer on the right-hand side of the '-' operator (the smaller operand).
     * @return The result of subtraction as an unsigned integer.
     */
    UnsignedHugeInt operator-(const unsigned long long subtrahend) const;

    /**
     * @brief Subtracts two unsigned integers to produce an UnsignedHugeInt object.
     * The minuend is not permitted to have a lower value than the subtrahend.
     * @param minuend The integer on the left side of the '-' operator.
     * @param subtrahend The integer on the right-hand side of the '-' operator (the smaller operand).
     * @return The result of subtraction as an unsigned integer.
     */
    friend UnsignedHugeInt operator-(const unsigned long long minuend, const UnsignedHugeInt& subtrahend);
    
    /**
     * @brief Multiplies two unsigned integers to produce an UnsignedHugeInt object.
     * @param factorA One of the integer factors of the multiplication.
     * @param factorB One of the integer factors of the multiplication.
     * @return The result of multiplication as an unsigned integer.
     */
    static UnsignedHugeInt multiply(const UnsignedHugeInt& factorA, const UnsignedHugeInt& factorB);

    /**
     * @brief Multiplies two unsigned integers to produce an UnsignedHugeInt object.
     * @param factorA One of the integer factors of the multiplication.
     * @param factorB One of the integer factors of the multiplication.
     * @return The result of multiplication as an unsigned integer.
     */
    UnsignedHugeInt operator*(const UnsignedHugeInt& factor) const;

    /**
     * @brief Multiplies two unsigned integers to produce an UnsignedHugeInt object.
     * @param factor The integer factor on the right-hand side of the '*' operator.
     * @return The result of multiplication as an unsigned integer.
     */
    UnsignedHugeInt operator*(const unsigned long long factor) const;

    /**
     * @brief Multiplies two unsigned integers to produce an UnsignedHugeInt object.
     * @param factorA The integer factor on the left side of the '*' operator.
     * @param factorB The integer factor on the right-hand side of the '*' operator.
     * @return The result of multiplication as an unsigned integer.
     */
    friend UnsignedHugeInt operator*(const unsigned long long factorA, const UnsignedHugeInt& factorB);

    /**
     * @brief Performs integer division on the two unsigned operands, and returns both the quotient and the remainder as a pair.
     * This method is called by both '/' and '%' operators.
     * @param dividend The dividend of the division operation.
     * @param divisor The divisor of the division operation.
     * @return The whole number quotient (first) and remainder (second) results of the division operation.
     */
    static std::pair<UnsignedHugeInt, UnsignedHugeInt> divide(const UnsignedHugeInt& dividend, const UnsignedHugeInt& divisor);

    /**
     * @brief Divides the unsigned integers and returns the whole number quotient result as an UnsignedHugeInt object.
     * @param divisor The divisor of the division operation, on the right-hand side of the '/' operator.
     * @return The whole number quotient of the division operation.
     */
    UnsignedHugeInt operator/(const UnsignedHugeInt& divisor) const;

    /**
     * @brief Divides the unsigned integers and returns the whole number quotient result as an UnsignedHugeInt object.
     * @param divisor The divisor of the division operation, on the right-hand side of the '/' operator.
     * @return The whole number quotient of the division operation.
     */
    UnsignedHugeInt operator/(const unsigned long long divisor) const;

    /**
     * @brief Divides the unsigned integers and returns the whole number quotient result as an UnsignedHugeInt object.
     * @param dividend The dividend of the division operation, on the left side of the '/' operator.
     * @param divisor The divisor of the division operation, on the right-hand side of the '/' operator.
     * @return The whole number quotient of the division operation.
     */
    friend UnsignedHugeInt operator/(const unsigned long long dividend, const UnsignedHugeInt& divisor);

    /**
     * @brief Performs modulus (remainder) division on the unsigned integers.
     * @param divisor The divisor of the division operation, on the right-hand side of the '%' operator.
     * @return The remainder of the division operation.
     */
    UnsignedHugeInt operator%(const UnsignedHugeInt& divisor) const;

    /**
     * @brief Performs modulus (remainder) division on the unsigned integers.
     * @param divisor The divisor of the division operation, on the right-hand side of the '%' operator.
     * @return The remainder of the division operation.
     */
    UnsignedHugeInt operator%(const unsigned long long divisor) const;

    /**
     * @brief Performs modulus (remainder) division on the unsigned integers.
     * @param dividend The dividend of the division operation, on the left side of the '%' operator.
     * @param divisor The divisor of the division operation, on the right-hand side of the '%' operator.
     * @return The remainder of the division operation.
     */
    friend UnsignedHugeInt operator%(const unsigned long long dividend, const UnsignedHugeInt& divisor);

    /**
     * @brief Increases the object's value by the specified unsigned integer amount.
     * This operation changes the value of the object itself.
     * @param addend Value that will be added to the object's value.
     * @return Reference to the UnsignedHugeInt object after its value is changed.
     */
    UnsignedHugeInt& operator+=(const UnsignedHugeInt& addend);

    /**
     * @brief Increases the object's value by the specified unsigned integer amount.
     * This operation changes the value of the object itself.
     * @param addend Value that will be added to the object's value.
     * @return Reference to the UnsignedHugeInt object after its value is changed.
     */
    UnsignedHugeInt& operator+=(const unsigned long long addend);

    /**
     * @brief Decreases the object's value by the specified unsigned integer amount.
     * This operation changes the value of the object itself. A negative result is not permitted.
     * @param subtrahend Value that will be subtracted from the object's value.
     * @return Reference to the UnsignedHugeInt object after its value is changed.
     */
    UnsignedHugeInt& operator-=(const UnsignedHugeInt& subtrahend);

    /**
     * @brief Decreases the object's value by the specified unsigned integer amount.
     * This operation changes the value of the object itself. A negative result is not permitted.
     * @param subtrahend Value that will be subtracted from the object's value.
     * @return Reference to the UnsignedHugeInt object after its value is changed.
     */
    UnsignedHugeInt& operator-=(const unsigned long long subtrahend);

    /**
     * @brief Multiplies the object's value by the specified unsigned integer factor.
     * This operation changes the value of the object itself.
     * @param factor Factor by which the value will be multiplied.
     * @return Reference to the UnsignedHugeInt object after its value is changed.
     */
    UnsignedHugeInt& operator*=(const UnsignedHugeInt& factor);

    /**
     * @brief Multiplies the object's value by the specified unsigned integer factor.
     * This operation changes the value of the object itself.
     * @param factor Factor by which the value will be multiplied.
     * @return Reference to the UnsignedHugeInt object after its value is changed.
     */
    UnsignedHugeInt& operator*=(const unsigned long long factor);

    /**
     * @brief Divides the object's value by the specified unsigned integer divisor.
     * This operation changes the value of the object itself. The resulting value is the whole number quotient of
     * the original value divided by the divisor.
     * @param divisor Integer by which the value will be divided.
     * @return Reference to the UnsignedHugeInt object after its value is changed.
     */
    UnsignedHugeInt& operator/=(const UnsignedHugeInt& divisor);

    /**
     * @brief Divides the object's value by the specified unsigned integer divisor.
     * This operation changes the value of the object itself. The resulting value is the whole number quotient of
     * the original value divided by the divisor.
     * @param divisor Integer by which the value will be divided.
     * @return Reference to the UnsignedHugeInt object after its value is changed.
     */
    UnsignedHugeInt& operator/=(const unsigned long long divisor);

    /**
     * @brief Performs modulus division on the object's value with the given divisor.
     * This operation changes the value of the object itself. The resulting value is the remainder of
     * the original value divided by the divisor.
     * @param divisor Integer by which the value will be divided.
     * @return Reference to the UnsignedHugeInt object after its value is changed.
     */
    UnsignedHugeInt& operator%=(const UnsignedHugeInt& divisor);

    /**
     * @brief Performs modulus division on the object's value with the given divisor.
     * This operation changes the value of the object itself. The resulting value is the remainder of
     * the original value divided by the divisor.
     * @param divisor Integer by which the value will be divided.
     * @return Reference to the UnsignedHugeInt object after its value is changed.
     */
    UnsignedHugeInt& operator%=(const unsigned long long divisor);

    /**
     * @brief Increments the value of the unsigned integer by 1.
     * This operation changes the value of the object itself.
     * @return Reference to the UnsignedHugeInt object after its value is changed.
     */
    UnsignedHugeInt& operator++();

    /**
     * @brief Increments the value of the unsigned integer by 1.
     * This operation changes the value of the object itself.
     * @return A copy of the UnsignedHugeInt object before its value is changed.
     */
    UnsignedHugeInt operator++(int dummy);

    /**
     * @brief Decrements the value of the unsigned integer by 1.
     * This operation changes the value of the object itself.
     * @return Reference to the UnsignedHugeInt object after its value is changed.
     */
    UnsignedHugeInt& operator--();

    /**
     * @brief Decrements the value of the unsigned integer by 1.
     * This operation changes the value of the object itself.
     * @return A copy of the UnsignedHugeInt object before its value is changed.
     */
    UnsignedHugeInt operator--(int dummy);
    
    /**
     * @brief Returns the value of this UnsignedHugeInt object as a string.
     * @return The value of this object as a string of digits.
     */
    std::string to_string() const;
    
private:
    UnsignedHugeIntValue *value;

    /**
     * @brief Creates a new UnsignedHugeInt object with the value copied from the parameter.
     * This constructor is intended for internal use only.
     * @param value Initial value for the UnsignedHugeInt object as an UnsignedHugeIntValue object.
     */
    UnsignedHugeInt(UnsignedHugeIntValue& value);
        
    /**
     * @brief Creates a new UnsignedHugeInt object with a value moved from the argument.
     * The value does not not exist in the original argument object after this operation.
     * This constructor is intended for internal use only.
     * @param value Object whose value will be moved.
     */
    UnsignedHugeInt(UnsignedHugeIntValue&& value);

    /**
     * @brief Creates a new UnsignedHugeInt object with a value moved directly from the argument.
     * This constructor is intended for internal use only.
     * @param value Object whose value will be moved.
     */
    UnsignedHugeInt(UnsignedHugeIntValue* value);

};

// Operators involving UnsignedHugeInt, but not considered part of UnsignedHugeInt by the compiler.

/**
 * @brief Outputs the value of the UnsignedHugeInt object to the stream as a string.
 * @param out_stream The stream that receives the string form of the UnsignedHugeInt object.
 * @param huge_int_object The object whose value is output to the stream.
 */
std::ostream& operator<<(std::ostream& out_stream, const UnsignedHugeInt& huge_int_object);    
