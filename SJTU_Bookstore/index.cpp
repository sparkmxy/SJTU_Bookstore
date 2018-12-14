#include "index.h"

void multiIndex::add(keyT key, int recID) {
	//std::cout << "add: " << key << ' ' << recID << '\n';
	auto V = L.lookup(key);
	if (!V.size()) {
		//std::cout << "New key: " << key << '\n';
		indexT NewIndex(key);
		array A;
		A.push(recID);
		rec.push(A);
		NewIndex.push(rec.size());
		L.push(NewIndex);
	}
	else {
		int cur = V[0].tail();
		array A = rec.get(cur);
		if (A.full()) {
			array B;
			B.push(recID);
			rec.push(B);
			V[0].push(rec.size());
			L.modify(key, V[0]);
		}
		else {
			A.push(recID);
			rec.replace(A, cur);
		}
	}
	//std::cout << "add finished!\n";
}

std::vector<int> multiIndex::find(keyT key) {
	auto V = L.lookup(key);
	if (!V.size()) return std::vector<int>();
//	std::cout << "key found!\n";
	std::vector<int> ret;
	for (int i = 0; i < V[0].size(); i++) {
		array A = rec.get(V[0](i));
		for (int j = 0; j < A.size(); j++)
			if (A(j) != -1)ret.push_back(A(j));
	}
	return ret;
}

void multiIndex::erase(keyT key, int recID) {
	//std::cout << "erase: " << key << '\n';
	if (key == "") return;
	auto V = L.lookup(key);
	for (int i = 0; i < V[0].size(); i++) {
		array A = rec.get(V[0](i));
		for (int j = 0; j < A.size(); j++)
			if (A(j) == recID)A.del(j);
	}
	//std::cout << "erase finished!\n";
}


int singleIndex::find(keyT key) {
	auto V = L.lookup(key);
	if (!V.size()) return -1;
	return V[0].val();
}

bool singleIndex::add(keyT key, int recID) {
	auto V = L.lookup(key);
	if (!V.size()) {
		L.push(indexT2(key, recID));
		return true;
	}
	error("Name reused.");
}
bool singleIndex::del(keyT key) {
	try {
		L.erase(key);
	}
	catch (...) {
		return false;
	}
	return true;
}
