#include "UnsignedHugeInt.h"
#include "UnsignedHugeIntValue.h"

UnsignedHugeInt::UnsignedHugeInt() {
    this->value = new UnsignedHugeIntValue();
}

UnsignedHugeInt::UnsignedHugeInt(const unsigned long long value) {
    this->value = new UnsignedHugeIntValue(value);
}

UnsignedHugeInt::UnsignedHugeInt(const std::string integer_string) {
    this->value = new UnsignedHugeIntValue(integer_string);
}

UnsignedHugeInt::UnsignedHugeInt(const char* integer_string) {
    std::string cppIntegerString(integer_string);
    this->value = new UnsignedHugeIntValue(cppIntegerString);
}

UnsignedHugeInt::UnsignedHugeInt(const UnsignedHugeInt& orig) {
    this->value = new UnsignedHugeIntValue(orig.value);
}

UnsignedHugeInt::UnsignedHugeInt(const UnsignedHugeInt* orig) {
    this->value = new UnsignedHugeIntValue(orig->value);
}

UnsignedHugeInt::UnsignedHugeInt(UnsignedHugeInt&& orig) {
    this->value = orig.value;
    orig.value = NULL;
}

UnsignedHugeInt::UnsignedHugeInt(UnsignedHugeIntValue& value) {
    this->value = new UnsignedHugeIntValue(value);
}

UnsignedHugeInt::UnsignedHugeInt(UnsignedHugeIntValue&& value) {
    this->value = new UnsignedHugeIntValue(std::move(value));
}

UnsignedHugeInt::UnsignedHugeInt(UnsignedHugeIntValue* value) {
    this->value = value;
}

UnsignedHugeInt::~UnsignedHugeInt() {
    delete this->value;
}

UnsignedHugeInt UnsignedHugeInt::number_of_digits() const {
    return UnsignedHugeInt(this->value->number_of_digits());
}

UnsignedHugeInt UnsignedHugeInt::length() const {
    return UnsignedHugeInt(this->value->number_of_digits());
}

void UnsignedHugeInt::read_from_text_file(std::string file_path) {
    this->value->read_from_text_file(file_path);
}

void UnsignedHugeInt::read_from_text_file(FILE* integer_file) {
    this->value->read_from_text_file(integer_file);
}
    
void UnsignedHugeInt::write_to_text_file(std::string file_path) const {
    this->value->write_to_text_file(file_path);
}
    
void UnsignedHugeInt::write_to_text_file(FILE* integer_file) const {
    this->value->write_to_text_file(integer_file);
}
    
void UnsignedHugeInt::read_from_binary_file(std::string file_path) {
    this->value->read_from_binary_file(file_path);
}
    
void UnsignedHugeInt::write_to_binary_file(std::string file_path) const {
    this->value->write_to_binary_file(file_path);
}
    
UnsignedHugeInt::operator std::string() const {
    return this->value->to_string();
}

UnsignedHugeInt& UnsignedHugeInt::operator=(const UnsignedHugeInt& orig) {
    this->value->operator=(orig.value);
    return *this;
}

UnsignedHugeInt& UnsignedHugeInt::operator=(const UnsignedHugeInt* orig) {
    this->value->operator=(orig->value);
    return *this;
}
    
UnsignedHugeInt& UnsignedHugeInt::operator=(UnsignedHugeInt&& orig) {
    delete(this->value);
    this->value = orig.value;
    orig.value = NULL;
    return *this;
}

UnsignedHugeInt& UnsignedHugeInt::operator=(const unsigned long long value) {
    this->value->operator=(value);
    return *this;
}

UnsignedHugeInt& UnsignedHugeInt::operator=(const std::string value_string) {
    this->value->operator=(value_string);
    return *this;
}

UnsignedHugeInt& UnsignedHugeInt::operator=(const char* value_string) {
    this->value->operator=(value_string);
    return *this;
}

