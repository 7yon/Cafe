#include "stdafx.h"
#include "Header.h"

void Report::reportGeneration(int typeOfReport,Menu myMenu, Cashbox myCashbox, Kitchen myKitchen, ofstream &fileOfReport) {
	if (typeOfReport == 1){
		checkDishInCashbox(myKitchen.allCookedDish, myMenu, myCashbox.allChecks, fileOfReport);
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
		cout << "\n�������� ������ �� ������� ���������� ��������� �����:" << endl;
		cout << "1 - �� ��������� ���� (������� ����)" << endl;
		cout << "2 - �� ������������ �����" << endl;
		cout << "3 - �� ��������� ������ (������� ���� � 6 �������������� ����) � ������������ �� ����" << endl;
		cout << "4 - �� �������� ������ � ������������ �� ����" << endl;
		cin >> period;
	}
	/*else {
		cout << "������� ��������� ����" << endl;
		cout << "����� : ";
		cin >> dd1;
		cout << "����� (��������: ������ - 1): ";
		cin >> mm1;
		cout << "��� (��������: 2016): ";
		cin >> yy1;

		cout << "������� �������� ����" << endl;
		cout << "�����: ";
		cin >> dd2;
		cout << "����� (��������: ������ - 1): ";
		cin >> mm2;
		cout << "���(��������: 2016): ";
		cin >> yy2;
		myPeriod.firstDay.setDate(dd1, mm1, yy1);
		myPeriod.lastDay.setDate(dd2, mm2, yy2);
	}*/
	if (period == 1) {
		time_t rawtime;
		struct tm timeinfo; 

		time(&rawtime);

		localtime_s(&timeinfo, &rawtime); 
		myPeriod.firstDay.setDate(timeinfo.tm_mday, timeinfo.tm_mon + 1, timeinfo.tm_year + 1900);
		myPeriod.lastDay.setDate(timeinfo.tm_mday, timeinfo.tm_mon + 1, timeinfo.tm_year + 1900);
	}

	if (period == 2) {
		cout << "������� ����" << endl;
		cout << "�����: ";
		cin >> dd1;
		cout << "����� (��������: ������ - 1): ";
		cin >> mm1;
		cout << "���(��������: 2016): ";
		cin >> yy1;
		myPeriod.firstDay.setDate(dd1, mm1, yy1);
		myPeriod.lastDay.setDate(dd1, mm1, yy1);
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
		myPeriod.firstDay.setDate(timeinfo.tm_mday, timeinfo.tm_mon + 1, timeinfo.tm_year + 1900);

		changeDate(dd2, mm2, yy2);
		myPeriod.lastDay.setDate(dd2, mm2, yy2);
	}
	if ((i == 3)||(period == 4)) {
		cout << "������� ��������� ����" << endl;
		cout << "����� : ";
		cin >> dd1; 
		cout << "����� (��������: ������ - 1): ";
		cin >> mm1;
		cout << "��� (��������: 2016): ";
		cin >> yy1;

		cout << "������� �������� ����" << endl;
		cout << "�����: ";
		cin >> dd2;
		cout << "����� (��������: ������ - 1): ";
		cin >> mm2;
		cout << "���(��������: 2016): ";
		cin >> yy2;
		myPeriod.firstDay.setDate(dd1, mm1, yy1);
		myPeriod.lastDay.setDate(dd2, mm2, yy2);
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


	for (i = 0; i < allCategories.size() && !flagFound; i++) {//������ ������ ��� �� ���������� ������� ����� ����������, ���� ������ �������, ���� ��������� � ����������

		ItCategory = mapCategoryAndSubcategory.find(allCategories[i]->nameCategory);
		int space = 0;
		while (space != allCategories[i]->categoryLevel) {
			fileOfReport << '_';
			space++;
		}
		if (ItCategory == mapCategoryAndSubcategory.end()) 
			fileOfReport << allCategories[i]->nameCategory << ' ' << 0;
		else 
			fileOfReport << allCategories[i]->nameCategory << ' ' << mapCategoryAndSubcategory[allCategories[i]->nameCategory];
		fileOfReport << '\n';

		for (int j = 0; j < allCategories[i]->dishes.size(); j++) {//� ��� ���� ����� ������ ��� �����
			ItDishes = mapDishes.find(allCategories[i]->dishes[j].nameDish);
			int space = 0;
			while (space != allCategories[i]->categoryLevel + 1) {
				fileOfReport << '_';
				space++;
			}
			if (ItDishes == mapDishes.end()) 
				fileOfReport << allCategories[i]->dishes[j].nameDish << ' ' << 0;
			else 
				fileOfReport << allCategories[i]->dishes[j].nameDish << ' ' << mapDishes[allCategories[i]->dishes[j].nameDish];
			fileOfReport << '\n';
		}
		if (allCategories[i]->subcategory.size() != 0) {
			outputStatisticsInFile(mapDishes, mapCategoryAndSubcategory, allCategories[i]->subcategory, fileOfReport);
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
	//if (date1 == date2) {//���� ����(������� ��� �� ������)

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
		for (int i = 0; i < myCashbox.allChecks.size(); i++) {
			amountOfRevenue = amountOfRevenue + myCashbox.allChecks[i].total;
			counterOfChecks++;
		}
		//������� �����!!!
		//cout << '\n';
		/*fileOfReport << "�� ��������� ������:" << myPeriod.firstDay.getDate() << '-'<< myPeriod.firstDay.getDate() << endl;*/
		fileOfReport << "����� �������: " << amountOfRevenue << endl;
		fileOfReport << "���������� �������: " << counterOfChecks << endl;
		fileOfReport << "������� ���: " << amountOfRevenue / counterOfChecks << endl;

		for (int i = 0; i < myCashbox.allChecks.size(); i++) {//mapDishes
			for (int j = 0; j < myCashbox.allChecks[i].Dish.size(); j++) {
				Category* foundMyDish;
				foundMyDish = myMenu.findInMenu(myCashbox.allChecks[i].Dish[j].nameDish, myMenu.getMenu());//����� ���������, � ������� ����� � ��������� �����
				ItCategory = mapCategoryAndSubcategory.find(foundMyDish->nameCategory);//��� ��������� ���������� ������������ �����
				if (ItCategory == mapCategoryAndSubcategory.end()) {
					mapCategoryAndSubcategory[foundMyDish->nameCategory] = myCashbox.allChecks[i].Dish[j].count;
				}
				else {
					mapCategoryAndSubcategory[foundMyDish->nameCategory] = ItCategory->second + myCashbox.allChecks[i].Dish[j].count;
				}
				firstSearch = false;
				while ((foundMyDish->ParentCategory != NULL)||(!firstSearch)) {//���� �� �������� � ���������
					firstSearch = true;
					ItDishes = mapDishes.find(myCashbox.allChecks[i].Dish[j].nameDish);//���� � ��� ��������� ����� �� ����
					if (ItDishes == mapDishes.end()) {//���� �� �����, �� ������ ��������
						mapDishes[myCashbox.allChecks[i].Dish[j].nameDish] = myCashbox.allChecks[i].Dish[j].count;
					}
					else {//���� ����� ����� ��������� � ����� �� ���������
						mapDishes[myCashbox.allChecks[i].Dish[j].nameDish] = ItDishes->second + myCashbox.allChecks[i].Dish[j].count;
					}
					while(foundMyDish->ParentCategory != NULL) {
						foundMyDish = foundMyDish->ParentCategory;//������� �� ������������ ���������
						ItCategory = mapCategoryAndSubcategory.find(foundMyDish->nameCategory);//��� ��������� ���������� ������������ �����
						if (ItCategory == mapCategoryAndSubcategory.end()) {
							mapCategoryAndSubcategory[foundMyDish->nameCategory] = myCashbox.allChecks[i].Dish[j].count;
						}
						else {
							mapCategoryAndSubcategory[foundMyDish->nameCategory] = ItCategory->second + myCashbox.allChecks[i].Dish[j].count;
						}
					}
				}
			}
		}
		//������ �� ������ � ������ � ����
		fileOfReport << '\n';
		outputStatisticsInFile(mapDishes, mapCategoryAndSubcategory, myMenu.getMenu(), fileOfReport);
		myCashbox.allChecks.clear();
		myMenu.deleteMenu(myMenu.getMenu());
	//}
	//else {//�����-�� ������
	//	/////////////////////////////
	//}
	//fileOfReport.close();
}

int Report::reportSelection(Cashbox myCashbox, Menu myMenu) {
	int numberOfReport;
	cout <<'\n'<< '\n';
	cout << "�������� ��� ������:"<< endl;
	cout << "1 - ����� �� ���������� ������" << endl;
	cout << "2 - ����� �� ���������� �������" << endl;
	cout << "3 - ����� �� �������� ��� � ���� " << endl;
	cout << "0 - ����� �� ���������" << endl;

	cin >> numberOfReport;
	while ((cin.fail())||(numberOfReport > 3)) {
		if (cin.fail()){
			cin.sync();
			cout << "������������ ������! ������� ��� ���" << endl;
		}
		else cout << "������ � ����� ������� ���! ������� ��� ���" << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> numberOfReport;
	}
	//if (numberOfReport == 3) priceBehavior();
	//periodOfTheReport(numberOfReport, myCashbox, myMenu);
	//else
	return numberOfReport;
}

void Report::priceBehavior(PeriodOfDate myPeriod) { //3 �����

	Cafe myCafe;

	ifstream menuBegin;
	ifstream menuEnd;
	ofstream fileOfReport;
	string nameFile = "priceDynamics-" + myPeriod.firstDay.getDate() + '-' + myPeriod.lastDay.getDate() + ".txt";
	fileOfReport.open(nameFile);
	fileOfReport << "priceDynamics-" + myPeriod.firstDay.getDate() + '-' + myPeriod.lastDay.getDate();
	bool finddish;
	map <string, float> menumapDateBegin;
	map <string, float> ::iterator itMapBegin;
	map <string, float> ::iterator itMapEnd;
	string nameBegin = "menu-" + myPeriod.firstDay.getDate() + ".txt";
	string nameEnd = "menu-" + myPeriod.lastDay.getDate() + ".txt";
	menuBegin.open(nameBegin);
	menuEnd.open(nameEnd);
	try {
		myCafe.myMenu.inputMenu(menuBegin);
		for (itMapBegin = myCafe.myMenu.menumap.begin(); itMapBegin != myCafe.myMenu.menumap.end(); itMapBegin++) {
			menumapDateBegin[itMapBegin->first] = itMapBegin->second;
		}
		myCafe.myMenu.menumap.clear();
		myCafe.myMenu.inputMenu(menuEnd);
	}
	catch (int i) {
		myCafe.outputErrors.outputErrors(i, "Menu", "Cashbox", "Kitchen");
	}

	for (itMapBegin = myCafe.myMenu.menumap.begin(); itMapBegin != myCafe.myMenu.menumap.end(); itMapBegin++) {
		for (itMapEnd = menumapDateBegin.begin(); itMapEnd != menumapDateBegin.end(); itMapEnd++) {
			if (itMapEnd->first == itMapBegin->first) {
				fileOfReport << itMapBegin->first << "  ��������� ����:  ";
				fileOfReport << abs(myCafe.myMenu.menumap[itMapBegin->first] - menumapDateBegin[itMapBegin->first]);
				fileOfReport << " � ���������:" << abs((menumapDateBegin[itMapBegin->first] - myCafe.myMenu.menumap[itMapBegin->first]) * 100 / menumapDateBegin[itMapBegin->first]) << endl;
			}
		}
	}

	fileOfReport << endl;
	for (itMapBegin = myCafe.myMenu.menumap.begin(); itMapBegin != myCafe.myMenu.menumap.end(); itMapBegin++) {
		finddish = false;
		for (itMapEnd = menumapDateBegin.begin(); itMapEnd != menumapDateBegin.end(); itMapEnd++) {
			if (itMapEnd->first == itMapBegin->first) {
				finddish = true;
			}
		}
		if (!finddish) {
			fileOfReport << "��������� �����: " << itMapBegin->first << endl;
		}
	}
	for (itMapEnd = menumapDateBegin.begin(); itMapEnd != menumapDateBegin.end(); itMapEnd++) {
		finddish = false;
		for (itMapBegin = myCafe.myMenu.menumap.begin(); itMapBegin != myCafe.myMenu.menumap.end(); itMapBegin++) {
			if (itMapBegin->first == itMapEnd->first) {
				finddish = true;
			}
		}
		if (!finddish) {
			fileOfReport << "������� �����: " << itMapEnd->first << endl;
		}
	}
	//reportoutprice.close();
}