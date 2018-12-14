#pragma once

#include "user.h"
#include "book.h"
#include "finance.h"
#include <string>
#include <sstream>

class bookstore {
	userList user;
	ibooks books;
	accountBook account;
	int bookno;
	userT curUser;
	bool _isNew;

	void init();

public:
	bookstore(std::string name) 
		:user(name), books(name), account(name),bookno(-1){
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

	void report() {
		std::cout << curUser.id << ' ' << curUser.level << "> ";
	}
	void curbk() {
		std::cout << bookno << '\n';
	}
};
