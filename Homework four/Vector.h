#pragma once

template <class T>
class Vector
{
public:
	Vector();
	Vector(const Vector<T>& other);
	void push(const T& elem);
	void removeElement(int index);
	Vector<T>& operator=(const  Vector<T>& other);
	T& operator[](int index) const;
	size_t getSize() const;
	bool empty() const;
	void free();
	~Vector();
private:
	void resize();
	void copyFrom(const Vector<T>& other);
private:
	T * vector;
	size_t size;
	size_t capacity;
};

template <class T>
inline Vector<T>::Vector()
{
	vector = NULL;
	size = 0;
	capacity = 0;
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
void Vector<T>::copyFrom(const Vector<T>& other)
{
	vector = new T[other.capacity];
	size = other.size;
	capacity = other.capacity;

	for (size_t i = 0; i < other.size; ++i)
	{
		vector[i] = other.vector[i];
	}
}


template <class T>
inline void Vector<T>::push(const T& elem)
{
	if (size == capacity)
	{
		try
		{
			resize();
		}
		catch (char* msg)
		{
			std::cerr << "Error: " << msg << "\n";
			return;
		}
	}

	vector[size++] = elem;
}

template <class T>
inline T& Vector<T>::operator[](int index) const
{
	if (index < 0 || index >= (int)size)
		throw "Invalid index (out of bounds)!";

	return vector[index];
}

template <class T>
inline void Vector<T>::removeElement(int index)
{
	if (index < 0 || index >= (int)size)
		throw "Invalid index (out of bounds)!";

	for (size_t i = (size_t)index; i < size - 1; i++)
	{
		vector[i] = vector[i + 1];
	}

	--size;
}

template <class T>
inline void Vector<T>::resize()
{
	capacity = (!capacity) ? 2 : capacity * 2; // if the capacity is 0, make it 2, otherwise make it twice as bigger
	T * temp = new T[capacity];

	for (size_t i = 0; i < size; ++i)
	{
		temp[i] = vector[i];
	}

	delete[] vector;
	vector = temp;
}

template <class T>
inline size_t Vector<T>::getSize() const
{
	return size;
}
template <class T>
bool Vector<T>::empty() const
{
	return size == 0;
}

template <class T>
inline void Vector<T>::free()
{
	delete[] vector;

	vector = NULL;
	size = 0;
	capacity = 0;
}

template <class T>
inline Vector<T>::~Vector()
{
	delete[] vector;
}