short UnsignedHugeInt::compare(const UnsignedHugeInt& numberA, const UnsignedHugeInt& numberB) {
    return UnsignedHugeIntValue::compare(numberA.value, numberB.value);
}
    
bool UnsignedHugeInt::operator<(const UnsignedHugeInt& right_operand) const {
    return (UnsignedHugeIntValue::compare(*this->value, right_operand.value) < 0);
}

bool UnsignedHugeInt::operator<(const unsigned long long right_operand) const {
    return (UnsignedHugeIntValue::compare(*this->value, UnsignedHugeIntValue(right_operand)) < 0);
}

bool operator<(const unsigned long long left_operand, const UnsignedHugeInt& right_operand) {
    return (UnsignedHugeIntValue::compare(UnsignedHugeIntValue(left_operand), *right_operand.value) < 0);
}

bool UnsignedHugeInt::operator<=(const UnsignedHugeInt& right_operand) const {
    return (UnsignedHugeIntValue::compare(*this->value, right_operand.value) <= 0);
}

bool UnsignedHugeInt::operator<=(const unsigned long long right_operand) const {
    return (UnsignedHugeIntValue::compare(*this->value, UnsignedHugeIntValue(right_operand)) <= 0);
}

bool operator<=(const unsigned long long left_operand, const UnsignedHugeInt& right_operand) {
    return (UnsignedHugeIntValue::compare(UnsignedHugeIntValue(left_operand), *right_operand.value) <= 0);
}

bool UnsignedHugeInt::operator>(const UnsignedHugeInt& right_operand) const {
    return (UnsignedHugeIntValue::compare(*this->value, right_operand.value) > 0);
}

bool UnsignedHugeInt::operator>(const unsigned long long right_operand) const {
    return (UnsignedHugeIntValue::compare(*this->value, UnsignedHugeIntValue(right_operand)) > 0);
}

bool operator>(const unsigned long long left_operand, const UnsignedHugeInt& right_operand) {
    return (UnsignedHugeIntValue::compare(UnsignedHugeIntValue(left_operand), *right_operand.value) > 0);
}

bool UnsignedHugeInt::operator>=(const UnsignedHugeInt& right_operand) const {
    return (UnsignedHugeIntValue::compare(*this->value, right_operand.value) >= 0);
}

bool UnsignedHugeInt::operator>=(const unsigned long long right_operand) const {
    return (UnsignedHugeIntValue::compare(*this->value, UnsignedHugeIntValue(right_operand)) >= 0);
}

bool operator>=(const unsigned long long left_operand, const UnsignedHugeInt& right_operand) {
    return (UnsignedHugeIntValue::compare(UnsignedHugeIntValue(left_operand), *right_operand.value) >= 0);
}

bool UnsignedHugeInt::operator==(const UnsignedHugeInt& right_operand) const {
    return (UnsignedHugeIntValue::compare(*this->value, right_operand.value) == 0);
}

bool UnsignedHugeInt::operator==(const unsigned long long right_operand) const {
    return (UnsignedHugeIntValue::compare(*this->value, UnsignedHugeIntValue(right_operand)) == 0);
}

bool operator==(const unsigned long long left_operand, const UnsignedHugeInt& right_operand) {
    return (UnsignedHugeIntValue::compare(UnsignedHugeIntValue(left_operand), *right_operand.value) == 0);
}

bool UnsignedHugeInt::operator!=(const UnsignedHugeInt& right_operand) const {
    return (UnsignedHugeIntValue::compare(*this->value, right_operand.value) != 0);
}

bool UnsignedHugeInt::operator!=(const unsigned long long right_operand) const {
    return (UnsignedHugeIntValue::compare(*this->value, UnsignedHugeIntValue(right_operand)) != 0);
}

bool operator!=(const unsigned long long left_operand, const UnsignedHugeInt& right_operand) {
    return (UnsignedHugeIntValue::compare(UnsignedHugeIntValue(left_operand), *right_operand.value) != 0);
}

