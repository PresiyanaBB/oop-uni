#include <iostream>
#include <exception>
template <typename T>
class MyStack
{
	T* data;
	size_t capacity;
	size_t size;

	void resize();

	void moveFrom(MyStack<T>&& other);
	void copyFrom(const MyStack<T>& other);
	void free();
public:
	MyStack();

	MyStack(const MyStack<T>& other);
	MyStack<T>& operator=(const MyStack<T>& other);

	MyStack(MyStack<T>&& other);
	MyStack<T>& operator=(MyStack<T>&& other);

	void push(const T& obj);
	void push(T&& obj);
	void pop();

	const T& peek() const;
	bool isEmpty() const;

	~MyStack();
};

template <typename T>
MyStack<T>::MyStack()
{
	capacity = 4;
	data = new T[capacity];
	size = 0;
}

template <typename T>
void MyStack<T>::push(const T& obj)
{
	if (size == capacity)
		resize();

	data[size++] = obj; //operator=
}

template <typename T>
void MyStack<T>::push(T&& obj)
{
	if (size == capacity)
		resize();

	data[size++] = std::move(obj); //move operator =
}

template <typename T>
bool MyStack<T>::isEmpty() const
{
	return size == 0;
}

template <typename T>
const T& MyStack<T>::peek() const
{
	if (isEmpty())
		throw std::logic_error("Empty stack!");

	return data[size - 1];
}

template <typename T>
void MyStack<T>::pop()
{
	if (isEmpty())
		throw std::logic_error("Empty stack!");
	
	size--;
}

template <typename T>
void MyStack<T>::resize()
{
	T* resizedData = new T[capacity * 2];
	for (size_t i = 0; i < size; i++)
		resizedData[i] = data[i];

	capacity *= 2;
	delete[] data;
	data = resizedData;
}


template <typename T>
void MyStack<T>::copyFrom(const MyStack<T>& other)
{
	data = new T[other.capacity];
	for (int i = 0; i < other.capacity; i++)
		data[i] = other.data[i];

	size = other.size;
	capacity = other.capacity;
}

template <typename T>
void MyStack<T>::moveFrom(MyStack<T>&& other)
{
	size = other.size;
	capacity = other.capacity;

	data = other.data;
	other.data = nullptr;

	other.size = other.capacity = 0;
}

template <typename T>
void MyStack<T>::free()
{
	delete[] data;
}

template <typename T>
MyStack<T>::MyStack(const MyStack<T>& other)
{
	copyFrom(other);
}

template <typename T>
MyStack<T>& MyStack<T>::operator=(const MyStack<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template <typename T>
MyStack<T>::MyStack(MyStack<T>&& other)
{
	moveFrom(std::move(other));
}

template <typename T>
MyStack<T>& MyStack<T>::operator=(MyStack<T>&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}


template <typename T>
MyStack<T>::~MyStack()
{
	free();
}