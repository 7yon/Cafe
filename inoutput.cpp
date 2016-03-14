#include "stdafx.h"
#include "Header.h"

void outputIsFoundChecks(ostream &outputStream, vector <check> findChecks) {
	for (int i = 0; i < findChecks.size(); i++) {
		outputStream << "Заказ№ " << findChecks[i].number << '\n';
		for (int j = 0; j < findChecks[i].Dish.size(); j++) {
			outputStream << findChecks[i].Dish[j].nameDish << ' ' << findChecks[i].Dish[j].count << '\n';
		}
		outputStream << "Total: " << findChecks[i].total << '\n' << "==========" << '\n';
	}
}

void findDishInCheckbox(string nameDish, vector <check> cashbox, int flagOutput){
	setlocale(LC_ALL, "Russian");
	vector <check> findChecks;
	ofstream outputChecks("outputChecks.txt");
	ostream &out = cout;

	bool findDishInCheck;
	for (int i = 0; i < cashbox.size(); i++){
		findDishInCheck = false;
		for (int j = 0; j < cashbox[i].Dish.size() && !findDishInCheck; j++){
			if (nameDish == cashbox[i].Dish[j].nameDish){
				findDishInCheck = true;
				findChecks.push_back(cashbox[i]);
			}
		}
	}
	if (flagOutput == 1) {
		outputIsFoundChecks(cout, findChecks);
	}
	else outputIsFoundChecks(outputChecks, findChecks);
}

void inputFindDish(vector <check> cashbox){
	string nameDish;
	int flagOutput;

	cout << "\nВведите название блюда\n";
	getline(cin, nameDish);
	cout << "Введите 1, если хотите вывести результат на консоль, если записать в файл - 2\n";
	cin >> flagOutput;

	if ((flagOutput == 1) || (flagOutput == 2)){
		findDishInCheckbox(nameDish, cashbox, flagOutput);
	}
	else cout << "Ошибка!!!";
}

void outputResult(map<string, int> calculation, float totalCheck, float loss){
	map <string, int>::iterator it;

	for (it = calculation.begin(); it != calculation.end(); it++) {
		cout << it->first << ' ' << it->second << endl;
	}
	cout << endl;
	cout << "Убыток от потерянных блюд: " << loss << endl;//потери 
	cout << "Ошибка в рассчете итога: " << totalCheck;
}

void inputMenu(map <string, float> &menuMap, vector <Category> &Menu, ifstream &menuF) {
	if (!menuF) throw 4;

	string str;
	map <string, float> strMap;
	map <string, float>::iterator It;
	int level = 0;
	int idetidentifierFile = 1;
	Category newCategory;
	Dish dishOfMenu;
	size_t numbeOfSpaces;
	Category *subc = &newCategory;
	bool flagOfLetter = false;
	int levelCheck=0;
	bool newSubCat = false;

	while (!menuF.eof()) {
		getline(menuF, str);
		strMap = inputErrors(str, idetidentifierFile);//передаем считанную строку и идентификатор файла
		It = strMap.begin();
		if (It->second == 0) {
			newSubCat = true;
			int i = 0;
			flagOfLetter = false;
			for (i = 0; i < It->first.size() && !flagOfLetter; i++) {
				if (It->first[i] != ' ') flagOfLetter = true;
			}
			 level = i - 1;
			if (level == 0) {
				newCategory.categoryLevel = level;
				newCategory.nameCategory = It->first;
				Menu.push_back(newCategory);
			}
			else {
				Category *newC = new Category;
				newC->categoryLevel = level;
				newC->nameCategory = It->first;
				Category *pointOfCategory = newC;
				if (level > 1) {
					int i = 0;
					subc = Menu[Menu.size() - 1].subcategory[Menu[Menu.size() - 1].subcategory.size() - 1];
					/*while (i < level) {
						subc = subc->subcategory[subc->subcategory.size()];
						i++;
					}*/
					subc->categoryLevel = level;
					subc->subcategory.push_back(pointOfCategory);
					subc = subc->subcategory[subc->subcategory.size() - 1];///
				}
				else {
					//Menu[Menu.size() - 1].subcategory[Menu[Menu.size() - 1].subcategory.size()]->subcategory.push_back(pointOfCategory);
					Menu[Menu.size() - 1].subcategory.push_back(pointOfCategory);
					subc = Menu[Menu.size() - 1].subcategory[Menu[Menu.size() - 1].subcategory.size() - 1];
					for (int i = 0; i < level - 2; i++) {
						subc = subc->subcategory[subc->subcategory.size()];
					}
					//subc->subcategory.push_back(pointOfCategory);
					//Menu[Menu.size()].subcategory.push_back(pointOfCategory);
					subc->categoryLevel = level;
				}
			}
			//newCategory.nameCategory.clear();
		}
		else {
			dishOfMenu.nameDish = It->first;
			dishOfMenu.count = It->second;
			Dish* point;
			point = &dishOfMenu;
			if (level > 0) {
				int i = 0;		
				//if (levelCheck != level) {
				//	newSubCat = false;
				//	levelCheck = level;
				//	while (i < level - 1) {
				//		//subc->dishes.push_back(dishOfMenu);
				//		subc = subc->subcategory[subc->subcategory.size() - 1];
				//		i++;
				//	}
				//}
				//else  {
					subc->dishes.push_back(dishOfMenu);
					//subc->subcategory[subc->subcategory.size()]->dishes.push_back(dishOfMenu);
				//}
				//subc->dishes.push_back(dishOfMenu);
				//subc->dishes.push_back(dishOfMenu);
			}
			else {
				Menu[Menu.size() - 1].dishes.push_back(dishOfMenu);
				dishOfMenu.count = 0;
				dishOfMenu.nameDish.clear();
			}
		}
	}
}

