#pragma once
#include <iostream>

using nz = unsigned; //demek vmesto unsigned moga da pisha nz i shte go zameni navsqkude
const nz a = 5; //const unsigned a = 5;
using nz2 = void(*)(char,int); //return type ,(*) shtot e pointer kum funkciq, (char,int) sa parametri det priema 
//

using func = unsigned(*)(unsigned);

//natural numbers function -> funkciq da gledash v koe chislo kakvo vrushta
class NF {
protected:
	func f;
	unsigned(*f2)(unsigned);
	//f i f2 sa edno i sushto - ako zamenim vsichki f v .cpp faila s f2 nqma da ima razlika 
	//ama e po-kratko kato podavash kato parametur da e (func f), a ne ( unsigned(*f)(unsigned) ) inache koet zapomnish po-lesno
public:
	unsigned countFixedPoints(int lowerBound, int upperBound) const;

	virtual unsigned eval(unsigned value) const;
	virtual void setFunc(func f);

	NF();
	explicit NF(func f);
	virtual ~NF() = default;
};

bool fixBounds(int& lowerBound, int& upperBound);
bool areSameInInterval(const NF& lhs, const NF& rhs, int lowerBound, int upperBound);