#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <set>

using namespace std;

class Score {
	string name;
	int score1;
	int score2;
	int VariableRank;
	int BeforeRank = 0;
public:
	Score() {}
	Score(string n, int s1, int s2) :  name(n), score1(s1), score2(s2) {}
	string getName() { return name; }
	int getScore1() const { return score1; }
	void setScore1(int s) { score1 = s; }
	int getScore2() const { return score2; }
	void setVariableRank(int v) { VariableRank = v; }
	int getVariableRank() { return VariableRank; }
	void setBeforeRank(int r) { BeforeRank = r; }
	int getBeforeRank() { return BeforeRank; }

};
void makeData();
int main() {
	makeData();

	vector<Score> v;
	v.reserve(20000);
	string inData;
	int inScore1;
	int inScore2;

	///////// 1
	ifstream in("2017년 1학기 중간시험.txt");
	while (in >> inData >> inScore1 >> inScore2) 
		v.push_back(Score(inData, inScore1, inScore2));	

	///////// 2
	sort(v.begin(), v.end(), [](const Score& a, const Score& b) { return (a.getScore1() + a.getScore2()) > (b.getScore1() + b.getScore2()); });
	cout << "Name : " << v[9999].getName() << " Socre1 : "<< v[9999].getScore1() << " Score2 : " << v[9999].getScore2() << endl;
	string name = v[9999].getName();
	///////// 3	
	default_random_engine dre;
	dre.seed(20170425);
	uniform_int_distribution<> ui(1, 100000);

	for (int i = 0; i < v.size(); ++i) {
		int score = ui(dre);
		v[i].setBeforeRank(i + 1);
		if (score > v[i].getScore1())
			v[i].setScore1(score);
	}

	sort(v.begin(), v.end(), [](const Score& a, const Score& b) { return (a.getScore1() + a.getScore2()) > (b.getScore1() + b.getScore2()); });
	for (int i = 0; i < v.size(); ++i) 
		v[i].setVariableRank(v[i].getBeforeRank() - (i + 1));

	for (int i = 0; i < v.size(); ++i) {
		if (v[i].getName() == name)
			cout << v[i].getName() << " " << "변동폭" << v[i].getVariableRank() << " " << v[i].getScore1() << " " << v[i].getScore2() << endl;
	}
	/*for (int i = 0; i < v.size(); ++i) {
		if (v[i].getBeforeRank() == 10000)
			cout << v[i].getName() << " " << "변동폭" << v[i].getVariableRank() << " " << v[i].getScore1() << " " << v[i].getScore2() << endl;
	}*/
}
void makeData() {
	string name;
	int score1;
	int score2;

	default_random_engine dre;
	dre.seed(20170425);
	uniform_int_distribution<> ui(1, 100000);
	
	ofstream out("2017년 1학기 중간시험.txt");


	for (int i = 0; i < 20000; ++i) {
		out << 'p' << i + 1 << '\t';
		out << ui(dre) << '\t' << ui(dre) << endl;
	}
	cout << "20000개의 자료를 생성하여 파일에 기록하였음" << endl;
}