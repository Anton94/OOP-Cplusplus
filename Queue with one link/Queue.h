#pragma once

/*
	If some memory allocations failed- throws exeption.
	If the peek() or dequeue() is called with empty tail- throws exeption.
*/

#include "ElemQueue.h"

template <class T>
class Queue
{
public:
	Queue();
	Queue(const Queue<T>& other);
	Queue<T>& operator=(const Queue<T>& other);
	~Queue();
public:
	T peek() const;
	T dequeue();
	void enqueue(const T& el);
	bool isEmpty() const;
	size_t getSize() const;
private:
	void copyFrom(const Queue<T>& other);
	void free();
	void init();
private:
	ElemQueue<T> *head, *tail;
	size_t size;
public:
	class Iterator
	{
	public:
		Iterator(ElemQueue<T>* pElement, Queue<T>* pOwner);
		operator bool() const;
		bool operator==(const Iterator& other) const;
		bool operator!=(const Iterator& other) const;
		Iterator& operator++();
		const Iterator& operator++() const;
		T& operator*();
		const T& operator*() const;
	private:
		Queue<T>* owner;
		ElemQueue<T>* element;
	};

	Iterator begin();
	Iterator end();
};

template <class T>
Queue<T>::Queue()
{
	init();
}

template <class T>
Queue<T>::Queue(const Queue<T>& other)
{
	copyFrom(other);
}

template <class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

template <class T>
Queue<T>::~Queue()
{
	delete tail;
}

// returns a copy of the value of the next item in the tail.

template <class T>
T Queue<T>::peek() const
{
	if (isEmpty())
		throw "The queue is empty and called peek()!";

	return tail->data;
}

template <class T>
T Queue<T>::dequeue()
{
	if (isEmpty())
		throw "The queue is empty and called dequeue()!";

	ElemQueue<T> * x = tail;
	tail = tail->next;	// if the element was last one, the next will be NULL, so the tail will be NULL->empty tail
	T val = x->data;
	x->next = NULL;		// to break the cascade destructor of the ElemQueue class
	delete x;
	--size;
	return val;
}

template <class T>
void Queue<T>::enqueue(const T& other)
{
	ElemQueue<T> * p = new ElemQueue<T>(other); // creates new cell with value- 'other' and next pointer- 'NULL'
	
	// if the list is empty- makes the tail and the head pointing the created element
	if (isEmpty())
		tail = p;
	else
		head->next = p;

	head = p;
	++size;
}

template <class T>
bool Queue<T>::isEmpty() const
{
	return tail == NULL; // size == 0
}

template <class T>
size_t Queue<T>::getSize() const
{
	return size;
}

template <class T>
void Queue<T>::copyFrom(const Queue<T>& other)
{
	if (!other.isEmpty())
	{
		// let`s set the tail pointer
		tail = new ElemQueue<T>(*other.tail);

		// and now let`s set the head pointer
		// to set the head pointer it had to go thru all elements of the tail...
		ElemQueue<T> * p = tail;
		while (p->next != NULL)
		{
			p = p->next;
		}

		head = p;

		size = other.size;
	}
	else
	{
		init();
	}
}

// the destructor of the ElemQueue class is cascade, so he will delete the rest of the elements in the tail

template <class T>
void Queue<T>::free()
{
	delete tail; // If the tail is empty(tail == NULL), the delete won't do anything..
	init();
}

template <class T>
void Queue<T>::init()
{
	tail = head = NULL;
	size = 0;
}

// begins with the tail element and ends at the head element

template <class T>
typename Queue<T>::Iterator Queue<T>::begin()
{
	return Iterator(tail, this);
}

template <class T>
typename Queue<T>::Iterator Queue<T>::end()
{
	return Iterator(head, this);
}

/*

///
/// class Iterator
///

*/

template <class T>
Queue<T>::Iterator::Iterator(ElemQueue<T>* pElement, Queue<T>* pOwner) : element(pElement), owner(pOwner) {}

template <class T>
Queue<T>::Iterator::operator bool() const
{
	return element; // element != NULL
}

// compare the two pointers (if they point to the same object)

template <class T>
bool Queue<T>::Iterator::operator==(const Iterator& other) const
{
	return element == other.element;
}

template <class T>
bool Queue<T>::Iterator::operator!=(const Iterator& other) const
{
	return !operator==(other);
}

// if the iterator points to some valid object->it translate the iterator to the next object

template <class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++()
{
	if (element)
		element = element->next;

	return *this;
}

template <class T>
typename const Queue<T>::Iterator& Queue<T>::Iterator::operator++() const
{
	if (element)
		element = element->next;

	return *this;
}

template <class T>
T& Queue<T>::Iterator::operator*()
{
	if (!element)
		throw "Invalid possition for the Queue iterator and called operator*()!";

	return element->data;
}

template <class T>
const T& Queue<T>::Iterator::operator*() const
{
	if (!element)
		throw "Invalid possition for the Queue iterator and called operator*()!";

	return element->data;
}