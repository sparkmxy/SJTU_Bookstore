#pragma once
#include "index.h"
#include <iostream>
#include <string>

class userList;
class bookstore;

class userT {
	friend class userList;
	friend class bookstore;
	
	keyT id, pswd, name;
	int level;
	char del;
public:
	userT(keyT _id, keyT _pswd, keyT _name,int _level) 
		:id(_id),pswd(_pswd),name(_name),level(_level){}
	userT():level(-1),del('.'){}
	
	bool legal() {
		return level == 1 || level == 3 || level == 7;
	}
	friend std::istream& operator>>(std::istream &is, userT& o) {
		is >> o.id >> o.pswd >> o.level >> o.name;
		return is;
	}
};

class userList {
	singleIndex I;
	dataFile<userT> data;
	bool NEW;
public:
	userList(std::string name) :I(name+"_user"),data(name+"_user"){
		if (data.size() == 0) NEW = true;
		else NEW = false;
	}

	bool isNew() { return NEW; }

	// ������û�������Ѿ����ڣ�����false
	bool add(userT newUser);
	//ɾ���û�����������ڣ�����false
	bool erase(keyT id);
	
	// ���ص�level = -1�����û���ҵ�
	userT find(keyT id);
	
	//�޸����û����룬�ɹ�����true
	bool modify(keyT id,keyT oldpswd,keyT newpswd);
	
	//ǿ�и����룬�ϰ��ã�����û������ڷ���false
	bool Modify(keyT id, keyT newpswd);
	
	//��¼�������Ƿ�ɹ�
	std::pair<bool,userT> login(keyT _id, keyT _pawd);
};