#include "stdafx.h"
#include "Header.h"

Dish Menu::findInMenu(string str) {
	bool flagFound = false;
	Dish foundDish;

	for (int i = 0; i < allCategories.size() && !flagFound; i++) {
		for (int j = 0; j < allCategories[i]->dishes.size() && !flagFound; j++) {
			if (allCategories[i]->dishes[j].nameDish == str) {
				foundDish.nameDish = allCategories[i]->dishes[j].nameDish;
				foundDish.price = allCategories[i]->dishes[j].price;
				flagFound = true;
				//cout << "Ќайдено :" << str;
				return foundDish;
				break;
			}
		}
		if (allCategories[i]->subcategory.size() != 0) {
			if (!flagFound) {
				findInMenu(str);
			}
		}
	}
}

void Menu::checkDishes(vector <cookedDish> allCookedDish, vector <Check> allChecks) {
	bool flagFound = false;

	for (int i = 0; i < allCookedDish.size() && !flagFound; i++) {
		findInMenu(allCookedDish[i].nameDish);
		flagFound = true;
	}
	if (!flagFound) throw 7;

	flagFound = false;
	for (int i = 0; i < allChecks.size() && !flagFound; i++) {
		for (int j = 0; j < allChecks[i].Dish.size() && !flagFound; j++) {
			findInMenu(allChecks[i].Dish[j].nameDish);
			flagFound = true;
		}
	}
	if (!flagFound) throw 8;
}

void Cashbox::checkDishInCashbox(vector <cookedDish> kitchen, Menu myMenu) {//проверка и вывод на консоль
	bool flag = false;
	Dish myDish;
	map<string, int>::iterator it;

	for (int i = 0; i < kitchen.size(); i++) {
		if (calculation[kitchen[i].nameDish]) {
			calculation[kitchen[i].nameDish] = calculation[kitchen[i].nameDish] + kitchen[i].count;
		}
		else calculation[kitchen[i].nameDish] = kitchen[i].count;
	}

	for (int i = 0; i < allChecks.size(); i++) {//сравниваем количество блюд на кухне и на кассе
		for (int j = 0; j < allChecks[i].Dish.size(); j++) {
			for (it = calculation.begin(); it != calculation.end() && !flag; it++) {
				if (allChecks[i].Dish[j].nameDish == it->first) {
					it->second = it->second - allChecks[i].Dish[j].count;
					if (it->second < 0)
						throw 9;
					flag = true;
				}
			}
			if ((it == calculation.end()) && (!flag))
				throw 10;
			flag = false;
		}
	}
	cout << " оличество потер€нных блюд:" << endl;
	cout << endl;

	for (it = calculation.begin(); it != calculation.end() && !flag; it++) {
		myDish = myMenu.findInMenu(it->first);
		loss = loss + it->second * myDish.price;
	}

	for (int i = 0; i < allChecks.size(); i++) {//ошибка в расчете total
		for (int j = 0; j < allChecks[i].Dish.size(); j++) {
			myDish = myMenu.findInMenu(allChecks[i].Dish[j].nameDish);
			totalCheck = totalCheck + allChecks[i].Dish[j].count * myDish.price;
		}
		totalCheck = allChecks[i].total - totalCheck;
	}
}