#pragma once

#include "dataFile.h"
#include "book.h"
#include "user.h"

class accountBook { 
	struct trade {
		keyT userid;
		double v;

		trade(keyT _userid, double _v) :userid(_userid), v(_v) {}
		trade() = default;
		friend std::ostream& operator << (std::ostream& os, const trade& o) {
			os << o.userid << ' ' << o.v;
			return os;
		}
	};

	dataFile<trade> data;
	dataFile<int> sales;
	double totalCost, totalIncome;

public:
	
	//Constructor
	accountBook(std::string name);

	~accountBook();

	//增加一条销售记录
	void add(keyT _user, double _v);

	void buy(int bookno, int quantity);

	//time项省略时，输出总的收入与支出；否则输出近[time]次进货、卖出操作（分别算一次）的收入
	void show(int time = -1);

	// 返回销量最高的书 返回 pair<书号，销量>
	std::vector< std::pair<int, int> >  bestSeller();

	// 向流<os> 中打印财务报表
	void report(std::ostream& os);

	// 添加一本书
	void addBook();

	//向流<os> 中打印所有交易记录
	void showAll(std::ostream& os);
};
