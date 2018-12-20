#include "bookstore.h"
#include "tool.h"

const int TYPENO = 5;
static const std::string _type[TYPENO] = {"-ISBN","-name","-author","-keyword","-price"};

infoType getType(const std::string &s) {
	int id = 0;
	int i=0,l = s.length();
	while (i < l -1 && s[i+1] == ' ')i++;
	std::string temp = s.substr(i+1,l-i-1);
	while (id < TYPENO && _type[id] != temp) id++;
	if (id == TYPENO) {
		error("Wrong parameter: " + temp);
	}
	if (id == 0) return ISBN;
	if (id == 1) return NAME;
	if (id == 2) return AUTHOR;
	if (id == 3) return KEYWORD;
	if (id == 4) return PRICE;
}

std::vector< std::pair<infoType, keyT> > parse(std::stringstream& ss) {
	std::string lhs,rhs;
	std::vector< std::pair<infoType, keyT> > V;
	while (true) {
		std::getline(ss, lhs, '=');
		if (ss.fail() || ss.eof()) break;
		infoType type = getType(lhs);
		if (type == NAME || type == AUTHOR || type == KEYWORD) {
			char temp;
			ss >> temp;
			if(temp!='"') error("Wrong format -quotes.");
			getline(ss,rhs,'"');
		}
		else ss >> rhs;
		if (ss.fail()) error("Wrong format: " + lhs + " " + rhs);
		V.push_back(std::make_pair(type, keyT(rhs)));
	}
	return V;
}


void bookstore::select(std::stringstream &ss) {
	if (curUser.level < 3) error("select: Not allowed.");
	keyT isbn;
	ss >> isbn;
	if (!isempty(ss)) error("select: Invalid command.");
	int id = books.find(isbn);
	if (id == -1)
		bookno = books.add(isbn);
	else bookno = id;
}

void bookstore::modify(std::stringstream &ss) {
	if (curUser.level < 3) error("modify: Not allowed.");
	if (bookno == -1) error("Haven't selected yet.");
	auto V = parse(ss);
	if (V.size() == 0) error("modify: Wrong parameter.");
	for (int i = 0; i < V.size(); i++) {
		//std::cerr << "Modifying: " << V[i].first << " " << V[i].second << '\n';
		books.modify(bookno, V[i].first, V[i].second);
	}
}

void bookstore::_import(std::stringstream &ss) {
	if (curUser.level < 3) error("import: Not allowed.");
	if (bookno == -1) error("Haven't selected yet.");
	int q;
	double cost;
	ss >> q >> cost;
	if(ss.fail() || !isempty(ss)) error("import: Invalid command.");
	books.modifyQ(bookno, q);
	account.add(curUser.id, -cost);
}

void bookstore::show(std::stringstream &ss) {
	if (curUser.level < 1) error("show: Not allowed.");
	auto D = parse(ss);
	int n = D.size();
	if (!n) {
		//std::cout << "ShowAll!\n";
		books.showAll();
	}
	std::vector<int> V[5];
	std::vector<bookT> ans;
	for (int i = 0; i < n; i++) V[i] = books.search(D[i].first, D[i].second);
	for (int i = 0; i < n; i++) std::sort(V[i].begin(),V[i].end());
	for (int j = 0; j < V[0].size(); j++) {
		//std::cout << "checking: " << V[0][j] << '\n';
		bool ok = true;
		for (int i = 1; i < n ; i++) {
			int L = 0, R = V[i].size(),ans = -1;
			while (L <= R) {
				int mid = (L + R) >> 1;
				if (V[i][mid] == V[0][j]) { ans = mid; break; }
				else if (V[i][mid] < V[0][j]) L = mid + 1;
				else R = mid - 1;
			}
			if (ans == -1) {
				ok = false;
				break;
			}
		}
		if (ok) {
			bookT cur = books.get(V[0][j]);
			ans.push_back(cur);
		}
	}
	std::sort(ans.begin(), ans.end());
	for (int i = 0; i < ans.size(); i++) ans[i].display();
}



void bookstore::showFinance(std::stringstream &ss) {
	if (curUser.level < 7) error("showFinance: Not allowed.");
	int time;
	ss >> time;
	if (ss.fail()) account.show();
	else if (!isempty(ss)) error("showFinance: Invalid command.");
	else account.show(time);
}

void bookstore::buy(std::stringstream &ss) {
	if (curUser.level < 1) error("buy: Not allowed.");
	keyT isbn;
	int x;
	ss >> isbn >> x;
	if (ss.fail() || !isempty(ss)) error("buy: Invalid command.");
	int no = books.find(isbn);
	if (no == -1) error("buy: Book doesn't exist.");
	bookT bk = books.get(no);
	books.modifyQ(no, -x);
	account.add(curUser.id, x*bk._price());
	account.buy(no, x);
}

void bookstore::login(std::stringstream &ss) {
	keyT id, pswd;
	ss >> id >> pswd;
	if (ss.fail() || !isempty(ss)) error("login: Invalid command.");
	auto temp = user.login(id,pswd);
	if (temp.first) curUser = temp.second;
	else error("login: Wrong password.");
}

void bookstore::logout(std::stringstream &ss) {
	if (!isempty(ss)) error("Extra words.");
	if (curUser.level == 0) error("Havn't logged in yet.");
	curUser.level = 0;
}

