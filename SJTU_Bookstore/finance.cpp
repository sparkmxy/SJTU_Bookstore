#include "finance.h"

accountBook::accountBook(std::string name) :data(name + "_fnc"),sales(name+"_sale"){
	if (data.size()) {
		trade temp = data.get(data.size());
		data.pop();
		totalCost = temp.v;
		temp = data.get(data.size());
		data.pop();
		totalIncome = temp.v;
	}
	else
		totalCost = totalIncome = 0;
}

accountBook::~accountBook() {
	data.push(trade("",totalIncome));
	data.push(trade("", totalCost));
}

void accountBook::add(keyT _userid, double _v) {
	if (_v > 0) totalIncome += _v;
	else totalCost -= _v;
	data.push(trade(_userid, _v));
}

//time项省略时，输出总的收入与支出；否则输出近[time]次进货、卖出操作（分别算一次）的收入
void accountBook::show(int time) {
	int size = data.size();
	if (time == -1) {
		std::cout << "+ " << totalIncome << " - " << totalCost << std::endl;
		return;
	}
	if(time > size) time = size;
	trade *p = new trade[time];
	data.load(size-time+1,size,p);
	double income = 0, cost = 0;
	for (int i = 0; i < time; i++)
		if (p[i].v > 0) income += p[i].v;
		else cost -= p[i].v;
	std::cout << "+ " << income << " - " << cost << std::endl;
	delete [] p;
}

void accountBook::buy(int bookno, int quantity) {
	int cur = sales.get(bookno);
	cur += quantity;
	sales.replace(cur, bookno);
}

void accountBook::report(std::ostream &os) {
	os << "Total income: " << totalIncome << '\n';
	os << "Total expenditure: " << totalCost << '\n';
	os << "Net Income: " << totalIncome - totalCost << '\n';
}

std::vector< std::pair<int,int> > accountBook::bestSeller() {
	int size = sales.size();
	int *p = new int[size];
	int *q = new int[size];
	for (int i = 0; i < size; i++) q[i] = i;
	std::sort(q, q + size, [p](int x, int y)->bool {return p[x] > p[y]; });
	std::vector< std::pair<int, int> > ret;
	for (int i = 0; i < size && i < 10; i++) 
		ret.push_back(std::make_pair(q[i],p[q[i]]));
	return ret;
}

void accountBook::showAll(std::ostream &os) {
	int size = data.size();
	trade *p = new trade[size];
	data.loadAll(p);
	for (int i = 0; i < size; i++) {
		os << "record# " << i + 1 << ": " << p[i] << '\n';
	}
	delete[] p;
}