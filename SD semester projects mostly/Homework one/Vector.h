#ifndef VECTOR_H
#define VECTOR_H

/// ������� ���������, ������ ����� ����� ���� ������.
/// ��������, ����� ����� �� ����� ����������� ��� ������� ������ �� ���� �������� �������/�����������:
/// 1. ����������� �� ������������.
/// 2. �������� �� �����������.


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
private:
	T * vector;
	size_t size;
	size_t capacity;
};

/// ����������� �� ������������.

template <class T>
inline Vector<T>::Vector()
{
	vector = NULL;
	size = 0;
	capacity = 0;
}

/// ������� �����������

template <class T>
inline Vector<T>::Vector(const Vector<T>& other)
{
	for (size_t i = 0; i < other.getSize(); ++i)
	{
		push(other[i]);
	}
}

/// ������ ���� ������� ��� �������, ��� � ����� ������ ��-������ ����� ����� �� �������.

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

/// �������� =

template <class T>
inline Vector<T>& Vector<T>::operator=(const Vector<T>& other)
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

/// �������� []. ����� �������� �� ����������� ������� ��� �������. ��� ������� � ����������- ������ ��������� �� ������.

template <class T>
inline T& Vector<T>::operator[](int index) const
{
	if (index < 0 || index >= (int)size)
		throw "Invalid index (out of bounds)!";

	return vector[index];
}

/// �������� ������� �� ����������� ������� ��� �������. ��� ������� � ����������- ������ ��������� �� ������.
/// ��������� ��������� ������� �� ������� �� ��������. �� ������� ���������� �� ���������� ��� �������.

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

/// ������ ��-������ ����� ����� �� �������. ��������� ������� � ���� 3 �������� �������.

template <class T>
inline void Vector<T>::resize()
{
	capacity += 3;
	T * temp = new T[capacity];

	for (size_t i = 0; i < size; ++i)
	{
		temp[i] = vector[i];
	}

	delete[] vector;
	vector = temp;
}

/// ����� ������� �� �������(���� �� ���������� � ����).

template <class T>
inline size_t Vector<T>::getSize() const
{
	return size;
}

/// ��������� ���� ������� � ������(���� �������� � ����).

template <class T>
inline bool Vector<T>::empty() const
{
	return size == 0;
}

/// ����������� ������� � ����� ��������� ���������.

template <class T>
inline void Vector<T>::free()
{
	delete[] vector;

	vector = NULL;
	size = 0;
	capacity = 0;
}

/// ����������.

template <class T>
inline Vector<T>::~Vector()
{
	delete[] vector;
}

#endif

