#pragma once
//�����ļ�ʵ�ֵ�һ��vector

#include <string>
#include <fstream>
#include <iostream>

template<class T>
class dataFile {
	std::string fileName;
	std::ifstream in;
	std::fstream out;
	int _size;
	const int sizeofT;
public:
	//���캯��������Ϊ�ļ�������������ھʹ���
	dataFile(std::string name) :sizeofT(sizeof(T)),fileName(name) {
		in.open(fileName,ios::binary);
		if (!in) {
			out.open(fileName,fstream::out|ios::binary);
			_size = 0;
			out.seekp(0);
			out.write(reinterpret_cast<const char *>(&_size), sizeof(int));
			out.flush();
			in.open(fileName,ios::binary);
		}
		else {
			out.open(fileName,fstream::in|fstream::out|ios::binary);
			in.seekg(0);
			in.read(reinterpret_cast<char *>(&_size), sizeof(int));
			std ::cout << "File "<<fileName<<"exist,size = " << _size << '\n';
		}
	}
	dataFile() = delete;

	// �����������ر��ļ�
	~dataFile() {
		in.close();
		out.close();
	}
	// get: return the i th record
	T get(int i); 

	// replace the i th record with 'now'
	void replace(const T& now, int i);

	// push in a new record
	void push(const T& ele);

	int size() { return _size; }

	void loadAll(T *ptr);

	void upload(int __size, T *ptr);
};

template<class T>
T dataFile<T>::get(int i) {
	in.seekg((i - 1)*sizeofT + sizeof(int));
	T ret;
	in.read(reinterpret_cast<char *>(&ret), sizeofT);
	return ret;
}

template<class T>
void dataFile<T>::replace(const T& now, int i) {
	out.seekp((i - 1)*sizeofT + sizeof(int));
	out.write(reinterpret_cast<const char *>(&now), sizeofT);
	out.flush();
}

template<class T>
void dataFile<T>::push(const T& ele) {
	_size++;
	out.seekp(0);
	out.write(reinterpret_cast<const char *>(&_size), sizeof(int));
	out.seekp((_size - 1)*sizeofT + sizeof(int));
	out.write(reinterpret_cast<const char *>(&ele), sizeofT);
	out.flush();
}

template<class T>
void dataFile<T>::loadAll(T* ptr) {
	in.seekg(sizeof(int));
	in.read(reinterpret_cast<char *>(ptr), _size*sizeofT);
}

template<class T>
void dataFile<T>::upload(int __size,T* ptr) {
	out.seekp(0);
	_size = __size;
	out.write(reinterpret_cast<const char *>(&_size), sizeof(int));
	out.seekp(sizeof(int));
	out.write(reinterpret_cast<const char *>(ptr), _size*sizeofT);
	out.flush();
}