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
	string getDate() {
		string myDate = to_string(yy) + to_string(mm) + to_string(dd);
		return myDate;
	}
	int getMM() {
		return mm;
	}
	int getDD() {
		return dd;
	}
	int getYY() {
		return yy;
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
	map <string, float> menumap;//лера
	vector <Category*> getMenu() {
		return allCategories;
	}
	~Menu() { allCategories.clear(); }
	Category* findInMenu(string str, vector <Category*> allCategories);
	Dish checkMenuForErrors(string str);
	int numberOfSpace(string str);
	void inputMenu(ifstream &menuF);
	void checkDishes(vector <cookedDish> allCookedDish, vector <Check> allChecks);
	void deleteMenu(vector <Category*> allCategories);
	//~Menu() {
	//	//deleteMenu(allCategories);
	//}
	//vector <Category*> getMenu() {//лера
	//	return allCategories;
	//}
};

class Cashbox {
	/*map<string, int> calculation;
	float totalCheck = 0, loss = 0;*/
public:
	vector <Check> allChecks;
	void inputCashbox(ifstream &cashboxF);
	//void checkDishInCashbox(vector <cookedDish> kitchen, Menu myMenu);
	void outputResult(ofstream &reportout, string fileDate);/*//изменен
	void outputResult(ofstream &reportout, string fileDate);*///Лера
	void inputFindDish();
	void findDishInCheckbox(string nameDish, int flagOutput);//изменен
	void outputIsFoundChecks(ostream &outputStream, vector <Check> findChecks);
};

class Kitchen {
public:
	vector <cookedDish> allCookedDish;
	void inputKitchen(ifstream &kitchenF);
};


class Error {
public:
	void outputErrors(int i, string nameMenu, string nameCashbox, string nameKitchen);
};

class Report {
	map<string, int> calculation;
	float totalCheck = 0, loss = 0;
public:
	void reportGeneration(int typeOfReport, Menu myMenu, Cashbox myCashbox, Kitchen myKitchen, ofstream &fileOfReport);///////////////
	int reportSelection(Cashbox myCashbox, Menu myMenu);
	void createReport(Menu myMenu, Cashbox myCashbox, Kitchen myKitchen, Error outputErrors);
	void statisticsOfOrders(Cashbox myCashbox, Menu myMenu, ofstream &fileOfReport);
	void priceBehavior(PeriodOfDate myPeriod);//лера
	void checkDishInCashbox(vector <cookedDish> kitchen, Menu myMenu, vector <Check> allChecks, ofstream &fileOfReport);
	void outputResult(ofstream &fileOfReport, float loss, float totalCheck);
	void outputStatisticsInFile(map <string, int> mapDishes, map <string, int> mapCategoryAndSubcategory, vector <Category*> allCategories, ofstream &fileOfReport);
	PeriodOfDate periodOfTheReport(int i, Cashbox myCashbox, Menu myMenu);
	/*PeriodOfDate periodOfTheReport(int i);*///лера
	void changeDate(int &dd1, int &mm1, int &yy1);

};

class Cafe {
public:
	Menu myMenu;
	Cashbox myCashbox;
	Kitchen myKitchen;
	Error outputErrors;
	Report myReport;
};
//////МОЕЕЕЕЕ!!!!!!!!!!!!!!!!!!!!!!