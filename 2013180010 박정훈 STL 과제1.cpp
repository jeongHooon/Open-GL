#include <iostream>
#include <fstream>
#include <Windows.h>
#include <set>
#include <vector>
#include <string>
#include <ctime>
#include <random>
#include <algorithm>
#define NumberOfPlayer 20000

using namespace std;

default_random_engine dre;
uniform_int_distribution<> ID(1,50000);
uniform_int_distribution<> Start_Score(0, 15000000);
uniform_int_distribution<> Random_Score(0, 25000000);
uniform_int_distribution<> Player_ID(0, 19999);
uniform_int_distribution<> Arena_Number(1, 5);

class Player{
	int ID;
	int Arena_Score[5];
	int Arena_Rank[5];
	int Total_Score;
	int Total_Rank;
	int Variable_Rank;
public:
	//생성자
	Player(int ID) { this->ID = ID; }
	//ID
	void Set_ID(int ID) { this->ID = ID; }
	int Get_ID() const { return ID; }
	//Arena_Score
	void Set_Arena_Score(int Arena, int Score) { Arena_Score[Arena] = Score; }
	int Get_Arena_Score(int Arena) const { return Arena_Score[Arena]; }
	//Total_Arena_Score
	void Set_Total_Arena_Score() { 
		Total_Score = 0;
		for (int Score : Arena_Score)
			Total_Score += Score;
	}
	int Get_Total_Arena_Score() const { return Total_Score; }
	//Arena_Rank
	void Set_Arena_Rank(int Arena, int Score) { Arena_Rank[Arena] = Score; }
	int Get_Arena_Rank(int Arena) const { return Arena_Rank[Arena]; }
	//Total_Arena_Rank
	void Set_Total_Arena_Rank(int Rank) { Total_Rank = Rank; }
	int Get_Total_Arena_Rank() const { return Total_Rank; }
	//Variable_Rank
	void Set_Variable_Rank(int Variable_Rank) { this->Variable_Rank = Variable_Rank; }
	int Get_Variable_Rank() const { return Variable_Rank; }
};

void Display_Menu();
void Play_Game(set<int> Manage_Players, vector<Player>& Players);
void Search_Player(vector<Player>& Players);
void Load_Players(vector<Player>& Players, ifstream& in);
void Save_Players(vector<Player>& Players);
void Set_Players(set<int> Manage_Players, vector<Player>& Players);

void main() {

	vector<Player> Players;
	Players.reserve(NumberOfPlayer);
	set<int> Manage_Players;
	int My_ID = 0;

	ifstream in("ManagementPlayer.txt");
	if (!in){
		Set_Players(Manage_Players, Players);
	}
	else Load_Players(Players, in);
	while (true) {
		system("cls");
		vector<Player>::iterator iter = find_if(Players.begin(), Players.end(), [&My_ID](const Player& a) { return a.Get_ID() == My_ID; });
		cout << "==============================" << endl;
		cout << "Up ID : " << (iter-1)->Get_ID() << endl;
		cout << "Total Score : " << (iter - 1)->Get_Total_Arena_Score() << endl;
		for (int i = 0; i < 5; ++i)
			cout << "Arena" << i + 1 << " Score : " << (iter - 1)->Get_Arena_Score(i) << "Rank : " << float((iter - 1)->Get_Arena_Rank(i)) / NumberOfPlayer * 100 << "%" << endl;
		cout << "Total Rank" << (iter - 1)->Get_Total_Arena_Rank() << "(" << float((iter - 1)->Get_Total_Arena_Rank()) / NumberOfPlayer * 100 << "%)" << endl;
		cout << "변동 폭" << " ";
		cout << (iter - 1)->Get_Variable_Rank() << endl;
		cout << "==============================" << endl;

		cout << "==============================" << endl;
		cout << "My ID : " << iter->Get_ID() << endl;
		cout << "Total Score : " << iter->Get_Total_Arena_Score() << endl;
		for (int i = 0; i < 5; ++i)
			cout << "Arena" << i + 1 << " Score : " << iter->Get_Arena_Score(i) << "Rank : " << float(iter->Get_Arena_Rank(i)) / NumberOfPlayer * 100 << "%" << endl;
		cout << "Total Rank" << iter->Get_Total_Arena_Rank() << "(" << float(iter->Get_Total_Arena_Rank()) / NumberOfPlayer * 100 << "%)" << endl;
		cout << "변동 폭" << " ";
		cout << iter->Get_Variable_Rank() << endl;
		cout << "==============================" << endl;

		cout << "==============================" << endl;
		cout << "Up ID : " << (iter + 1)->Get_ID() << endl;
		cout << "Total Score : " << (iter + 1)->Get_Total_Arena_Score() << endl;
		for (int i = 0; i < 5; ++i)
			cout << "Arena" << i + 1 << " Score : " << (iter + 1)->Get_Arena_Score(i) << "Rank : " << float((iter + 1)->Get_Arena_Rank(i)) / NumberOfPlayer * 100 << "%" << endl;
		cout << "Total Rank" << (iter + 1)->Get_Total_Arena_Rank() << "(" << float((iter + 1)->Get_Total_Arena_Rank()) / NumberOfPlayer * 100 << "%)" << endl;
		cout << "변동 폭" << " ";
		cout << (iter + 1)->Get_Variable_Rank() << endl;
		cout << "==============================" << endl;

		Display_Menu();
		int select;
		cout << "Select Menu" << endl;
		cin >> select;
		switch (select) {
		case 1:
			Play_Game(Manage_Players, Players);
			break;
		case 2:
			Search_Player(Players);
			break;
		case 3:
			Save_Players(Players);
			break;
		default:
			break;
		}
	}
}
void Display_Menu() {
	
	cout << "=============Menu=============" << endl;
	cout << "\t1. Play Game" << endl;
	cout << "\t2. Search ID" << endl;
	cout << "\t3. Save" << endl;
	cout << "==============================" << endl;
	//cin >> menu;
}

