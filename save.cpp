#include <iostream>
#include <chrono>
#include <ctime>
#include <string>
#include <fstream>

using namespace std;

void save() {

	cout << "현재 파일이 저장되었습니다" << endl;

	//날짜와 시간을 기록
	auto tp = chrono::system_clock::now();
	time_t t = chrono::system_clock::to_time_t(tp);
	string date = ctime(&t);

	//현재 소스.cpp 를 기록한다	
	//저장할 파일을 연다.
	ifstream in("소스.cpp");
	if (!in)
		cout << " 존재하지 않음 " << endl;
	ofstream out("2017 1 STL 화56목23.txt", ios::app);

	//출력 파일에 저장할 파일에 덧붙인다.
	out << endl << endl << endl;
	out << "========================" << endl;
	out << date;
	out << "========================" << endl;

	//입력파일의 모든 내용을 출력파일에 쓴다
	char c;
	while (in.get(c))
		out.put(c);


}