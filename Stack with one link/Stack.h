#ifndef LINK_STACK
#define LINK_STACK

// Structure: tos->firstElement --(*next)--->secondElement----(*next)--->thirdElement
// with cascade destructor

template <class T>
struct elem
{
public:
	elem(const T& x, elem<T>* p = NULL);
	elem(const elem & other);
	elem& operator=(const elem& other);
	~elem();
private:
	void copyFrom(const elem & other);
	void free();
public:
	T data;
	elem<T>* next;
};

template <class T>
elem<T>::elem(const T& x, elem<T>* p = NULL) : data(x), next(p) {}

template <class T>
elem<T>::elem(const elem & other)
{
	copyFrom(other);
}

template <class T>
elem<T>& elem<T>::operator=(const elem & other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

template <class T>
elem<T>::~elem()
{
	free();
}

template <class T>
void elem<T>::copyFrom(const elem & other)
{
	data = other.data;

	if (other.next)
	{
		next = new elem<T>(*other.next);
	}
	else
	{
		next = NULL;
	}
}

template <class T>
void elem<T>::free()
{
	if (next)		  // if next is NULL it will do , anyway..
		delete next;  // deletes the memory and calls the destructor of the element, pointed by the 'next' and etc...
}


template <class T>
class Stack
{
public:
	Stack();
	Stack(const Stack& other);
	Stack& operator=(const Stack& other);
	~Stack();
public:
	const T& peek() const;
	T pop();
	void push(const T& val);
	bool isEmpty() const;
private:
	void free();
	void copyFrom(const Stack& other);

private:
	elem<T> * tos; // top of stack
};

template <class T>
Stack<T>::Stack() : tos(NULL) {}

template <class T>
Stack<T>::Stack(const Stack& other)
{
	copyFrom(other);
}

template <class T>
Stack<T>& Stack<T>::operator=(const Stack& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

template <class T>
Stack<T>::~Stack()
{
	delete tos;
}

template <class T>
const T& Stack<T>::peek() const
{
	if (isEmpty())
	{
		throw "Stack is empty and called peek!";
	}

	return tos->data;
}

template <class T>
T Stack<T>::pop()
{
	if (isEmpty())
	{
		throw "Stack is empty and called pop!";
	}

	T val = tos->data;
	elem<T> * temp = tos;
	tos = tos->next;
	temp->next = NULL; // break the cascade destructor
	delete temp;
	return val;
}

template <class T>
void Stack<T>::push(const T& val)
{
	elem<T> * temp = new elem < T >(val);
	temp->next = tos;
	tos = temp;

	// OR:  elem<T> * tos = new elem<T>(val, tos);
}

template <class T>
bool Stack<T>::isEmpty() const
{
	return tos == NULL; // !tos
}

template <class T>
void  Stack<T>::free()
{
	while (!isEmpty())
	{
		pop();
	}
}

template <class T>
void  Stack<T>::copyFrom(const Stack& other)
{
	if (other.tos)
		tos = new elem<T>(*other.tos);
}

#endif

