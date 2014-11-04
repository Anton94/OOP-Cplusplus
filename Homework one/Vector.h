#ifndef VECTOR_H
#define VECTOR_H

/// Запазва наредбата, когато някой елемт бъде изтрит.
/// Обектите, които могат да бъдат съхранявани във вектора трябва да имат следните функции/възможности:
/// 1. Конструктор по подразбиране.
/// 2. Оператор за присвояване.


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

/// Конструктор по подразбиране.

template <class T>
inline Vector<T>::Vector()
{
	vector = NULL;
	size = 0;
	capacity = 0;
}

/// Копиращ конструктор

template <class T>
inline Vector<T>::Vector(const Vector<T>& other)
{
	for (size_t i = 0; i < other.getSize(); ++i)
	{
		push(other[i]);
	}
}

/// Добавя един елемент във вектора, ако е нужно заделя по-голямо парче памет за вектора.

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

/// Оператор =

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

/// Оператор []. Връща елемента на съответната позиция във вектора. Ако индекса е некоректен- хвърля съобщение за грешка.

template <class T>
inline T& Vector<T>::operator[](int index) const
{
	if (index < 0 || index >= (int)size)
		throw "Invalid index (out of bounds)!";

	return vector[index];
}

/// Премахва елемент на съответната позиция във вектора. Ако индекса е некоректен- хвърля съобщение за грешка.
/// Премества последния елемент на мястото на изтрития. Не запазва подредбата на елементите във вектора.

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

/// Заделя по-голямо парче памет за вектора. Увеличава вектора с нови 3 свободни позиции.

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

/// Връща размера на вектора(броя на елементите в него).

template <class T>
inline size_t Vector<T>::getSize() const
{
	return size;
}

/// Проверява дали вектора е празен(няма елементи в него).

template <class T>
inline bool Vector<T>::empty() const
{
	return size == 0;
}

/// Освобождава паметта и сетва началните стойности.

template <class T>
inline void Vector<T>::free()
{
	delete[] vector;

	vector = NULL;
	size = 0;
	capacity = 0;
}

/// Деструктор.

template <class T>
inline Vector<T>::~Vector()
{
	delete[] vector;
}

#endif

