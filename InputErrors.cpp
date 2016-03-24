#include "stdafx.h"
#include "Header.h"

Dish Menu::checkMenuForErrors(string str) {
	Dish DishInMenu;
	string price;
	//regex dish("(\\s*.+)[\\s=]+(\\d+)[,\\.](\\d{2})");
	regex dish("(\\s*.+?) [\\s=]+(\\d+)[,\\.](\\d{2})");
	regex category("(\\s*.+)\\s*");
	smatch match;
	if (regex_search(str, match, dish)) {
		//cout << str << endl;
		//cout << match.str(1) << endl;
		//cout << match.str(2) << endl;
		//cout << match.str(3) << endl;

		price = match.str(2) + '.' + match.str(3);
		DishInMenu.nameDish = match.str(1);
		DishInMenu.price = atof(price.c_str());
		return DishInMenu;
	}
	else if (regex_search(str, match, category)) {
		//cout << str << endl;
		//cout << match.str(1) << endl;
		DishInMenu.nameDish = match.str(1);
		DishInMenu.price = 0;
		return DishInMenu;
	}
	else throw 1;
}

int Menu::numberOfSpace(string str) {
	regex space("\\s*");
	smatch match;
	regex_search(str, match, space);

	return match.str(0).size();
}

void Error::outputErrors(int i, string nameMenu, string nameCashbox, string nameKitchen) {

	if (i == 1) cout << "Синтаксическая ошибка в файле " << nameMenu << "!";
	if (i == 2) cout << "Синтаксическая ошибка в файле " << nameKitchen << "!";
	if (i == 3) cout << "Синтаксическая ошибка в файле " << nameCashbox << "!";
	if (i == 4) cout << "Файл " << nameMenu << " не удалось открыть!";
	if (i == 5) cout << "Файл " << nameKitchen << " не удалось открыть!";
	if (i == 6) cout << "Файл " << nameCashbox << " не удалось открыть!";
	if (i == 7) cout << "На кухне приготовили блюдо, которого нет в меню!";
	if (i == 8) cout << "В чеке есть блюдо, которого нет в меню!";
	if (i == 9) cout << "На кухне меньше блюд, чем на кассе!";
	if (i == 10) cout << "На кассе блюдо, которое не было приготовлено!";
}