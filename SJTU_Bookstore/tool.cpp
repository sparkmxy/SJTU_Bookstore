#include "tool.h"

void error(std::string msg) {
	throw(errorT(msg));
}

keyT keyT::substr(int i, int j) {
	keyT ret;
	for (int k = 0; k < j - i + 1; k++)
		ret.key[k] = key[i + k];
	ret.key[j - i + 1] = '\0';
	return ret;
}

double keyT::asdouble() {
	std::stringstream ss((std::string)(key));
	double d;
	ss >> d;
	return d;
}

int keyT::asint() {
	std::stringstream ss((std::string)(key));
	int d;
	ss >> d;
	return d;
}

bool isempty(std::stringstream &ss) {
	std::string a;
	ss >> a; return a == "";
}

callType getCallFromUser() {
	while (1) {
		std::cout << "Please Input Y for yes , N for no.\n";
		std:: string ch;
		std::getline(std::cin,ch);
		if (ch == "Y" || ch == "y" || ch == "YES" || ch == "yes") return YES;
		else if (ch == "N" || ch == "n" || ch == "NO" || ch == "no") return NO;
	}
}

void toLowerCase(std::string &s) {
	int l = s.length();
	for (int i = 0; i < l; i++)
		if (s[i] >= 'A' &&  s[i] <= 'Z')
			s[i] = 'a' + (s[i] - 'A');
}