void bookstore::addUser(std::stringstream &ss) {
	if (curUser.level < 1) error("adduesr: Not allowed.");
	userT newUser;
	ss >> newUser;
	if (ss.fail() || !isempty(ss) || !newUser.legal()) error("adduesr: Extra words.");
	if (newUser.level >= curUser.level) error("adduesr: Not allowed.");
	if (!user.add(newUser)) error("adduesr: User existed.");
}

void bookstore::_register(std::stringstream &ss) {
	keyT name, id, pswd;
	ss >> id >> pswd >> name;
	if (ss.fail() || !isempty(ss)) error("register: Invalid command.");
	if (!user.add(userT(id, pswd, name, 1))) error("register: User existed.");
}

void bookstore::pswdChange(std::stringstream &ss) {
	if (curUser.level < 1) error("pswd: not allowed.");
	keyT id, old, New;
	ss >> id;
	if (ss.fail()) error("pswd: Too few tokens.");
	if (curUser.level == 7) ss >> New;
	else ss >> old >> New;
	if (ss.fail() || !isempty(ss)) error("pswd: Invalid command.");
	bool ok;
	if (curUser.level == 7) ok = user.Modify(id, New);
	else ok = user.modify(id, old, New);
	if (!ok) error("pswd: User doesn't exist.");
}

void bookstore::deleteUser(std::stringstream &ss) {
	if (curUser.level < 7) error("delete: Not allowed.");
	keyT id;
	ss >> id;
	if (ss.fail() || !isempty(ss)) error("delete: Invalid command.");
	if (!user.erase(id)) error("delete: User doesn't exist.");
}

void bookstore::init() {
	user.add(userT("root","sjtu","root",7));
}

void bookstore::root() {
	curUser = user.find("root");
}

void bookstore::who() {
	if (curUser.level == 0) {
		std::cout << "visitor >";
	}
	else 
		std::cout << curUser.id << " >";
}

void bookstore::report(std::stringstream &ss) {
	std::string what;
	ss >> what;
	if (ss.fail() || !isempty(ss)) error("report: Extra words.");
	if (what == "finance") reportFinance();
	else if (what == "myself") reportMyself();
	else if (what == "employee") reportEmployee();
	else error("Wrong command.");
}

void bookstore::reportFinance() {
	if (curUser.level < 7) error("report: Not allowed.");
	auto V = account.bestSeller();
	std::vector<bookT> U;
	for (int i = 0; i < V.size(); i++)
		U.push_back(books.get(V[i].first));
	std::cout << "------------------------Finance Report-----------------------------\n";
	account.report(std::cout);
	std::cout << "Best Sellers:\n";
	for (int i = 0; i < U.size(); i++)
		U[i].display2(V[i].second,std::cout);
	std::cout << "---------------------------------End-------------------------------\n";
	std::cout << "Do you want to put this into a file(finance.txt)?\n";
	callType call = getCallFromUser();
	if (call == NO) return;
	std::ofstream out("finance.txt");
	out << "------------------------Finance Report-----------------------------\n";
	account.report(out);
	out << "Best Sellers:\n";
	for (int i = 0; i < U.size(); i++)
		U[i].display2(V[i].second,out);
	out << "--------------------------------End--------------------------------\n";
	std::cout << "Finished!\n";
}

void bookstore::help() {
	instruction(curUser.level);
}

void bookstore::record(const std::string &s) {
	_record.add(curUser.id,s);
}

void bookstore::showLog(std::stringstream &ss) {
	if (curUser.level < 7) error("report: Not allowed.");
	std::cout << "------------------------Log-----------------------------\n";
	std::cout << "Operations:\n";
	_record.showAll(std::cout);
	std::cout << "------------------------------------------------------------\n";
	std::cout << "Finance Details:\n";
	account.showAll(std::cout);
	std::cout << "------------------------End-----------------------------\n";
	std::cout << "Do you want to put this into a file(log.txt)?\n";
	callType call = getCallFromUser();
	if (call == NO) return;
	std::ofstream out("log.txt");
	out << "------------------------Log-----------------------------\n";
	out << "Operations:\n";
	_record.showAll(out);
	out << "------------------------------------------------------------\n";
	out << "Finance Details:\n";
	account.showAll(out);
	out << "------------------------End-----------------------------\n";
}

void bookstore::reportMyself() {
	std::cout << "------------------------Log-----------------------------\n";
	_record.show(curUser.id,std::cout);
	std::cout << "------------------------End-----------------------------\n";
}

void bookstore::reportEmployee() {
	if (curUser.level < 7) error("report: Not allowed.");
	std::cout << "------------------------Employee-----------------------------\n";
	_record.employee(std::cout);
	std::cout << "------------------------End-----------------------------\n";
	std::cout << "Do you want to put this into a file(employee.txt)?\n";
	callType call = getCallFromUser();
	if (call == NO) return;
	std::ofstream out("employee.txt");
	std::cout << "------------------------Employee-----------------------------\n";
	_record.employee(out);
	std::cout << "------------------------End-----------------------------\n";
}

void bookstore::clean() {
	for (int i = 1; i <= 35; i++) {
		Sleep(rand()%100);
		std::cout << '=';
	}
	std::cout << '\n';
	std::cout << "垃圾清理完成，程序跑的飞快！\n";
}