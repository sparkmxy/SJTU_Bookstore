#include"book.h"

bool operator < (const bookT &b1, const bookT &b2) {
	return strcmp(b1.isbn.key,b2.isbn.key)<0;
}

void bookT::display() {
	std::cout << isbn << '\t' << name << '\t' << author << '\t';
	for (int i = 0; i < size; i++) {
		std::cout << keys[i];
		if (i != size - 1) std::cout << '|';
	}
	std::cout << '\t' << price << '\t' << quantity << "本\n";
}

void bookT::display2(int sold, std::ostream &os) {
	os << isbn << '\t' << name << '\t' << author << '\t';
	os << '\t' << price << "\t 库存" << quantity << "本\n";
	os << "总共卖出： " << sold << " 本\n";
}

void bookT::renew(keyT newkeys) {
	int l = 0,len = newkeys.length();
	size = 0;
	for(int i=0;i<len;i++)
		if (newkeys.key[i] == '|') {
			keys[size++] = newkeys.substr(l,i-1);
		//	std::cout << "newKEY: " << keys[size - 1] << '\n';
			l = i + 1;
		}
	keys[size++] = newkeys.substr(l,len-1);
}

int ibooks::find(keyT isbn) {
	return I.find(isbn);
}

//返回编号为no的图书
bookT ibooks::get(int no) {
	return books.get(no);
}

void ibooks::modify(int no, infoType type, keyT info) {
	bookT cur = books.get(no);
	switch (type) {
	case ISBN:
		I.del(cur.isbn);
		//std::cout << "change isbn: " << cur.isbn << " to " << info << '\n';
		cur.isbn = info;
		I.add(cur.isbn, no);
		break;
	case AUTHOR:
		A.erase(cur.author, no);
		cur.author = info;
		A.add(cur.author, no);
		break;
	case NAME:
		N.del(cur.name);
		cur.name = info;
		N.add(cur.name, no);
		break;
	case PRICE:
		cur.price = info.asdouble();
		break;
	case KEYWORD:
		//std::cout << "cur_size = " << cur.size << '\n';
		for (int i = 0; i < cur.size; i++) K.erase(cur.keys[i], no);
		cur.renew(info);
		for (int i = 0; i < cur.size; i++) K.add(cur.keys[i], no);
	}
	books.replace(cur, no);
}

std::vector<int> ibooks::search(infoType type, keyT info) {
	if (type == ISBN || type == NAME) {
		int id = type == ISBN ? I.find(info) : N.find(info);
		std::vector<int> V;
		if (id != -1) V.push_back(id);
		return V;
	}
	else if (type == AUTHOR)
		return A.find(info);
	else if (type == KEYWORD)
		return K.find(info);
	error("Invalid search");
}

int ibooks::add(keyT isbn) {
	//std::cout << "add: " << isbn << '\n';
	if (!I.add(isbn, books.size()+1)) error("book existed.");
	books.push(bookT(isbn));
	return books.size();
}

void ibooks::modifyP(int no, double pri) {
	bookT cur = books.get(no);
	cur.price = pri;
	books.replace(cur, no);
}

void ibooks::modifyQ(int no, int delta) {
	bookT cur = books.get(no);
	if (cur.quantity + delta < 0) error("Not enough.");
	cur.quantity += delta;
	books.replace(cur, no);
}

void ibooks::showAll() {
	int n = books.size();
	bookT *p = new bookT[n];
	books.loadAll(p);
	std::sort(p, p + n);
	for (int i = 0; i < n; i++)
		p[i].display();
	delete [] p;
}