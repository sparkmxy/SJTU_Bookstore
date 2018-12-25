#pragma warning(disable : 4996)

#include <iostream>
#include "bookstore.h"
#include "book.h"
#include <iomanip>
#include <cstdlib> 
using namespace std;

bookstore B("sjtu");

void run(const string &s);

ifstream in("command.txt");

#define plus_1_s NULL

int main() {
	//freopen("ans.txt", "w", stdout);
	srand(19260817^time(plus_1_s));
	cout << fixed << setprecision(2);
	string s;
	bool testFlag = false;
	if (in) {
		B.root();
		testFlag = true;
	}
	while (true) {
		if (!testFlag) B.who();
		if (in && !in.eof()) getline(in, s);
		else getline(cin,s);
		try{
			run(s);
		}
		catch (const errorT& e){
			if(testFlag)
				cout << "Invalid" << endl;
			else {
				B.who();
				cout << "Invalid! " << e.msg << endl;
			}
		}
	}
	return 0;
}


const int CMDNO = 17;
const string CMD[CMDNO] = { "load","exit","su","logout","useradd","register","delete","passwd",
	"select","modify","show","buy","import","log","report","help","clean"
};

void run(const string &s) {
	stringstream ss(s);
	string cmd;
	ss >> cmd;
	toLowerCase(cmd);
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
	case 13:
		B.showLog(ss);
		break;
	case 14:
		B.report(ss);
		break;
	case 15:
		B.help();
		break;
	case 16:
		B.clean();
		break;
	default:
		error("Wrong command.You can try [help].");
	}
	if (id == 4 || id == 5 || id == 6 || id == 8 || id == 9 || id == 11 || id == 12)
		B.record(s);
}
