#pragma once

#include "dataFile.h"
#include "tool.h"
#include "index.h"

class Log {
	static const int MAXSIZE = 150;
	struct recT{
		keyT userid;
		char what[MAXSIZE];
		int level;
		recT(keyT _userid,int _level,std::string _what) :userid(_userid),level(_level){
			std::strcpy(what,_what.c_str());
		}
		recT() = default;

		friend std::ostream& operator<<(std::ostream &os,const recT& o) {
			os << o.userid << "> " << o.what;
			return os;
		}

		bool operator < (const recT& o)const {
			return userid < o.userid;
		}
	};
	dataFile<recT> data;
	multiIndex R;

public:
	Log(std::string name) :data(name + "_log") ,R(name+"_log"){}

	//����<os> �д�ӡȫ��������¼
	void showAll(std::ostream &os);

	//���һ��������¼
	void add(keyT _userid,int level,const std::string &s);

	//����<os> �д�ӡĳ���û��Ĳ�����¼
	void show(keyT userid, std::ostream &os);

	//���� <os> �д�ӡÿ��Ա���Ĳ�����¼
	void employee(std::ostream &os);
};
