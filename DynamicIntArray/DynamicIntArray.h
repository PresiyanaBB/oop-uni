#pragma once

//collection ot int
class DynamicIntArray
{
protected:
	int* data = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	void free();
	void copyFrom(const DynamicIntArray& other);
	void moveFrom(DynamicIntArray&&);

	void resize(size_t);
public:
	DynamicIntArray();

	DynamicIntArray(const DynamicIntArray& other);
	DynamicIntArray(DynamicIntArray&& other);

	DynamicIntArray& operator=(const DynamicIntArray& other);
	DynamicIntArray& operator=(DynamicIntArray&& other);

	void add(int number);
	void remove(int number);
	unsigned count(int number) const;
	bool contains(int number) const;

	~DynamicIntArray();
};
