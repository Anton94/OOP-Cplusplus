#pragma once

/*
	Boxes which will contain the information of the list.
	One parametar for the data.
	Two pointers to the next box and the prev box.
*/

template <class T>
struct Elem
{ 
public:
	Elem(T x, Elem<T>* pNext = NULL, Elem<T>* pPrev = NULL);
	Elem(const Elem<T>& other);
private:
	void copFrom(const Elem<T>& other);
public:
	T data;
	Elem<T> *next, *prev;
};
template <class T>
Elem<T>::Elem(T x, Elem<T>* pNext = NULL, Elem<T>* pPrev = NULL) : data(x), next(pNext), prev(pPrev) {}

template <class T>
Elem<T>::Elem(const Elem<T>& other)
{
	copFrom();
}

// copy the value and set`s the pointers to NULL!

template <class T>
void Elem<T>::copFrom(const Elem<T>& other)
{
	data = other.data;
	next = NULL;
	prev = NULL;
}