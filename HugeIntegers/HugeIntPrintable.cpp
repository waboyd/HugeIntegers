#include "HugeIntPrintable.h"

HugeIntPrintable::HugeIntPrintable()
{
    this->word_values = new std::vector<WordType>();
}

HugeIntPrintable::~HugeIntPrintable()
{
    delete this->word_values;
}
