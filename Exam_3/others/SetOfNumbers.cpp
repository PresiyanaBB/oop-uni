#include "SetOfNumbers.h"


SetOfNumbers::SetOfNumbers(unsigned capacity)
{
    maxNum = capacity - 1;
    unsigned bucketCount = ((maxNum / 8) + 1);
    data = new unsigned char[bucketCount];
    
    for (unsigned i = 0; i < bucketCount; i++)
        data[i] = 0;
}
unsigned SetOfNumbers::getBucketsCount() const
{
    return ((maxNum / 8) + 1);
}
unsigned SetOfNumbers::getBucketIndex(unsigned number) const
{
    return number / 8;
}
unsigned char SetOfNumbers::getMask(unsigned number) const
{
    return (1 << (7 - (number % 8)));
}
bool SetOfNumbers::contains(unsigned number) const
{
    return (getMask(number) & data[getBucketIndex(number)]);
}
void SetOfNumbers::addOrRemove(unsigned number, bool wantToAdd)
{
    if (wantToAdd)
        data[getBucketIndex(number)] |= getMask(number);

    else 
        if(contains(number))
            data[getBucketIndex(number)] ^= getMask(number);
}
SetOfNumbers unionOrIntersection(const SetOfNumbers& lhs, const SetOfNumbers& rhs, bool wantUnion)
{
    if (lhs.maxNum != rhs.maxNum) throw;

    SetOfNumbers result(lhs.maxNum + 1);
    
    unsigned bucketCount = lhs.getBucketsCount();
    if (wantUnion)
        for (unsigned i = 0; i < bucketCount; i++)
            result.data[i] = (lhs.data[i] | rhs.data[i]);
    
    else
        for (unsigned i = 0; i < bucketCount; i++)
            result.data[i] = (lhs.data[i] & rhs.data[i]);

    return result;
}












//cF,free
void SetOfNumbers::copyFrom(const SetOfNumbers& other)
{
    maxNum = other.maxNum;
    unsigned bucketsCount = other.getBucketsCount();
    data = new unsigned char[bucketsCount];
    for (unsigned i = 0; i < bucketsCount; i++)
        data[i] = other.data[i];

}
void SetOfNumbers::free()
{
    delete[] data;
}

//print - prosto for ot 0 do maks i ako contains(i) pechatam
void SetOfNumbers::print() const
{
    std::cout << "{ ";

    for (size_t i = 0; i <= maxNum; i++)
        if (contains(i))
            std::cout << i << " ";

    std::cout << "} " << std::endl;
}

//add and remove using mutual method
void SetOfNumbers::addNumber(unsigned number)
{
    return addOrRemove(number, true);
}
void SetOfNumbers::removeNumber(unsigned number)
{
    return addOrRemove(number, false);
}

//union and intersection using mutual method
SetOfNumbers unionOfSets(const SetOfNumbers& lhs, const SetOfNumbers& rhs)
{
    return unionOrIntersection(lhs, rhs, true);
}
SetOfNumbers intersectionOfSets(const SetOfNumbers& lhs, const SetOfNumbers& rhs)
{
    return unionOrIntersection(lhs, rhs, false);
}

//Big 4
SetOfNumbers::SetOfNumbers(const SetOfNumbers& other)
{
    copyFrom(other);
}
SetOfNumbers& SetOfNumbers::operator=(const SetOfNumbers& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}
SetOfNumbers::~SetOfNumbers()
{
    free();
}