#pragma once

#include<string>
#include<iostream>

struct errorT {
	std::string msg;
	errorT(std::string _msg) :msg(_msg) {}
};

void error(std::string msg) {
	throw(errorT(msg));
}

const int blockSize = 150;
template<class elementT>
struct block {
	int cnt, next;
	elementT V[blockSize];
	char del[blockSize];
	block() : cnt(0), next(-1) {}
};

class keyT{
	static const int SIZE = 50;
public:
	char key[SIZE];
	keyT(std::string _key) {
		strcpy_s(key, _key.c_str());
	}
	keyT(const char * _key) {
		strcpy_s(key, _key);
	}
	keyT(const keyT &obj) {
		strcpy_s(key, obj.key);
	}
	keyT() = default;

	keyT& operator=(const keyT &right) {
		strcpy_s(key, right.key);
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

	friend std::ostream& operator<<(std::ostream &os, const keyT &o) {
		os << o.key;
		return os;
	}
};

