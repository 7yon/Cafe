#pragma once
#include "stdafx.h"
#include <windows.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <iterator>
using namespace std;

struct cookedDish {
	string nameDish;
	int count;
};

struct check {//checks, cheques
	vector<cookedDish> Dish;
	float total;
	int number;
};

void outputErrors(int i);
void inputMenu(map <string, float> &menuMap, ifstream &menuF);
void inputCashbox(vector <check> &cashbox, ifstream &cashboxF);
void inputKitchen(vector <cookedDish> &kitchen, ifstream &kitchenF);
map <string, float> inputErrors(string str, int idetidentifierFile);
void outputResult(map<string, int> calculation, float totalCheck, float loss);
void checkDishes(map <string, float> menuMap, vector <cookedDish> kitchen, vector <check> cashbox);
void checkDish(vector <check> cashbox, vector <cookedDish> kitchen, map <string, float> menuMap, map<string, int> &calculation, float &totalCheck, float &loss);
void findDishInCheckbox(string nameDish, vector <check> cashbox);
void inputFindDish(vector <check> cashbox);
void outputIsFoundChecks(ostream &file, vector <check> findChecks);