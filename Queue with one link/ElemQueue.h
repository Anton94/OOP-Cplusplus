#pragma once

template <class T>
struct ElemQueue
{
public:
	ElemQueue(const T& x, ElemQueue<T>* p = NULL);
	ElemQueue(const ElemQueue<T> & other);
	ElemQueue<T>& operator=(const ElemQueue<T> & other);
	~ElemQueue();
private:
	void copyFrom(const ElemQueue<T>& other);
	void free();
public:
	ElemQueue<T> * next;
	T data;
};

template <class T>
ElemQueue<T>::ElemQueue(const T& x, ElemQueue<T>* p = NULL) : data(x), next(p) {}

template <class T>
ElemQueue<T>::ElemQueue(const ElemQueue<T> & other)
{
	copyFrom(other);
}

template <class T>
ElemQueue<T>& ElemQueue<T>::operator=(const ElemQueue<T> & other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}


// cascade destructor, till next is NULL.

template <class T>
ElemQueue<T>::~ElemQueue()
{
	free();
}

template <class T>
void ElemQueue<T>::copyFrom(const ElemQueue<T>& other)
{
	data = other.data;

	if (other.next)
	{
		next = new ElemQueue<T>(*other.next);
	}
	else
	{
		next = NULL;
	}
}

template <class T>
void ElemQueue<T>::free()
{
	if (next)		  // if next is NULL it will work with delete , anyway..
		delete next;  // deletes the memory and calls the destructor of the element, pointed by the 'next' and etc...
}