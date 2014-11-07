#pragma once

template <class T>
struct Elem
{
public:
	Elem(const T& x, Elem<T>* p = NULL);
	//Elem(const Elem<T> & other);
	//Elem<T>& operator=(const Elem<T> & other);
	~Elem();
public:
	Elem<T> * next;
	T data;
};

template <class T>
Elem<T>::Elem(const T& x, Elem<T>* p = NULL) : data(x), next(p) {}

// cascade destructor, till next is NULL.

template <class T>
Elme<T>::~Elem()
{
	delete next;
}