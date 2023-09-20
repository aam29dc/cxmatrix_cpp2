import matrix;
import strint;

import <iostream>;
import <vector>;
import <initializer_list>;
import <memory>;

template <typename T>
class xvector : public std::vector<int> {
public:
	xvector() {}
	xvector<T>(std::initializer_list<T> l) : std::vector<T>(l) {}
	friend std::ostream& operator<<(std::ostream& os, const std::vector<T>& src) {
		for (auto& i : src) {
			std::cout << i << " ";
		}
		return os;
	}
	void myfunc(){}
};

consteval int squr(const int n) { return n * n; }


int main() {
	Matrix<int> M{ 1,2,3 };
	return 0;
}
