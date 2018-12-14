#include "finance.h"

accountBook::accountBook(std::string name) :data(name + "_fnc") {
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

//打印一张财务报表
void report();