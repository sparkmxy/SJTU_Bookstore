#pragma once
#include "linkList.h"
#include "dataFile.h"
#include<vector>
#include<string>


/*����������*/
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

/*�洢��ţ��ÿ�״����ά����Ԫ��*/
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
�������������һ�����ؼ��ֿ��Զ�Ӧ�ܶ��¼��������
*/

class multiIndex {
	linkList<indexT> L;                 // ������ѯ�洢��¼�Ŀ���
	dataFile< array > rec; // �����洢��¼�Ŀ�
public:
	multiIndex(std::string name) :L(name + "_list"), rec(name + "_rec") {}
	
	// ���عؼ���Ϊ <key> �����м�¼���
	std::vector<int> find(keyT key);

	//�ڹؼ���<key>�����һ����¼ recID
	void add(keyT key, int recID);

	//�Ƴ��ؼ���<key>����ӵ�һ����¼ recID
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

/*���������ʵ���ùؼ��ֲ�ѯ��¼�ţ�֧��ɾ��*/
class singleIndex {
	linkList<indexT2> L;
public:
	singleIndex(std::string name) :L(name + "list") {}

	int find(keyT key);
	bool add(keyT key, int recID);
	bool del(keyT key);
};