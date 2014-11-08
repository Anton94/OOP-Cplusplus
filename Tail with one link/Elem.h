#pragma once

template <class T>
struct Elem
{
public:
	Elem(const T& x, Elem<T>* p = NULL);
	Elem(const Elem<T> & other);
	Elem<T>& operator=(const Elem<T> & other);
	~Elem();
private:
	void copyFrom(const Elem<T>& other);
	void free();
public:
	Elem<T> * next;
	T data;
};

template <class T>
Elem<T>::Elem(const T& x, Elem<T>* p = NULL) : data(x), next(p) {}

template <class T>
Elem<T>::Elem(const Elem<T> & other)
{
	copyFrom(other);
}

template <class T>
Elem<T>& Elem<T>::operator=(const Elem<T> & other)
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
Elem<T>::~Elem()
{
	free();
}

template <class T>
void Elem<T>::copyFrom(const Elem<T>& other)
{
	data = other.data;

	if (other.next)
	{
		next = new Elem<T>(*other.next);
	}
	else
	{
		next = NULL;
	}
}

template <class T>
void Elem<T>::free()
{
	if (next)		  // if next is NULL it will work with delete , anyway..
		delete next;  // deletes the memory and calls the destructor of the element, pointed by the 'next' and etc...
}