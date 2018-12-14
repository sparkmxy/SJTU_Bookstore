#include "user.h"

bool userList::add(userT newUser) {
	int no = I.find(newUser.id);
	if (no != -1) return false;
	data.push(newUser);
	I.add(newUser.id, data.size());
	return true;
}

//删除用户，如果不存在，返回false
bool userList::erase(keyT id) {
	int no = I.find(id);
	if (no == -1) return false;
	I.del(id);
	userT info = data.get(no);
	info.del = 'x';
	return true;
}

// 返回的level = -1，如果没有找到
userT userList::find(keyT id) {
	int no = I.find(id);
	if (no == -1) return userT();
	return data.get(no);
}

//修改与用户密码，成功返回true
bool userList::modify(keyT id, keyT oldpswd, keyT newpswd) {
	int no = I.find(id);
	if (no == -1) return false;
	userT info = data.get(no);
	if (info.pswd != oldpswd) return false;
	info.pswd = newpswd;
	data.replace(info,no);
	return true;
}

//强行改密码，老板用
bool userList::Modify(keyT id, keyT newpswd) {
	int no = I.find(id);
	if (no == -1) return false;
	userT info = data.get(no);
	info.pswd = newpswd;
	data.replace(info, no);
	return true;
}

//登录，返回是否成功
std::pair<bool,userT> userList::login(keyT _id, keyT _pswd) {
	userT info = find(_id);
	if (info.level == -1) return std::make_pair(false, info);
	return std::make_pair(info.pswd == _pswd,info);
}