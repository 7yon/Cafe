#include "stdafx.h"
#include "Header.h"

void Report::reportGeneration(int typeOfReport,Menu myMenu, Cashbox myCashbox, Kitchen myKitchen, ofstream &fileOfReport) {
	if (typeOfReport == 1){
		checkDishInCashbox(myKitchen.getAllCookedDish(), myMenu, myCashbox.getAllChecks(), fileOfReport);
	}

	if (typeOfReport == 2) {
		statisticsOfOrders(myCashbox, myMenu, fileOfReport);
	}
	/*if (typeOfReport == 3) {
		priceBehavior(fileOfReport);
	}*/
}

void Report::changeDate(int &dd1, int &mm1, int &yy1) {
	int days_1[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if ((yy1 % 4 == 0 || (yy1 % 100 != 0 && yy1 % 400 == 0)) && (mm1 == 3 && dd1 == 1)) {
		dd1 = 29;
		mm1--;
	}
	else {
		if (dd1 == 1) {
			dd1 = days_1[mm1 - 1];
			if (mm1 == 1) {
				mm1 = 12;
				yy1--;
			}
			else mm1--;
		}
		else dd1--;
	}
}

PeriodOfDate Report::periodOfTheReport(int i, Cashbox myCashbox, Menu myMenu) {
	int period = 0;
	int dd1, mm1, yy1;
	int dd2, mm2, yy2;
	PeriodOfDate myPeriod;
	if (i < 3) {
		cout << "\nВыберете период за который необходимо построить отчет:" << endl;
		cout << "1 - За последний день (текущая дата)" << endl;
		cout << "2 - За определенные сутки" << endl;
		cout << "3 - За последнюю неделю (текущая дата и 6 предшествующих дней) с детализацией по дням" << endl;
		cout << "4 - За заданный период с детализацией по дням" << endl;
		cin >> period;
	}
	/*else {
		cout << "Введите начальную дату" << endl;
		cout << "Число : ";
		cin >> dd1;
		cout << "Месяц (например: Январь - 1): ";
		cin >> mm1;
		cout << "Год (например: 2016): ";
		cin >> yy1;

		cout << "Введите конечную дату" << endl;
		cout << "Число: ";
		cin >> dd2;
		cout << "Месяц (например: Январь - 1): ";
		cin >> mm2;
		cout << "Год(например: 2016): ";
		cin >> yy2;
		myPeriod.firstDay.setDate(dd1, mm1, yy1);
		myPeriod.lastDay.setDate(dd2, mm2, yy2);
	}*/
	if (period == 1) {
		time_t rawtime;
		struct tm timeinfo; 

		time(&rawtime);

		localtime_s(&timeinfo, &rawtime); 
		myPeriod.getFirstDay().setDate(timeinfo.tm_mday, timeinfo.tm_mon + 1, timeinfo.tm_year + 1900);
		myPeriod.getLastDay().setDate(timeinfo.tm_mday, timeinfo.tm_mon + 1, timeinfo.tm_year + 1900);
	}

	if (period == 2) {
		cout << "Введите дату" << endl;
		cout << "Число: ";
		cin >> dd1;
		cout << "Месяц (например: Январь - 1): ";
		cin >> mm1;
		cout << "Год(например: 2016): ";
		cin >> yy1;
		myPeriod.getFirstDay().setDate(dd1, mm1, yy1);
		myPeriod.getLastDay().setDate(dd1, mm1, yy1);
	}
	if (period == 3) {
		time_t rawtime;
		struct tm timeinfo;  // no longer a pointer

		time(&rawtime);
		// on platforms with POSIX localtime_r but no localtime_s, add this macro
		// #define localtime_s(x, y) localtime_r(y, x)
		localtime_s(&timeinfo, &rawtime); // fills in your structure,
										  //								  // instead of returning a pointer to a static one
										  //cout << endl;
										  //cout << timeinfo.tm_hour << endl;  // no longer using a pointer
										  //cout << timeinfo.tm_min << endl;
										  ////cout << timeinfo.tm_sec << endl;
										  //cout << timeinfo.tm_mday << endl;
										  //cout << timeinfo.tm_mon + 1 << endl;
										  //cout << timeinfo.tm_year + 1900 << endl;
		int dd2, mm2, yy2;
		dd2 = timeinfo.tm_mday;
		mm2 = timeinfo.tm_mon + 1;
		yy2 = timeinfo.tm_year + 1900;
		myPeriod.getFirstDay().setDate(timeinfo.tm_mday, timeinfo.tm_mon + 1, timeinfo.tm_year + 1900);

		changeDate(dd2, mm2, yy2);
		myPeriod.getLastDay().setDate(dd2, mm2, yy2);
	}
	if ((i == 3)||(period == 4)) {
		cout << "Введите начальную дату" << endl;
		cout << "Число : ";
		cin >> dd1; 
		cout << "Месяц (например: Январь - 1): ";
		cin >> mm1;
		cout << "Год (например: 2016): ";
		cin >> yy1;

		cout << "Введите конечную дату" << endl;
		cout << "Число: ";
		cin >> dd2;
		cout << "Месяц (например: Январь - 1): ";
		cin >> mm2;
		cout << "Год(например: 2016): ";
		cin >> yy2;
		myPeriod.getFirstDay().setDate(dd1, mm1, yy1);
		myPeriod.getLastDay().setDate(dd2, mm2, yy2);
	}

	/*if (i == 3) priceBehavior(myPeriod);*/
	return myPeriod;
}

void Report::outputStatisticsInFile(map <string, int> mapDishes, map <string, int> mapCategoryAndSubcategory, vector <Category*> allCategories, ofstream &fileOfReport) {
	bool flagFound = false;
	Category* foundCategory;
	map <string, int>::iterator ItDishes;
	map <string, int>::iterator ItCategory;
	int i;

	ItDishes = mapDishes.begin();
	ItCategory = mapCategoryAndSubcategory.begin();


	for (i = 0; i < allCategories.size() && !flagFound; i++) {//короче говоря тут мы записывает отступы перед категорией, чтоб видеть лесенку, саму категорию и количество

		ItCategory = mapCategoryAndSubcategory.find(allCategories[i]->getNameCategory());
		int space = 0;
		while (space != allCategories[i]->getCategoryLevel()) {
			fileOfReport << '_';
			space++;
		}
		if (ItCategory == mapCategoryAndSubcategory.end()) 
			fileOfReport << allCategories[i]->getNameCategory() << ' ' << 0;
		else 
			fileOfReport << allCategories[i]->getNameCategory() << ' ' << mapCategoryAndSubcategory[allCategories[i]->getNameCategory()];
		fileOfReport << '\n';

		for (int j = 0; j < allCategories[i]->getDishes().size(); j++) {//а тут тоже самое только для блюда
			ItDishes = mapDishes.find(allCategories[i]->getDishes()[j].getNameDish());
			int space = 0;
			while (space != allCategories[i]->getCategoryLevel() + 1) {
				fileOfReport << '_';
				space++;
			}
			if (ItDishes == mapDishes.end()) 
				fileOfReport << allCategories[i]->getDishes()[j].getNameDish() << ' ' << 0;
			else 
				fileOfReport << allCategories[i]->getDishes()[j].getNameDish() << ' ' << mapDishes[allCategories[i]->getDishes()[j].getNameDish()];
			fileOfReport << '\n';
		}
		if (allCategories[i]->getSubcategory().size() != 0) {
			outputStatisticsInFile(mapDishes, mapCategoryAndSubcategory, allCategories[i]->getSubcategory(), fileOfReport);
		}
	}
	allCategories.clear();

}

void Report::statisticsOfOrders(Cashbox myCashbox, Menu myMenu, ofstream &fileOfReport) {
	string date1;
	string  date2;
	string nameFile;
	bool firstSearch = false;

	/*date1 = myPeriod.firstDay.getDate();
	date2 = myPeriod.lastDay.getDate();

*/
	//if (date1 == date2) {//один день(текущий или по выбору)

		float amountOfRevenue = 0;
		int counterOfChecks = 0;

		map <string, int> mapDishes;
		map <string, int> mapCategoryAndSubcategory;
		map <string, int>::iterator ItDishes;
		map <string, int>::iterator ItCategory;

		mapDishes.clear();
		mapCategoryAndSubcategory.clear();

		ItDishes = mapDishes.begin();
		ItCategory = mapCategoryAndSubcategory.begin();
		for (int i = 0; i < myCashbox.getAllChecks().size(); i++) {
			amountOfRevenue = amountOfRevenue + myCashbox.getAllChecks()[i].getTotal();
			counterOfChecks++;
		}
		//СДЕЛАТЬ ОБЩИМ!!!
		//cout << '\n';
		/*fileOfReport << "За указанный период:" << myPeriod.firstDay.getDate() << '-'<< myPeriod.firstDay.getDate() << endl;*/
		fileOfReport << "Сумма выручки: " << amountOfRevenue << endl;
		fileOfReport << "Количество заказов: " << counterOfChecks << endl;
		fileOfReport << "Средний чек: " << amountOfRevenue / counterOfChecks << endl;

		for (int i = 0; i < myCashbox.getAllChecks().size(); i++) {//mapDishes
			for (int j = 0; j < myCashbox.getAllChecks()[i].getDish().size(); j++) {
				Category* foundMyDish;
				foundMyDish = myMenu.findInMenu(myCashbox.getAllChecks()[i].getDish()[j].getNameDish(), myMenu.getMenu());//нашли категорию, в которой блюдо и сохранили адрес
				ItCategory = mapCategoryAndSubcategory.find(foundMyDish->getNameCategory());//при вложенных категориях возвращается мусор
				if (ItCategory == mapCategoryAndSubcategory.end()) {
					mapCategoryAndSubcategory[foundMyDish->getNameCategory()] = myCashbox.getAllChecks()[i].getDish()[j].getCount();
				}
				else {
					mapCategoryAndSubcategory[foundMyDish->getNameCategory()] = ItCategory->second + myCashbox.getAllChecks()[i].getDish()[j].getCount();
				}
				firstSearch = false;
				while ((foundMyDish->getParentCategory() != NULL)||(!firstSearch)) {//пока не уперлись в категорию
					firstSearch = true;
					ItDishes = mapDishes.find(myCashbox.getAllChecks()[i].getDish()[j].getNameDish());//ищем в мап категорию блюда из чека
					if (ItDishes == mapDishes.end()) {//если не нашли, то просто запушили
						mapDishes[myCashbox.getAllChecks()[i].getDish()[j].getNameDish()] = myCashbox.getAllChecks()[i].getDish()[j].getCount();
					}
					else {//если нашли такую категорию в блюде то суммируем
						mapDishes[myCashbox.getAllChecks()[i].getDish()[j].getNameDish()] = ItDishes->second + myCashbox.getAllChecks()[i].getDish()[j].getCount();
					}
					while(foundMyDish->getParentCategory() != NULL) {
						foundMyDish = foundMyDish->getParentCategory();//перешли по родительской категории
						ItCategory = mapCategoryAndSubcategory.find(foundMyDish->getNameCategory());//при вложенных категориях возвращается мусор
						if (ItCategory == mapCategoryAndSubcategory.end()) {
							mapCategoryAndSubcategory[foundMyDish->getNameCategory()] = myCashbox.getAllChecks()[i].getDish()[j].getCount();
						}
						else {
							mapCategoryAndSubcategory[foundMyDish->getNameCategory()] = ItCategory->second + myCashbox.getAllChecks()[i].getDish()[j].getCount();
						}
					}
				}
			}
		}
		//проход по дереву и запись в файл
		fileOfReport << '\n';
		outputStatisticsInFile(mapDishes, mapCategoryAndSubcategory, myMenu.getMenu(), fileOfReport);
		myCashbox.getAllChecks().clear();
		myMenu.deleteMenu(myMenu.getMenu());
	//}
	//else {//какой-то период
	//	/////////////////////////////
	//}
	//fileOfReport.close();
}

int Report::reportSelection(Cashbox myCashbox, Menu myMenu) {
	int numberOfReport;
	cout <<'\n'<< '\n';
	cout << "Выберите тип отчета:"<< endl;
	cout << "1 - Отчет об украденных блюдах" << endl;
	cout << "2 - Отчет по статистике заказов" << endl;
	cout << "3 - Отчет по динамике цен в меню " << endl;
	cout << "0 - Выйти из программы" << endl;

	cin >> numberOfReport;
	while ((cin.fail())||(numberOfReport > 3)) {
		if (cin.fail()){
			cin.sync();
			cout << "Неккоректный символ! Введите ещё раз" << endl;
		}
		else cout << "Отчета с таким номером нет! Введите ещё раз" << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> numberOfReport;
	}
	//if (numberOfReport == 3) priceBehavior();
	//periodOfTheReport(numberOfReport, myCashbox, myMenu);
	//else
	return numberOfReport;
}

void Report::priceBehavior(PeriodOfDate myPeriod, ofstream &fileOfReport) { //3 отчет

	Cafe myCafe;

	ifstream menuBegin;
	ifstream menuEnd;;
	bool finddish;
	map <string, map<string, float>> menuAllDay;
	map <string, float> ::iterator itMapBegin;
	map <string, float> ::iterator itMapEnd;
	menuBegin.open("menu-" + myPeriod.getFirstDay().getDate() + ".txt");
	menuEnd.open("menu-" + myPeriod.getLastDay().getDate() + ".txt");
	try {
		myCafe.getMyMenu().inputMenu(menuBegin);
		menuAllDay[myPeriod.getFirstDay().getDate()] = myCafe.getMyMenu().getMenuMap();
		myCafe.getMyMenu().clearMenuMap();
		myCafe.getMyMenu().inputMenu(menuEnd);
		menuAllDay[myPeriod.getLastDay().getDate()] = myCafe.getMyMenu().getMenuMap();
	}
	catch (int i) {
		myCafe.getOutputErrors().outputErrors.outputErrors(i, "Menu", "Cashbox", "Kitchen");
	}
	for (itMapBegin = menuAllDay[myPeriod.getFirstDay().getDate()].begin(); itMapBegin != menuAllDay[myPeriod.getFirstDay().getDate()].end(); itMapBegin++) {
		for (itMapEnd = menuAllDay[myPeriod.getLastDay().getDate()].begin(); itMapEnd != menuAllDay[myPeriod.getLastDay().getDate()].end(); itMapEnd++) {
			if (itMapEnd->first == itMapBegin->first) {
				fileOfReport << itMapBegin->first << "  изменение цены:  ";
				fileOfReport << abs(itMapBegin->second - itMapEnd->second);
				fileOfReport << " в процентах:" << abs((itMapBegin->second - itMapEnd->second) * 100 / itMapBegin->second) << endl;
			}
		}
	}
	fileOfReport << endl;
	for (itMapEnd = menuAllDay[myPeriod.getLastDay().getDate()].begin(); itMapEnd != menuAllDay[myPeriod.getLastDay().getDate()].end(); itMapEnd++) {
		finddish = false;
		for (itMapBegin = menuAllDay[myPeriod.getFirstDay().getDate()].begin(); itMapBegin != menuAllDay[myPeriod.getFirstDay().getDate()].end(); itMapBegin++) {
			if (itMapEnd->first == itMapBegin->first) {
				finddish = true;
			}
		}
		if (!finddish) {
			fileOfReport << "Добавлено блюдо: " << itMapEnd->first << endl;
		}
	}
	for (itMapBegin = menuAllDay[myPeriod.getFirstDay().getDate()].begin(); itMapBegin != menuAllDay[myPeriod.getFirstDay().getDate()].end(); itMapBegin++) {
		finddish = false;
		for (itMapEnd = menuAllDay[myPeriod.getLastDay().getDate()].begin(); itMapEnd != menuAllDay[myPeriod.getLastDay().getDate()].end(); itMapEnd++) {
			if (itMapBegin->first == itMapEnd->first) {
				finddish = true;
			}
		}
		if (!finddish) {
			fileOfReport << "Удалено блюдо: " << itMapBegin->first << endl;
		}
	}
	cout << "";
	menuBegin.close();
	menuEnd.close();
}

void Report::createReport(Menu myMenu, Cashbox myCashbox, Kitchen myKitchen, Error outputErrors) {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int typeOfReport;
	PeriodOfDate myPeriod;
	typeOfReport = reportSelection(myCashbox, myMenu);
	myPeriod = periodOfTheReport(typeOfReport, myCashbox, myMenu);

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	ifstream menuF;
	ifstream cashboxF;
	ifstream kitchenF;

	string date1;
	string  date2;
	string nameFile;
	int dd2, mm2, yy2;
	bool firstOperation = false;
	int counterOfDay = 0;

	date1 = myPeriod.getFirstDay().getDate();
	date2 = myPeriod.getLastDay().getDate();

	dd2 = myPeriod.getLastDay().getDD();
	mm2 = myPeriod.getLastDay().getMM();
	yy2 = myPeriod.getLastDay().getYY();

	ofstream fileOfReport;

	if (date1 == date2) {
		if (typeOfReport == 1)
			nameFile = "stolenDishes-" + myPeriod.getFirstDay().getDate() + ".txt";

		if (typeOfReport == 2)
			nameFile = "statisticsOfOrders-" + myPeriod.getFirstDay().getDate() + ".txt";

		if (typeOfReport == 3)
			nameFile = "priceDynamics-" + myPeriod.getFirstDay().getDate() + ".txt";
	}

	else {
		if (typeOfReport == 1)
			nameFile = "stolenDishes-" + myPeriod.getFirstDay().getDate() + '-' + myPeriod.getLastDay().getDate() + ".txt";

		if (typeOfReport == 2)
			nameFile = "statisticsOfOrders-" + myPeriod.getFirstDay().getDate() + '-' + myPeriod.getLastDay().getDate() + ".txt";

		if (typeOfReport == 3)
			nameFile = "priceDynamics-" + myPeriod.getFirstDay().getDate() + '-' + myPeriod.getLastDay().getDate() + ".txt";
	}
	fileOfReport.open(nameFile);

	fileOfReport << "За указанный период:" << myPeriod.getFirstDay().getDate() << '-' << myPeriod.getLastDay().getDate() << endl;

	while ((date1 != date2) || (!firstOperation)) {

		counterOfDay++;
		string nameMenu, nameCashbox, nameKitchen;

		nameMenu = "menu-" + date1 + ".txt";
		nameCashbox = "cashbox-" + date1 + ".txt";
		nameKitchen = "kitchen-" + date1 + ".txt";

		menuF.open(nameMenu);
		cashboxF.open(nameCashbox);
		kitchenF.open(nameKitchen);
		//добавить цикл для недельки
		try {
			myMenu.inputMenu(menuF);
			myKitchen.inputKitchen(kitchenF);
			myCashbox.inputCashbox(cashboxF);
			myMenu.checkDishes(myKitchen.getAllCookedDish(), myCashbox.getAllChecks());
			//checkDishInCashbox(myKitchen.allCookedDish, myMenu, myCashbox.allChecks);
			//myCafe.myCashbox.outputResult();
			//myCafe.myCashbox.inputFindDish();
			//fileOfReport << date2<< '\n';
			if (typeOfReport == 3) priceBehavior(myPeriod);
			else {
				reportGeneration(typeOfReport, myMenu, myCashbox, myKitchen, fileOfReport);
				fileOfReport << "\n==========================================================================================" << "\n";
			}
			//myCafe.myReport.reportSelection(myCafe.myCashbox, myCafe.myMenu, fileOfReport);

			if ((typeOfReport == 3) && (counterOfDay != 7)) firstOperation = false;
			//if (typeOfReport == 2) firstOperation = true;
			if (date1 == date2) firstOperation = true;
			else {
				changeDate(dd2, mm2, yy2);
				date2.clear();
				date2 = to_string(yy2) + to_string(mm2) + to_string(dd2);
				firstOperation = false;
			}
			if (typeOfReport == 3) firstOperation = true;
			menuF.close();
			cashboxF.close();
			kitchenF.close();
		}
		catch (int i) {
			outputErrors.outputErrors(i, nameMenu, nameCashbox, nameKitchen);
			break;
		}
	}
	//myCafe.myMenu.deleteMenu(myCafe.myMenu);
	fileOfReport.close();
}


void Report::checkDishInCashbox(vector <cookedDish> kitchen, Menu myMenu, vector <Check> allChecks, ofstream &fileOfReport) {//проверка и вывод на консоль
	bool flag = false;
	Dish myDish;
	Category* foundCategory;
	map<string, int>::iterator it;

	for (int i = 0; i < kitchen.size(); i++) {
		if (calculation[kitchen[i].getNameDish()]) {
			calculation[kitchen[i].getNameDish()] = calculation[kitchen[i].getNameDish()] + kitchen[i].getCount();
		}
		else calculation[kitchen[i].getNameDish()] = kitchen[i].getCount();
	}

	for (int i = 0; i < allChecks.size(); i++) {//сравниваем количество блюд на кухне и на кассе
		for (int j = 0; j < allChecks[i].getDish().size(); j++) {
			for (it = calculation.begin(); it != calculation.end() && !flag; it++) {
				if (allChecks[i].getDish()[j].getNameDish() == it->first) {
					it->second = it->second - allChecks[i].getDish()[j].getCount();
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
	//cout << "Количество потерянных блюд:" << endl;
	//cout << endl;

	for (it = calculation.begin(); it != calculation.end() && !flag; it++) {
		//myDish = myMenu.findInMenu(it->first);
		foundCategory = myMenu.findInMenu(it->first, myMenu.getMenu());
		//loss = loss + it->second * myDish.price;
		int i, y;
		for (i = 0; i < foundCategory->getDishes().size(); i++)
			if (foundCategory->getDishes()[i].getNameDish() == it->first) break;
		loss = loss + it->second * foundCategory->getDishes()[i].getPrice();
	}

	for (int i = 0; i < allChecks.size(); i++) {//ошибка в расчете total
		for (int j = 0; j < allChecks[i].getDish().size(); j++) {
			//myDish = myMenu.findInMenu(allChecks[i].Dish[j].nameDish);
			foundCategory = myMenu.findInMenu(allChecks[i].getDish()[j].getNameDish(), myMenu.getMenu());
			//totalCheck = totalCheck + allChecks[i].Dish[j].count * myDish.price;
			int l;
			for (l = 0; i < foundCategory->getDishes().size(); l++)
				if (foundCategory->getDishes()[l].getNameDish() == allChecks[i].getDish()[j].getNameDish()) break;
			totalCheck = totalCheck + allChecks[i].getDish()[j].getCount() * foundCategory->getDishes()[l].getPrice();
		}
		totalCheck = allChecks[i].getTotal() - totalCheck;
	}
	outputResult(fileOfReport, loss, totalCheck);
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

Date::Date() {
	dd = 0;
	mm = 0;
	yy = 0;
}

void Date::setDate(int day, int month, int year) {
	dd = day;
	mm = month;
	yy = year;
}

string Date::getDate() {
	string myDate = to_string(yy) + to_string(mm) + to_string(dd);
	return myDate;
}

int Date::getMM() {
	return mm;
}

int Date::getDD() {
	return dd;
}

int Date::getYY() {
	return yy;
}

Date PeriodOfDate::getFirstDay() {
	return firstDay;
}
Date PeriodOfDate::getLastDay() {
	return lastDay;
}
void PeriodOfDate::setFirstDay(Date myFirstDay) {
	firstDay = myFirstDay;
}
void PeriodOfDate::setLastDay(Date myLastDay) {
	lastDay = myLastDay;
}

map<string, int> Report::getCalculation() {
	return calculation;
}
void Report::setCalculation(string name, int count) {
	calculation[name] = count;
}