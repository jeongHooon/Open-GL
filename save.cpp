#include <iostream>
#include <chrono>
#include <ctime>
#include <string>
#include <fstream>

using namespace std;

void save() {

	cout << "���� ������ ����Ǿ����ϴ�" << endl;

	//��¥�� �ð��� ���
	auto tp = chrono::system_clock::now();
	time_t t = chrono::system_clock::to_time_t(tp);
	string date = ctime(&t);

	//���� �ҽ�.cpp �� ����Ѵ�	
	//������ ������ ����.
	ifstream in("�ҽ�.cpp");
	if (!in)
		cout << " �������� ���� " << endl;
	ofstream out("2017 1 STL ȭ56��23.txt", ios::app);

	//��� ���Ͽ� ������ ���Ͽ� �����δ�.
	out << endl << endl << endl;
	out << "========================" << endl;
	out << date;
	out << "========================" << endl;

	//�Է������� ��� ������ ������Ͽ� ����
	char c;
	while (in.get(c))
		out.put(c);


}