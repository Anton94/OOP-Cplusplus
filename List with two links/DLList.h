#pragma once

#include "Elem.h"


template <class T>
class DLLists
{
public:
	List();
	/*List(const List<T>& other);
	List<T>& operator=(const List<T>& other);*/
	T peek_front() const;
	T peek_back() const;
	T pop_front();
	T pop_back();
	void push_front(const T& x);
	void push_back(const T& x);
	bool isEmpty();
	~List();
private:
	Elem<T> head;
};