void Play_Game(set<int> Manage_Players, vector<Player>& Players) {
	int TenPerPlayers = NumberOfPlayer / 10 - 1;
	int Select_Arena;
	int Arena_Score;

	Select_Arena = Arena_Number(dre);
	Arena_Score = Random_Score(dre);
	switch (Select_Arena) {
	case 1: {
		set<int> s;
		s.insert(0);
		for (int i = 0; i < 1999; ++i) {
			int ran = Player_ID(dre);
			if (!s.count(Players[ran].Get_ID())) s.insert(Players[ran].Get_ID());
			else --i;
		}
		for (auto i = s.begin(); i != s.end(); ++i) {
			int k = *i;
			vector<Player>::iterator iter = find_if(Players.begin(), Players.end(), [&k](const Player& a) { return a.Get_ID() == k; });
			int score{ Random_Score(dre) };
			if(score > iter->Get_Arena_Score(0))
				iter->Set_Arena_Score(0, score);
		}
		break; 
	}
	case 2: {
		set<int> s;
		s.insert(0);
		for (int i = 0; i < 1999; ++i) {
			int ran = Player_ID(dre);
			if (!s.count(Players[ran].Get_ID())) s.insert(Players[ran].Get_ID());
			else --i;
		}
		for (auto i = s.begin(); i != s.end(); ++i) {
			int k = *i;
			vector<Player>::iterator iter = find_if(Players.begin(), Players.end(), [&k](const Player& a) { return a.Get_ID() == k; });
			int score{ Random_Score(dre) };
			if (score > iter->Get_Arena_Score(1))
				iter->Set_Arena_Score(1, score);
		}
		break;
	}
	case 3: {
		set<int> s;
		s.insert(0);
		for (int i = 0; i < 1999; ++i) {
			int ran = Player_ID(dre);
			if (!s.count(Players[ran].Get_ID())) s.insert(Players[ran].Get_ID());
			else --i;
		}
		for (auto i = s.begin(); i != s.end(); ++i) {
			int k = *i;
			vector<Player>::iterator iter = find_if(Players.begin(), Players.end(), [&k](const Player& a) { return a.Get_ID() == k; });
			int score{ Random_Score(dre) };
			if (score > iter->Get_Arena_Score(2))
				iter->Set_Arena_Score(2, score);
		}
		break;
	}
	case 4: {
		set<int> s;
		s.insert(0);
		for (int i = 0; i < 1999; ++i) {
			int ran = Player_ID(dre);
			if (!s.count(Players[ran].Get_ID())) s.insert(Players[ran].Get_ID());
			else --i;
		}
		for (auto i = s.begin(); i != s.end(); ++i) {
			int k = *i;
			vector<Player>::iterator iter = find_if(Players.begin(), Players.end(), [&k](const Player& a) { return a.Get_ID() == k; });
			int score{ Random_Score(dre) };
			if (score > iter->Get_Arena_Score(3))
				iter->Set_Arena_Score(3, score);
		}
		break;
	}
	case 5: {
		set<int> s;
		s.insert(0);
		for (int i = 0; i < 1999; ++i) {
			int ran = Player_ID(dre);
			if (!s.count(Players[ran].Get_ID())) s.insert(Players[ran].Get_ID());
			else --i;
		}
		for (auto i = s.begin(); i != s.end(); ++i) {
			int k = *i;
			vector<Player>::iterator iter = find_if(Players.begin(), Players.end(), [&k](const Player& a) { return a.Get_ID() == k; });
			int score{ Random_Score(dre) };
			if (score > iter->Get_Arena_Score(4))
				iter->Set_Arena_Score(4, score);
		}
		break;
	}
	}
	for (int i = 0; i < 5; ++i) {
		sort(Players.begin(), Players.end(), [&i](const Player& a, const Player& b) {
			return (a.Get_Arena_Score(i) > b.Get_Arena_Score(i));
		});
		for (int j = 0; j < NumberOfPlayer; ++j)
			Players[j].Set_Arena_Rank(i, j + 1);
	}
	for (int i = 0; i < NumberOfPlayer; ++i)
		Players[i].Set_Total_Arena_Score();
	sort(Players.begin(), Players.end(), [](const Player& a, const Player& b) {return a.Get_Total_Arena_Score() > b.Get_Total_Arena_Score(); });
	for (int i = 0; i < NumberOfPlayer; ++i) {
		Players[i].Set_Variable_Rank(Players[i].Get_Total_Arena_Rank() - (i + 1));
		Players[i].Set_Total_Arena_Rank(i + 1);
	}
}

