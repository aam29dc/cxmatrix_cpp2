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

getting typeid at runtime with, typeid, but conditional types in overloaded ~ or - operators didn't work for floats, despite being conditioned not to do anything

````c++
if(typeid(_m[0]) != typeid(float) && typeid(_m[0]) != typeid(double) ...)
````

specialized template for certain types, ex: size_t, by inheriting we can also keep original class functions, etc
````c++
template <>
class Matrix<std::size_t> : public Matrix<int> {
public:
	void only_size_t() {}
};
...
Matrix<std::size_t> Mat;
````

pointer to class memebers, other than being more explicit on the type of pointer, idk other uses.
````c++
size_t Matrix<int>::* name = &Matrix<int>::accessible;
````

annoymous namespace means the variables aren't included in other translation units, this is prefered over the C static way:
````c++
//header.hpp
namespace {
	int x;
}

...

//header2.hpp
#include <header.hpp>
int x;	// this doesn't conflict with header.hpp x
````
Nested classes, where we can define the nested class later.
````c++
class A {
public:
	class B;
};

class A::B {
public:
	A::B();
};

A::B::B() {
	//constructor
}
````
reference qualifiers for member functions, invoked for rvales (&&) or lvalues (&). Can have either both r/l-values or neither (regular function) only.
````c++
class C {
public:
	int data;
	int ret_data() & {
		return data;
	}
	int ret_data() && {
		return data;
	}
};

...

void main(){
	C c;
	int x = 0;
	x = c.ret_data();	// lvalue
	x = C().ret_data();	// rvalue
}
````

