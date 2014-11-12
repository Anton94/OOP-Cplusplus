#pragma once

#include "Elem.h"


template <class T>
class DLList
{
public:
	DLList();
	/*DLList(const DLList<T>& other);
	DLList<T>& operator=(const DLList<T>& other);*/
	T peek_front() const;
	T peek_back() const;
	T pop_front();
	T pop_back();
	void push_front(const T& x);
	void push_back(const T& x);
	bool isEmpty() const;
	~DLList();
private:
	Elem<T> * head;
};

template <class T>
DLList<T>::DLList()
{
	head = new Elem<T>();
	head->next = head;
	head->prev = head;
}

template <class T>
T DLList<T>::peek_front() const
{
	if (isEmpty())
		throw "The list is empty and called peek_front()!";
	
	return head->next->data;
}

template <class T>
T DLList<T>::peek_back() const
{
	if (isEmpty())
		throw "The list is empty and called peek_back()!";

	return head->prev->data;
}

template <class T>
T DLList<T>::pop_front()
{
	if (isEmpty())
		throw "The list is empty and called pop_front()!";

	Elem<T>* n = head->next;

	n->next->prev = head;
	head->next = n->next;

	n->prev = n->next = NULL;
	T val = n->data;
	delete n;
	return val;
}

template <class T>
T DLList<T>::pop_back()
{
	if (isEmpty())
		throw "The list is empty and called pop_back()!";

	Elem<T>* n = head->prev;

	n->prev->next = head;
	head->prev = n->prev;

	n->next = n->prev = NULL;
	T val = n->data;
	delete n;
	return val;
}

template <class T>
void DLList<T>::push_front(const T& x)
{
	Elem<T> * newElem = new Elem<T>(x);
	newElem->next = head->next;
	newElem->prev = head;

	if (!isEmpty()) 
	{
		head->next->prev = newElem;
	}
	else
	{
		head->prev = newElem;
	}

	head->next = newElem;
}

template <class T>
void DLList<T>::push_back(const T& x)
{
	Elem<T> * newElem = new Elem<T>(x);
	newElem->next = head;
	newElem->prev = head->prev;

	if (!isEmpty())
	{
		head->prev->next = newElem;
	}
	else
	{
		head->next = newElem;
	}

	head->prev = newElem;
}

// It will delete the memory for the head cell and calls it`s cascade destructor.

template <class T>
DLList<T>::~DLList()
{
	Elem<T> * n = head->next;
	head->next = NULL;
	delete n;  // with the next pointer it will start from the first element and go thru all and delete the head element (head->next is null where it will stop)
}

template <class T>
bool DLList<T>::isEmpty() const
{
	return head->next == head;
}