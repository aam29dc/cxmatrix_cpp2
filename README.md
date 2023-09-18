# cxmatrix_cpp2

strint is a string with added functionality of an bool, so branchless string operations with multiplication and addition are possible:
  ````c++
    return strint("Rows can't be zero.")*(rows <= 0) + strint("Cols can't be zero.")*(cols <= 0);
  ````

In this module I tried using strict c++, its newer features, the stl, and avoid using raw pointers.


This is required in the matrix.h, this denotes the possible types that the Matrix class can be.
````c++
template class Matrix<int>;
template class Matrix<unsigned int>;
...
````

This is possible, by friending the ostream and overloading the << operator
````c++
friend inline std::ostream& operator<<(std::ostream& os, const Matrix<T>& src)
{
	src.print();
	return os;
}

...

Matrix<int> A(2,2,0);
std::cout << A;
````

With the use of initalizer lists:
````c++
#include <initializer_list>

template <typename T>
Matrix<T>::Matrix(std::initializer_list<T> l) : _m(l) {
	_rows = 1;
	_cols = _m.size();
}
...
Matrix<int> A{1,2,3,4,5};
````
