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
#include <regex>
#include <vld.h> 
#include "conio.h"
#include <cstdlib>
#include <ctime>

using namespace std;

class Date {
	int dd;
	int mm;
	int yy;
public:
	Date() {
		dd = 0;
		mm = 0;
		yy = 0;
	}
	void setDate(int day, int month, int year) {
		dd = day;
		mm = month;
		yy = year;
	}
	Date getDate() {
		Date myDate;
		myDate.dd = dd;
		myDate.mm = mm;
		myDate.yy = yy;
		return myDate;
	}
};

class PeriodOfDate {
public:
	Date firstDay;
	Date lastDay;
};

class Dish {
public:
	string nameDish;
	float price;
};

class cookedDish {
public:
	string nameDish;
	int count;
};

class Category {
public:
	int categoryLevel;
	string nameCategory;
	Category *ParentCategory;
	vector <Dish> dishes;
	vector <Category*> subcategory;
};

class Check {//checks, cheques
public:
	vector <cookedDish> Dish;
	float total;
	int number;
};

class Menu {
	vector <Category*> allCategories;
public:
	Dish findInMenu(string str);
	Dish checkMenuForErrors(string str);
	int numberOfSpace(string str);
	void inputMenu(ifstream &menuF);
	void checkDishes(vector <cookedDish> allCookedDish, vector <Check> allChecks);
	void deleteMenu(vector <Category*> allCategories);
	~Menu() {
		//deleteMenu(allCategories);
	}
};

class Cashbox {
	map<string, int> calculation;
	float totalCheck = 0, loss = 0;
public:
	vector <Check> allChecks;
	void inputCashbox(ifstream &cashboxF);
	void checkDishInCashbox(vector <cookedDish> kitchen, Menu myMenu);
	void outputResult();
	void inputFindDish();
	void findDishInCheckbox(string nameDish, int flagOutput);
	void outputIsFoundChecks(ostream &outputStream, vector <Check> findChecks);
};

class Kitchen {
public:
	vector <cookedDish> allCookedDish;
	void inputKitchen(ifstream &kitchenF);
};


class Error {
public:
	void outputErrors(int i);
};

class Report {
public:
	void statisticsOfOrders();
	void reportSelection();
	PeriodOfDate periodOfTheReport(int i);
};

class Cafe {
public:
	Menu myMenu;
	Cashbox myCashbox;
	Kitchen myKitchen;
	Error outputErrors;
	Report myReport;
};
