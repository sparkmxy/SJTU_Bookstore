#pragma once

#include "dataFile.h"
#include "index.h"
#include <iomanip>
#include <string>
#include <vector>

class bookT{
	friend class ibooks;
	friend bool operator < (const bookT &b1, const bookT &b2);

	static const int MAX_KEYNO = 10;
	keyT isbn,author,name;
	keyT keys[MAX_KEYNO]; // 0 - based
	double price;
	int size,quantity; 
	char del;
public:
	bookT(keyT _isbn = "") :
		isbn(_isbn),size(0),quantity(0),price(0),
		author(""),name(""),del('.'){}
	void display();
	void display2(int sold, std::ostream& os);
	void renew(keyT newkeys);
	double _price() { return price; }
	bool exist() { return del != 'x'; }
};

enum infoType{
	ISBN, KEYWORD, AUTHOR, NAME,PRICE
};

class ibooks{
	dataFile<bookT> books;
	singleIndex I,N;
	multiIndex K, A;

public:
	ibooks(std::string name) :
		books(name + "_book"),
		I(name + "_isbn"), K(name + "_key"), A(name + "_a"), N(name + "_name") {}
	
	// 返回图书的编号，如果没有，返回-1；
	int find(keyT isbn);

	// 添加一本书并返回其编号
	int add(keyT isbn);

	//返回编号为no的图书
	bookT get(int no);

	// 已选定修改某本书的某些信息，保证信息是合法的
	void modify(int no, infoType type, keyT info);

	void modifyP(int no, double pri);

	void modifyQ(int no, int delta);

	void showAll();

	std::vector<int> search(infoType type, keyT info);
};
