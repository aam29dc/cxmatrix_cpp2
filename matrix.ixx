export module matrix;

import strint;

#include <assert.h>
import <algorithm>;
import <iostream>;
import <ostream>;
import <vector>;

export template <typename T>
class Matrix {
private:
	size_t _rows, _cols;
	std::vector<T> _m;
	static size_t _count;
public:
	size_t accessible;
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

export template <>
class Matrix<std::size_t> : public Matrix<int> {
public:
	void only_size_t() {}
};

template <typename T>
Matrix<T>::Matrix(const size_t rows, const size_t cols, const T val) : _rows(rows), _cols(cols), _m{ 0 } {
	assert(rows != 0 && cols != 0);
	
	_m[0] = val;

	for (size_t i = 1; i < _rows * _cols; ++i) {
		_m.push_back(val);	//std::vector<T>.resize() doesn't take a variable, only a Rvalue
	}

	_count++;
}

template <typename T>
Matrix<T>::Matrix(std::initializer_list<T> l) : _m(l) {
	_rows = 1;
	_cols = _m.size();
}

template <typename T>
Matrix<T>::~Matrix() {
	_m.clear();
	_rows = 0;
	_cols = 0;
}

template <typename T>
inline size_t Matrix<T>::getRows() const { return _rows; }

template <typename T>
inline size_t Matrix<T>::getCols() const { return _cols; }

template <typename T>
inline std::vector<T> Matrix<T>::getMatrix() const { return _m; }

template <typename T>
T Matrix<T>::getEntry(const size_t i) const {
	assert(i <= (_rows * _cols) && i >= 0);
	return _m[i];
}

template <typename T>
void Matrix<T>::print() const {
	for (size_t row = 0; row < _rows; ++row) {
		for (size_t col = 0; col < _cols; ++col) {
			std::cout << _m[col+row*_cols] << " ";
		}
		std::cout << "\n";
	}

	std::cout << "\n";
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& src) {
	assert(src.getRows() != 0 && src.getCols() != 0);
	_m = src.getMatrix();
	_rows = src.getRows();
	_cols = src.getCols();
}

/*template <typename T>
Matrix<T>& Matrix<T>::operator ~ () {
	auto it = _m.begin();

	std::cout << typeid(*it).name();

	if (typeid(*it) != typeid(float)
		&& typeid(*it) != typeid(double)
		&& typeid(*it) != typeid(long double)) {
		for (; it != _m.end(); ++it) {
			*it = ~(*it);
		}
	}
	return *this;
}


template <typename T>
Matrix<T>& Matrix<T>::operator - () {
	auto it = _m.begin();

	if(typeid(*it) != typeid(unsigned int)
		&& typeid(*it) != typeid(unsigned long)
		&& typeid(*it) != typeid(unsigned long long)){
		for (; it != _m.end(); ++it) {
			*it = -(*it);
		}
	}
	return *this;
}*/

template <typename T>
inline bool Matrix<T>::operator == (const Matrix<T>& src) const {
	return src.getRows() == _rows && src.getCols() == _cols && src.getMatrix() == _m;
}

template <typename T>
inline bool Matrix<T>::operator != (const Matrix<T>& src) const {
	return !(*this == src);
}

template <typename T>
Matrix<T>& Matrix<T>::operator + (const Matrix<T>& src) {
	assert(_rows == src.getRows() && _cols == src.getCols());
	for (size_t i = 0; i < _rows * _cols; ++i) {
		_m[i] += src.getEntry(i);
	}

	return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator - (const Matrix<T>& src) {
	assert(_rows == src.getRows() && _cols == src.getCols());
	for (size_t i = 0; i < _rows * _cols; ++i) {
		_m[i] -= src.getEntry(i);
	}

	return *this;
}

template <typename T>
inline T Matrix<T>::operator () (const size_t index) const {
	return this->getMatrix()[index];
}

template <typename T>
inline T Matrix<T>::operator [] (const size_t index) const {
	return this->getMatrix()[index];
}

template <typename T>
size_t Matrix<T>::_count = 0;

template class Matrix<int>;
template class Matrix<unsigned int>;
template class Matrix<float>;
template class Matrix<double>;
template class Matrix<long>;
template class Matrix<unsigned long>;
template class Matrix<long long>;
template class Matrix<unsigned long long>;
template class Matrix<long double>;