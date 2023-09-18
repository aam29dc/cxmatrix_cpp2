#ifndef STRINT_HPP
#define STRINT_HPP
#pragma once

#include <string>

class strint : public std::string {
private:
	std::string _txt;
public:
	strint(const char* s);
	strint(const std::string& s);

	strint operator * (const bool& right) const;

	strint operator + (const strint& right) const;

	strint operator () (void) const;

	friend std::ostream& operator << (std::ostream& os, const strint& stri) {
		os << stri._txt;
		return os;
	}
};

#endif