void Search_Player(vector<Player>& Players) {
	int Search_ID = 0;

	cout << "찾을 ID를 입력하세요 : ";
	cin >> Search_ID;
	vector<Player>::iterator iter = find_if(Players.begin(), Players.end(), [&Search_ID](const Player& a) { return a.Get_ID() == Search_ID; });
	
	if (iter == Players.end())
		cout << "해당 플레이어는 존재하지 않습니다." << endl;
	else {
		cout << "==============================" << endl;
		cout << "My ID : " << iter->Get_ID() << endl;
		cout << "Total Score : " << iter->Get_Total_Arena_Score() << endl;
		for (int i = 0; i < 5; ++i)
			cout << "Arena" << i + 1 << " Score : " << iter->Get_Arena_Score(i) << "Rank : " << float(iter->Get_Arena_Rank(i)) / NumberOfPlayer * 100<< "%" << endl;
		cout << "Total Rank" << iter->Get_Total_Arena_Rank() << "(" << float(iter->Get_Total_Arena_Rank()) / NumberOfPlayer * 100 << "%)" << endl;
		cout << "변동 폭" << " ";
		cout << iter->Get_Variable_Rank() << endl;
		cout << "==============================" << endl;
	}
	system("pause");
}

void Set_Players(set<int> Manage_Players, vector<Player>& Players) {
	dre.seed(time(NULL));
	int n = 0;
	for (int i = 0; i < NumberOfPlayer - 1; ++i){
		n = ID(dre);
		if (!Manage_Players.count(n)) Manage_Players.insert(n);
		else --i;
	}
	Manage_Players.insert(0);

	for (auto i = Manage_Players.begin(); i != Manage_Players.end(); ++i){
		Player A(*i);
		Players.push_back(A);
	}
	for (int i = 0; i < NumberOfPlayer; ++i)
		for (int j = 0; j < 5; ++j)
			Players[i].Set_Arena_Score(j, Start_Score(dre));
	for (int i = 0; i < 5; ++i){
		sort(Players.begin(), Players.end(), [&i](const Player& a, const Player& b) {
			return (a.Get_Arena_Score(i) > b.Get_Arena_Score(i));
		});
		for (int j = 0; j < NumberOfPlayer; ++j)
			Players[j].Set_Arena_Rank(i, j + 1);
	}
	for (int i = 0; i < NumberOfPlayer; ++i)
		Players[i].Set_Total_Arena_Score();
	sort(Players.begin(), Players.end(), [](const Player& a, const Player& b) {return a.Get_Total_Arena_Score() > b.Get_Total_Arena_Score(); });
	for (int i = 0; i < NumberOfPlayer; ++i) {
		Players[i].Set_Total_Arena_Rank(i + 1);
		Players[i].Set_Variable_Rank(0);
	}
}

void Load_Players(vector<Player>& Players, ifstream& in)
{
	int Save_Data = 0;
	for (int i = 0; i < NumberOfPlayer; ++i) {
		Player A(100000);
		Players.push_back(A);
	}
	for (int i = 0; i < NumberOfPlayer; ++i){
		in >> Save_Data;
		Players[i].Set_ID(Save_Data);
		in >> Save_Data;
		Players[i].Set_Total_Arena_Rank(Save_Data);
		for (int j = 0; j < 5; ++j){
			in >> Save_Data;
			Players[i].Set_Arena_Score(j, Save_Data);
		}
		for (int j = 0; j < 5; ++j){
			in >> Save_Data;
			Players[i].Set_Arena_Rank(j, Save_Data);
		}
		in >> Save_Data;
		Players[i].Set_Variable_Rank(Save_Data);
		Players[i].Set_Total_Arena_Score();
	}
}

void Save_Players(vector<Player>& Players)
{
	ofstream out("ManagementPlayer.txt");

	for (int i = 0; i < NumberOfPlayer; ++i){
		out << Players[i].Get_ID() << endl;
		out << Players[i].Get_Total_Arena_Rank() << endl;
		for (int j = 0; j < 5; ++j)
			out << Players[i].Get_Arena_Score(j) << endl;
		for (int j = 0; j < 5; ++j)
			out << Players[i].Get_Arena_Rank(j) << endl;
		out << Players[i].Get_Variable_Rank() << endl;
	}
}