void inputKitchen(vector <cookedDish> &kitchen, ifstream &kitchenF) {
	if (!kitchenF) throw 5;

	string str;
	cookedDish dishes;
	int idetidentifierFile = 2;
	map <string, float> strMap;
	map <string, float>::iterator itMap;

	while (!kitchenF.eof()) {
		getline(kitchenF, str);
		strMap = inputErrors(str, idetidentifierFile);
		itMap = strMap.begin();
		dishes.nameDish = itMap->first;
		dishes.count = itMap->second;
		kitchen.push_back(dishes);
		dishes.nameDish.clear();
		dishes.count = 0;
	}
}

void inputCashbox(vector <check> &cashbox, ifstream &cashboxF) {//пока не конец файла заполняем вектор структурами
	if (!cashboxF) throw 6;

	string str;
	check blanck;
	bool flag = false;
	cookedDish blanckDish;
	int idetidentifierFile = 3;
	map <string, float> strMap;
	map <string, float>::iterator itMap;

	getline(cashboxF, str);
	while (!cashboxF.eof()) {
		while (str.find("total") == string::npos) {//пока не найден total
			strMap = inputErrors(str, idetidentifierFile);
			itMap = strMap.begin();
			if (itMap->first == "") {
				blanck.number = itMap->second;
			}
			else {
				blanckDish.count = itMap->second;
				blanckDish.nameDish = itMap->first;
				blanck.Dish.push_back(blanckDish);
				blanckDish.count = 0;
				blanckDish.nameDish.clear();
			}
			getline(cashboxF, str);
		}
		strMap = inputErrors(str, idetidentifierFile);
		itMap = strMap.begin();
		blanck.total = itMap->second;
		cashbox.push_back(blanck);
		blanck.Dish.clear();
		blanck.number = 0;
		blanck.total = 0;
		getline(cashboxF, str);
		if (str == "==========")
			getline(cashboxF, str);
		else throw 3;
	}
}

void outputErrors(int i) {

	if (i == 1) cout << "Синтаксическая ошибка в файле menu.txt!";
	if (i == 2) cout << "Синтаксическая ошибка в файле kitchen.txt!";
	if (i == 3) cout << "Синтаксическая ошибка в файле cashbox.txt!";
	if (i == 4) cout << "Файл menu.txt не удалось открыть!";
	if (i == 5) cout << "Файл kitchenF.txt не удалось открыть!";
	if (i == 6) cout << "Файл cashbox.txt не удалось открыть!";
	if (i == 7) cout << "На кухне приготовили блюдо, которого нет в меню!";
	if (i == 8) cout << "В чеке есть блюдо, которого нет в меню!";
	if (i == 9) cout << "На кухне меньше блюд, чем на кассе!";
	if (i == 10) cout << "На кассе блюдо, которое не было приготовлено!";
}