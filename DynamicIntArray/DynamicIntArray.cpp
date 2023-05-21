#include "DynamicIntArray.h"
#include <utility> // std::move

void DynamicIntArray::free()
{
	delete[] data;
}

void DynamicIntArray::copyFrom(const DynamicIntArray& other)
{
	size = other.size;
	capacity = other.capacity;
	data = new int[capacity];

	for (size_t i = 0; i < size; i++)
	{
		data[i] = other.data[i];
	}
}

void DynamicIntArray::moveFrom(DynamicIntArray&& other)
{
	data = other.data;
	other.data = nullptr;

	other.size = other.capacity = 0;
}

DynamicIntArray::DynamicIntArray(DynamicIntArray&& other)
{
	moveFrom(std::move(other));
}

DynamicIntArray& DynamicIntArray::operator=(DynamicIntArray&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

void DynamicIntArray::resize(size_t nCap)
{
	int* newData = new int[nCap];

	for (size_t i = 0; i < size; i++)
	{
		newData[i] = data[i];
	}

	delete[] data;
	data = newData;
	capacity = nCap;
}

DynamicIntArray::DynamicIntArray()
{
	size = 0;
	capacity = 8;

	data = new int[capacity];
}

DynamicIntArray::DynamicIntArray(const DynamicIntArray& other)
{
	copyFrom(other);
}

DynamicIntArray& DynamicIntArray::operator=(const DynamicIntArray& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

DynamicIntArray::~DynamicIntArray()
{
	free();
}

void DynamicIntArray::add(int elem)
{
	if (size == capacity)
	{
		resize(2 * size);
	}

	data[size++] = elem;
}

void DynamicIntArray::remove(int elem)
{
	int elemIndex = -1;

	for (size_t i = 0; i < size; i++)
	{
		if (data[i] == elem)
		{
			elemIndex = i;
			break;
		}
	}

	if (elemIndex != -1)
	{
		std::swap(data[elemIndex], data[size - 1]);
		size--;
	}
}

unsigned DynamicIntArray::count(int elem) const
{
	unsigned elementCounter = 0;

	for (size_t i = 0; i < size; i++)
	{
		if (data[i] == elem)
		{
			++elementCounter;
		}
	}

	return elementCounter;
}

bool DynamicIntArray::contains(int elem) const
{
	for (size_t i = 0; i < size; i++)
	{
		if (data[i] == elem)
		{
			return true;
		}
	}
	return false;
}