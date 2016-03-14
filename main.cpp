#include "stdafx.h"
#include "Header.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	vector <cookedDish> kitchen;
	vector <check> cashbox;
	vector <Category> Menu;

	map<string, int> calculation;
	map <string, float> menuMap;
	float totalCheck = 0;
	float loss = 0;

	ifstream menuF;
	ifstream cashboxF;
	ifstream kitchenF;

	menuF.open("menu.txt");
	cashboxF.open("cashbox.txt");
	kitchenF.open("kitchen.txt");

	try {
		inputMenu(menuMap, Menu, menuF);

		inputKitchen(kitchen, kitchenF);
		inputCashbox(cashbox, cashboxF);
		checkDishes(menuMap, kitchen, cashbox);
		checkDish(cashbox, kitchen, menuMap, calculation, totalCheck, loss);
		outputResult(calculation, totalCheck, loss);
		inputFindDish(cashbox);
	}
	catch (int i) {
		outputErrors(i);
	}

	menuF.close();
	cashboxF.close();
	kitchenF.close();

	return 0;
}