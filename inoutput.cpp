#include "stdafx.h"
#include "Header.h"

void Menu::inputMenu(ifstream &menuF) {
	if (!menuF) throw 4;

	string str;
	int countOfSpace;
	Dish inputDish;
	bool flagFirstCategory = false;
	Dish newDish;
	Category s;
	Category* subcategory = &s;
	Category* currentCategory = &s;

	while (!menuF.eof()) {

		getline(menuF, str);
		inputDish = checkMenuForErrors(str);
		countOfSpace = numberOfSpace(inputDish.nameDish);
		size_t first = inputDish.nameDish.find_first_not_of(' ');
		size_t last = inputDish.nameDish.find_last_not_of(' ');
		inputDish.nameDish = inputDish.nameDish.substr(first, (last - first + 1));

		if (inputDish.price == 0) {
			Category *newCategory = new Category;//утечка!
			if (countOfSpace == 0) {
				newCategory->categoryLevel = countOfSpace;
				newCategory->nameCategory = inputDish.nameDish;
				newCategory->ParentCategory = NULL;
				allCategories.push_back(newCategory);
				currentCategory = allCategories[allCategories.size() - 1];
			}
			else {
				if (countOfSpace == currentCategory->categoryLevel + 1) {
					newCategory->categoryLevel = countOfSpace;
					newCategory->nameCategory = inputDish.nameDish;
					newCategory->ParentCategory = currentCategory;
					Category* tmp;
					tmp = newCategory;
					currentCategory->subcategory.push_back(tmp);
					currentCategory = tmp;
				}
				else
					if (countOfSpace < currentCategory->categoryLevel) {//newCategory=currentCategory
						int changeLevel = countOfSpace;
						while (changeLevel != currentCategory->categoryLevel + 1) {
							currentCategory = currentCategory->ParentCategory;
						}
						newCategory->categoryLevel = countOfSpace;
						newCategory->nameCategory = inputDish.nameDish;
						newCategory->ParentCategory = currentCategory;
						Category* tmp;
						tmp = newCategory;
						currentCategory->subcategory.push_back(tmp);
						currentCategory = tmp;

					}
					else
						if (countOfSpace == currentCategory->categoryLevel) {
							currentCategory = currentCategory->ParentCategory;

							newCategory->categoryLevel = countOfSpace;
							newCategory->nameCategory = inputDish.nameDish;
							newCategory->ParentCategory = currentCategory;
							Category* tmp;
							tmp = newCategory;
							currentCategory->subcategory.push_back(tmp);
							currentCategory = tmp;
						}
						else throw 1;
			}
		}
		else { //блюдо
			if (currentCategory->categoryLevel > countOfSpace) {//////////////////
																//    Горячее
																//Суп	
				int tmp = currentCategory->categoryLevel;
				newDish.nameDish = inputDish.nameDish;
				newDish.price = inputDish.price;
				menumap[inputDish.nameDish] = inputDish.price;
				subcategory = currentCategory->ParentCategory;
				while (tmp != countOfSpace) {
					subcategory = subcategory->ParentCategory;
				}
				subcategory->dishes.push_back(newDish);
			}
			if (currentCategory->categoryLevel == countOfSpace) {
				//Горячее
				//Суп
				subcategory = currentCategory->ParentCategory;
				newDish.nameDish = inputDish.nameDish;
				newDish.price = inputDish.price;
				menumap[inputDish.nameDish] = inputDish.price;
				allCategories[allCategories.size() - 1]->dishes.push_back(newDish);
			}
			if (currentCategory->categoryLevel == countOfSpace - 1) {
				//все хорошо
				//Суп
				// Гороховый = 12.10
				newDish.nameDish = inputDish.nameDish;
				newDish.price = inputDish.price;
				menumap[inputDish.nameDish] = inputDish.price;
				currentCategory->dishes.push_back(newDish);

			}
		}
	}
}


void Kitchen::inputKitchen(ifstream &kitchenF) {
	if (!kitchenF) throw 5;

	string str;
	regex tmp("\\s*(.+?) [\\s=]+(\\d+)");
	smatch match;
	cookedDish dishes;
	bool checksyntax;

	while (!kitchenF.eof()) {
		getline(kitchenF, str);
		checksyntax = false;
		if (regex_search(str, match, tmp)) {
			dishes.nameDish = match.str(1);
			dishes.count = stoi(match.str(2));
			allCookedDish.push_back(dishes);
			dishes.nameDish.clear();
			dishes.count = 0;
			checksyntax = true;
		}
		if (!checksyntax)
			throw 2;
	}
}

