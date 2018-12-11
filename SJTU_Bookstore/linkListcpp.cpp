#include "linkList.h"

template<class elementT> 
void linkList<elementT> ::tryMerge(int i) {
	block<elementT> cur = data.get(i);
	if (cur.next == -1) return;
	block<elementT> _next = data.get(cur.next);
	block<elementT> trash = data.get(1);
	if (cur.cnt + _next.cnt < block) {
		for (int i = 0; i < _next.cnt; i++)
			cur.V[i + cur.cnt] = _next.V[i];
		cur.cnt += _next.cnt;
		int next2 = _next.next;
		_next.next = trash.next;
		trash.next = cur.next;
		cur.next = next2;
		data.replace(cur, i);
	}
}

template<class elementT>
void linkList<elementT>::split(int i) {
	block<elementT> New, cur = data.get(i);
	block<elementT> trash = data.get(1);
	for (int i = blockSize; i < cur.cnt; i++)
		New.V[i - blockSize] = cur.V[i];
	New.cnt = cur.cnt - blockSize;
	cur.cnt = blockSize;
	New.next = cur.next;
	if (trash.next != -1) {
		block<elementT> temp = data.get(trash.next);
		cur.next = trash.next;
		trash.next = temp.next;
		data.replace(New,trash.next);
	}
	else {
		data.push(New);
		cur.next = data.size();
	}
}

template<class elementT>
void linkList<elementT>::erase(int blockno, int i) {
	block<elementT> cur = data.get(blockno);
	cur.cnt--;
	for (int j = i; j < cur.cnt; j++)
		cur.V[j] = cur.V[j + 1];
	data.replace(cur, blockno);
	tryMerge(blockno);
}

template<class elementT>
void linkList<elementT>::add(int i,const elementT & ele) {
	block<elementT> cur = data.get(i);
	cur.V[cur.cnt++] =  ele;
	data.replace(i, cur);
	if (cur.cnt == blockSize * 2)
		split(i);
}

template<class elementT>
int linkList<elementT>::push(const elementT & ele,int head) {
	if (head == 0) {
		block<elementT> New;
		New[New.cnt++] = ele;
		data.push(New);
		return data.size();
	}
	block<elementT> cur = data.get(head);
	int id = head;
	while (cur.next != -1) {
		id = cur.next;
		cur = data.get(cur.next);
	}
	cur.V[cur.cnt++] = ele;
	data.replace(id, cur);
	if (cur.cnt == blockSize * 2) split(id);
}

template<class elementT>
std::vector<elementT> linkList<elementT> ::getWholeList(int i) {
	block<elementT> cur =  data.get(i);
	std::vector <elementT> ret;
	while (1) {
		for (int i = 0; i < cur.cnt; i++)
			ret.push_back(cur.V[i]);
		if (cur.next == -1) return;
		cur = data.get(cur.next);
	}
	return ret;
}