UnsignedHugeInt UnsignedHugeInt::sum_of(const UnsignedHugeInt& addendA, const UnsignedHugeInt& addendB) {
    return UnsignedHugeInt(UnsignedHugeIntValue::sum_of(*addendA.value, *addendB.value));
}

UnsignedHugeInt UnsignedHugeInt::sum_of(const UnsignedHugeInt& addendA, const unsigned long long addendB) {
    return UnsignedHugeInt(UnsignedHugeIntValue::sum_of(*addendA.value, addendB));
}

UnsignedHugeInt UnsignedHugeInt::operator+(const UnsignedHugeInt& addend) const {
    return UnsignedHugeInt(UnsignedHugeIntValue::sum_of(*this->value, *addend.value));
}

UnsignedHugeInt UnsignedHugeInt::operator+(const unsigned long long addend) const {
    return UnsignedHugeInt(UnsignedHugeIntValue::sum_of(*this->value, addend));
}

UnsignedHugeInt operator+(const unsigned long long addendA, const UnsignedHugeInt& addendB) {
    return UnsignedHugeInt(UnsignedHugeIntValue::sum_of(*addendB.value, addendA));
}

UnsignedHugeInt UnsignedHugeInt::subtract(const UnsignedHugeInt& minuend, const UnsignedHugeInt& subtrahend) {
    return UnsignedHugeInt(UnsignedHugeIntValue::subtract(*minuend.value, *subtrahend.value));
}

UnsignedHugeInt UnsignedHugeInt::operator-(const UnsignedHugeInt& subtrahend) const {
    return UnsignedHugeInt(UnsignedHugeIntValue::subtract(*this->value, *subtrahend.value));
}

UnsignedHugeInt UnsignedHugeInt::operator-(const unsigned long long subtrahend) const {
    return UnsignedHugeInt(UnsignedHugeIntValue::subtract(*this->value, UnsignedHugeIntValue(subtrahend)));
}

UnsignedHugeInt operator-(const unsigned long long minuend, const UnsignedHugeInt& subtrahend) {
    return UnsignedHugeInt(UnsignedHugeIntValue::subtract(UnsignedHugeIntValue(minuend), *subtrahend.value));
}
    
UnsignedHugeInt UnsignedHugeInt::multiply(const UnsignedHugeInt& factorA, const UnsignedHugeInt& factorB) {
    return UnsignedHugeInt(UnsignedHugeIntValue::multiply(*factorA.value, *factorB.value));
}

UnsignedHugeInt UnsignedHugeInt::operator*(const UnsignedHugeInt& factor) const {
    return UnsignedHugeInt(UnsignedHugeIntValue::multiply(*this->value, *factor.value));
}

UnsignedHugeInt UnsignedHugeInt::operator*(const unsigned long long factor) const {
    return UnsignedHugeInt(this->value->multiply_by_int(factor));
}

UnsignedHugeInt operator*(const unsigned long long factorA, const UnsignedHugeInt& factorB) {
    return UnsignedHugeInt(factorB.value->multiply_by_int(factorA));
}

std::pair<UnsignedHugeInt, UnsignedHugeInt> UnsignedHugeInt::divide(const UnsignedHugeInt& dividend, const UnsignedHugeInt& divisor) {
    // Divide and store the quotient and remainder in a pair.
    std::pair<UnsignedHugeIntValue, UnsignedHugeIntValue> divisionResults;
    divisionResults = UnsignedHugeIntValue::divide(*dividend.value, *divisor.value);
    return std::pair<UnsignedHugeInt, UnsignedHugeInt>(UnsignedHugeInt(divisionResults.first), UnsignedHugeInt(divisionResults.second));
}

UnsignedHugeInt UnsignedHugeInt::operator/(const UnsignedHugeInt& divisor) const {
    return UnsignedHugeInt(UnsignedHugeIntValue::divide(*this->value, *divisor.value).first);
}

