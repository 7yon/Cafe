#pragma once
#include "stdafx.h"
#include "header.h"

class Date {
	int dd;
	int mm;
	int yy;
public:
	Date();
	void setDate(int day, int month, int year);
	string getDate();
	int getMM();
	int getDD();
	int getYY();
};

class PeriodOfDate {
	Date firstDay;
	Date lastDay;
public:
	Date getFirstDay();
	Date getLastDay();
	void setFirstDay(Date myFirstDay);
	void setLastDay(Date myLastDay);
};

class Report {
	map<string, int> calculation;
	float totalCheck = 0, loss = 0;
public:
	void reportGeneration(int typeOfReport, Menu myMenu, Cashbox myCashbox, Kitchen myKitchen, ofstream &fileOfReport);///////////////
	int reportSelection(Cashbox myCashbox, Menu myMenu);
	void createReport(Menu myMenu, Cashbox myCashbox, Kitchen myKitchen, Error outputErrors);
	void statisticsOfOrders(Cashbox myCashbox, Menu myMenu, ofstream &fileOfReport);
	void priceBehavior(PeriodOfDate myPeriod, ofstream &fileOfReport);//лера
	void checkDishInCashbox(vector <cookedDish> kitchen, Menu myMenu, vector <Check> allChecks, ofstream &fileOfReport);
	void outputResult(ofstream &fileOfReport, float loss, float totalCheck);
	void outputStatisticsInFile(map <string, int> mapDishes, map <string, int> mapCategoryAndSubcategory, vector <Category*> allCategories, ofstream &fileOfReport);
	PeriodOfDate periodOfTheReport(int i, Cashbox myCashbox, Menu myMenu);
	/*PeriodOfDate periodOfTheReport(int i);*///лера
	void changeDate(int &dd1, int &mm1, int &yy1);
public:
	map<string, int> getCalculation();
	void setCalculation(string name, int count);
};