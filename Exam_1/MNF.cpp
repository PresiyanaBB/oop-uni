#include "MNF.h"

//ctors
MNF::MNF() : MNF([](unsigned n) { return n; }, 2) {}
MNF::MNF(func f, unsigned pointsToChange) : NF(f), capacity(pointsToChange) {
	modified = new Pair[capacity];
}


//find
int MNF::findPointIndex(unsigned point) const {
	for (unsigned i = 0; i < count; ++i)
		if (point == modified[i].point)
			return i;

	return InvalidIndex;
}


//modifications
bool MNF::modify(unsigned point, unsigned value) {
	int index = findPointIndex(point);
	if (index == InvalidIndex) {
		if (count >= capacity)
			return false;

		index = count++;
	}
	modified[index].point = point;
	modified[index].value = value;

	return true;
}
void MNF::removeAllModifications() {
	for (size_t i = 0; i < count; i++)
		if (modified[i].point != InvalidIndex || modified[i].value != InvalidIndex)
			modified[i].point = modified[i].value = InvalidIndex;
	
	count = 0;
}
bool MNF::removeModification(unsigned point) {
	int index = findPointIndex(point);
	if (index == InvalidIndex)
		return false;

	modified[index].point = InvalidIndex;
	modified[index].value = InvalidIndex;

	if (index != --count)
		std::swap(modified[index], modified[count]);

	return true;
}


//from NF
unsigned MNF::eval(unsigned value) const {
	int index = findPointIndex(value);
	return InvalidIndex == index ? f(value) : modified[index].value;
}
void MNF::setFunc(func f) {
	removeAllModifications();
	this->f = f;
}





//Big 6
//
void MNF::copyFrom(const MNF& other) {
	capacity = other.capacity;
	modified = new Pair[capacity];

	for (unsigned i = 0; i < count; ++i)
		modified[i] = other.modified[i];
}

void MNF::moveFrom(MNF&& other) {
	capacity = other.capacity;
	modified = other.modified;

	other.capacity = 0;
	other.modified = nullptr;
}

void MNF::free() {
	delete[] modified;
}
//
MNF::MNF(const MNF& other) : NF(other) {
	copyFrom(other);
}

MNF::MNF(MNF&& other) noexcept : NF(std::move(other)) {
	moveFrom(std::move(other));
}

MNF& MNF::operator=(const MNF& other) {
	if (this != &other) {
		free();
		NF::operator=(other);
		copyFrom(other);
	}

	return *this;
}

MNF& MNF::operator=(MNF&& other) noexcept {
	if (this != &other) {
		free();
		NF::operator=(std::move(other));
		moveFrom(std::move(other));
	}

	return *this;
}

MNF::~MNF() {
	free();
}