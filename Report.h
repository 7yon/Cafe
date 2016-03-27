
#include "stdafx.h"
//#include "header.h"
#include "Cafe.h"

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
	map <string, Cafe> historyAboutCafe;
	map<string, int> calculation;
	float totalCheck = 0, loss = 0;
public:
	void reportGeneration(int typeOfReport);///////////////
	void reportSelection();
	void outputStatisticFromSubcategory(map<string, map<string, int>> mapAllDishAndCategory, ofstream &fileOfReport, vector <Category*> allCategories);

	void statisticsOfOrders();//работаем с historyAboutCafe;
	void priceBehavior(PeriodOfDate myPeriod, ofstream &fileOfReport);//лера
	void checkDishInCashbox(Cafe myCafe);
	void outputResult(ofstream &fileOfReport, float loss, float totalCheck);
	void outputStatisticsInFile(map <string, map<string, map<string, int>>> mapAllDishAndCategory, ofstream &fileOfReport);
	/*PeriodOfDate periodOfTheReport(int i, Cashbox myCashbox, Menu myMenu);*/
	/*PeriodOfDate periodOfTheReport(int i);*///лера
	void changeDate(int &dd1, int &mm1, int &yy1);
	void checkKitchenCashboxMenu(string myDate);
	void fillingMapHistory(PeriodOfDate myPeriod, int typeReport);
	void periodOfTheReport(int i);
	//void reportGeneration(int typeOfReport);///////////////
	//int reportSelection(Cashbox myCashbox, Menu myMenu);
public:
	map<string, int> getCalculation();
	void setCalculation(string name, int count);
	void deleteMenu(vector <Category*> allCategories);
};