#pragma once

/*
	Tail:
		If some allocations fail, throws exeption
		the size of the tail is minimum 1. (the resize is size*2..)
		The tail -> element
		The head -> one after the element

*/

template <class T>
class Tail
{
public:
	Tail();
	Tail(size_t startingSize);
	Tail(const Tail& other);
	Tail& operator=(const Tail& other);
	T peek() const;
	void enqueue(T value);
	T dequeue();
	bool isEmpty() const;
	size_t getSize() const;
	void destroy();
	~Tail();
private:
	void init(size_t startingSize);
	void copyFrom(const Tail& other);
	void resize();
	bool isFull() const;
private:
	T * arr;
	size_t size;
	int head, tail;
};

template <class T>
Tail<T>::Tail()
{
	init(2);
}

template <class T>
Tail<T>::Tail(size_t startingSize)
{
	init(startingSize);
}

template <class T>
Tail<T>::Tail(const Tail& other)
{
	copyFrom(other);
}

template <class T>
Tail<T>& Tail<T>::operator=(const Tail& other)
{
	if (this != &other)
	{
		destroy();
		copyFrom(other);
	}

	return *this;
}

template <class T>
T Tail<T>::peek() const
{
	if (isEmpty())
		throw "The tail is empty and called peek()!";

	return arr[tail];
}

template <class T>
void Tail<T>::enqueue(T value)
{
	if (isFull())
		resize();
	
	arr[head] = value;
	head = (head + 1) % size;
}

template <class T>
T Tail<T>::dequeue()
{
	if (isEmpty())
		throw "The tail is empty and called dequeue()!";

	T x = arr[tail];
	tail = (tail + 1) % size;

	return x;
}

template <class T>
bool Tail<T>::isEmpty() const
{
	return tail == head;
}

template <class T>
size_t Tail<T>::getSize() const
{
	if (head < tail)
		return size - tail + head;
	else
		return head - tail;
}

template <class T>
void Tail<T>::destroy()
{
	delete[] arr;
	init(2);
}

template <class T>
Tail<T>::~Tail()
{
	delete[] arr;
}

// If the starting size is smaller than 1, throws a exeption...

template <class T>
void Tail<T>::init(size_t startingSize)
{
	if (startingSize < 1)
		throw "Invalid size for the array of the tail!";

	arr = new T[startingSize];
	size = startingSize;
	head = tail = 0;
}

template <class T>
void Tail<T>::copyFrom(const Tail& other)
{
	arr = new T[other.size]; // the size of the other tail is minimum 1

	for (size_t i = other.tail, j = 0; i != other.head; i = (i + 1) % size, ++j)
	{
		arr[j] = other.arr[i];
	}

	size = other.size;
	head = other.head;
	tail = other.tail;
}

template <class T>
void Tail<T>::resize()
{
	T * temp = arr;
	arr = new T[size * 2];

	for (size_t i = 0; i < size - 1; ++i)
	{
		arr[i] = temp[(tail + i) % size];
	}

	delete[] temp;
	head = size - 1; // 1 buffer element
	tail = 0;
	size *= 2;
}

// One buffer item so the tail and the haid don`t stuck together when the tail is full

template <class T>
bool Tail<T>::isFull() const
{
	return getSize() == size - 1;
}