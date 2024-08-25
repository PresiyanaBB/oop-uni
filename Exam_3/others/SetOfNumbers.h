#pragma once
#include <iostream>
#include <assert.h>

/*
bitwise operations:
& -> AND
| -> OR
^ -> XOR
~ -> NOT

>>,<<
(chislo v desetichna , nakude se mesti, kolko pozicii) slaga se edno tolkova nuli v ediniq krai
realno 1 << n = 2 na stepen n

1 (10) = 0000 0001 (2)
1 << 1 -> 0000 0010
1 << 5 -> 0010 0000
1 << 20 -> 0001 0000 0000 0000 0000 0000

64 (10) = 0010 0000 (2)
64 >> 3 = 0000 0100
*/

class SetOfNumbers
{
    //char = 1byte = 8bits
    unsigned char* data;
    unsigned maxNum; //capacity = 10 => [0,9] => maxNum = 9

    //bucket0->[0,7] ,bucket1->[8,15] ,bucket2->[16,23] i tn 
    //bucketa [neshto det se deli na 8 bez ostatuk, sledvashtoto det se deli na 8 bez ostatyk - 1]
    unsigned getBucketIndex(unsigned number) const;
    unsigned getBucketsCount() const; 

    /*
    maskata e na poziciqta na chisloto da e 1 i vs dr nuli -> 1 edinica i 6 nuli shtot e za bucket
    shtot kato praish pobitovo i -> 1 i 1 = 1 , 0 i 1 = 0  i taka znaesh ima li go , nqma li go
    primerno ako imame capacity 8 demek maxNum = 7 demek 1 bucket stiga i toi shte e na data[0] i da rechem imame 2,3,7
    data[0]   = 0 0 1 1 0 0 0 1
    mask na 2 = 0 0 1 0 0 0 0 0
    pobitovo i na dvete shte dade 0 na vs pozicii osven na 2 kudeto shte dade 1 ako imame 2 v seta i 0 ako nqmame
    data[0] & mask = 0 0 1 0 0 0 0 0
    (bool)0 = 0
    (bool)vs ostanalo e 1 => (bool)3 = 1 , (bool)'a' = 1, (bool)kakvoto i da dade data[0]&mask ako ne sa samo nuli mi ima 1 shte dade 1
    */
    unsigned char getMask(unsigned number) const;

    void addOrRemove(unsigned number, bool wantToAdd);
    friend SetOfNumbers unionOrIntersection(const SetOfNumbers& lhs, const SetOfNumbers& rhs, bool wantUnion);

    void copyFrom(const SetOfNumbers& other);
    void free();
public:
    SetOfNumbers(unsigned capacity);

    SetOfNumbers(const SetOfNumbers& other);
    SetOfNumbers& operator=(const SetOfNumbers& other);
    ~SetOfNumbers();

    bool contains(unsigned number) const;

    void addNumber(unsigned number);
    void removeNumber(unsigned number);

    void print() const;
};
//ako nqmah obshtata func deto e friend trqqshe teq da sa friend za da imat dostup do private neshtata
SetOfNumbers unionOfSets(const SetOfNumbers& lhs, const SetOfNumbers& rhs);
SetOfNumbers intersectionOfSets(const SetOfNumbers& lhs, const SetOfNumbers& rhs);

