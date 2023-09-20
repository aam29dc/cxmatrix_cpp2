export module strint;

import <string>;
import <ostream>;

export class strint : public std::string {
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