#include "UnsignedHugeInt.h"

    // ToDo: Set the maxWordValue here and in HugeIntWord.
    unsigned long long UnsignedHugeInt::maxWordValue = 1000000000;

UnsignedHugeInt::UnsignedHugeInt() {
    this->numWords = 1;
    HugeIntWord *newWord = new HugeIntWord(0);
    this->mostSigWord = newWord;
    this->leastSigWord = newWord;
}

UnsignedHugeInt::UnsignedHugeInt(const unsigned long long value) {
    this->numWords = 1;
    HugeIntWord *newWord = new HugeIntWord(value);
    this->mostSigWord = newWord;
    this->leastSigWord = newWord;
}

UnsignedHugeInt::UnsignedHugeInt(const UnsignedHugeInt& orig) {
    // ToDo: Complete this method.
}

UnsignedHugeInt::~UnsignedHugeInt() {
    // ToDo: Complete this method.
}

UnsignedHugeInt UnsignedHugeInt::operator+(UnsignedHugeInt addend) {
    // ToDo: Complete this method.
    UnsignedHugeInt sum;
    
    return sum;
}

UnsignedHugeInt UnsignedHugeInt::operator+(long long addend) {
    // ToDo: Complete this method.
    UnsignedHugeInt sum;
    
    return sum;
}

UnsignedHugeInt UnsignedHugeInt::operator-(UnsignedHugeInt minuend) {
    // ToDo: Complete this method.
    UnsignedHugeInt difference;
    
    return difference;
}

UnsignedHugeInt UnsignedHugeInt::operator-(long long minuend) {
    // ToDo: Complete this method.
    UnsignedHugeInt difference;
    
    return difference;
}

UnsignedHugeInt UnsignedHugeInt::operator*(UnsignedHugeInt factor) {
    // ToDo: Complete this method.
    UnsignedHugeInt product;
    
    return product;
}

UnsignedHugeInt UnsignedHugeInt::operator*(long long factor) {
    // ToDo: Complete this method.
    UnsignedHugeInt product;
    
    return product;
}

UnsignedHugeInt UnsignedHugeInt::operator/(UnsignedHugeInt divisor) {
    // ToDo: Complete this method.
    UnsignedHugeInt quotient;
    
    return quotient;
}

UnsignedHugeInt UnsignedHugeInt::operator/(long long divisor) {
    // ToDo: Complete this method.
    UnsignedHugeInt quotient;
    
    return quotient;
}

long UnsignedHugeInt::num_words() {
    return this->numWords;
}

bool UnsignedHugeInt::is_prime() {
    // ToDo: Complete this method.
    return false;
}

std::string UnsignedHugeInt::to_string() {
    // ToDo: Complete this method.
    std::string numberString = "";
//    std::ostringstream numberToStringStream;
//    if (this->numWords == 0)
//        numberString = "0";
//    else if (this->numWords == 1) {
////        numberString = std::to_string(this->words[0]);        
//    numberToStringStream << this->words[0];
//    numberString = numberToStringStream.str();
//    }
    // ToDo: If numWords > 1
    return numberString;
}
