#include "matrix.hpp"
#include "strint.hpp"

#include <iostream>
#include <vector>
#include <initializer_list>
#include <memory>

template <typename T>
class xvector : public std::vector<int> {
public:
	xvector() {}
	xvector(std::initializer_list<T> l) : std::vector<T>(l) {}
	friend std::ostream& operator<<(std::ostream& os, const std::vector<T>& src) {
		for (auto& i : src) {
			std::cout << i << " ";
		}
		return os;
	}
};


int main() {
	auto ptr = std::make_unique<Matrix<int>>(2, 2, 3);

	std::unique_ptr<Matrix<int>> ptr2 = std::move(ptr);

	ptr2->print();

	ptr->print();

	return 0;
}