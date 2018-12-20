#include "help.h"

std::string cmd[7]{
	"exit ���˳�����",
	"su [user�\id] [passwd]:��¼",
	"logout �����ص�δ��¼״̬",
	"passwd [user�\id] [old�\passwd(if not root)] [new�\passwd] ���޸�����",
	"register[user�\id][passwd][name] ��ע��",
	"show �\ISBN = [ISBN] �\name = [name] �\author = [author] �\keyword = [keyword]������ͼ��",
	"buy[ISBN][quantity] #1������ͼ��"
};

std::string admin[5]{
	"select[ISBN]��ѡ��",
	"modify �\ISBN = [ISBN] �\name = [name] �\author = [author] �\keyword = [keyword] �\price = [price]���޸��鼮��Ϣ"
	"import[quantity][cost_price(in total)]�����ͼ��",
	"clean������ϵͳ����"
	"report myself���ҵĲ�����¼"
};

std::string boss[3]{
	"report finance�� ���񱨱�"
	"report employee��Ա���������"
	"log��ϵͳ��־"
};

void instruction(int level) {
	std::cout << "-------------------------Help-------------------------\n";
	for (int i = 0; i < 7; i++)
		std::cout << cmd[i] << '\n';
	if (level == 3) {
		std::cout << "����Ա���\n";
		for (int i = 0; i < 5; i++)
			std::cout << admin[i] << '\n';
	}
	if (level == 7) {
		std::cout << "�ϰ壬���!\n";
		for (int i = 0; i < 3; i++)
			std::cout << boss[i] << '\n';
	}
	std::cout << "--------------------------End-------------------------\n";
}
