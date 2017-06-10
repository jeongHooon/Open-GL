#include<iostream>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include <list>
#include <chrono>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define SPACE 32
#define SIZE 19
#define WHITE 2
#define BLACK 1
#define EMPTY 0
using namespace std;

void gotoxy(int x, int y);
void Draw_Base(list<int>& a);
void inputKey(char base[][19], char, int *, int *);
void Draw_Stone(char base[][19]);
list<int> playGame(list<int>& a);
void saveGame(list<int>& a);
void replay(list<int>& a);
void step_replay(list<int>& a);
void menu();
void check34(char base[][19]);
void AI_BLACK(char base[][19]);
void AI_WHITE(char base[][19]);

typedef struct aaa {
	int x;
	int y;
	double c;
}aaa;

aaa AI_value = { 0 };
aaa qwe1[SIZE][SIZE] = { 0 };
aaa qwe2[SIZE][SIZE] = { 0 };
int myTurn = 0;
int nowB[2][SIZE] = { 0 }, nowW[2][SIZE] = { 0 };
int max_H[4][SIZE], max_V[2][SIZE], max_D1[2][SIZE], max_D2[2][SIZE], max_D3[2][SIZE], max_D4[2][SIZE];
double value[SIZE][SIZE] = { 0 };
bool state = true;
int main() {
	int select = 0;
	list<int> key_Que;
	while (select!= 27) {
		system("cls");
		menu();
		for (auto d : key_Que)
			cout << d << endl;
		cin >> select;
		rewind(stdin);
		switch (select) {
		case 1: {
			system("cls");
			key_Que.clear();
			key_Que = playGame(key_Que);
			break;
		}
		case 2: {
			saveGame(key_Que);
			break;
		}
		case 3: {
			replay(key_Que);
			break;
		}
		case 4: {
			step_replay(key_Que);
			break;
		}
		}
	}
}
void menu() {
	cout << "=============" << endl;
	cout << "1.惟績獣拙" << endl;
	cout << "2.煽舌馬奄" << endl;
	cout << "3.軒巴傾戚" << endl;
	cout << "4.舘域紺 軒巴傾戚" << endl;
	cout << "=============" << endl;
}
list<int> playGame(list<int>& a) {
	char base[SIZE][SIZE] = { 0 };
	int x = 0, y = 0;
	char Key = 0;
	list<int> key_Que = a;
	base[19][19] = 0;
	Draw_Base(key_Que);
	gotoxy(x, y);
	while (Key != 27 && state) {
		auto start = chrono::system_clock::now();
		Key = getch();
		auto end = chrono::system_clock::now();
		auto sec = end - start;
		auto msec = chrono::duration_cast<chrono::milliseconds>(sec);
		if (msec.count() != 0)
			key_Que.push_back(msec.count());
		if (Key != -32)
			key_Que.push_back(Key);
		inputKey(base, Key, &x, &y);
		check34(base);
		system("cls");
		gotoxy(0, 0);
		Draw_Base(key_Que);
		AI_WHITE(base);
		check34(base);
		Draw_Stone(base);
		gotoxy(x, y);
	}
	if (!state) {
		system("cls");
		if (myTurn % 2 == 0) {
			cout << "Player White Win" << endl;
		}
		else {
			cout << "Player Black Win" << endl;
		}
	}
	return key_Que;
}
void saveGame(list<int>& a) {
	ofstream out("replay.txt");
	for (auto d : a) {
		out << d << endl;
	}
}
void replay(list<int>& a) {
	char base[SIZE][SIZE] = { 0 };
	int x = 0, y = 0;
	char Key = 0;
	list<int> key_Que = a;
	base[19][19] = 0;
	system("cls");
	Draw_Base(key_Que);
	gotoxy(x, y);
	if (!key_Que.size()) {
		int save;
		ifstream in("replay.txt");
		if (!in)
			return;
		while (!in.eof()) {
			in >> save;
			key_Que.push_back(save);
		}
	}
	bool turn = true;
	for(auto d: key_Que) {
		if (turn) {
			Sleep(d);
			turn = false;
		}
		else {
			inputKey(base, d, &x, &y);
			check34(base);
			system("cls");
			gotoxy(0, 0);
			Draw_Base(key_Que);
			AI_WHITE(base);
			check34(base);
			Draw_Stone(base);
			gotoxy(x, y);
			turn = true;
		}
	}
	while (Key != 27) {
		gotoxy(0, 21);
		cout << "宜焼亜形檎 ESC" << endl;
		Key = getch();
	}
}
void step_replay(list<int>& a) {
	char base[SIZE][SIZE] = { 0 };
	int x = 0, y = 0;
	char Key = 0;
	list<int> key_Que = a;
	bool turn = true; 
	base[19][19] = 0;
	system("cls");
	Draw_Base(key_Que);
	gotoxy(0, 20);
	cout << "Next Step : SpaceBar";
	if (!key_Que.size()) {
		int save;
		ifstream in("replay.txt");
		if (!in)
			return;
		while (!in.eof()) {
			in >> save;
			key_Que.push_back(save);
		}
	}
	gotoxy(x, y);
	while (getch() != SPACE);
	for (auto d : key_Que) {
		if (turn) {
			turn = false;
		}
		else {
			inputKey(base, d, &x, &y);
			check34(base);
			system("cls");
			gotoxy(0, 20);
			cout << "Next Step : SpaceBar";
			gotoxy(0, 0);
			Draw_Base(key_Que);
			Draw_Stone(base);
			gotoxy(x, y);
			while (getch() != SPACE);
			AI_WHITE(base);
			check34(base);
			Draw_Stone(base);
			gotoxy(x, y);
			turn = true;
		}
	}
	while (Key != 27) {
		gotoxy(0, 21);
		cout << "宜焼亜形檎 ESC" << endl;
		Key = getch();
	}
}
void gotoxy(int x, int y)
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}
void AI_WHITE(char base[][19]) {
	for (int i = 0; i < SIZE; ++i)//search max vlaue
		for (int j = 0; j < SIZE; ++j)
			if (value[i][j]>AI_value.c) {
				AI_value.c = value[i][j];
				AI_value.x = j;
				AI_value.y = i;
			}
	if (myTurn == 0) {
		AI_value.x = 9;
		AI_value.y = 9;
		AI_value.c = 1;
	}

	else if (base[AI_value.y][AI_value.x] != WHITE && base[AI_value.y][AI_value.x] != BLACK)
		if (myTurn % 2 == 1) {
			base[AI_value.y][AI_value.x] = WHITE;
			++myTurn;
		}
	AI_value.y = 0;
	AI_value.x = 0;
	AI_value.c = 0;
}
void AI_BLACK(char base[][19]) {
	for (int i = 0; i < SIZE; ++i)//search max vlaue
		for (int j = 0; j < SIZE; ++j)
			if (value[i][j]>AI_value.c) {
				AI_value.c = value[i][j];
				AI_value.x = j;
				AI_value.y = i;
			}
	if (myTurn == 0) {
		base[9][9] = BLACK;
		++myTurn;
	}

	else if (base[AI_value.y][AI_value.x] != WHITE && base[AI_value.y][AI_value.x] != BLACK)
		if (myTurn % 2 == 0) {
			base[AI_value.y][AI_value.x] = BLACK;
			++myTurn;
		}
	AI_value.y = 0;
	AI_value.x = 0;
	AI_value.c = 0;
}
void Draw_Base(list<int>& key_Que) {
	int i;
	int j;
	printf("Γ");
	for (i = 0; i< 17; ++i)
		printf("Θ");
	printf("Δ");
	printf("\n");


	for (i = 0; i < SIZE - 2; ++i) {
		printf("Η");
		for (j = 0; j < SIZE - 2; ++j)
			printf("Λ");
		printf("Ι");

		printf("\n");
	}
	printf("Ζ");
	for (i = 0; i < SIZE - 2; ++i)
		printf("Κ");
	printf("Ε\n");
}
void inputKey(char base[][19], char Key, int *x, int *y) {
	switch (Key) {
	case UP:
		if (*y != 0)
			--(*y);
		break;
	case DOWN:
		if (*y != 18)
			++(*y);
		break;
	case RIGHT:
		if (*x != 36)
			*x += 2;
		break;
	case LEFT:
		if (*x != 0)
			*x -= 2;
		break;
	case SPACE:
		if (base[*y][(*x) / 2] != WHITE && base[*y][(*x) / 2] != BLACK) {
			if (myTurn % 2 == 0) {
				base[*y][*x / 2] = BLACK;
				++myTurn;
			}
			else {
				base[*y][*x / 2] = WHITE;
				++myTurn;
			}
		}
		break;
	}
}
void Draw_Stone(char base[][19]) {
	for (int i = 0; i < SIZE; ++i)
		for (int j = 0; j < SIZE; ++j) {
			if (base[i][j] == 1) {
				gotoxy(j * 2, i);
				printf("】");
			}
			else if (base[i][j] == 2) {
				gotoxy(j * 2, i);
				printf("＋");
			}
		}
}
void check34(char base[][19]) {
	for (int i = 0; i < SIZE; ++i)
		for (int j = 0; j < SIZE; ++j)
			value[i][j] = 0;
	for (int i = 0; i < SIZE; ++i)
		for (int j = 0; j < SIZE; ++j) {
			if (base[i][j] == BLACK) {// o
				if ((j - 1) > -1 && base[i][j - 1] == EMPTY)
					value[i][j - 1] += 0.15;
				if ((j + 1) < SIZE &&base[i][j + 1] == EMPTY)
					value[i][j + 1] += 0.15;
				if ((i - 1) > -1 && base[i - 1][j] == EMPTY)
					value[i - 1][j] += 0.15;
				if ((i + 1) < SIZE &&base[i + 1][j] == EMPTY)
					value[i + 1][j] += 0.15;
				if ((j - 1) > -1 && (i - 1) > -1 && base[i - 1][j - 1] == EMPTY)
					value[i - 1][j - 1] += 0.15;
				if ((j - 1) > -1 && (i + 1) < SIZE && base[i + 1][j - 1] == EMPTY)
					value[i + 1][j - 1] += 0.15;
				if ((j + 1) < SIZE && (i - 1) > -1 && base[i - 1][j + 1] == EMPTY)
					value[i - 1][j + 1] += 0.15;
				if ((j + 1) < SIZE && (i + 1) < SIZE && base[i + 1][j + 1] == EMPTY)
					value[i + 1][j + 1] += 0.15;
			}
			//////亜稽
			if (base[i][j] == BLACK &&base[i][j + 1] == BLACK) {////oo
				if ((j - 1) > -1 && base[i][j - 1] == EMPTY)
					value[i][j - 1] += 0.5;
				if ((j + 2) < SIZE &&base[i][j + 2] == EMPTY)
					value[i][j + 2] += 0.5;
				//// special
				if ((j - 1) > -1 && base[i][j - 1] == EMPTY && base[i][j + 2] == WHITE)
					value[i][j - 1] -= 0.3;
				if ((j + 2) < SIZE &&base[i][j + 2] == EMPTY && base[i][j - 1] == WHITE)
					value[i][j + 2] -= 0.3;

			}

			if (base[i][j] == BLACK&&base[i][j + 1] == BLACK&&base[i][j + 2] == BLACK) { //ししし
				if ((j - 1) > -1 && base[i][j - 1] == EMPTY) {
					value[i][j - 1] += 1.5;
					if ((j + 3) < SIZE &&base[i][j + 3] == WHITE)
						value[i][j - 1] -= 0.5;
				}
				if ((j + 3) < SIZE &&base[i][j + 3] == EMPTY) {
					value[i][j + 3] += 1.5;
					if ((j - 1) > -1 && base[i][j - 1] == WHITE)
						value[i][j + 3] -= 0.5;
				}
			}
			if (base[i][j] == BLACK&&base[i][j + 1] == BLACK&&base[i][j + 2] == EMPTY && base[i][j + 3] == BLACK) {//ししxし
				if ((j - 1) > -1 && base[i][j - 1] == EMPTY) {
					value[i][j - 1] += 1.5;
					if ((j + 4) < SIZE &&base[i][j + 4] == WHITE)
						value[i][j - 1] -= 0.5;
				}
				if ((j + 4) < SIZE &&base[i][j + 4] == EMPTY) {
					value[i][j + 4] += 1.5;
					if ((j - 1) > -1 && base[i][j - 1] == WHITE)
						value[i][j + 4] -= 0.5;
				}
				value[i][j + 2] += 1.5;
				if (((j + 4) < SIZE &&base[i][j + 4] == WHITE) || ((j - 1) > -1 && base[i][j - 1] == WHITE))
					value[i][j + 2] -= 0.5;
			}
			if (base[i][j] == BLACK&&base[i][j + 1] == EMPTY&&base[i][j + 2] == BLACK&&base[i][j + 3] == BLACK) {//しxしし
				if ((j - 1) > -1 && base[i][j - 1] == EMPTY)
					value[i][j - 1] += 1.5;
				if ((j + 4) < SIZE &&base[i][j + 4] == EMPTY)
					value[i][j + 4] += 1.5;
				value[i][j + 1] += 1.5;
				if (((j + 4) < SIZE &&base[i][j + 4] == WHITE) || ((j - 1) > -1 && base[i][j - 1] == WHITE))
					value[i][j + 1] -= 0.5;
			}
			if (base[i][j] == BLACK&&base[i][j + 1] == BLACK&&base[i][j + 2] == BLACK&&base[i][j + 3] == BLACK) {//しししし
				if ((j - 1) > -1 && base[i][j - 1] == EMPTY)
					value[i][j - 1] += 20;
				if ((j + 4) < SIZE &&base[i][j + 4] == EMPTY)
					value[i][j + 4] += 20;
			}
			if (base[i][j] == BLACK&&base[i][j + 1] == BLACK&&base[i][j + 2] == BLACK&&base[i][j + 3] == EMPTY&&base[i][j + 4] == BLACK) {//しししxし
				if ((j - 1) > -1 && base[i][j - 1] == EMPTY)
					--value[i][j - 1];
				if ((j + 5) < SIZE &&base[i][j + 5] == EMPTY)
					--value[i][j + 5];
				value[i][j + 3] += 20;
			}
			if (base[i][j] == BLACK&&base[i][j + 1] == BLACK&&base[i][j + 2] == EMPTY&&base[i][j + 3] == BLACK&&base[i][j + 4] == BLACK) {//ししxしし
				if ((j - 1) > -1 && base[i][j - 1] == EMPTY)
					--value[i][j - 1];
				if ((j + 5) < SIZE &&base[i][j + 5] == EMPTY)
					--value[i][j + 5];
				value[i][j + 2] += 20;
			}
			if (base[i][j] == BLACK&&base[i][j + 1] == EMPTY&&base[i][j + 2] == BLACK&&base[i][j + 3] == BLACK&&base[i][j + 4] == BLACK) {//しxししし
				if ((j - 1) > -1 && base[i][j - 1] == EMPTY)
					--value[i][j - 1];
				if ((j + 5) < SIZE &&base[i][j + 5] == EMPTY)
					--value[i][j + 5];
				value[i][j + 1] += 20;
			}
			if (base[i][j] == BLACK&&base[i][j + 1] == BLACK&&base[i][j + 2] == BLACK&&base[i][j + 3] == BLACK&&base[i][j + 4] == BLACK) {//ししししし
				state = false;
			}
			////// 室稽
			if (base[i][j] == BLACK &&base[i + 1][j] == BLACK) {////oo
				if ((i - 1) > -1 && base[i - 1][j] == EMPTY) {
					value[i - 1][j] += 0.5;
					if ((i + 2) < SIZE &&base[i + 2][j] == WHITE)
						value[i - 1][j] -= 0.3;
				}
				if ((i + 2) < SIZE &&base[i + 2][j] == EMPTY) {
					value[i + 2][j] += 0.5;
					if ((i - 1) > -1 && base[i - 1][j] == WHITE)
						value[i + 2][j] -= 0.3;
				}
			}
			if (base[i][j] == BLACK&&base[i + 1][j] == BLACK&&base[i + 2][j] == BLACK) { //ししし
				if ((i - 1) > -1 && base[i - 1][j] == EMPTY) {
					value[i - 1][j] += 1.5;
					if ((i + 3) < SIZE &&base[i + 3][j] == WHITE)
						value[i - 1][j] -= 0.5;
				}
				if ((i + 3) < SIZE &&base[i + 3][j] == EMPTY) {
					value[i + 3][j] += 1.5;
					if ((i - 1) > -1 && base[i - 1][j] == WHITE)
						value[i + 3][j] -= 0.5;
				}
			}
			if (base[i][j] == BLACK&&base[i + 1][j] == BLACK&&base[i + 2][j] == EMPTY && base[i + 3][j] == BLACK) {//ししxし

				if ((i - 1) > -1 && base[i - 1][j] == EMPTY) {
					value[i - 1][j] += 1.5;
					if ((i + 4) < SIZE &&base[i + 4][j] == WHITE)
						value[i - 1][j] -= 0.5;
				}
				if ((i + 4) < SIZE &&base[i + 4][j] == EMPTY) {
					value[i + 4][j] += 1.5;
					if ((i - 1) > -1 && base[i - 1][j] == WHITE)
						value[i + 4][j] -= 0.5;
				}
				value[i + 2][j] += 1.5;
				if ((i + 4) < SIZE &&base[i + 4][j] == WHITE)
					value[i + 2][j] -= 0.7;
				if ((i - 1) > -1 && base[i - 1][j] == WHITE)
					value[i + 2][j] -= 0.7;
			}
			if (base[i][j] == BLACK&&base[i + 1][j] == EMPTY&&base[i + 2][j] == BLACK&&base[i + 3][j] == BLACK) {//しxしし
				if ((i - 1) > -1 && base[i - 1][j] == EMPTY) {
					value[i][j - 1] += 1.5;
					if ((i + 4) < SIZE &&base[i + 4][j] == WHITE)
						value[i][j - 1] -= 0.5;
				}
				if ((i + 4) < SIZE &&base[i + 4][j] == EMPTY) {
					value[i + 4][j] += 1.5;
					if ((i - 1) > -1 && base[i - 1][j] == WHITE)
						value[i + 4][j] -= 0.5;
				}
				value[i + 1][j] += 1.5;
				if ((i + 4) < SIZE &&base[i + 4][j] == WHITE)
					value[i + 1][j] -= 0.5;
				if ((i - 1) > -1 && base[i - 1][j] == WHITE)
					value[i + 1][j] -= 0.5;

			}
			if (base[i][j] == BLACK&&base[i + 1][j] == BLACK&&base[i + 2][j] == BLACK&&base[i + 3][j] == BLACK) {//しししし
				if ((i - 1) > -1 && base[i - 1][j] == EMPTY)
					value[i - 1][j] += 20;
				if ((i + 4) < SIZE &&base[i + 4][j] == EMPTY)
					value[i + 4][j] += 20;
			}
			if (base[i][j] == BLACK&&base[i + 1][j] == BLACK&&base[i + 2][j] == BLACK&&base[i + 3][j] == EMPTY&&base[i + 4][j] == BLACK) {//しししxし
				if ((i - 1) > -1 && base[i - 1][j] == EMPTY)
					--value[i - 1][j];
				if ((i + 5) < SIZE &&base[i + 5][j] == EMPTY)
					--value[i + 5][j];
				value[i + 3][j] += 20;
			}
			if (base[i][j] == BLACK&&base[i + 1][j] == BLACK&&base[i + 2][j] == EMPTY&&base[i + 3][j] == BLACK&&base[i + 4][j] == BLACK) {//ししxしし
				if ((i - 1) > -1 && base[i - 1][j] == EMPTY)
					--value[i - 1][j];
				if ((i + 5) < SIZE &&base[i + 5][j] == EMPTY)
					--value[i + 5][j];
				value[i + 2][j] += 20;
			}
			if (base[i][j] == BLACK&&base[i + 1][j] == EMPTY&&base[i + 2][j] == BLACK&&base[i + 3][j] == BLACK&&base[i + 4][j] == BLACK) {//しxししし
				if ((i - 1) > -1 && base[i - 1][j] == EMPTY)
					--value[i - 1][j];
				if ((i + 5) < SIZE &&base[i + 5][j] == EMPTY)
					--value[i + 5][j];
				value[i + 1][j] += 20;
			}
			if (base[i][j] == BLACK&&base[i + 1][j] == BLACK&&base[i + 2][j] == BLACK&&base[i + 3][j] == BLACK&&base[i + 4][j] == BLACK) {//ししししし
				state = false;
			}
			//////企唖識 1
			if (base[i][j] == BLACK &&base[i + 1][j + 1] == BLACK) {////oo
				if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == EMPTY) {
					value[i - 1][j - 1] += 0.5;
					if ((i + 2) < SIZE && (j + 2) < SIZE && base[i + 2][j + 2] == WHITE)
						value[i - 1][j - 1] -= 0.3;
				}
				if ((i + 2) < SIZE && (j + 2) < SIZE && base[i + 2][j + 2] == EMPTY) {
					value[i + 2][j + 2] += 0.5;
					if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == WHITE)
						value[i + 2][j + 2] -= 0.3;
				}
			}
			if (base[i][j] == BLACK&&base[i + 1][j + 1] == BLACK&&base[i + 2][j + 2] == BLACK) { //ししし
				if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == EMPTY) {
					value[i - 1][j - 1] += 1.5;
					if ((i + 3) < SIZE && (j + 3) < SIZE &&base[i + 3][j + 3] == WHITE)
						value[i - 1][j - 1] -= 0.5;
				}
				if ((i + 3) < SIZE && (j + 3) < SIZE &&base[i + 3][j + 3] == EMPTY) {
					value[i + 3][j + 3] += 1.5;
					if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == WHITE)
						value[i + 3][j + 3] -= 0.5;
				}
			}
			if (base[i][j] == BLACK&&base[i + 1][j + 1] == BLACK&&base[i + 2][j + 2] == EMPTY && base[i + 3][j + 3] == BLACK) {//ししxし
				if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == EMPTY) {
					value[i - 1][j - 1] += 1.5;
					if ((i + 4) < SIZE && (j + 4) < SIZE &&base[i + 4][j + 4] == WHITE)
						value[i - 1][j - 1] -= 0.5;
				}
				if ((i + 4) < SIZE && (j + 4) < SIZE &&base[i + 4][j + 4] == EMPTY) {
					value[i + 4][j + 4] += 1.5;
					if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == WHITE)
						value[i + 4][j + 4] -= 0.5;
				}
				value[i + 2][j + 2] += 1.5;
				if ((i + 4) < SIZE && (j + 4) < SIZE &&base[i + 4][j + 4] == WHITE)
					value[i + 2][j + 2] -= 0.7;
				if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == WHITE)
					value[i + 2][j + 2] -= 0.7;
			}
			if (base[i][j] == BLACK&&base[i + 1][j + 1] == EMPTY&&base[i + 2][j + 2] == BLACK&&base[i + 3][j + 3] == BLACK) {//しxしし
				if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == EMPTY) {
					value[i - 1][j - 1] += 1.5;
					if ((i + 4) < SIZE && (j + 4) < SIZE &&base[i + 4][j + 4] == WHITE)
						value[i - 1][j - 1] -= 0.5;
				}
				if ((i + 4) < SIZE && (j + 4) < SIZE &&base[i + 4][j + 4] == EMPTY) {
					value[i + 4][j + 4] += 1.5;
					if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == WHITE)
						value[i + 4][j + 4] -= 0.5;
				}
				value[i + 1][j + 1] += 1.5;
				if ((i + 4) < SIZE && (j + 4) < SIZE &&base[i + 4][j + 4] == WHITE)
					value[i + 1][j + 1] -= 0.7;
				if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == WHITE)
					value[i + 1][j + 1] -= 0.7;
			}
			if (base[i][j] == BLACK&&base[i + 1][j + 1] == BLACK&&base[i + 2][j + 2] == BLACK&&base[i + 3][j + 3] == BLACK) {//しししし
				if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == EMPTY)
					value[i - 1][j - 1] += 20;
				if ((i + 4) < SIZE && (j + 4) < SIZE &&base[i + 4][j + 4] == EMPTY)
					value[i + 4][j + 4] += 20;
			}
			if (base[i][j] == BLACK&&base[i + 1][j + 1] == BLACK&&base[i + 2][j + 2] == BLACK&&base[i + 3][j + 3] == EMPTY&&base[i + 4][j + 4] == BLACK) {//しししxし
				if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == EMPTY)
					--value[i - 1][j - 1];
				if ((i + 5) < SIZE && (j + 5) < SIZE &&base[i + 5][j + 5] == EMPTY)
					--value[i + 5][j + 5];
				value[i + 3][j + 3] += 20;
			}
			if (base[i][j] == BLACK&&base[i + 1][j + 1] == BLACK&&base[i + 2][j + 2] == EMPTY&&base[i + 3][j + 3] == BLACK&&base[i + 4][j + 4] == BLACK) {//ししxしし
				if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == EMPTY)
					--value[i - 1][j - 1];
				if ((i + 5) < SIZE && (j + 5) < SIZE &&base[i + 5][j + 5] == EMPTY)
					--value[i + 5][j + 5];
				value[i + 2][j + 2] += 20;
			}
			if (base[i][j] == BLACK&&base[i + 1][j + 1] == EMPTY&&base[i + 2][j + 2] == BLACK&&base[i + 3][j + 3] == BLACK&&base[i + 4][j + 4] == BLACK) {//しxししし
				if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == EMPTY)
					--value[i - 1][j - 1];
				if ((i + 5) < SIZE && (j + 5) < SIZE &&base[i + 5][j + 5] == EMPTY)
					--value[i + 5][j + 5];
				value[i + 1][j + 1] += 20;
			}
			if (base[i][j] == BLACK&&base[i + 1][j + 1] == BLACK&&base[i + 2][j + 2] == BLACK&&base[i + 3][j + 3] == BLACK&&base[i + 4][j + 4] == BLACK) {//ししししし
				state = false;
			}
			//////企唖識 2
			if (base[i][j] == BLACK &&base[i + 1][j - 1] == BLACK) {////oo
				if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == EMPTY) {
					value[i - 1][j + 1] += 0.5;
					if ((i + 2) < SIZE && (j - 2) > -1 && base[i + 2][j - 2] == WHITE)
						value[i - 1][j + 1] -= 0.3;
				}
				if ((i + 2) < SIZE && (j - 2) > -1 && base[i + 2][j - 2] == EMPTY) {
					value[i + 2][j - 2] += 0.5;
					if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == EMPTY)
						value[i + 2][j - 2] -= 0.3;
				}
			}
			if (base[i][j] == BLACK&&base[i + 1][j - 1] == BLACK&&base[i + 2][j - 2] == BLACK) { //ししし
				if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == EMPTY) {
					value[i - 1][j + 1] += 1.5;
					if ((i + 3) < SIZE && (j - 3) > -1 && base[i + 3][j - 3] == WHITE)
						value[i - 1][j + 1] -= 0.5;
				}
				if ((i + 3) < SIZE && (j - 3) > -1 && base[i + 3][j - 3] == EMPTY) {
					value[i + 3][j - 3] += 1.5;
					if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == WHITE)
						value[i + 3][j - 3] -= 0.5;
				}
			}
			if (base[i][j] == BLACK&&base[i + 1][j - 1] == BLACK&&base[i + 2][j - 2] == EMPTY && base[i + 3][j - 3] == BLACK) {//ししxし
				if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == EMPTY) {
					value[i - 1][j + 1] += 1.5;
					if ((i + 4) < SIZE && (j - 4) > -1 && base[i + 4][j - 4] == WHITE)
						value[i - 1][j + 1] -= 0.5;
				}
				if ((i + 4) < SIZE && (j - 4) > -1 && base[i + 4][j - 4] == EMPTY) {
					value[i + 4][j - 4] += 1.5;
					if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == WHITE)
						value[i + 4][j - 4] -= 0.5;
				}
				value[i + 2][j - 2] += 1.5;
				if ((i + 4) < SIZE && (j - 4) > -1 && base[i + 4][j - 4] == WHITE)
					value[i + 2][j - 2] -= 0.7;
				if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == WHITE)
					value[i + 2][j - 2] -= 0.7;
			}
			if (base[i][j] == BLACK&&base[i + 1][j - 1] == EMPTY&&base[i + 2][j - 2] == BLACK&&base[i + 3][j - 3] == BLACK) {//しxしし
				if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == EMPTY) {
					value[i - 1][j + 1] += 1.5;
					if ((i + 4) < SIZE && (j - 4) > -1 && base[i + 4][j - 4] == WHITE)
						value[i - 1][j + 1] -= 0.5;
				}
				if ((i + 4) < SIZE && (j - 4) > -1 && base[i + 4][j - 4] == EMPTY) {
					value[i + 4][j - 4] += 1.5;
					if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == WHITE)
						value[i + 4][j - 4] -= 0.5;
				}
				value[i + 1][j - 1] += 1.5;
				if ((i + 4) < SIZE && (j - 4) > -1 && base[i + 4][j - 4] == WHITE)
					value[i + 1][j - 1] -= 0.7;
				if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == WHITE)
					value[i + 1][j - 1] -= 0.7;
			}
			if (base[i][j] == BLACK&&base[i + 1][j - 1] == BLACK&&base[i + 2][j - 2] == BLACK&&base[i + 3][j - 3] == BLACK) {//しししし
				if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == EMPTY)
					value[i - 1][j + 1] += 20;
				if ((i + 4) < SIZE && (j - 4) > -1 && base[i + 4][j - 4] == EMPTY)
					value[i + 4][j - 4] += 20;
			}
			if (base[i][j] == BLACK&&base[i + 1][j - 1] == BLACK&&base[i + 2][j - 2] == BLACK&&base[i + 3][j - 3] == EMPTY&&base[i + 4][j - 4] == BLACK) {//しししxし
				if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == EMPTY)
					--value[i - 1][j + 1];
				if ((i + 5) < SIZE && (j - 5) > -1 && base[i + 5][j - 5] == EMPTY)
					--value[i + 5][j - 5];
				value[i + 3][j - 3] += 20;
			}
			if (base[i][j] == BLACK&&base[i + 1][j - 1] == BLACK&&base[i + 2][j - 2] == EMPTY&&base[i + 3][j - 3] == BLACK&&base[i + 4][j - 4] == BLACK) {//ししxしし
				if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == EMPTY)
					--value[i - 1][j + 1];
				if ((i + 5) < SIZE && (j - 5) > -1 && base[i + 5][j - 5] == EMPTY)
					--value[i + 5][j - 5];
				value[i + 2][j - 2] += 20;
			}
			if (base[i][j] == BLACK&&base[i + 1][j - 1] == EMPTY&&base[i + 2][j - 2] == BLACK&&base[i + 3][j - 3] == BLACK&&base[i + 4][j - 4] == BLACK) {//しxししし
				if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == EMPTY)
					--value[i - 1][j + 1];
				if ((i + 5) < SIZE && (j - 5) > -1 && base[i + 5][j - 5] == EMPTY)
					--value[i + 5][j - 5];
				value[i + 1][j - 1] += 20;
			}
			if (base[i][j] == BLACK&&base[i + 1][j - 1] == BLACK&&base[i + 2][j - 2] == BLACK&&base[i + 3][j - 3] == BLACK&&base[i + 4][j - 4] == BLACK) {//ししししし
				state = false;
			}
		}
	for (int i = 0; i < SIZE; ++i)
		for (int j = 0; j < SIZE; ++j) {
			if (base[i][j] == WHITE) {// o
				if ((j - 1) > -1 && base[i][j - 1] == EMPTY)
					value[i][j - 1] += 0.1;
				if ((j + 1) < SIZE &&base[i][j + 1] == EMPTY)
					value[i][j + 1] += 0.1;
				if ((i - 1) > -1 && base[i - 1][j] == EMPTY)
					value[i - 1][j] += 0.1;
				if ((i + 1) < SIZE &&base[i + 1][j] == EMPTY)
					value[i + 1][j] += 0.1;
				if ((j - 1) > -1 && (i - 1) > -1 && base[i - 1][j - 1] == EMPTY)
					value[i - 1][j - 1] += 0.1;
				if ((j - 1) > -1 && (i + 1) < SIZE && base[i + 1][j - 1] == EMPTY)
					value[i + 1][j - 1] += 0.1;
				if ((j + 1) < SIZE && (i - 1) > -1 && base[i - 1][j + 1] == EMPTY)
					value[i - 1][j + 1] += 0.1;
				if ((j + 1) < SIZE && (i + 1) < SIZE && base[i + 1][j + 1] == EMPTY)
					value[i + 1][j + 1] += 0.1;
			}
			//////亜稽
			if (base[i][j] == WHITE &&base[i][j + 1] == WHITE) {////oo
				if ((j - 1) > -1 && base[i][j - 1] == EMPTY)
					value[i][j - 1] += 0.5;
				if ((j + 2) < SIZE &&base[i][j + 2] == EMPTY)
					value[i][j + 2] += 0.5;
				//// special
				if ((j - 1) > -1 && base[i][j - 1] == EMPTY && base[i][j + 2] == BLACK)
					value[i][j - 1] -= 0.3;
				if ((j + 2) < SIZE &&base[i][j + 2] == EMPTY && base[i][j - 1] == BLACK)
					value[i][j + 2] -= 0.3;

			}

			if (base[i][j] == WHITE&&base[i][j + 1] == WHITE&&base[i][j + 2] == WHITE) { //ししし
				if ((j - 1) > -1 && base[i][j - 1] == EMPTY) {
					value[i][j - 1] += 1.5;
					if ((j + 3) < SIZE &&base[i][j + 3] == BLACK)
						value[i][j - 1] -= 0.5;
				}
				if ((j + 3) < SIZE &&base[i][j + 3] == EMPTY) {
					value[i][j + 3] += 1.5;
					if ((j - 1) > -1 && base[i][j - 1] == BLACK)
						value[i][j + 3] -= 0.5;
				}
			}
			if (base[i][j] == WHITE&&base[i][j + 1] == WHITE&&base[i][j + 2] == EMPTY && base[i][j + 3] == WHITE) {//ししxし
				if ((j - 1) > -1 && base[i][j - 1] == EMPTY) {
					value[i][j - 1] += 1.5;
					if ((j + 4) < SIZE &&base[i][j + 4] == BLACK)
						value[i][j - 1] -= 0.5;
				}
				if ((j + 4) < SIZE &&base[i][j + 4] == EMPTY) {
					value[i][j + 4] += 1.5;
					if ((j - 1) > -1 && base[i][j - 1] == BLACK)
						value[i][j + 4] -= 0.5;
				}
				value[i][j + 2] += 1.5;
				if ((j + 4) < SIZE &&base[i][j + 4] == BLACK)
					value[i][j + 2] -= 0.7;
				if ((j - 1) > -1 && base[i][j - 1] == BLACK)
					value[i][j + 2] -= 0.7;
			}
			if (base[i][j] == WHITE&&base[i][j + 1] == EMPTY&&base[i][j + 2] == WHITE&&base[i][j + 3] == WHITE) {//しxしし
				if ((j - 1) > -1 && base[i][j - 1] == EMPTY) {
					value[i][j - 1] += 1.5;
					if ((j + 4) < SIZE &&base[i][j + 4] == BLACK)
						value[i][j - 1] -= 0.5;
				}
				if ((j + 4) < SIZE &&base[i][j + 4] == EMPTY) {
					value[i][j + 4] += 1.5;
					if ((j - 1) > -1 && base[i][j - 1] == BLACK)
						value[i][j + 4] -= 0.5;
				}
				value[i][j + 1] += 1.5;
				if ((j + 4) < SIZE &&base[i][j + 4] == BLACK)
					value[i][j + 1] -= 0.7;
				if ((j - 1) > -1 && base[i][j - 1] == BLACK)
					value[i][j + 1] -= 0.7;
			}
			if (base[i][j] == WHITE&&base[i][j + 1] == WHITE&&base[i][j + 2] == WHITE&&base[i][j + 3] == WHITE) {//しししし
				if ((j - 1) > -1 && base[i][j - 1] == EMPTY)
					value[i][j - 1] += 20;
				if ((j + 4) < SIZE &&base[i][j + 4] == EMPTY)
					value[i][j + 4] += 20;
			}
			if (base[i][j] == WHITE&&base[i][j + 1] == WHITE&&base[i][j + 2] == WHITE&&base[i][j + 3] == EMPTY&&base[i][j + 4] == WHITE) {//しししxし
				if ((j - 1) > -1 && base[i][j - 1] == EMPTY)
					--value[i][j - 1];
				if ((j + 5) < SIZE &&base[i][j + 5] == EMPTY)
					--value[i][j + 5];
				value[i][j + 3] += 20;
			}
			if (base[i][j] == WHITE&&base[i][j + 1] == WHITE&&base[i][j + 2] == EMPTY&&base[i][j + 3] == WHITE&&base[i][j + 4] == WHITE) {//ししxしし
				if ((j - 1) > -1 && base[i][j - 1] == EMPTY)
					--value[i][j - 1];
				if ((j + 5) < SIZE &&base[i][j + 5] == EMPTY)
					--value[i][j + 5];
				value[i][j + 2] += 20;
			}
			if (base[i][j] == WHITE&&base[i][j + 1] == EMPTY&&base[i][j + 2] == WHITE&&base[i][j + 3] == WHITE&&base[i][j + 4] == WHITE) {//しxししし
				if ((j - 1) > -1 && base[i][j - 1] == EMPTY)
					--value[i][j - 1];
				if ((j + 5) < SIZE &&base[i][j + 5] == EMPTY)
					--value[i][j + 5];
				value[i][j + 1] += 20;
			}
			if (base[i][j] == WHITE&&base[i][j + 1] == WHITE&&base[i][j + 2] == WHITE&&base[i][j + 3] == WHITE&&base[i][j + 4] == WHITE) {//ししししし
				state = false;
			}
			////// 室稽
			if (base[i][j] == WHITE &&base[i + 1][j] == WHITE) {////oo
				if ((i - 1) > -1 && base[i - 1][j] == EMPTY) {
					value[i - 1][j] += 0.5;
					if ((i + 2) < SIZE &&base[i + 2][j] == BLACK)
						value[i - 1][j] -= 0.3;
				}
				if ((i + 2) < SIZE &&base[i + 2][j] == EMPTY) {
					value[i + 2][j] += 0.5;
					if ((i - 1) > -1 && base[i - 1][j] == BLACK)
						value[i + 2][j] -= 0.3;
				}
			}
			if (base[i][j] == WHITE&&base[i + 1][j] == WHITE&&base[i + 2][j] == WHITE) { //ししし
				if ((i - 1) > -1 && base[i - 1][j] == EMPTY) {
					value[i - 1][j] += 1.5;
					if ((i + 3) < SIZE &&base[i + 3][j] == BLACK)
						value[i - 1][j] -= 0.5;
				}
				if ((i + 3) < SIZE &&base[i + 3][j] == EMPTY) {
					value[i + 3][j] += 1.5;
					if ((i - 1) > -1 && base[i - 1][j] == BLACK)
						value[i + 3][j] -= 0.5;
				}
			}
			if (base[i][j] == WHITE&&base[i + 1][j] == WHITE&&base[i + 2][j] == EMPTY && base[i + 3][j] == WHITE) {//ししxし
				if ((i - 1) > -1 && base[i - 1][j] == EMPTY) {
					value[i - 1][j] += 1.5;
					if ((i + 4) < SIZE &&base[i + 4][j] == BLACK)
						value[i - 1][j] -= 0.5;
				}
				if ((i + 4) < SIZE &&base[i + 4][j] == EMPTY) {
					value[i + 4][j] += 1.5;
					if ((i - 1) > -1 && base[i - 1][j] == BLACK)
						value[i + 4][j] -= 0.5;
				}
				value[i + 2][j] += 1.5;
				if ((i + 4) < SIZE &&base[i + 4][j] == BLACK)
					value[i + 2][j] -= 0.7;
				if ((i - 1) > -1 && base[i - 1][j] == BLACK)
					value[i + 2][j] -= 0.7;
			}
			if (base[i][j] == WHITE&&base[i + 1][j] == EMPTY&&base[i + 2][j] == WHITE&&base[i + 3][j] == WHITE) {//しxしし
				if ((i - 1) > -1 && base[i - 1][j] == EMPTY) {
					value[i][j - 1] += 1.5;
					if ((i + 4) < SIZE &&base[i + 4][j] == BLACK)
						value[i][j - 1] -= 0.5;
				}
				if ((i + 4) < SIZE &&base[i + 4][j] == EMPTY) {
					value[i + 4][j] += 1.5;
					if ((i - 1) > -1 && base[i - 1][j] == BLACK)
						value[i + 4][j] -= 0.5;
				}
				value[i + 1][j] += 1.5;
				if ((i + 4) < SIZE &&base[i + 4][j] == BLACK)
					value[i + 1][j] -= 0.7;
				if ((i - 1) > -1 && base[i - 1][j] == BLACK)
					value[i + 1][j] -= 0.7;
			}
			if (base[i][j] == WHITE&&base[i + 1][j] == WHITE&&base[i + 2][j] == WHITE&&base[i + 3][j] == WHITE) {//しししし
				if ((i - 1) > -1 && base[i - 1][j] == EMPTY)
					value[i - 1][j] += 20;
				if ((i + 4) < SIZE &&base[i + 4][j] == EMPTY)
					value[i + 4][j] += 20;
			}
			if (base[i][j] == WHITE&&base[i + 1][j] == WHITE&&base[i + 2][j] == WHITE&&base[i + 3][j] == EMPTY&&base[i + 4][j] == WHITE) {//しししxし
				if ((i - 1) > -1 && base[i - 1][j] == EMPTY)
					--value[i - 1][j];
				if ((i + 5) < SIZE &&base[i + 5][j] == EMPTY)
					--value[i + 5][j];
				value[i + 3][j] += 20;
			}
			if (base[i][j] == WHITE&&base[i + 1][j] == WHITE&&base[i + 2][j] == EMPTY&&base[i + 3][j] == WHITE&&base[i + 4][j] == WHITE) {//ししxしし
				if ((i - 1) > -1 && base[i - 1][j] == EMPTY)
					--value[i - 1][j];
				if ((i + 5) < SIZE &&base[i + 5][j] == EMPTY)
					--value[i + 5][j];
				value[i + 2][j] += 20;
			}
			if (base[i][j] == WHITE&&base[i + 1][j] == EMPTY&&base[i + 2][j] == WHITE&&base[i + 3][j] == WHITE&&base[i + 4][j] == WHITE) {//しxししし
				if ((i - 1) > -1 && base[i - 1][j] == EMPTY)
					--value[i - 1][j];
				if ((i + 5) < SIZE &&base[i + 5][j] == EMPTY)
					--value[i + 5][j];
				value[i + 1][j] += 20;
			}
			if (base[i][j] == WHITE&&base[i + 1][j] == WHITE&&base[i + 2][j] == WHITE&&base[i + 3][j] == WHITE&&base[i + 4][j] == WHITE) {//ししししし
				state = false;
			}
			//////企唖識 1
			if (base[i][j] == WHITE &&base[i + 1][j + 1] == WHITE) {////oo
				if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == EMPTY) {
					value[i - 1][j - 1] += 0.5;
					if ((i + 2) < SIZE && (j + 2) < SIZE && base[i + 2][j + 2] == BLACK)
						value[i - 1][j - 1] -= 0.3;
				}
				if ((i + 2) < SIZE && (j + 2) < SIZE && base[i + 2][j + 2] == EMPTY) {
					value[i + 2][j + 2] += 0.5;
					if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == BLACK)
						value[i + 2][j + 2] -= 0.3;
				}
			}
			if (base[i][j] == WHITE&&base[i + 1][j + 1] == WHITE&&base[i + 2][j + 2] == WHITE) { //ししし
				if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == EMPTY) {
					value[i - 1][j - 1] += 1.5;
					if ((i + 3) < SIZE && (j + 3) < SIZE &&base[i + 3][j + 3] == BLACK)
						value[i - 1][j - 1] -= 0.5;
				}
				if ((i + 3) < SIZE && (j + 3) < SIZE &&base[i + 3][j + 3] == EMPTY) {
					value[i + 3][j + 3] += 1.5;
					if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == BLACK)
						value[i + 3][j + 3] -= 0.5;
				}
			}
			if (base[i][j] == WHITE&&base[i + 1][j + 1] == WHITE&&base[i + 2][j + 2] == EMPTY && base[i + 3][j + 3] == WHITE) {//ししxし
				if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == EMPTY) {
					value[i - 1][j - 1] += 1.5;
					if ((i + 4) < SIZE && (j + 4) < SIZE &&base[i + 4][j + 4] == BLACK)
						value[i - 1][j - 1] -= 0.5;
				}
				if ((i + 4) < SIZE && (j + 4) < SIZE &&base[i + 4][j + 4] == EMPTY) {
					value[i + 4][j + 4] += 1.5;
					if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == BLACK)
						value[i + 4][j + 4] -= 0.5;
				}
				value[i + 2][j + 2] += 1.5;
				if ((i + 4) < SIZE && (j + 4) < SIZE &&base[i + 4][j + 4] == BLACK)
					value[i + 2][j + 2] -= 0.7;
				if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == BLACK)
					value[i + 2][j + 2] -= 0.7;
			}
			if (base[i][j] == WHITE&&base[i + 1][j + 1] == EMPTY&&base[i + 2][j + 2] == WHITE&&base[i + 3][j + 3] == WHITE) {//しxしし
				if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == EMPTY) {
					value[i - 1][j - 1] += 1.5;
					if ((i + 4) < SIZE && (j + 4) < SIZE &&base[i + 4][j + 4] == BLACK)
						value[i - 1][j - 1] -= 0.5;
				}
				if ((i + 4) < SIZE && (j + 4) < SIZE &&base[i + 4][j + 4] == EMPTY) {
					value[i + 4][j + 4] += 1.5;
					if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == BLACK)
						value[i + 4][j + 4] -= 0.5;
				}
				value[i + 1][j + 1] += 1.5;
				if ((i + 4) < SIZE && (j + 4) < SIZE &&base[i + 4][j + 4] == BLACK)
					value[i + 1][j + 1] -= 0.7;
				if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == BLACK)
					value[i + 1][j + 1] -= 0.7;
			}
			if (base[i][j] == WHITE&&base[i + 1][j + 1] == WHITE&&base[i + 2][j + 2] == WHITE&&base[i + 3][j + 3] == WHITE) {//しししし
				if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == EMPTY)
					value[i - 1][j - 1] += 20;
				if ((i + 4) < SIZE && (j + 4) < SIZE &&base[i + 4][j + 4] == EMPTY)
					value[i + 4][j + 4] += 20;
			}
			if (base[i][j] == WHITE&&base[i + 1][j + 1] == WHITE&&base[i + 2][j + 2] == WHITE&&base[i + 3][j + 3] == EMPTY&&base[i + 4][j + 4] == WHITE) {//しししxし
				if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == EMPTY)
					--value[i - 1][j - 1];
				if ((i + 5) < SIZE && (j + 5) < SIZE &&base[i + 5][j + 5] == EMPTY)
					--value[i + 5][j + 5];
				value[i + 3][j + 3] += 20;
			}
			if (base[i][j] == WHITE&&base[i + 1][j + 1] == WHITE&&base[i + 2][j + 2] == EMPTY&&base[i + 3][j + 3] == WHITE&&base[i + 4][j + 4] == WHITE) {//ししxしし
				if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == EMPTY)
					--value[i - 1][j - 1];
				if ((i + 5) < SIZE && (j + 5) < SIZE &&base[i + 5][j + 5] == EMPTY)
					--value[i + 5][j + 5];
				value[i + 2][j + 2] += 20;
			}
			if (base[i][j] == WHITE&&base[i + 1][j + 1] == EMPTY&&base[i + 2][j + 2] == WHITE&&base[i + 3][j + 3] == WHITE&&base[i + 4][j + 4] == WHITE) {//しxししし
				if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == EMPTY)
					--value[i - 1][j - 1];
				if ((i + 5) < SIZE && (j + 5) < SIZE &&base[i + 5][j + 5] == EMPTY)
					--value[i + 5][j + 5];
				value[i + 1][j + 1] += 20;
			}
			if (base[i][j] == WHITE&&base[i + 1][j + 1] == WHITE&&base[i + 2][j + 2] == WHITE&&base[i + 3][j + 3] == WHITE&&base[i + 4][j + 4] == WHITE) {//しxししししし
				state = false;
			}
			//////企唖識 2
			if (base[i][j] == WHITE &&base[i + 1][j - 1] == WHITE) {////oo
				if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == EMPTY) {
					value[i - 1][j + 1] += 0.5;
					if ((i + 2) < SIZE && (j - 2) > -1 && base[i + 2][j - 2] == BLACK)
						value[i - 1][j + 1] -= 0.3;
				}
				if ((i + 2) < SIZE && (j - 2) > -1 && base[i + 2][j - 2] == EMPTY) {
					value[i + 2][j - 2] += 0.5;
					if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == BLACK)
						value[i + 2][j - 2] -= 0.3;
				}
			}
			if (base[i][j] == WHITE&&base[i + 1][j - 1] == WHITE&&base[i + 2][j - 2] == WHITE) { //ししし
				if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == EMPTY) {
					value[i - 1][j + 1] += 1.5;
					if ((i + 3) < SIZE && (j - 3) > -1 && base[i + 3][j - 3] == BLACK)
						value[i - 1][j + 1] -= 0.5;
				}
				if ((i + 3) < SIZE && (j - 3) > -1 && base[i + 3][j - 3] == EMPTY) {
					value[i + 3][j - 3] += 1.5;
					if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == BLACK)
						value[i + 3][j - 3] -= 0.5;
				}
			}
			if (base[i][j] == WHITE&&base[i + 1][j - 1] == WHITE&&base[i + 2][j - 2] == EMPTY && base[i + 3][j - 3] == WHITE) {//ししxし
				if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == EMPTY) {
					value[i - 1][j + 1] += 1.5;
					if ((i + 4) < SIZE && (j - 4) > -1 && base[i + 4][j - 4] == BLACK)
						value[i - 1][j + 1] -= 0.5;
				}
				if ((i + 4) < SIZE && (j - 4) > -1 && base[i + 4][j - 4] == EMPTY) {
					value[i + 4][j - 4] += 1.5;
					if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == BLACK)
						value[i + 4][j - 4] -= 0.5;
				}
				value[i + 2][j - 2] += 1.5;
				if ((i + 4) < SIZE && (j - 4) > -1 && base[i + 4][j - 4] == BLACK)
					value[i + 2][j - 2] -= 0.7;
				if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == BLACK)
					value[i + 2][j - 2] -= 0.7;
			}
			if (base[i][j] == WHITE&&base[i + 1][j - 1] == EMPTY&&base[i + 2][j - 2] == WHITE&&base[i + 3][j - 3] == WHITE) {//しxしし
				if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == EMPTY) {
					value[i - 1][j + 1] += 1.5;
					if ((i + 4) < SIZE && (j - 4) > -1 && base[i + 4][j - 4] == BLACK)
						value[i - 1][j + 1] -= 0.5;
				}
				if ((i + 4) < SIZE && (j - 4) > -1 && base[i + 4][j - 4] == EMPTY) {
					value[i + 4][j - 4] += 1.5;
					if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == BLACK)
						value[i + 4][j - 4] -= 0.5;
				}
				value[i + 1][j - 1] += 1.5;
			}
			if (base[i][j] == WHITE&&base[i + 1][j - 1] == WHITE&&base[i + 2][j - 2] == WHITE&&base[i + 3][j - 3] == WHITE) {//しししし
				if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == EMPTY)
					value[i - 1][j + 1] += 20;
				if ((i + 4) < SIZE && (j - 4) > -1 && base[i + 4][j - 4] == EMPTY)
					value[i + 4][j - 4] += 20;
			}
			if (base[i][j] == WHITE&&base[i + 1][j - 1] == WHITE&&base[i + 2][j - 2] == WHITE&&base[i + 3][j - 3] == EMPTY&&base[i + 4][j - 4] == WHITE) {//しししxし
				if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == EMPTY)
					--value[i - 1][j + 1];
				if ((i + 5) < SIZE && (j - 5) > -1 && base[i + 5][j - 5] == EMPTY)
					--value[i + 5][j - 5];
				value[i + 3][j - 3] += 20;
			}
			if (base[i][j] == WHITE&&base[i + 1][j - 1] == WHITE&&base[i + 2][j - 2] == EMPTY&&base[i + 3][j - 3] == WHITE&&base[i + 4][j - 4] == WHITE) {//ししxしし
				if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == EMPTY)
					--value[i - 1][j + 1];
				if ((i + 5) < SIZE && (j - 5) > -1 && base[i + 5][j - 5] == EMPTY)
					--value[i + 5][j - 5];
				value[i + 2][j - 2] += 20;
			}
			if (base[i][j] == WHITE&&base[i + 1][j - 1] == EMPTY&&base[i + 2][j - 2] == WHITE&&base[i + 3][j - 3] == WHITE&&base[i + 4][j - 4] == WHITE) {//しxししし
				if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == EMPTY)
					--value[i - 1][j + 1];
				if ((i + 5) < SIZE && (j - 5) > -1 && base[i + 5][j - 5] == EMPTY)
					--value[i + 5][j - 5];
				value[i + 1][j - 1] += 20;
			}
			if (base[i][j] == WHITE&&base[i + 1][j - 1] == WHITE&&base[i + 2][j - 2] == WHITE&&base[i + 3][j - 3] == WHITE&&base[i + 4][j - 4] == WHITE) {//ししししし
				state = false;
			}
		}
}