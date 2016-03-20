#include "stdafx.h"
#include "Header.h"

void Report::periodOfTheReport(int i, Cashbox myCashbox, Menu myMenu) {
	int period;
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
	if (period == 1) {
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
		myPeriod.firstDay.setDate(timeinfo.tm_mday, timeinfo.tm_mon + 1, timeinfo.tm_year + 1900);
		myPeriod.lastDay.setDate(timeinfo.tm_mday, timeinfo.tm_mon + 1, timeinfo.tm_year + 1900);
	}

	if (period == 2) {
		cout << "������� ����" << endl;
		cout << "����� (��������: 01 ��� 27): ";
		cin >> dd1;
		cout << "����� (��������: ������ - 01): ";
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
		myPeriod.firstDay.setDate(timeinfo.tm_mday, timeinfo.tm_mon + 1, timeinfo.tm_year + 1900);
		myPeriod.lastDay.setDate(timeinfo.tm_mday - 6, timeinfo.tm_mon + 1, timeinfo.tm_year + 1900);
	}
	if ((i == 3)||(period == 4)) {
		cout << "������� ��������� ����" << endl;
		cout << "����� (��������: 01 ��� 27): ";
		cin >> dd1;
		cout << "����� (��������: ������ - 01): ";
		cin >> mm1;
		cout << "���(��������: 2016): ";
		cin >> yy1;

		cout << "������� �������� ����" << endl;
		cout << "����� (��������: 01 ��� 27): ";
		cin >> dd2;
		cout << "����� (��������: ������ - 01): ";
		cin >> mm2;
		cout << "���(��������: 2016): ";
		cin >> yy2;
		myPeriod.firstDay.setDate(dd1, mm1, yy1);
		myPeriod.lastDay.setDate(dd2, mm2, yy2);
	}

	statisticsOfOrders(myPeriod, myCashbox, myMenu);
}

void Report::outputStatisticsInFile(map <string, int> mapDishes, map <string, int> mapCategoryAndSubcategory, vector <Category*> allCategories) {
	bool flagFound = false;
	Category* foundCategory;
	map <string, int>::iterator ItDishes;
	map <string, int>::iterator ItCategory;
	int i;

	ofstream fileOfReport;
	fileOfReport.open("statisticsOfOrders.txt");

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
			while (space != allCategories[i]->categoryLevel) {
				fileOfReport << '_';
				space++;
			}
			if (ItDishes == mapDishes.end()) 
				fileOfReport << allCategories[i]->dishes[j].nameDish << ' ' << 0;
			else 
				fileOfReport << allCategories[i]->nameCategory << ' ' << mapDishes[allCategories[i]->dishes[j].nameDish];
			fileOfReport << '\n';
		}
		if (allCategories[i]->subcategory.size() != 0) {
			fileOfReport.close();
			break;
			//outputStatisticsInFile(mapDishes, mapCategoryAndSubcategory, allCategories[i]->subcategory);
		}
	}
	fileOfReport.close();
}

void Report::statisticsOfOrders(PeriodOfDate myPeriod, Cashbox myCashbox, Menu myMenu) {
	string date1;
	string  date2;
	bool firstSearch = false;
	date1 = myPeriod.firstDay.getDate();
	date2 = myPeriod.lastDay.getDate();
	if (date1 == date2) {//���� ����
		string nameFile;
		ifstream myOrder;
		float amountOfRevenue = 0;
		int counterOfChecks = 0;

		nameFile = "orders-" + myPeriod.firstDay.getDate();
		myOrder.open(nameFile);

		map <string, int> mapDishes;
		map <string, int> mapCategoryAndSubcategory;
		map <string, int>::iterator ItDishes;
		map <string, int>::iterator ItCategory;

		ItDishes = mapDishes.begin();
		ItCategory = mapCategoryAndSubcategory.begin();
		for (int i = 0; i < myCashbox.allChecks.size(); i++) {
			amountOfRevenue = amountOfRevenue + myCashbox.allChecks[i].total;
			counterOfChecks++;
		}

		cout << '\n';
		cout << "�� ��������� ������:" << endl;
		cout << "����� �������: " << amountOfRevenue << endl;
		cout << "���������� �������: " << counterOfChecks << endl;
		cout << "������� ���: " << amountOfRevenue / counterOfChecks << endl;

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
					if (foundMyDish->ParentCategory != NULL)
						foundMyDish = foundMyDish->ParentCategory;//������� �� ������������ ���������
				}
				//mapCategoryAndSubcategory[foundMyDish->nameCategory] = 0;
			}
		}
		//������ �� ������ � ������ � ����
		outputStatisticsInFile(mapDishes, mapCategoryAndSubcategory, myMenu.getMenu());
	}
	else {//�����-�� ������

		/////////////////////////////
	}
}

void Report::reportSelection(Cashbox myCashbox, Menu myMenu) {
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
	periodOfTheReport(numberOfReport, myCashbox, myMenu);
}
