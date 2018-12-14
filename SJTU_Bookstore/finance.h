#pragma once

#include "dataFile.h"
#include "user.h"

struct trade {
	keyT userid;
	double v;

	trade(keyT _userid, double _v) :userid(_userid), v(_v) {}
	trade() = default;
};

class accountBook { 
	dataFile<trade> data;
	double totalCost, totalIncome;

public:
	
	//Constructor
	accountBook(std::string name);

	~accountBook();

	//增加一条销售记录
	void add(keyT _user, double _v);

	//time项省略时，输出总的收入与支出；否则输出近[time]次进货、卖出操作（分别算一次）的收入
	void show(int time = -1);

	//打印一张财务报表
	void report();
};
