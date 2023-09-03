#include "NF.h"

//ctors
NF::NF() {
	// Identity function: f(x) = x
	f = [](unsigned value){
		return value;
	};
}
NF::NF(func f) : f(f) {}


void NF::setFunc(func newf) {
	f = newf;
}
unsigned NF::eval(unsigned value) const {
	return f(value);
}
bool fixBounds(int& lowerBound, int& upperBound)
{
	if (lowerBound > upperBound)  // Fix order of variables
		std::swap(lowerBound, upperBound);

	if (upperBound < 0)  // All numbers are negative
		return false;

	// We have checked that upperBound is >= 0,
	// If lowerBound is negative, adjust it to 0
	if (lowerBound < 0)
		lowerBound = 0;

	return true;
}
unsigned NF::countFixedPoints(int lowerBound, int upperBound) const 
{
	if (!fixBounds(lowerBound, upperBound))
		return 0; // return 0, because the provided interval is not valid.

	unsigned counter = 0;
	for (unsigned i = lowerBound; i <= upperBound; i++)
		if (eval(i) == i)  //f(k) = k
			counter++;

	return counter;
}
bool areSameInInterval(const NF& lhs, const NF& rhs, int lowerBound, int upperBound)
{
	if (!fixBounds(lowerBound, upperBound))
		throw std::logic_error("Interval is not valid!");

	for (unsigned i = lowerBound; i <= upperBound; i++)
		if (lhs.eval(i) != rhs.eval(i)) //f(k) = k, demek edno i suhto li vrushtat v toq interval dvete
			return false;

	return true;
}