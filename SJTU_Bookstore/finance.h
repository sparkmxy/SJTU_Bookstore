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

	//����һ�����ۼ�¼
	void add(keyT _user, double _v);

	void buy(int bookno, int quantity);

	//time��ʡ��ʱ������ܵ�������֧�������������[time]�ν����������������ֱ���һ�Σ�������
	void show(int time = -1);

	// ����������ߵ��� ���� pair<��ţ�����>
	std::vector< std::pair<int, int> >  bestSeller();

	// ����<os> �д�ӡ���񱨱�
	void report(std::ostream& os);

	// ���һ����
	void addBook();

	//����<os> �д�ӡ���н��׼�¼
	void showAll(std::ostream& os);
};
