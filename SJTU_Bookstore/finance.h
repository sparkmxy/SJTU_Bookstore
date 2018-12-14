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

	//����һ�����ۼ�¼
	void add(keyT _user, double _v);

	//time��ʡ��ʱ������ܵ�������֧�������������[time]�ν����������������ֱ���һ�Σ�������
	void show(int time = -1);

	//��ӡһ�Ų��񱨱�
	void report();
};
