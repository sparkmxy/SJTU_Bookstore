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
