#include "stdafx.h"
#include "Header.h"

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

	date1 = myPeriod.firstDay.getDate();
	date2 = myPeriod.lastDay.getDate();

	dd2 = myPeriod.lastDay.getDD();
	mm2 = myPeriod.lastDay.getMM();
	yy2 = myPeriod.lastDay.getYY();

	ofstream fileOfReport;

	if (date1 == date2) {
		if (typeOfReport == 1)
			nameFile = "stolenDishes-" + myPeriod.firstDay.getDate() + ".txt";

		if (typeOfReport = 2)
			nameFile = "statisticsOfOrders-" + myPeriod.firstDay.getDate() + ".txt";

		if (typeOfReport == 3)
			nameFile = "priceDynamics-" + myPeriod.firstDay.getDate() + ".txt";
	}

	else {
		if (typeOfReport == 1)
			nameFile = "stolenDishes-" + myPeriod.firstDay.getDate() + myPeriod.lastDay.getDate() + ".txt";

		if (typeOfReport = 2)
			nameFile = "statisticsOfOrders-" + myPeriod.firstDay.getDate() + myPeriod.lastDay.getDate() + ".txt";

		if (typeOfReport == 3)
			nameFile = "priceDynamics-" + myPeriod.firstDay.getDate() + myPeriod.lastDay.getDate() + ".txt";
	}
	fileOfReport.open(nameFile);

	fileOfReport << "За указанный период:" << myPeriod.firstDay.getDate() << '-' << myPeriod.lastDay.getDate() << endl;
	while ((date1 != date2)||(!firstOperation)){

		string nameMenu, nameCashbox, nameKitchen;

		nameMenu = "menu-" + date1 + ".txt";
		nameCashbox = "cashbox-" + date1 + ".txt";
		nameKitchen = "kitchen-" + date1 + ".txt";

		menuF.open(nameMenu);
		cashboxF.open(nameCashbox);
		kitchenF.open(nameKitchen);

		try {
			myMenu.inputMenu(menuF);
			myKitchen.inputKitchen(kitchenF);
			myCashbox.inputCashbox(cashboxF);
			myMenu.checkDishes(myKitchen.allCookedDish, myCashbox.allChecks);
			myCashbox.checkDishInCashbox(myKitchen.allCookedDish, myMenu);
			//myCafe.myCashbox.outputResult();
			//myCafe.myCashbox.inputFindDish();
			fileOfReport << date2<< '\n';
			reportGeneration(typeOfReport, myMenu, myCashbox, myKitchen, fileOfReport);
			fileOfReport << "==========================================================================================" << "\n";
			//myCafe.myReport.reportSelection(myCafe.myCashbox, myCafe.myMenu, fileOfReport);
		}
		catch (int i) {
			outputErrors.outputErrors(i);
		}

		if (date1 == date2) firstOperation = true;
		else {
			changeDate(dd2, mm2, yy2);
			date2.clear();
			date2 = to_string(yy2) + to_string(mm2) + to_string(dd2);
			firstOperation = false;
		}
		menuF.close();
		cashboxF.close();
		kitchenF.close();
	}
	//myCafe.myMenu.deleteMenu(myCafe.myMenu);
	fileOfReport.close();
}