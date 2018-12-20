#include "log.h"

void Log::showAll(std::ostream &os) {
	int size = data.size();
	recT *p = new recT[size];
	data.loadAll(p);
	for (int i = 0; i < size; i++)
		os << "record# "<<i+1<<" : "<<p[i] << '\n';
	delete[] p;
}

void Log::add(keyT _userid, const std::string &s) {
	data.push(recT(_userid,s));
	R.add(_userid, data.size());
}

void Log::show(keyT userid, std::ostream &os) {
	std::vector<int> V = R.find(userid);
	std::sort(V.begin(),V.end());
	for (int i = 0; i < V.size(); i++) {
		recT cur = data.get(V[i]);
		os << "record# " << i + 1 << " : " << cur << '\n';
	}
}

void Log::employee(std::ostream &os) {
	int size = data.size(),cnt;
	recT *p = new recT[size];
	data.loadAll(p);
	std::stable_sort(p, p + size);
	keyT cur;
	for (int i = 0; i < size; i++) {
		if (cur != p[i].userid) {
			cur = p[i].userid;
			cnt = 0;
			os << " User: " << cur << '\n';
		}
		cnt++;
		os << "record# "<<cnt<<": "<<p[i].what << '\n';
	}
	delete[] p;
}