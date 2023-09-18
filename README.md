# cxmatrix_cpp2

strint is a string with added functionality of an bool, so branchless string operations with multiplication and addition are possible:
  ````c++
    return strint("Rows can't be zero.")*(rows <= 0) + strint("Cols can't be zero.")*(cols <= 0);
  ````

In this module I tried using strict c++, its newer features, the stl, and avoided using raw pointers. This wasn't about rewriting cxmatrix, but learning more modern c++.


This is required in the Matrix.hpp, this denotes the possible types that the Matrix class can be.
````c++
template class Matrix<int>;
template class Matrix<unsigned int>;
...
````

std::cout << A; is possible, by friending the ostream and overloading the << operator
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

Allowing the use of initalizer lists on a Matrix class:
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

getting typeid at runtime with, typeid, but conditional types in overloaded ~ or - operators didn't work for floats

````c++
typeid(int) == typeid(_m[0])
````
