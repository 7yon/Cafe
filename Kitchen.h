
#include "stdafx.h"
#include "header.h"
//#include "Error.h"

class cookedDish {
	string nameDish;
	int count;
public:
	string getNameDish();
	int getCount();
	void setNameDish(string myNameDish);
	void setCount(int myCount);
	void clearNameDish();
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
