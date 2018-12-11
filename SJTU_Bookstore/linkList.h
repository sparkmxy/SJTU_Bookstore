#pragma once

#include "dataFile.h"
#include "tool.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
// 将若干元素打包成块


const std::string headFlag = "__head";
struct blockInfo {
	keyT first, last;
	int next;
	blockInfo(keyT _first, keyT _last, int _next) :first(_first),last(_last),next(_next) {}
	blockInfo() = default;
};

// The first block is a flag for recycled blocks.

template<class elementT>
class linkList {
	static const int maxBlockNo = 1000;
	dataFile< block<elementT> > data;
	dataFile< blockInfo > blocks;
	blockInfo info[maxBlockNo];
	int blockNo;
	int head;

private:
	void merge(int i);

	void split(int i);

public:
	//Constructor
	linkList(std::string fileName) :data(fileName), blocks(fileName + "_block") {
		blockNo = blocks.size();
		if (blockNo) {
			blocks.loadAll(&info[1]);
			head = info[blockNo].next;
			blockNo--;
			std::cout<<"reload: head = "<<head<<'\n';
		}
		else  head = -1;  
	}
	linkList() = delete;

	~linkList();
	// erase: Delete record with key = <key>
	void erase(const keyT& key);

	// Add a new element with key = <key>
	void push(const elementT& ele);

	std::vector<elementT> lookup(const keyT &key);
};

template<class elementT>
linkList<elementT>::~linkList() {
	info[++blockNo] = blockInfo(headFlag,headFlag, head);
	blocks.upload(blockNo,&info[1]);
}


template<class elementT>
std::vector<elementT> linkList<elementT>::lookup(const keyT &key) {
	int blockid = head;
	while (blockid != -1) {
	//	std::cout << "cmp: " << info[blockid].first << ' ' << info[blockid].last << '\n';
		if (key >= info[blockid].first && key <= info[blockid].last)
			break;
		blockid = info[blockid].next;
	}
	//std::cout << "blockid Found: " << blockid << '\n';
	if (blockid == -1) return std::vector<elementT>();
	block<elementT> cur = data.get(blockid);
	std::vector<elementT> ret;
	for (int i = 0; i < cur.cnt; i++)
		if (cur.del[i] != '#' &&key == cur.V[i].key)
			ret.push_back(cur.V[i]);
	return ret;
}

template<class elementT>
void linkList<elementT>::push(const elementT& ele) {
	const keyT& key = ele.key;
	int cur = head;
	while (cur != -1) {
		if (key >= info[cur].first && key <= info[cur].last)
			break;
		cur = info[cur].next;
	}
	if (cur == -1) {
	//	std::cout << "null ptr\n";
		if (head == -1) {
			data.push(block<elementT>());
			head = blockNo = 1;
			info[head].next = -1;
		}
		cur = head;
		while (info[cur].next != -1) cur = info[cur].next;
	}
	//std::cout << "Block Found: " << cur << '\n';
	block<elementT> B = data.get(cur);
	B.V[B.cnt++] = ele;
	if (B.cnt == blockSize) { // split
		block<elementT> newB,B1;
		for (int i = 0; i < B.cnt; i++)
			if (B.del[i] != '#')B1.V[B1.cnt++] = B.V[i];
		std::sort(B1.V, B1.V + B1.cnt);
		for (int i = B1.cnt >> 1; i < B1.cnt; i++) newB.V[newB.cnt++] = B.V[i];
		B1.cnt >>= 1;
		data.push(newB);
		B1.next = ++blockNo;
		data.replace(B1,cur);
		info[cur] = blockInfo(B1.V[0].key,B1.V[B1.cnt-1].key,blockNo);
		info[blockNo] = blockInfo(newB.V[0].key, newB.V[newB.cnt - 1].key, -1);
	}
	else {
		data.replace(B, cur);
		if (B.cnt == 1) info[cur].first = info[cur].last = key;
		else {
			keyT &_first = info[cur].first, &_last = info[cur].last;
			if (_first > key) _first = key;
			if (_last < key) _last = key;
		}
		//std::cout << "info: " << info[cur].first << ' ' << info[cur].last << '\n';
	}
}

template<class elementT>
void linkList<elementT>::erase(const keyT &key) {
	int cur = head;
	while (cur != -1) {
		if (key>=info[cur].first && key <= info[cur].last)
			break;
		cur = info[cur].next;
	}
	if (cur == -1)  error("erase  error");
	block<elementT> B = data.get(cur);
	for(int i=0;i<B.cnt;i++)
		if (B.del[i]!='#' && key == B.V[i].key) {
			B.del[i] = '#';
			//std::cout << "Succeed!\n";
			return;
		}
	error("erase error");

	// merge
	if (B.next != -1) {
		block<elementT> C = data.get(B.next);
		if (B.cnt + C.cnt < blockSize) {
			for (int i = 0; i < C.cnt; i++)
				if (C.del[i] != '#')
					B.V[++B.cnt] = C.V[i];
		}
		info[cur].last = info[B.next].last;
		info[cur].next = B.next = C.next;
	}
}