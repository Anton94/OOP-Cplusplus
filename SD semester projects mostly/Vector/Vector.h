#ifndef VECTOR_H
#define VECTOR_H

/// Запазва наредбата, когато някой елемт бъде изтрит.
/// Обектите, които могат да бъдат съхранявани във вектора трябва да имат следните функции/възможности:
/// 1. Конструктор по подразбиране.
/// 2. Оператор за присвояване.
/// 3. Копиращ конструктор.


template <class T>
class Vector
{
public:
	Vector();
	Vector(const Vector<T>& other);
	void push(const T& elem);
	void removeElement(int index);
	Vector<T>& operator=(const  Vector<T>& other);
	T& operator[](int index);
	const T& operator[](int index) const;
	int getSize() const;
	bool empty() const;
	void free();
	void resize(int size);
	~Vector();
private:
	void resizeArray(int size);
private:
	T * vector;
	int size;
	int capacity;
};


template <class T>
Vector<T>::Vector()
{
	vector = NULL;
	size = 0;
	capacity = 0;
}


template <class T>
Vector<T>::Vector(const Vector<T>& other)
{
	for (size_t i = 0; i < other.getSize(); ++i)
	{
		push(other[i]);
	}
}


template <class T>
void Vector<T>::push(const T& elem)
{
	if (size == capacity)
	{
		resizeArray(capacity == 0 ? 2 : 2 * capacity);
	}

	vector[size++] = elem;
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
	if (this != &other)
	{
		free();
		for (size_t i = 0; i < other.getSize(); ++i)
		{
			push(other[i]);
		}
	}

	return *this;
}


template <class T>
T& Vector<T>::operator[](int index)
{
	if (index < 0 || index >= (int)size)
		throw "Invalid index (out of bounds)!";

	return vector[index];
}


template <class T>
const T& Vector<T>::operator[](int index) const
{
	if (index < 0 || index >= (int)size)
		throw "Invalid index (out of bounds)!";

	return vector[index];
}

template <class T>
void Vector<T>::removeElement(int index)
{
	if (index < 0 || index >= (int)size)
		throw "Invalid index (out of bounds)!";

	for (size_t i = (size_t)index; i < size - 1; i++)
	{
		vector[i] = vector[i + 1];
	}

	--size;
}


/// Makes the array with the newSize (if < 0 throws exeption). If the array before the resize is smaller than the array after the resize- all new cells are with default constructor.

template <class T>
void Vector<T>::resizeArray(int newSize)
{
	if (newSize < 0)
		throw "Invalid size capacity for the vector!";

	T * temp = new T[newSize];

	int numberOfElements = (newSize < size ? newSize : size);

	for (size_t i = 0; i < numberOfElements; ++i)
	{
		temp[i] = vector[i];
	}

	delete[] vector;
	vector = temp;
	size = numberOfElements;
	capacity = newSize;
}

/// Public method. Resize the vector and fill the rest of the cells with default once(if the new size is bigger than the current one) (size = newSize...)

template <class T>
void Vector<T>::resize(int newSize)
{
	resizeArray(newSize);
	size = newSize;
}

template <class T>
int Vector<T>::getSize() const
{
	return size;
}

template <class T>
bool Vector<T>::empty() const
{
	return size == 0;
}
template <class T>
void Vector<T>::free()
{
	delete[] vector;

	vector = NULL;
	size = 0;
	capacity = 0;
}

template <class T>
Vector<T>::~Vector()
{
	delete[] vector;
}

#endif

