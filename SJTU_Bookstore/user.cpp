#include "user.h"

bool userList::add(userT newUser) {
	int no = I.find(newUser.id);
	if (no != -1) return false;
	data.push(newUser);
	I.add(newUser.id, data.size());
	return true;
}

//ɾ���û�����������ڣ�����false
bool userList::erase(keyT id) {
	int no = I.find(id);
	if (no == -1) return false;
	I.del(id);
	userT info = data.get(no);
	info.del = 'x';
	return true;
}

// ���ص�level = -1�����û���ҵ�
userT userList::find(keyT id) {
	int no = I.find(id);
	if (no == -1) return userT();
	return data.get(no);
}

//�޸����û����룬�ɹ�����true
bool userList::modify(keyT id, keyT oldpswd, keyT newpswd) {
	int no = I.find(id);
	if (no == -1) return false;
	userT info = data.get(no);
	if (info.pswd != oldpswd) return false;
	info.pswd = newpswd;
	data.replace(info,no);
	return true;
}

//ǿ�и����룬�ϰ���
bool userList::Modify(keyT id, keyT newpswd) {
	int no = I.find(id);
	if (no == -1) return false;
	userT info = data.get(no);
	info.pswd = newpswd;
	data.replace(info, no);
	return true;
}

//��¼�������Ƿ�ɹ�
std::pair<bool,userT> userList::login(keyT _id, keyT _pswd) {
	userT info = find(_id);
	if (info.level == -1) return std::make_pair(false, info);
	return std::make_pair(info.pswd == _pswd,info);
}