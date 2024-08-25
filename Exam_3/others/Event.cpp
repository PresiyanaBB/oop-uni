#include "Event.h"

bool Event::isValid(unsigned day) const
{
	return (day >= 1 && day <= 31);
}

unsigned Event::mask(unsigned day) const
{
	return (1 << (31 - day));
}

bool Event::contains(unsigned day) const
{
	if (!isValid(day))
		return false; //throw exception
	
	return (mask(day) & data);
}

void Event::addOrRemove(unsigned day, bool add)
{
	if (add)
		data |= mask(day);

	else
		if (contains(day))
			data ^= mask(day);
}

void Event::add(unsigned day)
{
	addOrRemove(day, true);
}
void Event::remove(unsigned day)
{
	addOrRemove(day, false);
}

Event unionOrIntersection(const Event& lhs, const Event& rhs, bool uni)
{
	Event res(lhs);

	if (uni)
		res.data |= rhs.data;

	else
		res.data &= rhs.data;

	return res;
}

Event Union(const Event& lhs, const Event& rhs)
{
	return unionOrIntersection(lhs,rhs,true);
}

Event Intersection(const Event& lhs, const Event& rhs)
{
	return unionOrIntersection(lhs, rhs, false);
}

//monday = 1, tuesday = 2, ..., saturday = 6, sunday = 0 -> 01.01.2023 is sunday
unsigned Event::onWeekday(unsigned dayOfWeek) const
{
	if (dayOfWeek < 0 || dayOfWeek > 6)
		throw;

	unsigned count = 0;
	for (size_t i = dayOfWeek; i < 32; i+=7)
		if (contains(i+1))
			count++;

	return count;
}

void Event::print() const
{
	for (size_t i = 1; i <= 31; i++)
		if (contains(i))
			std::cout << i << " ";

	std::cout << std::endl;
}

void Event::write(const char* filename) const
{
	std::ofstream ofs(filename, std::ios::out | std::ios::binary);

	if (!ofs.is_open())
		throw;

	ofs.write((const char*)&data,sizeof(data));

	ofs.close();
}

void Event::read(const char* filename)
{
	std::ifstream ifs(filename, std::ios::in | std::ios::binary);

	if (!ifs.is_open())
		throw;

	ifs.read((char*)&data,sizeof(data));

	ifs.close();
}
