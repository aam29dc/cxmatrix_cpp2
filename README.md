# cxmatrix_cpp2

strint is a string with added functionality of an bool, so branchless string operations with multiplication and addition are possible:
  ````c++
    return strint("Rows can't be zero.")*(rows <= 0)+strint("Cols can't be zero.")*(cols <= 0);
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

a function pointer can't point a function within a class (member function): we either change the function pointer or make the member function `static` (one function for all objects of this type):
````c++
void (*cb)() = nullptr;

class A{
public:
	void func(){
	}
}

cb = func; 	// error: func is value of type A::void not void

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

pointer to class members, other than being more explicit on the type of pointer, idk other uses.
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
When we define a Base class, and a Derived class, we must use pointers to use polymorphic behavior.
````c++
class A{
virtual void func();
};

class B: public A{
void func();
}

void main(){
	A a[10];
	B b;
	a[0] = b;	// this will end up calling the base class function, because we need to use pointers to get polymorphic behavior
}
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
Reference Qualifiers for member functions, invoked for rvalues (&&) or lvalues (&). Can have either both r/l-values or neither (regular function) only. An lvalue is an object(int,...), and a rvalue is a value (32).
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

lambda expressions or annoymous functions are usually, short, specific use, like a loop. Syntax: [pass by value, or reference to body of function]<template>(function parameters) -> return type {function body}(invokes function);
````c++
int n  = 5;
auto a = [&n]<typename T>(const T val) -> T{ return val*n*5;}(3);	//returns 75
...
````

3-way comparison operator (<=>) returns negative, positive, or zero based on operands, auto keyword should be used:
````c++
int a = 2;
int b = 3;

auto result = a <=> b;

if(result < 0){
	std::cout << "less";
}
else if(result == 0){
	std::cout << "equal";
}
else if(reuslt > 0){
	std::cout << "greater";
}
//prints "less"
````

initilization in a ranged base for loop:
````c++
for(std::vector<int> v{1,2,3}; auto& i : v){
	std::cout << i;	//prints 123
}
````

import, export, module: C++ std has to be latest (23/experimental), and "Scan Sources for Module Dependencies" has to be set to Yes, and the file extenstion has to be .ixx in VSC.
Benefits are faster compile times, and less source files since declarations aren't required in seperate header files. Not everything has to be included in the module. Include guards are not required.
````c++
//mod1.ixx
export module mod1;
int not_exported_func(){ return 23;}
export int func_from_mod1(){
	return 12;
}
````
...
````c++
//main.cpp
import mod1;
import <iostream>;

int main(){
	std::cout << func_from_mod1();	//prints out 12
	not_exported_func();	// error: id not found
	return 0;
}
````
declare global variables extern in hpp file and declare again in cpp file
````c++
//file.hpp
extern int gv;
````
````c++
//file.cpp
int gv;
````

to add a description to a function /* describe ur function */ when the function is brought up in an IDE like vs, .hpp comment seems to overwrite .cpp comment:
````c++
/* description */
int func();
````
to support chaining in your classes, the member function should return invoking object (this):
````c++
class A {
public:
	A& some(){
		return *this;
	}
}
A a.some().some();
````
move assignment, move constructor, copy assignment, copy constructor: syntax, how they operate, and how to invoke them. Copy makes copies, Move moves or shares without making a copy, etc
````c++
class A {
public:
	//C
	A() {}
	//MA
	A& operator=(A&& other) {
		/*check if other is this, if other is nullptr,
		assign this to other, then other to nullptr*/
	}
	//CA
	A& operator=(const A& other) {
		/*check if other is this, if other is nullptr
		* if this is null allocate memory
		* copy values into data elements
		*/
	}
	//MC
	A(A&& other) {
		/*check if other is nullptr,
		* then point this to other
		* then other to nullptr
		*/
	}
	//CC
	A(const A& other) {
		/*check if other is nullptr
		* since its a constructor: allocate memory,
		* copy values into data elements
		*/
	}
};
#include <vector>
int main() {
	A a();	//C
	A b(a);	//C, CC
	a = b; //CA
	a = std::move(b); //MA
	std::vector<A> vec(A()) // C -> MC
	return 0;
}
````
With a Singleton class, the static instance should be defined in the .cpp file, otherwise you'll get a linker error from including multiple instances when including it in the .hpp file:
````c++
//.hpp file
class Singleton{
private:
	Singleton() = default;
	~Singleton() = default;
	static Singleton* instance;
public:
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	static Singleton* instance(){
		if(nullptr == instance) return instance = new Singleton;
		return instance;
	}
}

