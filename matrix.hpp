#ifndef MATRIX_HPP
#define MATRIX_HPP
#pragma once

#include <vector>
#include <iostream>
#include <initializer_list>

template <typename T>
class Matrix {
private:
	size_t _rows, _cols;
	std::vector<T> _m;
	static size_t _count;
public:
	Matrix<T>(const size_t rows = 1, const size_t cols = 1, const T val = 0);
	Matrix<T>(const std::initializer_list<T> l);
	~Matrix<T>();

	inline size_t getRows() const;
	inline size_t getCols() const;
	inline std::vector<T> getMatrix() const;
	inline T getEntry(const size_t i) const;
	void print() const;

	//linker error when def is here and declaration is in hpp file
	friend inline std::ostream& operator<<(std::ostream& os, const Matrix<T>& src)
	{
		src.print();
		return os;
	}


	Matrix<T>(const Matrix<T>& src = {});

	//Matrix<T>& operator ~ ();	//float, double, cant do ~
	//Matrix<T>& operator - ();	// ^

	inline bool operator == (const Matrix<T>& src) const;
	inline bool operator != (const Matrix<T>& src) const;

	Matrix<T>& operator + (const Matrix<T>& src);
	Matrix<T>& operator - (const Matrix<T>& src);
	inline T operator () (const size_t index) const;
	inline T operator [] (const size_t index) const;
};

template <>
class Matrix<std::size_t> : public Matrix<int> {
public:
	void only_size_t() {}
};


#endif