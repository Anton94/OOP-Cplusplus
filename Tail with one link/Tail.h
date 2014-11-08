#pragma once

#include "Elem.h"

template <class T>
class Tail
{
public:
	Tail();
	Tail(const Tail<T>& other);
	Tail<T>& operator=(const Tail<T>& other);
	~Tail();
public:
	T peek();
	void enqueue(const T& el);
	T dequeue();
	bool isEmpty() const;
private:
	void copyFrom(const Tail<T>& other);
	void free();
private:
	Elem<T> *head, *tail;
};

template <class T>
Tail<T>::Tail()
{
	head = tail = NULL;
}

template <class T>
Tail<T>::Tail(const Tail<T>& other)
{
	copyFrom(other);
}

template <class T>
Tail<T>& Tail<T>::operator=(const Tail<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

template <class T>
Tail<T>::~Tail()
{
	free();
}

template <class T>
bool Elem<T>::isEmpty() const
{
	return tail == NULL;
}

template <class T>
void Tail<T>::copyFrom(const Tail<T>& other)
{
	if (!other.isEmpty())
	{
		// let`s set the tail pointer
		tail = new Elem<T>(other.tail);

		// and now let`s set the head pointer
		// to set the head pointer it had to go thru all elements of the tail...
		Elem<T> * p = tail;
		while (p->next != NULL)
		{
			p = p->next;
		}

		head = p;
	}
	else
	{
		tail = head = NULL;
	}
}

// the destructor of the elem type is cascade, so he will delete the rest of the elements in the tail

template <class T>
void Tail<T>::free()
{
	delete tail; // If the tail is empty(tail == NULL), the delete won't do anything..
}