//.cpp file
Singleton* Singleton::instance = nullptr;
...
````
inheritance with access modifiers: B is a subtype of A, and within B we have access to public and protected data members of A, outside of B we only have access to the public one. B never has access to A's private data members(unless B is a friend of A). Changing the inheritance access modifier shifts the modifiers 1.public -> 2.protected -> 3.private. If public then they all stay the same, if private then they're all private. If protected then public goes to protected.
````c++
class A {
private:
	int x;
protected:
	int y;
public:
	int z;
	A() : x(0), y(1), z(2) {
		A::x = -1;
		A::A::A::A::A::x = -2;	//unusal but it works
	}

	int retX() const { return x; }
	int retY() const { return y; }

};

class B : public A {
public:
	B() {
		/*B::A::x = 0;	// all the same, and all access violations
		B::x = 0;
		x = 0;*/

		y = 4;
		z = 3;
	}
};
````

with inheritance, a calling function that uses the base class in the parameter is able to take derived classes as a value. It'll act as the base class. Derived classes cannot take base or classes before in ther chain hierarchy as a value in the parameter. Here: B inherits A, B is a subclass of A, etc.
````c++
void takes_a(A* a) {
	a->say();
	return;
}

void takes_b(B* b) {
	b->say();
	return;
}

int main() {
	A a;
	A* Ap = new A;
	A* Ab = new B;
	B b;
	B* Bp = new B;

	//prints out // A A B A B A A
	takes_a(&a);
	takes_a(&b);
	takes_b(&b);
	takes_a(Bp);
	takes_b(Bp);
	takes_a(Ap);
	takes_a(Ab);
}
````
When A's function say() is virtual, then takes_a(&b) will call B's say() instead of A's even though the parameter is type A, it will invoke the derived classes function (if it exists, otherwise it'll use the Base Class).
````c++
class A {
public:
	A() : a_x(0) {}
	~A() {}
	int a_x;
	virtual void say() {
		std::cout << "A\n";
	}
};

class B : public A {
public:
	B() : b_x(1) {}
	int b_x;

	void say() {
		std::cout << "B\n";
	}
};

int main() {
	A a;
	A* Ap = new A;
	A* Ab = new B;

	B b;
	B* Bp = new B;

	takes_a(&a);	//a
	takes_a(&b);	//b
	takes_b(&b);	//b
	takes_a(Bp);	//b
	takes_b(Bp);	//b
	takes_a(Ap);	//a
	takes_a(Ab);	//b
} // A B B B B A B
````

When a derived class (B) is created on the heap, the base classes destructor should be set to virtual, so the derived class is able to invoke the destructor on the base class. When class B is created on the stack, when it goes out of scope, it'll invoke the base destructor virtual or not. B "is a" A, if we were to make another class C that has a data member in it of class A, then C would be "has a" A.
````c++
class A {
public:
	A() { std::cout << "AC\n"; }
	virtual ~A() { std::cout << "AD\n"; }
};

class B : public A {
public:
	B() : b_x(1) { std::cout << "BC\n"; }
	~B() { std::cout << "BD\n"; }
};

int main(){
	B b; //this will go out of scope and call the destructor on A regardless if its virtual: AC,BC,BD,AD
	A *ab = new B; // AC BC,
	delete ab;	// now: BD AD
}
````
There are two different syntaxes for operator overloading, one with friend and one without. The friend will take two parameters. The nonfriend will only take one, and we'll have to use (this) to explicitly access the data memebers on the called object. I prefer to use the nonfriend way for overloading operators, unless its: cout <<.  cin >>, etc Friends should come from other foreign classes.
````c++
class Vector2D{
private:
	int x, y;
public:
	friend Vector2D& operator+(Vector2D& l, const Vector2D& r){
		l.x += r.x;
		l.y += r.y;
		return l;
	}
	//versus
	Vector2D& operator+(const Vector2D& other){
		this->x += other.x;
		this->y += other.y;
		return *this;
	}
}
````

two variables can be used w/ the same name, if one is global and the other is local scope, the scope resolution operator `::` is used to refer to the global scope variable.
````c++
int x = 0;
int main(){
	int x = 1;
	std::cout << ::x << " " << x;	//prints "0 1"
	return 0;
}
````

with multiple inheritances, virtual inheritance prevents additional copies from a Base class when other classes are using that Base.
````c++
class A {
    public:
    int x;
    A() : x(0) {}
};

class B : virtual public A {
};

class C : virtual public A {
};

class D : public B, public C {
};

