#pragma once
#include "stdafx.h"
#include "header.h"

class Check {//checks, cheques
	vector <cookedDish> Dish;
	float total;
	int number;
public:
	vector <cookedDish> getDish();
	float getTotal();
	int getNumber();
	void clearDish();
	void setDish(cookedDish myCookedDish);
	void setTotal(float myTotal);
	void setNumber(int myNumber);
	vector <cookedDish> setDish(vector <cookedDish> myDish);
};

class Cashbox {
	vector <Check> allChecks;
public:
	vector <Check> getAllChecks();
	void setAllChecks(Check myCheck);
public:
	void inputCashbox(ifstream &cashboxF);
	//void checkDishInCashbox(vector <cookedDish> kitchen, Menu myMenu);
	//void outputResult(ofstream &reportout, string fileDate);/*//изменен
	//void outputResult(ofstream &reportout, string fileDate);*///Лера
	void inputFindDish();
	void findDishInCheckbox(string nameDish, int flagOutput);//изменен
	void outputIsFoundChecks(ostream &outputStream, vector <Check> findChecks);
};
