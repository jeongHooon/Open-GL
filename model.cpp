#include "model.h"
#include <iostream>

using namespace std;
int gid;
Model::Model() : size(0), data(nullptr), id(gid++) { cout << id << "default 생성자" << endl; }

Model::Model(int i) : size(i), id(gid++) {
	data = new char[size];
	cout << id << "생성자" << size << "byte 주소 " << (void*)data << endl;
}

Model::Model(const Model & other) : size(other.size), id(gid++) {
	data = new char[size];
	memcpy(data, other.data, size);
	cout << id << "복사 생성자" << size << "byte 주소 " << (void*)data << endl;
}

//이동 생성자

Model::Model(Model && other) : id(gid++) {
	size = other.size;
	data = other.data;
	other.size = 0;
	other.data = nullptr;
	cout << id << "이동 생성자" << size << "byte 주소 " << (void*)data << endl;
}
Model::~Model() {
	cout << id << "소멸자" << size << "byte 주소 " << (void*)data << endl;
	if (data != nullptr)
		delete[] data;
}
void Model::show()
{
	cout << id << "  " << size << "byte 주소 " <<  endl;
	cout << "---" << endl;
}
Model& Model::operator=(const Model& other) {
	if (this == &other)
		return *this;
	if (data != nullptr)
		delete[] data;
	size = other.size;
	data = new char[size];
	memcpy(data, other.data, size);
	cout << id << "할당연산자" << size << "byte 주소 " << (void*)data << endl;
	return *this;
}
Model& Model::operator=(Model&& other) {
	//나를 이동시키는건 의미가없다.
	if (this == &other)
		return *this;
	//내가 할당받은 메모리가 있다면 먼저 해지한다.
	if (data != nullptr)
		delete[] data;
	size = other.size;
	data = other.data;

	//내 멤버를 other의 멤버값으로 쓴다.
	other.size = 0;
	other.data = nullptr;
	//other의 멤버를 초기화한다.

	cout << id << "이동대입연산자" << size << "byte 주소 " << (void*)data << endl;
	return *this;
}
