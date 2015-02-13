#pragma once

#include "ElemDLList.h"


template <class T>
class DLList
{
public:
	DLList();
	DLList(const DLList<T>& other);
	DLList<T>& operator=(const DLList<T>& other);
	DLList<T>& operator+=(const DLList<T>& other);
	~DLList();
public:
	T peek_front() const;
	T peek_back() const;
	T pop_front();
	T pop_back();
	void push_front(const T& x);
	void push_back(const T& x);
	void push_front_list(const DLList<T>& other);
	void push_back_reversed_list(const DLList<T>& other);
	bool isEmpty() const;
	size_t getSize() const;
private:
	void init();
	void free();
	void copyFrom(const DLList<T>& other);
private:
	ElemDLList<T> * head;
	size_t size;
public:
	class Iterator
	{
		friend class DLList<T>;
	public:
		Iterator(ElemDLList<T>* pElement, DLList<T>* pOwner);
		operator bool() const;
		bool operator==(const Iterator& other) const;
		bool operator!=(const Iterator& other) const;
		T& operator*();
		const T& operator*() const;
		typename DLList<T>::Iterator& operator++();
		typename const DLList<T>::Iterator& operator++() const;
	private:
		DLList<T>* owner;
		ElemDLList<T>* element;
	};
public:
	Iterator begin();
	Iterator end();
	void removeAt(Iterator& iter);
};

template <class T>
DLList<T>::DLList()
{
	init();
}

template <class T>
DLList<T>::DLList(const DLList<T>& other)
{
	init();
	copyFrom(other);
}

template <class T>
DLList<T>& DLList<T>::operator=(const DLList<T>& other)
{
	if (this != &other)
	{
		free();
		init();
		copyFrom(other);
	}

	return *this;
}

template <class T>
DLList<T>& DLList<T>::operator+=(const DLList<T>& other)
{
	copyFrom(other);

	return *this;
}

template <class T>
DLList<T>::~DLList()
{
	free();
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

	ElemDLList<T>* n = head->next;

	n->next->prev = head;
	head->next = n->next;

	n->prev = n->next = NULL;
	T val = n->data;
	delete n;
	--size;
	return val;
}

template <class T>
T DLList<T>::pop_back()
{
	if (isEmpty())
		throw "The list is empty and called pop_back()!";

	ElemDLList<T>* n = head->prev;

	n->prev->next = head;
	head->prev = n->prev;

	n->next = n->prev = NULL;
	T val = n->data;
	delete n;
	--size;
	return val;
}

template <class T>
void DLList<T>::push_front(const T& x)
{
	ElemDLList<T> * newElem = new ElemDLList<T>(x);
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
	++size;
}

template <class T>
void DLList<T>::push_back(const T& x)
{
	ElemDLList<T> * newElem = new ElemDLList<T>(x);
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
	++size;
}

/// Goes through every cell othe other list and adds it to the this one(from back to beginning), has pointer last, if happenes push_front_list(tihs)...

template <class T>
void DLList<T>::push_front_list(const DLList<T>& other)
{
	if (other.getSize() <= 0)
		return;

	ElemDLList<T>* n = other.head;

	ElemDLList<T>* last = other.head->next;

	while (n->prev != last)
	{
		push_front(n->prev->data);
		n = n->prev;
	}

	// Push last element if has one...
	if (n->prev != head)
		push_front(n->prev->data);

}

/// Goes through every cell othe other list and adds it to the this one(from back to beginning), has pointer last, if happenes push_back_reversed(tihs)...

template <class T>
void DLList<T>::push_back_reversed_list(const DLList<T>& other)
{
	if (other.getSize() <= 0)
		return;

	ElemDLList<T>* n = other.head;

	ElemDLList<T>* last = other.head->next;

	while (n->prev != last)
	{
		push_back(n->prev->data);
		n = n->prev;
	}

	// Push last element if has one...
	if (n->prev != head)
		push_back(n->prev->data);
}

template <class T>
bool DLList<T>::isEmpty() const
{
	return head->next == head; // size == 0
}

template <class T>
size_t DLList<T>::getSize() const
{
	return size;
}

template <class T>
typename DLList<T>::Iterator DLList<T>::begin()
{
	return Iterator(head->next, this);
}

template <class T>
typename DLList<T>::Iterator DLList<T>::end()
{
	return Iterator(head, this);
}

template <class T>
void DLList<T>::removeAt(Iterator& iter)
{
	if (iter.owner != this)
	{
		throw "Invalid iterator for the list, the iterator is from other list!";
	}

	if (!iter) // iter doesn`t points to the head
	{
		throw "Invalid possition for the DLList iterator and called removeAt()!";
	}
	else
	{
		ElemDLList<T> * n = iter.element;
		++iter;

		n->prev->next = n->next;
		n->next->prev = n->prev;

		n->next = n->prev = NULL;
		delete n;
		--size;
	}
}

template <class T>
void DLList<T>::init()
{
	head = new ElemDLList<T>();
	head->next = head;
	head->prev = head;
	size = 0;
}

// It will delete the memory for the head cell and calls it`s cascade destructor.
// Does not reset the data after it! (doesn`t call init function)

template <class T>
void DLList<T>::free()
{
	ElemDLList<T> * n = head->next;
	head->next = NULL;
	delete n;  // with the next pointer it will start from the first element and go thru all and delete the head element (head->next is null where it will stop)
}

/// NEEDs init before calling copyFrom!!! gets the last element

template <class T>
void DLList<T>::copyFrom(const DLList<T>& other)
{
	if (other.getSize() <= 0)
		return;

	ElemDLList<T>* n = other.head;

	ElemDLList<T>* last = other.head->prev;

	while (n->next != last)
	{
		push_back(n->next->data);
		n = n->next;
	}

	// Push last element if has one...
	if (n->next)
		push_back(n->next->data);
}


/*

///
///	class Iterator
///

*/

template <class T>
DLList<T>::Iterator::Iterator(ElemDLList<T>* pElement, DLList<T>* pOwner) : element(pElement), owner(pOwner) {}

template <class T>
DLList<T>::Iterator::operator bool() const
{
	return element != owner->head;
}

template <class T>
bool DLList<T>::Iterator::operator==(const Iterator& other) const
{
	return element == other.element;
}

template <class T>
bool DLList<T>::Iterator::operator!=(const Iterator& other) const
{
	return !operator==(other);
}

template <class T>
T& DLList<T>::Iterator::operator*()
{
	if (element == owner->head)
		throw "Invalid possition for the DLList iterator and called operator*()!";

	return element->data;
}

template <class T>
const T& DLList<T>::Iterator::operator*() const
{
	if (element == owner->head)
		throw "Invalid possition for the DLList iterator and called operator*()!";

	return element->data;
}

template <class  T>
typename DLList<T>::Iterator& DLList<T>::Iterator::operator++()
{
	if (operator bool())
		element = element->next;
	return *this;
}

template <class  T>
typename const DLList<T>::Iterator& DLList<T>::Iterator::operator++() const
{
	if (operator bool())
		element = element->next;
	return *this;
}