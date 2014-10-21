#ifndef STACK_H
#define STACK_H

// Stack with dynamic array
// Template so the functions had to be inline...

template <class T>
class Stack
{
public:
	// Default constructor, the stack starts with array with 8 elements.
	Stack()
	{
		size = 8;
		top = 0;
		arr = new T[size];		
	}

	// Copy constructor.
	Stack(const Stack& other)
	{
		arr = new T[other.size];

		for (size_t i = 0; i < other.size; ++i)
		{
			arr[i] = other.arr[i];
		}
		
		top = other.top;
		size = other.size;
	}

	// Operator '=' .
	Stack& operator=(const Stack& other)
	{
		if (this != &other)
		{
			delete[] arr;
			arr = new T[other.size];

			for (size_t i = 0; i < other.size; ++i)
			{
				arr[i] = other.arr[i];
			}

			top = other.top;
			size = other.size;
		}

		return *this;
	}

	// Insert new element into the stack.
	void push(T val)
	{
		if (top == size) // stack is full
		{
			resize();
		}

		arr[top++] = val;
	}

	// Returns a copy of the object.
	T pop()
	{
		if (isEmpty())
		{
			throw "The stack is empty and called pop!";
		}

		return arr[--top];
	}

	// Returns the top element of the stack.
	T peek() const
	{
		if (isEmpty())
		{
			throw "The stack is empty and called top!";
		}

		return arr[top - 1];
	}

	bool isEmpty() const
	{
		return top == 0;
	}

	~Stack()
	{
		delete[] arr;
	}

private:
	// Resize the array (doubles the size). Copy the values in the new array.
	void resize()
	{
		T* temp = arr;		
		arr = new T[size * 2];

		for (size_t i = 0; i < size; ++i)
		{
			arr[i] = temp[i];
		}

		size *= 2;
		delete[] temp;
	}

private:
	T * arr;
	unsigned size;
	unsigned top;
};

#endif

