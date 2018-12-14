#pragma warning(disable : 4996)

#include <iostream>
#include "bookstore.h"
#include "book.h"
#include <iomanip>
using namespace std;

bookstore B("sjtu");

void run(const string &s);

ifstream in("command.txt");


int main() {
	//freopen("ans.txt", "w", stdout);
	cout << fixed << setprecision(2);
	string s;
	if (in) B.root();
	while (true) {
		if (in && !in.eof()) getline(in, s);
		else getline(cin,s);
		try{
			run(s);
		}
		catch (const errorT& e){
			//B.report();
			cout << "Invalid" << endl;
			//cout << "Invalid: "<<e.msg<<endl;
		}
	}
	return 0;
}


const int CMDNO = 13;
const string CMD[CMDNO] = { "load","exit","su","logout","useradd","register","delete","passwd",
	"select","modify","show","buy","import"
};

void run(const string &s) {
	stringstream ss(s);
	string cmd;
	ss >> cmd;
	int id = 0;
	string temp;
	while (id < CMDNO && CMD[id] != cmd) id++;
	//cout << "Command :" << CMD[id] << endl;
	switch (id){
	case 0:
		cin >> temp;
		in.open(temp);
		break;
	case 1:
		exit(0);
		break;
	case 2:
		B.login(ss);
		break;
	case 3:
		B.logout(ss); 
		break;
	case 4:
		B.addUser(ss); 
		break;
	case 5:
		B._register(ss);
		break;
	case 6:
		B.deleteUser(ss);
		break;
	case 7:
		B.pswdChange(ss);
		break;
	case 8: 
		B.select(ss);
		break;
	case 9:
		B.modify(ss);
		break;
	case 10:
		ss >> temp;
		if (temp == "finance") B.showFinance(ss);
		else {
			stringstream sss(s);
			sss >> temp;
			B.show(sss);
		}
		break;
	case 11:
		B.buy(ss);
		break;
	case 12:
		B._import(ss);
		break;
	default:
		error("Wrong command.");
		break;
	}
}