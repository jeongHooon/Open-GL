#pragma once
#include <iostream>
using namespace std;

class Model {
	char* data;
	size_t size;
	int id;
public:
	Model();
	Model(int i);;
	Model(const Model& other);
	//이동 생성자
	Model(Model&& other);
	~Model();
	int getid() const { return id; };
	void show();
	size_t getdata() const { return size; };
	Model& operator=(const Model& other);
	Model& operator=(Model&& other);
	
};
