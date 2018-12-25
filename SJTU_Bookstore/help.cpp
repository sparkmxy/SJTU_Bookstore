#include "help.h"

std::string cmd[7]{
	"exit ：退出程序",
	"su [user‐id] [passwd]:登录",
	"logout ：返回到未登录状态",
	"passwd [user‐id] [old‐passwd(if not root)] [new‐passwd] ：修改密码",
	"register[user‐id][passwd][name] ：注册",
	"show ‐ISBN=[ISBN] ‐name=[name] ‐author=[author] ‐keyword=[keyword]：查找图书",
	"buy[ISBN][quantity] #1：购买图书"
};

std::string admin[6]{
	"select[ISBN]：选定",
	"modify ‐ISBN = [ISBN] ‐name=[name] ‐author=[author] ‐keyword=[keyword] ‐price=[price]：修改书籍信息",
	"import [quantity][cost_price(in total)]：买进图书",
	"useradd [id] [password] [level] [name] : 添加用户",
	"report myself：我的操作记录",
	"clean：清理系统垃圾"
};

std::string boss[3]{
	"report finance： 财务报表",
	"report employee：员工工作情况",
	"log：系统日志"
};

void instruction(int level) {
	std::cout << "-------------------------Help-------------------------\n";
	for (int i = 0; i < 7; i++)
		std::cout << cmd[i] << std::endl;
	if (level >= 3) {
		std::cout << "管理员命令:" << std::endl;
		for (int i = 0; i < 6; i++)
			std::cout << admin[i] << std::endl;
	}
	if (level == 7) {
		std::cout << "老板，你好!\n";
		for (int i = 0; i < 3; i++)
			std::cout << boss[i] << std::endl;
	}
	std::cout << "--------------------------End-------------------------\n";
}
