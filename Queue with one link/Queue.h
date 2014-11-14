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
	const T& peek() const;
	T& peek();
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

// returns a the value of the next item in the tail.

template <class T>
const T& Queue<T>::peek() const
{
	if (isEmpty())
		throw "The queue is empty and called peek()!";

	return tail->data;
}

// returns a the value of the next item in the tail.

template <class T>
T& Queue<T>::peek()
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
