#include "stdafx.h"
#include "Header.h"

;int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	ifstream menuF;
	ifstream cashboxF;
	ifstream kitchenF;

	menuF.open("menu.txt");
	cashboxF.open("cashbox.txt");
	kitchenF.open("kitchen.txt");

	Cafe myCafe;

	try {
		myCafe.myMenu.inputMenu(menuF);
		myCafe.myKitchen.inputKitchen(kitchenF);
		myCafe.myCashbox.inputCashbox(cashboxF);
		myCafe.myMenu.checkDishes(myCafe.myKitchen.allCookedDish, myCafe.myCashbox.allChecks);
		myCafe.myCashbox.checkDishInCashbox(myCafe.myKitchen.allCookedDish, myCafe.myMenu);
		myCafe.myCashbox.outputResult();
		myCafe.myCashbox.inputFindDish();
	}
	catch (int i) {
		myCafe.outputErrors.outputErrors(i);
	}

	menuF.close();
	cashboxF.close();
	kitchenF.close();

	return 0;
}