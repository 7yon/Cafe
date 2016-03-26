#include "stdafx.h"
#include "Report.h"

void Report::checkKitchenCashboxMenu(string myDate) {
	string currentDate = myDate;

	Cafe myCafe;
	Menu newMenu;
	Cashbox newCashbox;
	Kitchen newKitchen;

	string nameMenu = "menu-" + currentDate + ".txt";
	string nameCashbox = "cashbox-" + currentDate + ".txt";
	string nameKitchen = "kitchen-" + currentDate + ".txt";

	ifstream menuFile;
	ifstream cashboxFile;
	ifstream kitchenFile;

	menuFile.open(nameMenu);
	cashboxFile.open(nameCashbox);
	kitchenFile.open(nameKitchen);

	try {
		newMenu.inputMenu(menuFile);
		newKitchen.inputKitchen(kitchenFile);
		newCashbox.inputCashbox(cashboxFile);
		newMenu.checkDishes(newKitchen.getAllCookedDish(), newCashbox.getAllChecks());

		myCafe.setMyMenu(newMenu);
		myCafe.setMyKitchen(newKitchen);
		myCafe.setMyCashbox(newCashbox);
		historyAboutCafe[myDate] = myCafe;
	}

	catch (int i) {
		myCafe.getOutputErrors().outputErrors(i, nameMenu, nameCashbox, nameKitchen);
	}
}

