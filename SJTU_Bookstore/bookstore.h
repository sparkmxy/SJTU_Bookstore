#pragma once

#include "user.h"
#include "book.h"
#include "finance.h"
#include "log.h"
#include "help.h"
#include <windows.h>
#include <ctime>
#include <string>
#include <sstream>

class bookstore {
	userList user;
	ibooks books;
	accountBook account;
	Log _record;
	int bookno;
	userT curUser;
	bool _isNew;

public:
	bookstore(std::string name) 
		:user(name), books(name), account(name),bookno(-1),_record(name){
		curUser.level = 0;
		if (user.isNew()) init();
	}

	void select(std::stringstream &ss);

	void modify(std::stringstream &ss);

	void _import(std::stringstream &ss);

	void show(std::stringstream &ss);

	void showFinance(std::stringstream &ss);

	void buy(std::stringstream &ss);

	void login(std::stringstream &ss);

	void logout(std::stringstream &ss);

	void addUser(std::stringstream &ss);

	void _register(std::stringstream &ss);

	void pswdChange(std::stringstream &ss);

	void deleteUser(std::stringstream &ss);

	void root();

	void who();

	void report(std::stringstream &ss);

	void showLog(std::stringstream &ss);

	void help();

	void record(const std::string &s);

	void clean();
private:
	void init();

	void reportFinance();

	void reportEmployee();

	void reportMyself();
};
