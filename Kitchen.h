#pragma once
#include "stdafx.h"
#include "header.h"

class cookedDish {
	string nameDish;
	int count;
public:
	string getNameDish();
	int getCount();
	string setNameDish(string myNameDish);
	int setCount(int myCount);
};

class Kitchen {
	vector <cookedDish> allCookedDish;
public:
	vector <cookedDish> getAllCookedDish();
	void setAllCookedDish(cookedDish myCookedDish);
	void clearAllCookedDish();
public:
	void inputKitchen(ifstream &kitchenF);
};