void Cashbox::inputCashbox(ifstream &cashboxF) {//пока не конец файла заполняем вектор структурами
	if (!cashboxF) throw 6;

	string str;
	Check blanck;
	cookedDish blanckDish;

	regex tmpOrder("\\s*(Заказ)[\\s*N]+(\\d+)");
	regex tmpString("\\s*(.+?)[\\s=]+(\\d+)");
	regex tmpTotal("\\s*(total)[\\s:]+(\\d+)[,\\.](\\d{2})");

	smatch match;
	int checksyntax;

	getline(cashboxF, str);
	while (!cashboxF.eof()) {
		checksyntax = 0;
		if (regex_search(str, match, tmpOrder)) {
			blanck.number = stoi(match.str(2));
			checksyntax++;
		}
		else if (regex_search(str, match, tmpString)) {
			blanckDish.count = stoi(match.str(2));
			blanckDish.nameDish = match.str(1);
			blanck.Dish.push_back(blanckDish);
			blanckDish.count = 0;
			blanckDish.nameDish.clear();
			checksyntax++;
		}
		else if (regex_search(str, match, tmpTotal)) {
			blanck.total = stof(match.str(2));
			allChecks.push_back(blanck);
			blanck.Dish.clear();
			blanck.number = 0;
			blanck.total = 0;
			checksyntax++;
			getline(cashboxF, str);
			if (str != "==========") {
				throw 3;
			}
		}
		if (checksyntax == 0)
			throw 3;
		getline(cashboxF, str);
	}
}

void Report::outputResult(ofstream &fileOfReport, float loss, float totalCheck) {
	//map <string, int>::iterator it;

	//for (it = calculation.begin(); it != calculation.end(); it++) {
	//	cout << it->first << ' ' << it->second << endl;
	//}
	//cout << endl;
	//cout << "Убыток от потерянных блюд: " << loss << endl;//потери 
	//cout << "Ошибка в рассчете итога: " << totalCheck;
	map <string, int>::iterator it;
	fileOfReport << "\nКоличество потерянных блюд:";/* << fileDate << endl*/;
	fileOfReport << endl;

	for (it = calculation.begin(); it != calculation.end(); it++) {
		fileOfReport << it->first << ' ' << it->second << endl;
	}
	fileOfReport << endl;
	fileOfReport << "Убыток от потерянных блюд: " << loss << endl;//потери 
	fileOfReport << "Ошибка в рассчете итога: " << totalCheck;
}

void Cashbox::outputIsFoundChecks(ostream &outputStream, vector <Check> findChecks) {
	for (int i = 0; i < findChecks.size(); i++) {
		outputStream << "Заказ№ " << findChecks[i].number << '\n';
		for (int j = 0; j < findChecks[i].Dish.size(); j++) {
			outputStream << findChecks[i].Dish[j].nameDish << ' ' << findChecks[i].Dish[j].count << '\n';
		}
		outputStream << "Total: " << findChecks[i].total << '\n' << "==========" << '\n';
	}
}

void Cashbox::findDishInCheckbox(string nameDish, int flagOutput) {
	setlocale(LC_ALL, "Russian");
	vector <Check> findChecks;
	ofstream outputChecks("outputChecks.txt");
	ostream &out = cout;

	bool findDishInCheck;
	for (int i = 0; i < allChecks.size(); i++) {
		findDishInCheck = false;
		for (int j = 0; j < allChecks[i].Dish.size() && !findDishInCheck; j++) {
			if (nameDish == allChecks[i].Dish[j].nameDish) {
				findDishInCheck = true;
				findChecks.push_back(allChecks[i]);
			}
		}
	}
	if (flagOutput == 1) {
		outputIsFoundChecks(cout, findChecks);
	}
	else outputIsFoundChecks(outputChecks, findChecks);
}

void Cashbox::inputFindDish() {
	string nameDish;
	int flagOutput;

	cout << "\nВведите название блюда\n";
	getline(cin, nameDish);
	cout << "Введите 1, если хотите вывести результат на консоль, если записать в файл - 2\n";
	cin >> flagOutput;

	if ((flagOutput == 1) || (flagOutput == 2)) {
		findDishInCheckbox(nameDish, flagOutput);
	}
	else cout << "Ошибка!!!";
}

void Menu::deleteMenu(vector <Category*> allCategories) {
	Category * parent = allCategories[0]->ParentCategory;

	for (int i = 0; i < allCategories.size(); i++) {
		if (!allCategories[i]->subcategory.empty()) {
			if (allCategories[i]->subcategory.size() != 0) {
				deleteMenu(allCategories[i]->subcategory);
			}
			else {
				parent = allCategories[i]->ParentCategory;
				delete allCategories[i];
				//i++;
				if (parent != NULL) deleteMenu(parent->subcategory);
			}
		}
		else delete allCategories[i];
	}
}
