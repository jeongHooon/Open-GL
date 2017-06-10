#include "model.h"
#include <iostream>

using namespace std;
int gid;
Model::Model() : size(0), data(nullptr), id(gid++) { cout << id << "default ������" << endl; }

Model::Model(int i) : size(i), id(gid++) {
	data = new char[size];
	cout << id << "������" << size << "byte �ּ� " << (void*)data << endl;
}

Model::Model(const Model & other) : size(other.size), id(gid++) {
	data = new char[size];
	memcpy(data, other.data, size);
	cout << id << "���� ������" << size << "byte �ּ� " << (void*)data << endl;
}

//�̵� ������

Model::Model(Model && other) : id(gid++) {
	size = other.size;
	data = other.data;
	other.size = 0;
	other.data = nullptr;
	cout << id << "�̵� ������" << size << "byte �ּ� " << (void*)data << endl;
}
Model::~Model() {
	cout << id << "�Ҹ���" << size << "byte �ּ� " << (void*)data << endl;
	if (data != nullptr)
		delete[] data;
}
void Model::show()
{
	cout << id << "  " << size << "byte �ּ� " <<  endl;
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
	cout << id << "�Ҵ翬����" << size << "byte �ּ� " << (void*)data << endl;
	return *this;
}
Model& Model::operator=(Model&& other) {
	//���� �̵���Ű�°� �ǹ̰�����.
	if (this == &other)
		return *this;
	//���� �Ҵ���� �޸𸮰� �ִٸ� ���� �����Ѵ�.
	if (data != nullptr)
		delete[] data;
	size = other.size;
	data = other.data;

	//�� ����� other�� ��������� ����.
	other.size = 0;
	other.data = nullptr;
	//other�� ����� �ʱ�ȭ�Ѵ�.

	cout << id << "�̵����Կ�����" << size << "byte �ּ� " << (void*)data << endl;
	return *this;
}
