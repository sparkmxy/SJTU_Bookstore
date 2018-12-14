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

	// 添加新用户，如果已经存在，返回false
	bool add(userT newUser);
	//删除用户，如果不存在，返回false
	bool erase(keyT id);
	
	// 返回的level = -1，如果没有找到
	userT find(keyT id);
	
	//修改与用户密码，成功返回true
	bool modify(keyT id,keyT oldpswd,keyT newpswd);
	
	//强行改密码，老板用，如果用户不存在返回false
	bool Modify(keyT id, keyT newpswd);
	
	//登录，返回是否成功
	std::pair<bool,userT> login(keyT _id, keyT _pawd);
};