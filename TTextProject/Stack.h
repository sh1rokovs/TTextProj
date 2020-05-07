#pragma once
#include <stdio.h>
#include <iostream>

template <class T>
class stack
{
private:
	T* mas;
	int maxsize;
	int pos;

public:
	stack(int _size = 10)
	{
		mas = new T[_size];
		maxsize = _size;
		pos = -1;
	}

	~stack() { delete[] mas; }

	void clear()
	{
		pos = -1;
	}

	int Full() {
		if (pos == maxsize - 1)
			return 1;
		return 0;
	}

	int Empty() {
		return (pos == -1);
	}

	void push(T el) {
		mas[pos + 1] = el;
		pos++;
	}

	T pop() {
		pos--;
		return mas[pos + 1];
	}

	T top() {
		return mas[pos];
	}

	int getsize() const
	{
		return maxsize;
	}
};