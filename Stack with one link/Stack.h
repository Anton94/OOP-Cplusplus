#ifndef LINK_STACK
#define LINK_STACK

// Structure: tos->firstElement --(*next)--->secondElement----(*next)--->thirdElement
// with cascade destructor

template <class T>
struct elem
{
	T data;
	elem<T>* next;
	elem(const T& x, elem<T>* p = NULL) : data(x), next(p) {}
	~elem()
	{
		if (next)
		{
			delete next;
		}
	}
};

template <class T>
class Stack
{
public:
	Stack() : tos(NULL) {}

	const T& peek() const
	{
		if (isEmpty())
		{
			throw "Stack is empty and called peek!";
		}

		return tos->data;
	}

	T pop()
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

	void push(const T& val)
	{
		elem<T> * temp = new elem < T >(val);
		temp->next = tos;
		tos = temp;

		// OR:  elem<T> * tos = new elem<T>(val, tos);
	}

	bool isEmpty() const
	{
		return tos == NULL; // !tos
	}

	~Stack()
	{
		delete tos;
	}
private:
	elem<T> * tos; // top of stack


};

#endif