void Report::reportGeneration(int typeOfReport) {
	if (typeOfReport == 1){
		//checkDishInCashbox(myCafe);
	}
	if (typeOfReport == 2) {
		statisticsOfOrders();
	}
	if (typeOfReport == 3) {
		//priceBehavior(myCafe);
	}
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

void Report::periodOfTheReport(int i) {
	int period = 0;
	int dd1, mm1, yy1;
	int dd2, mm2, yy2;
	PeriodOfDate myPeriod;
	Date myDate;

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
		myDate.setDate(dd1, mm1, yy1);
		myPeriod.setFirstDay(myDate);
		myPeriod.setLastDay(myDate);
	}
	if (period == 3) {
		time_t rawtime;
		struct tm timeinfo; 
		time(&rawtime);

		localtime_s(&timeinfo, &rawtime);

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
	fillingMapHistory(myPeriod, i);
	//return myPeriod;
}

void Report::outputStatisticsInFile(map <string, map<string, map<string, int>>> mapAllDishAndCategory, ofstream &fileOfReport) {

	float amountOfRevenue = 0;
	int counterOfChecks = 0;
	bool flagFound = false;
	Category* foundCategory;

	map <string, int>::iterator ItDishes;
	map <string, int>::iterator ItCategory;
	map <string, Cafe>::iterator ItHistory;

	map <string, map<string, map<string, int>>>::iterator ItFirstAllDishAndCategory;
	map <string, map<string, map<string, int>>>::reverse_iterator ItLastAllDishAndCategory;

	ItFirstAllDishAndCategory = mapAllDishAndCategory.begin();
	ItLastAllDishAndCategory = mapAllDishAndCategory.rbegin();

	ItHistory = historyAboutCafe.begin();
	while (ItHistory != historyAboutCafe.end()) {
		fileOfReport << "Статистика за " << ItHistory->first << "\n";
		for (int i = 0; i < ItHistory->second.getMyMenu().getMenu().size() && !flagFound; i++) {//короче говоря тут мы записывает отступы перед категорией, чтоб видеть лесенку, саму категорию и количество
			ItCategory = mapAllDishAndCategory[ItHistory->first]["Category"].find(ItHistory->second.getMyMenu().getMenu()[i]->getNameCategory());
			int space = 0;
			while (space != ItHistory->second.getMyMenu().getMenu()[i]->getCategoryLevel()) {
				fileOfReport << '_';
				space++;
			}
			if (ItCategory == mapAllDishAndCategory[ItHistory->first]["Category"].end())
				fileOfReport << ItHistory->second.getMyMenu().getMenu()[i]->getNameCategory() << ' ' << 0;
			else
				fileOfReport << ItHistory->second.getMyMenu().getMenu()[i]->getNameCategory() << ' ' << mapAllDishAndCategory[ItHistory->first]["Category"][ItHistory->second.getMyMenu().getMenu()[i]->getNameCategory()];
			fileOfReport << '\n';

			for (int j = 0; j < ItHistory->second.getMyMenu().getMenu()[i]->getDishes().size(); j++) {//а тут тоже самое только для блюда
				ItDishes = mapAllDishAndCategory[ItHistory->first]["Dish"].find(ItHistory->second.getMyMenu().getMenu()[i]->getDishes()[j].getNameDish());
				int space = 0;
				while (space != ItHistory->second.getMyMenu().getMenu()[i]->getCategoryLevel() + 1) {
					fileOfReport << '_';
					space++;
				}
				if (ItDishes == mapAllDishAndCategory[ItHistory->first]["Dish"].end())
					fileOfReport << ItHistory->second.getMyMenu().getMenu()[i]->getDishes()[j].getNameDish() << ' ' << 0;
				else
					fileOfReport << ItHistory->second.getMyMenu().getMenu()[i]->getDishes()[j].getNameDish() << ' ' << mapAllDishAndCategory[ItHistory->first]["Dish"][ItHistory->second.getMyMenu().getMenu()[i]->getDishes()[j].getNameDish()];
				fileOfReport << '\n';
			}
			if (ItHistory->second.getMyMenu().getMenu()[i]->getSubcategory().size() != 0) {
				outputStatisticsInFile(mapAllDishAndCategory, fileOfReport);
			}
		}
		ItHistory++;
	}

	ItHistory = historyAboutCafe.begin();
	while (ItHistory != historyAboutCafe.end()) {
		for (int i = 0; i < ItHistory->second.getMyCashbox().getAllChecks().size(); i++){
			amountOfRevenue = amountOfRevenue + ItHistory->second.getMyCashbox().getAllChecks()[i].getTotal();
			counterOfChecks++;
		}
		ItHistory++;
	}
	fileOfReport << "\nЗа указанный период:" << ItFirstAllDishAndCategory->first << '-'<< ItLastAllDishAndCategory->first << endl;
	fileOfReport << "Сумма выручки: " << amountOfRevenue << endl;
	fileOfReport << "Количество заказов: " << counterOfChecks << endl;
	fileOfReport << "Средний чек: " << amountOfRevenue / counterOfChecks << endl;
	fileOfReport.close();
	//allCategories.clear();
}

void Report::statisticsOfOrders() {
	//string date1;
	//string  date2;
	string nameFile;
	bool firstSearch = false;
	ofstream fileOfReport;

	map <string, int> mapDishes;
	map <string, int> mapCategoryAndSubcategory;
	map <string, map<string, map<string, int>>> mapAllDishAndCategory;
	map <string, map<string, int>> mapDishAndCategory;

	map <string, int>::iterator ItDishes;
	map <string, int>::iterator ItCategory;
	map <string, Cafe>::iterator ItHistory;
	map <string, map<string, map<string, int>>>::iterator ItFirstAllDishAndCategory;
	map <string, map<string, map<string, int>>>::reverse_iterator ItLastAllDishAndCategory;

	mapDishes.clear();
	mapCategoryAndSubcategory.clear();

	ItHistory = historyAboutCafe.begin();
	ItDishes = mapDishes.begin();
	ItCategory = mapCategoryAndSubcategory.begin();

		//for (int i = 0; i < myCafe.getMyCashbox().getAllChecks().size(); i++) {
		//	amountOfRevenue = amountOfRevenue + myCafe.getMyCashbox().getAllChecks()[i].getTotal();
		//	counterOfChecks++;
		//}
		//СДЕЛАТЬ ОБЩИМ!!!
		//cout << '\n';
		/*fileOfReport << "За указанный период:" << myPeriod.firstDay.getDate() << '-'<< myPeriod.firstDay.getDate() << endl;*/
		//fileOfReport << "Сумма выручки: " << amountOfRevenue << endl;
		//fileOfReport << "Количество заказов: " << counterOfChecks << endl;
		//fileOfReport << "Средний чек: " << amountOfRevenue / counterOfChecks << endl;

	while (ItHistory != historyAboutCafe.end()) {
		for (int i = 0; i < ItHistory->second.getMyCashbox().getAllChecks().size(); i++) {//mapDishes
			for (int j = 0; j < ItHistory->second.getMyCashbox().getAllChecks()[i].getDish().size(); j++) {
				Category* foundMyDish;
				foundMyDish = ItHistory->second.getMyMenu().findInMenu(ItHistory->second.getMyCashbox().getAllChecks()[i].getDish()[j].getNameDish(), ItHistory->second.getMyMenu().getMenu());//нашли категорию, в которой блюдо и сохранили адрес

				ItCategory = mapCategoryAndSubcategory.find(foundMyDish->getNameCategory());//при вложенных категориях возвращается мусор
				if (ItCategory == mapCategoryAndSubcategory.end()) {
					mapCategoryAndSubcategory[foundMyDish->getNameCategory()] = ItHistory->second.getMyCashbox().getAllChecks()[i].getDish()[j].getCount();
				}
				else {
					mapCategoryAndSubcategory[foundMyDish->getNameCategory()] = ItCategory->second + ItHistory->second.getMyCashbox().getAllChecks()[i].getDish()[j].getCount();
				}
				firstSearch = false;
				while ((foundMyDish->getParentCategory() != NULL) || (!firstSearch)) {//пока не уперлись в категорию
					firstSearch = true;
					ItDishes = mapDishes.find(ItHistory->second.getMyCashbox().getAllChecks()[i].getDish()[j].getNameDish());//ищем в мап категорию блюда из чека
					if (ItDishes == mapDishes.end()) {//если не нашли, то просто запушили
						mapDishes[ItHistory->second.getMyCashbox().getAllChecks()[i].getDish()[j].getNameDish()] = ItHistory->second.getMyCashbox().getAllChecks()[i].getDish()[j].getCount();
					}
					else {//если нашли такую категорию в блюде то суммируем
						mapDishes[ItHistory->second.getMyCashbox().getAllChecks()[i].getDish()[j].getNameDish()] = ItDishes->second + ItHistory->second.getMyCashbox().getAllChecks()[i].getDish()[j].getCount();
					}
					while (foundMyDish->getParentCategory() != NULL) {
						foundMyDish = foundMyDish->getParentCategory();//перешли по родительской категории
						ItCategory = mapCategoryAndSubcategory.find(foundMyDish->getNameCategory());//при вложенных категориях возвращается мусор
						if (ItCategory == mapCategoryAndSubcategory.end()) {
							mapCategoryAndSubcategory[foundMyDish->getNameCategory()] = ItHistory->second.getMyCashbox().getAllChecks()[i].getDish()[j].getCount();
						}
						else {
							mapCategoryAndSubcategory[foundMyDish->getNameCategory()] = ItCategory->second + ItHistory->second.getMyCashbox().getAllChecks()[i].getDish()[j].getCount();
						}
					}
				}
			}
		}
		mapDishAndCategory["Category"] = mapCategoryAndSubcategory;
		mapDishAndCategory["Dish"] = mapDishes;
		mapAllDishAndCategory[ItHistory->first] = mapDishAndCategory;//заполнили map
		ItHistory++;
	}
	ItFirstAllDishAndCategory = mapAllDishAndCategory.begin();
	ItLastAllDishAndCategory = mapAllDishAndCategory.rbegin();
	fileOfReport.open("statisticsOfOrders-"+ ItFirstAllDishAndCategory->first + ItLastAllDishAndCategory->first +".txt");
	
	outputStatisticsInFile(mapAllDishAndCategory, fileOfReport);

		//проход по дереву и запись в файл
		//fileOfReport << '\n';
		//outputStatisticsInFile(mapDishes, mapCategoryAndSubcategory, myCafe.getMyMenu().getMenu());
		//myCafe.getMyCashbox().getAllChecks().clear();
		//myMenu.deleteMenu(myMenu.getMenu());
	//}
	//else {//какой-то период
	//	/////////////////////////////
	//}
	//fileOfReport.close();
}

void Report::reportSelection() {
	int numberOfReport = 1;

	cout << '\n' << '\n';
	cout << "Выберите тип отчета:" << endl;
	cout << "1 - Отчет об украденных блюдах" << endl;
	cout << "2 - Отчет по статистике заказов" << endl;
	cout << "3 - Отчет по динамике цен в меню " << endl;
	cout << "0 - Выйти из программы" << endl;

	cin >> numberOfReport;
	while (numberOfReport != 0) {
		while ((cin.fail()) || (numberOfReport > 3)) {
			if (cin.fail()) {
				cin.sync();
				cout << "Неккоректный символ! Введите ещё раз" << endl;
			}
			else cout << "Отчета с таким номером нет! Введите ещё раз" << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			cin >> numberOfReport;
		}
		periodOfTheReport(numberOfReport);
		cout << '\n' << '\n';
		cout << "Выберите тип отчета:" << endl;
		cout << "1 - Отчет об украденных блюдах" << endl;
		cout << "2 - Отчет по статистике заказов" << endl;
		cout << "3 - Отчет по динамике цен в меню " << endl;
		cout << "0 - Выйти из программы" << endl;
		cin >> numberOfReport;
	}
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
		myCafe.getOutputErrors().outputErrors(i, "Menu", "Cashbox", "Kitchen");
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

void Report::fillingMapHistory(PeriodOfDate myPeriod, int typeReport) {

	//setlocale(LC_ALL, "Russian");
	//int typeOfReport;
	//PeriodOfDate myPeriod;
	//typeOfReport = reportSelection(myCashbox, myMenu);
	//myPeriod = periodOfTheReport(typeOfReport, myCashbox, myMenu);
	//map <string, map<string, int>> mapFirstReport;
	//ifstream menuF;
	//ifstream cashboxF;
	//ifstream kitchenF;

	//string date1;
	//string  date2;
	//string nameFile;
	//int dd2, mm2, yy2;
	//bool firstOperation = false;
	//int counterOfDay = 0;

	//date1 = myPeriod.getFirstDay().getDate();
	//date2 = myPeriod.getLastDay().getDate();

	//dd2 = myPeriod.getLastDay().getDD();
	//mm2 = myPeriod.getLastDay().getMM();
	//yy2 = myPeriod.getLastDay().getYY();

	//ofstream fileOfReport;

	//if (date1 == date2) {
	//	if (typeOfReport == 1)
	//		nameFile = "stolenDishes-" + myPeriod.getFirstDay().getDate() + ".txt";

	//	if (typeOfReport == 2)
	//		nameFile = "statisticsOfOrders-" + myPeriod.getFirstDay().getDate() + ".txt";

	//	if (typeOfReport == 3)
	//		nameFile = "priceDynamics-" + myPeriod.getFirstDay().getDate() + ".txt";
	//}

	//else {
	//	if (typeOfReport == 1)
	//		nameFile = "stolenDishes-" + myPeriod.getFirstDay().getDate() + '-' + myPeriod.getLastDay().getDate() + ".txt";

	//	if (typeOfReport == 2)
	//		nameFile = "statisticsOfOrders-" + myPeriod.getFirstDay().getDate() + '-' + myPeriod.getLastDay().getDate() + ".txt";

	//	if (typeOfReport == 3)
	//		nameFile = "priceDynamics-" + myPeriod.getFirstDay().getDate() + '-' + myPeriod.getLastDay().getDate() + ".txt";
	//}
	//fileOfReport.open(nameFile);

	//fileOfReport << "За указанный период: " << myPeriod.getFirstDay().getDate() << '-' << myPeriod.getLastDay().getDate() << endl;

	//while ((date1 != date2) || (!firstOperation)) {
	//	fileOfReport << "Отчет за " << date2 << endl;
	//	counterOfDay++;
	//	string nameMenu, nameCashbox, nameKitchen;

	//	nameMenu = "menu-" + date1 + ".txt";
	//	nameCashbox = "cashbox-" + date1 + ".txt";
	//	nameKitchen = "kitchen-" + date1 + ".txt";

	//	menuF.open(nameMenu);
	//	cashboxF.open(nameCashbox);
	//	kitchenF.open(nameKitchen);
	//	//добавить цикл для недельки
	//	try {
	//		myMenu.inputMenu(menuF);
	//		myKitchen.inputKitchen(kitchenF);
	//		myCashbox.inputCashbox(cashboxF);
	//		myMenu.checkDishes(myKitchen.getAllCookedDish(), myCashbox.getAllChecks());
	//		//checkDishInCashbox(myKitchen.allCookedDish, myMenu, myCashbox.allChecks);
	//		//myCafe.myCashbox.outputResult();
	//		//myCafe.myCashbox.inputFindDish();
	//		//fileOfReport << date2<< '\n';
	//		if (typeOfReport == 3) priceBehavior(myPeriod, fileOfReport);
	//		else {
	//			reportGeneration(typeOfReport, myMenu, myCashbox, myKitchen, fileOfReport);
	//			mapFirstReport[date2] = calculation;
	//			fileOfReport << "\n==========================================================================================" << "\n";
	//		}
	//		//myCafe.myReport.reportSelection(myCafe.myCashbox, myCafe.myMenu, fileOfReport);

	//		if ((typeOfReport == 3) && (counterOfDay != 7)) firstOperation = false;
	//		//if (typeOfReport == 2) firstOperation = true;
	//		if (date1 == date2) firstOperation = true;
	//		else {
	//			changeDate(dd2, mm2, yy2);
	//			date2.clear();
	//			date2 = to_string(yy2) + to_string(mm2) + to_string(dd2);
	//			firstOperation = false;
	//		}
	//		if (typeOfReport == 3) firstOperation = true;
	//		menuF.close();
	//		cashboxF.close();
	//		kitchenF.close();
	//	}
	//	catch (int i) {
	//		outputErrors.outputErrors(i, nameMenu, nameCashbox, nameKitchen);
	//		break;
	//	}
	//}
	////myCafe.myMenu.deleteMenu(myCafe.myMenu);
	//fileOfReport.close();

	string firstDate;
	string lastDate;
	bool firstDay = false;
	firstDate = myPeriod.getFirstDay().getDate();
	lastDate = myPeriod.getLastDay().getDate();

	while ((firstDate != lastDate) || (!firstDay)) {//заполнили map (string, Cafe)
		firstDay = true;
		checkKitchenCashboxMenu(firstDate);
		//change date
		if ((typeReport == 3)&&(firstDate != lastDate)) {
			firstDay = false;
			firstDate = lastDate;
		}
	}
	reportGeneration(typeReport);
	//отправить мап на выаолнене отчетов
}

void Report::checkDishInCashbox(Cafe myCafe) {//проверка и вывод на консоль
	bool flag = false;
	Dish myDish;
	Category* foundCategory;
	map<string, int>::iterator it;

	for (int i = 0; i < myCafe.getMyKitchen().getAllCookedDish().size(); i++) {
		if (calculation[myCafe.getMyKitchen().getAllCookedDish()[i].getNameDish()]) {
			calculation[myCafe.getMyKitchen().getAllCookedDish()[i].getNameDish()] = calculation[myCafe.getMyKitchen().getAllCookedDish()[i].getNameDish()] + myCafe.getMyKitchen().getAllCookedDish()[i].getCount();
		}
		else calculation[myCafe.getMyKitchen().getAllCookedDish()[i].getNameDish()] = myCafe.getMyKitchen().getAllCookedDish()[i].getCount();
	}

	for (int i = 0; i < myCafe.getMyCashbox().getAllChecks().size(); i++) {//сравниваем количество блюд на кухне и на кассе
		for (int j = 0; j < myCafe.getMyCashbox().getAllChecks()[i].getDish().size(); j++) {
			for (it = calculation.begin(); it != calculation.end() && !flag; it++) {
				if (myCafe.getMyCashbox().getAllChecks()[i].getDish()[j].getNameDish() == it->first) {
					it->second = it->second - myCafe.getMyCashbox().getAllChecks()[i].getDish()[j].getCount();
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
		foundCategory = myCafe.getMyMenu().findInMenu(it->first, myCafe.getMyMenu().getMenu());
		//loss = loss + it->second * myDish.price;
		int i, y;
		for (i = 0; i < foundCategory->getDishes().size(); i++)
			if (foundCategory->getDishes()[i].getNameDish() == it->first) break;
		loss = loss + it->second * foundCategory->getDishes()[i].getPrice();
	}

	for (int i = 0; i < myCafe.getMyCashbox().getAllChecks().size(); i++) {//ошибка в расчете total
		for (int j = 0; j < myCafe.getMyCashbox().getAllChecks()[i].getDish().size(); j++) {
			//myDish = myMenu.findInMenu(allChecks[i].Dish[j].nameDish);
			foundCategory = myCafe.getMyMenu().findInMenu(myCafe.getMyCashbox().getAllChecks()[i].getDish()[j].getNameDish(), myCafe.getMyMenu().getMenu());
			//totalCheck = totalCheck + allChecks[i].Dish[j].count * myDish.price;
			int l;
			for (l = 0; i < foundCategory->getDishes().size(); l++)
				if (foundCategory->getDishes()[l].getNameDish() == myCafe.getMyCashbox().getAllChecks()[i].getDish()[j].getNameDish()) break;
			totalCheck = totalCheck + myCafe.getMyCashbox().getAllChecks()[i].getDish()[j].getCount() * foundCategory->getDishes()[l].getPrice();
		}
		totalCheck = myCafe.getMyCashbox().getAllChecks()[i].getTotal() - totalCheck;
	}
	//outputResult(fileOfReport, loss, totalCheck);
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