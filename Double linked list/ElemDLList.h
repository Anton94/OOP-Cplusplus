#pragma once

/*
	Boxes which will contain the information of the list.
	One parametar for the data.
	Two pointers to the next box and the prev box.
	Cascade destructor- deletes every cells untill 'next' points NULL.
*/

template <class T>
struct ElemDLList
{ 
public:
	ElemDLList();
	ElemDLList(const T& x, ElemDLList<T>* pNext = NULL, ElemDLList<T>* pPrev = NULL);
	ElemDLList(const ElemDLList<T>& other);
	ElemDLList<T>& operator=(const ElemDLList<T>& other);
	~ElemDLList();
private:
	void copFrom(const ElemDLList<T>& other);
public:
	T data;
	ElemDLList<T> *next, *prev;
};

template <class T>
ElemDLList<T>::ElemDLList()
{
	next = prev = NULL;
}

template <class T>
ElemDLList<T>::ElemDLList(const T& x, ElemDLList<T>* pNext = NULL, ElemDLList<T>* pPrev = NULL) : data(x), next(pNext), prev(pPrev) {}

template <class T>
ElemDLList<T>::ElemDLList(const ElemDLList<T>& other)
{
	copFrom();
}

template <class T>
ElemDLList<T>& ElemDLList<T>::operator=(const ElemDLList<T>& other)
{
	if (this != &other)
	{
		copFrom();
	}

	return *this;
}

template <class T>
ElemDLList<T>::~ElemDLList()
{
	delete next; // delete next cell
}

// copy the value and set`s the pointers to NULL!

template <class T>
void ElemDLList<T>::copFrom(const ElemDLList<T>& other)
{
	data = other.data;
	next = NULL;
	prev = NULL;
}