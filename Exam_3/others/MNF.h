#pragma once
#include "NF.h"

const int InvalidIndex = -1;

//modifiable natural numbers function
//-> sushtoto kato NF ama mojesh na nqkoq konkretna tochka da i slojish razlichna stoinost kudeto ne se durji kato funkciqta
class MNF : public NF {
	struct Pair {
		int point = -1;
		int value = -1;
	};
	Pair* modified = nullptr;
	unsigned capacity = 0;
	unsigned count = 0;

	int findPointIndex(unsigned point) const;
	void removeAllModifications();

	void copyFrom(const MNF& other);
	void moveFrom(MNF&& other);
	void free();
public:
	bool modify(unsigned point, unsigned value);
	bool removeModification(unsigned point);
	unsigned eval(unsigned value) const final;
	void setFunc(func pFunc) final;


	MNF();
	MNF(func f, unsigned pointsToChange);
	MNF(const MNF& other);
	MNF(MNF&& other) noexcept;
	MNF& operator=(const MNF& other);
	MNF& operator=(MNF&& other) noexcept;
	~MNF();
};