#ifndef VECTOR_H
#define VECTOR_H

/*
	
	operator[] - WITH NO CHECK...
	getAt - if the index is out of the bounds -> returns NULL pointer.

*/

template <class T>
class Vector
{
public:
	Vector();
	Vector(int size, const T& elem);
	Vector(const Vector<T>& other);
	Vector<T>& operator=(const  Vector<T>& other);
	T* getAt(int index);
	void push(const T& elem);
	void removeElement(int index);
	T& operator[](int index);
	const T& operator[](int index) const;
	int getSize() const;
	bool empty() const;
	void free();
	void resize(int size);
	~Vector();
private:
	void resizeArray(int size);
	void copyFrom(const  Vector<T>& other);
	void setDefaultValues();
private:
	T * vector;
	int size;
	int capacity;
};


template <class T>
inline Vector<T>::Vector()
{
	setDefaultValues();
}

/// Makes vector with given size and makes every element from the vector the given element.

template <class T>
inline Vector<T>::Vector(int newSize, const T& elem)
{
	setDefaultValues();
	resize(newSize);

	for (int i = 0; i < size; ++i)
		vector[i] = elem;
}

template <class T>
inline Vector<T>::Vector(const Vector<T>& other)
{
	copyFrom(other);
}


template <class T>
inline Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

template <class T>
inline void Vector<T>::copyFrom(const Vector<T> & other)
{
	setDefaultValues();
	resizeArray(other.capacity);

	for (int i = 0; i < other.size; ++i)
	{
		vector[i] = other.vector[i];
	}

	size = other.size;
	capacity = other.capacity;
}

template <class T>
inline void Vector<T>::setDefaultValues()
{
	vector = NULL;
	size = 0;
	capacity = 0;
}

template <class T>
inline void Vector<T>::push(const T& elem)
{
	if (size == capacity)
	{
		resizeArray(capacity == 0 ? 2 : 2 * capacity);
	}

	vector[size++] = elem;
}

template <class T>
inline T* Vector<T>::getAt(int index)
{
	if (index < 0 || index >= size)
		return NULL;

	return &vector[index];
}

template <class T>
inline T& Vector<T>::operator[](int index)
{
	return vector[index];
}

template <class T>
inline const T& Vector<T>::operator[](int index) const
{
	return vector[index];
}

template <class T>
inline void Vector<T>::removeElement(int index)
{
	if (index < 0 || index >= size)
		throw "Invalid index (out of bounds)!";

	for (int i = index; i < size - 1; i++)
	{
		vector[i] = vector[i + 1];
	}

	--size;
}


/// Makes the array with the newSize (if < 0 throws exeption). If the newSize is smaller than the current one, trims the last cells.

template <class T>
inline void Vector<T>::resizeArray(int newSize)
{
	if (newSize < 0)
		throw "Invalid size capacity for the vector!";

	T * temp = new T[newSize];

	int numberOfElements = (newSize < size ? newSize : size);

	for (int i = 0; i < numberOfElements; ++i)
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
inline void Vector<T>::resize(int newSize)
{
	resizeArray(newSize);
	size = newSize;
}

template <class T>
inline int Vector<T>::getSize() const
{
	return size;
}

template <class T>
inline bool Vector<T>::empty() const
{
	return size == 0;
}
template <class T>
inline void Vector<T>::free()
{
	delete[] vector;

	setDefaultValues();
}

template <class T>
inline Vector<T>::~Vector()
{
	delete[] vector;
}

#endif

