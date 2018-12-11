#include <iostream>
#include "linkList.h"
#include "dataFile.h"
#include "tool.h"

using namespace std;

class intType : public keyT{
	int val;
public:
	intType(string s, int _val) : keyT(s), val(_val) {}
	intType() = default;
	void display() {
		cout << key << " val = " << val << '\n';
	}
};
int n;
int main() {
	linkList<intType> L("test");
	cin >> n;
	string key;
	while (n--) {
		int cmd;
		cin >> cmd;
		if (cmd == 0) {
			cin >> key;
			try {
				L.erase(key);
			}
			catch (errorT err) {
				cout << err.msg << endl;
			}
		}
		else {
			cin >> key;
			vector<intType> V = L.lookup(key);
			for (int i = 0; i < V.size(); i++)
				V[i].display();
		}
	}
	cin >> n;
	return 0;
}