#include <iostream>
#include <vector>
#include <chrono>
#include <Windows.h>
using namespace std;

class Test {
	char* p;
public:
	Test() { p = new char[10000]; }
	~Test() { delete[] p; }
	Test(const Test& other) { p = new char[10000]; memcpy(p, other.p, 100000); }
	Test(Test && other) {
		p = other.p;
		other.p = nullptr;
	}
};

int main() {
	//system("chcp 949");
	vector<Test> v;

	auto start = chrono::system_clock::now();

	//for (int i = 0; i < 10; ++i)
		
	v.push_back(Test());

	auto end = chrono::system_clock::now();
	auto diff = end - start;
	auto msec = chrono::duration_cast<chrono::milliseconds>(diff);
	cout << "경과시간 - " << msec.count() << "mSec" << endl;


	v.clear();
	v.shrink_to_fit();
	cout << "v의 원소수 - " << v.size() << endl;

	
}