int main()
{
    D d;
    std::cout << d.x; //otherwise if B and C didn't inherit A with virutal we would have to d.B::x or d.C::x as it is disambigious, otherwise it uses the first inherited classes x (in this case it would be B)
}
````
Here this union is always the size of a `long long` even when its used as a int. Unions can only be one, not all, and its the size of its largest element.
````c++
union Abc {
	int x;
	float y;
	long long z;
}
````
a `constexpr` pointer is equal to a `const` pointer. A constexpr function is a function that can be used in a constant expression; it should only have one return, and it is evaluated at compile time. A literal is a constant expression. Constexpr functions are implicitly inline. A inline function is a function that doesn't use the stack call operations, it just replaces the call with the inner body.
````c++
constexpr int* cep = nullptr;	// these two pointers are
int* const cp = nullptr;	// the same kind

constexpr int func() {		// this function is implicitly inline and is evaluted at compile time
	return 123;
}
````
`decltype` is like `auto` except that it doesn't evaluate the expression of the function. It just takes its return type without evaluation. `decltype(auto) z = 123;` takes return type of rvalue.
````c++
decltype(f()) num = 123;	// num has the type of the return type of f()
````
If a data member is defined as `mutable` then even if the class object is defined as `const` the mutable data member can still be changed.
````c++
class A{
public:
	int x;
	mutable int y;
	A() : x(0), y(1) {}
}

int main(){
	const A a;	// a is const, except its mutable data member y.
	a.x = 123;	// error: a is const
	a.y = 234;	// ok: y is defined a mutable, despite the class object being const
}

````
Comments to help describe the function, `\param` and `\returns` within the comment section before a function in the .c/.cpp file, for IDE's when a user mouses over a function.
````c++
/* generate shape with lines going from every point
* \param num the number of sides
* \returns void
*/
void drawLinedShape(const unsigned int num, const int x = 0, const int y = 0,
	const unsigned int rad = 10, const float rot = 0.0f) {
	//...
}
````
`try`, `throw`, `catch` for exception handling. `try` calls some function, that may `throw` an exception of a specific type, then `catch` catches the raised exception.
````c++
auto func(int val) -> void {
	if (val == 1) {	throw std::exception("error");	}
	else if (val == 2) {	throw std::runtime_error("rte");}
	else throw std::string("error");
	return;
}

auto main() -> int {
	try {	func(22);	}
	catch (std::exception) {	std::cout << "couldn't connect\n";	}
	catch (std::runtime_error) {	std::cout << "runtime error\n";	}
	catch (...) {	std::cout << "unknown error.";	}
	return 0;
}
````

`explicit` for constructors, to prevent implicit use of a constructor.

`noexcept(true)` on a function to prevent propagation of an exception in a function. `noexcept(false)` is the default on every function.

`override` on virtual member functions in derived classes

`volatile` on variables that have side effects

`dynamic_cast<class>` for down casting for example from a base class to a derived class.

`const_cast<type>` for removing constness on a function; helps prevent code duplication, instead of having to duplicate a function with const.

----------------------------------------------------------------------------------------------------------------------------------------

Three different solutions for templated classes having a seperate header file for declarations and a cpp file for definitions.

-First solution is to have one header file, and no cpp file, and to define everything in the header file.

-Second solution is explicit initiation of all types the class will take: `template class Node<int>;` etc, in the cpp file.

-Third solution is to include the cpp file in the header file at the end. (use include guards on both files).

````c++
//.hpp file
	#ifndef NODE_DEC
	#define NODE_DEC
		template<typename T>
		class Node {
			T data;
		public:
			Node();
		}
		#include "Node.cpp"
	#endif

//.cpp file
	#ifndef NODE_DEF
	#define NODE_DEF
		template<typename T>
		Node<T>::Node(){
			//yada yada yada
		}
	#endif
````
Template metaprogramming similar to constexpr for computing at compile time. `constexpr` is preferred for readability. TMP can sometimes have faster compile times, unless compile time/performance is an issue `constexpr` should be used instead.
````c++
template<unsigned int n>
struct factorial {
	enum { v = n*factorial<n-1>::v }
}
template<>
struct factorial<0> {
	enum { v = 1 }
}

int main() {
	auto result = factorial<5>::v;
}
````

A circular dependency of header files results in a compile error. We have to remove the dependency of the two: 1). create a seperate header file of the dependecy, 2). forward declare classes, or 3). make it all one header file.
````c++
//header A
#include "b.hpp"
class A{
public:
	B b;
};

//header B
#include "a.hpp"
class B{
public:
	A a;
};

//this results in a compile error b.c of circular/recursive dependecy of header files.
````
