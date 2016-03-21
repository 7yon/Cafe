#include "stdafx.h"
#include "Header.h"

Category* Menu::findInMenu(string str, vector <Category*> allCategories) {
	bool flagFound = false;
	Category* foundCategory = allCategories[1];

	for (int i = 0; i < allCategories.size() && !flagFound; i++) {
		for (int j = 0; j < allCategories[i]->dishes.size() && !flagFound; j++) {
			if (allCategories[i]->dishes[j].nameDish == str) {
				//foundDish.nameDish = allCategories[i]->dishes[j].nameDish;
				//foundDish.price = allCategories[i]->dishes[j].price;
				foundCategory = allCategories[i];
				flagFound = true;
				//cout << "Ќайдено :" << str;
				break;
			}
		}
		if (allCategories[i]->subcategory.size() != 0) {
			//if (!flagFound) {
				foundCategory = findInMenu(str, allCategories[i]->subcategory);
			//}
		}
	}
	return foundCategory;
}

void Menu::checkDishes(vector <cookedDish> allCookedDish, vector <Check> allChecks) {
	bool flagFound = false;

	for (int i = 0; i < allCookedDish.size() && !flagFound; i++) {
		findInMenu(allCookedDish[i].nameDish, allCategories);
		flagFound = true;
	}
	if (!flagFound) throw 7;

	flagFound = false;
	for (int i = 0; i < allChecks.size() && !flagFound; i++) {
		for (int j = 0; j < allChecks[i].Dish.size() && !flagFound; j++) {
			findInMenu(allChecks[i].Dish[j].nameDish, allCategories);
			flagFound = true;
		}
	}
	if (!flagFound) throw 8;
}

void Cashbox::checkDishInCashbox(vector <cookedDish> kitchen, Menu myMenu) {//проверка и вывод на консоль
	bool flag = false;
	Dish myDish;
	Category* foundCategory;
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
		//myDish = myMenu.findInMenu(it->first);
		foundCategory = myMenu.findInMenu(it->first, myMenu.getMenu());
		//loss = loss + it->second * myDish.price;
		int i, y;
		for (i = 0; i < foundCategory->dishes.size(); i++)
			if (foundCategory->dishes[i].nameDish == it->first) break;
		loss = loss + it->second * foundCategory->dishes[i].price;
	}

	for (int i = 0; i < allChecks.size(); i++) {//ошибка в расчете total
		for (int j = 0; j < allChecks[i].Dish.size(); j++) {
			//myDish = myMenu.findInMenu(allChecks[i].Dish[j].nameDish);
			foundCategory = myMenu.findInMenu(allChecks[i].Dish[j].nameDish, myMenu.getMenu());
			//totalCheck = totalCheck + allChecks[i].Dish[j].count * myDish.price;
			int l;
			for (l = 0; i < foundCategory->dishes.size(); l++)
				if (foundCategory->dishes[l].nameDish == allChecks[i].Dish[j].nameDish) break;
			totalCheck = totalCheck + allChecks[i].Dish[j].count * foundCategory->dishes[l].price;
		}
		totalCheck = allChecks[i].total - totalCheck;
	}
}