UnsignedHugeInt UnsignedHugeInt::operator/(const unsigned long long divisor) const {
    return UnsignedHugeInt(UnsignedHugeIntValue::divide(*this->value, UnsignedHugeIntValue(divisor)).first);
}

UnsignedHugeInt operator/(const unsigned long long dividend, const UnsignedHugeInt& divisor) {
    return UnsignedHugeInt(UnsignedHugeIntValue::divide(UnsignedHugeIntValue(dividend), *divisor.value).first);
}

UnsignedHugeInt UnsignedHugeInt::operator%(const UnsignedHugeInt& divisor) const {
    return UnsignedHugeInt(UnsignedHugeIntValue::divide(*this->value, *divisor.value).second);
}

UnsignedHugeInt UnsignedHugeInt::operator%(const unsigned long long divisor) const {
    return UnsignedHugeInt(UnsignedHugeIntValue::divide(*this->value, UnsignedHugeIntValue(divisor)).second);
}

UnsignedHugeInt operator%(const unsigned long long dividend, const UnsignedHugeInt& divisor) {
    return UnsignedHugeInt(UnsignedHugeIntValue::divide(UnsignedHugeIntValue(dividend), *divisor.value).second);
}

UnsignedHugeInt& UnsignedHugeInt::operator+=(const UnsignedHugeInt& addend) {
    this->value->operator+=(*addend.value);
    return *this;
}

UnsignedHugeInt& UnsignedHugeInt::operator+=(const unsigned long long addend) {
    this->value->operator+=(addend);
    return *this;
}

UnsignedHugeInt& UnsignedHugeInt::operator-=(const UnsignedHugeInt& subtrahend) {
    this->value->operator-=(*subtrahend.value);
    return *this;
}

UnsignedHugeInt& UnsignedHugeInt::operator-=(const unsigned long long subtrahend) {
    this->value->operator-=(subtrahend);
    return *this;
}

UnsignedHugeInt& UnsignedHugeInt::operator*=(const UnsignedHugeInt& factor) {
    this->value->operator*=(*factor.value);
    return *this;
}

UnsignedHugeInt& UnsignedHugeInt::operator*=(const unsigned long long factor) {
    this->value->operator*=(factor);
    return *this;
}

UnsignedHugeInt& UnsignedHugeInt::operator/=(const UnsignedHugeInt& divisor) {
    this->value->operator/=(*divisor.value);
    return *this;
}

UnsignedHugeInt& UnsignedHugeInt::operator/=(const unsigned long long divisor) {
    this->value->operator/=(divisor);
    return *this;
}

UnsignedHugeInt& UnsignedHugeInt::operator%=(const UnsignedHugeInt& divisor) {
    this->value->operator%=(*divisor.value);
    return *this;
}

UnsignedHugeInt& UnsignedHugeInt::operator%=(const unsigned long long divisor) {
    this->value->operator%=(divisor);
    return *this;
}

UnsignedHugeInt& UnsignedHugeInt::operator++() {
    this->value->operator++();
    return *this;
}

UnsignedHugeInt UnsignedHugeInt::operator++(int dummy) {
    UnsignedHugeInt originalValue(*this);
    this->value->operator++();
    return originalValue;
}

UnsignedHugeInt& UnsignedHugeInt::operator--() {
    this->value->operator--();
    return *this;
}

UnsignedHugeInt UnsignedHugeInt::operator--(int dummy) {
    UnsignedHugeInt originalValue(*this);
    this->value->operator--();
    return originalValue;
}

std::string UnsignedHugeInt::to_string() const {
    return this->value->to_string();
}

std::ostream& operator<<(std::ostream& out_stream, const UnsignedHugeInt& huge_int_object) {
    out_stream << huge_int_object.to_string();
    return out_stream;
}
