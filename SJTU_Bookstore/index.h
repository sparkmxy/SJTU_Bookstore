#pragma once
#include "linkList.h"
#include "dataFile.h"
#include<vector>
#include<string>


/*定长数组类*/
class array {
	static const int SIZE = 500;
	int _size,delcnt;
	int V[SIZE];
	char _del[SIZE];

	//void rebuild();
public:
	array() : _size(0),delcnt(0){}
	int size() { return _size; }
	bool full() { return _size == SIZE; }
	void push(int x) { V[_size++] = x; _del[_size] = '.';}
	int operator()(int i) { return _del[i] == 'x' ?  -1 :V[i]; }
	void del(int i) { 
		_del[i] = 'x';
		//if (++delcnt > SIZE / 2) rebuild();
	}
};

/*存储块号，用块状量表维护的元素*/
class indexT :public keyT{
	static const int MAX_BLOCKNO = 100;
	int cnt;
	int blockID[MAX_BLOCKNO]; // 0-based
public:
	indexT(keyT _key) :keyT(_key), cnt(0) {}
	indexT() = default;

	void push(int x) {
		blockID[cnt++] = x;
	}
	int operator()(int i) {
		return blockID[i];
	}
	int size() {
		return cnt;
	}
	int tail() {
		return blockID[cnt - 1];
	}
};

/*
这个类用来构建一个单关键字可以对应很多记录的索引。
*/

class multiIndex {
	linkList<indexT> L;                 // 用来查询存储记录的块编号
	dataFile< array > rec; // 用来存储记录的块
public:
	multiIndex(std::string name) :L(name + "_list"), rec(name + "_rec") {}
	
	// 返回关键字为 <key> 的所有记录编号
	std::vector<int> find(keyT key);

	//在关键字<key>下添加一条记录 recID
	void add(keyT key, int recID);

	//移除关键字<key>下添加的一条记录 recID
	void erase(keyT key, int recID);
};


class indexT2 :public keyT {
	int num;
public:
	indexT2(keyT _key, int x) :keyT(_key), num(x) {}
	indexT2() = default;

 	int val() { return num; }

	int set(int x) { num = x; }
};

/*这个类用来实现用关键字查询记录号，支持删除*/
class singleIndex {
	linkList<indexT2> L;
public:
	singleIndex(std::string name) :L(name + "list") {}

	int find(keyT key);
	bool add(keyT key, int recID);
	bool del(keyT key);
};