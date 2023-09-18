#include "strint.hpp"

#include <ostream>

strint::strint(const char* s) : _txt(s) {}
strint::strint(const std::string& s) : _txt(s) {}

strint strint::operator * (const bool& right) const {
	if (right) return *this;
	return "";
}

strint strint::operator + (const strint& right) const {
	return strint(this->_txt + right._txt);
}

strint strint::operator () (void) const {
	return *this;
}