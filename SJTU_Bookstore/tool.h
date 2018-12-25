#pragma once
#pragma warning(disable : 4996)
#include<string>
#include<iostream>
#include<sstream>
#include<cstring>

struct errorT {
	std::string msg;
	errorT(std::string _msg) :msg(_msg) {}
};

void error(std::string msg);


const int blockSize = 150;
template<class elementT>
struct block {
	int cnt, next;
	elementT V[blockSize];
	char del[blockSize];
	block() : cnt(0), next(-1) {}
};

/*这个类是一个定长的字符串*/

class keyT{ 
	static const int SIZE = 50;

public:
	char key[SIZE];
	keyT(std::string _key) {
		strcpy(key, _key.c_str());
	}
	keyT(const char * _key) {
		strcpy(key, _key);
	}
	keyT(const keyT &obj) {
		strcpy(key, obj.key);
	}
	keyT() = default;

	keyT& operator=(const keyT &right) {
		strcpy(key, right.key);
		return *this;
	}

	bool operator <= (const keyT& right) const {
		int l1 = strlen(key),l2 = strlen(right.key);
		if (l1 != l2) return l1 < l2;
		return strcmp(key, right.key) <= 0;
	}
	bool operator >= (const keyT& right) const {
		int l1 = strlen(key), l2 = strlen(right.key);
		if (l1 != l2) return l1 > l2;
		return strcmp(key, right.key) >= 0;
	}
	bool operator < (const keyT& right) const {
		int l1 = strlen(key), l2 = strlen(right.key);
		if (l1 != l2) return l1 < l2;
		return strcmp(key, right.key) < 0;
	}
	bool operator > (const keyT& right) const {
		int l1 = strlen(key), l2 = strlen(right.key);
		if (l1 != l2) return l1 > l2;
		return strcmp(key, right.key) > 0;
	}
	bool operator == (const keyT& right) const {
		int l1 = strlen(key), l2 = strlen(right.key);
		if (l1 != l2) return false;
		return strcmp(key, right.key) == 0;
	}
	bool operator != (const keyT& right) const {
		return !(*this == right);
	}

	friend std::ostream& operator<<(std::ostream &os, const keyT &o) {
		os << o.key;
		return os;
	}

	friend std::istream& operator>>(std::istream &is, keyT &o) {
		is >> o.key;
		return is;
	}

	keyT substr(int i,int j);

	int length() { return strlen(key); }

	double asdouble();

	int asint();
};

bool isempty(std::stringstream &ss);

enum callType{
	YES,NO
};

callType getCallFromUser();

void toLowerCase(std::string &s);