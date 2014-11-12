#pragma once

/*
	Boxes which will contain the information of the list.
	One parametar for the data.
	Two pointers to the next box and the prev box.
	Cascade destructor- deletes every cells untill 'next' points NULL.
*/

template <class T>
struct Elem
{ 
public:
	Elem(const T& x = 0, Elem<T>* pNext = NULL, Elem<T>* pPrev = NULL);
	Elem(const Elem<T>& other);
	Elem<T>& operator=(const Elem<T>& other);
	~Elem();
private:
	void copFrom(const Elem<T>& other);
public:
	T data;
	Elem<T> *next, *prev;
};


template <class T>
Elem<T>::Elem(const T& x = 0, Elem<T>* pNext = NULL, Elem<T>* pPrev = NULL) : data(x), next(pNext), prev(pPrev) {}

template <class T>
Elem<T>::Elem(const Elem<T>& other)
{
	copFrom();
}

template <class T>
Elem<T>& Elem<T>::operator=(const Elem<T>& other)
{
	if (this != &other)
	{
		copFrom();
	}

	return *this;
}

template <class T>
Elem<T>::~Elem()
{
	delete next; // delete next cell
}

// copy the value and set`s the pointers to NULL!

template <class T>
void Elem<T>::copFrom(const Elem<T>& other)
{
	data = other.data;
	next = NULL;
	prev = NULL;
}