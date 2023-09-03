#pragma once
#include <iostream>
#include <fstream>

class Event
{
	unsigned data = 0;

	unsigned mask(unsigned day) const;
	bool isValid(unsigned day) const;
	void addOrRemove(unsigned day, bool add);
	friend Event unionOrIntersection(const Event& lhs, const Event& rhs, bool uni);

public:
	Event() = default;
	void add(unsigned day);
	void remove(unsigned day);
	bool contains(unsigned day) const;

	//monday = 1, tuesday = 2, ..., saturday = 6, sunday = 0 -> 01.01.2023 is sunday
	unsigned onWeekday(unsigned dayOfWeek) const;
	
	void write(const char* filename) const;
	void read(const char* filename);
	void print() const;
};
Event Union(const Event& lhs, const Event& rhs);
Event Intersection(const Event& lhs, const Event& rhs);