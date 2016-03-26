#include "stdafx.h"
#include "Report.h"

//void Report::createReport(Menu myMenu, Cashbox myCashbox, Kitchen myKitchen, Error outputErrors) {
//
//	//SetConsoleCP(1251);
//	//SetConsoleOutputCP(1251);
//	//int typeOfReport;
//	//PeriodOfDate myPeriod;
//	//typeOfReport = reportSelection(myCashbox, myMenu);
//	//myPeriod = periodOfTheReport(typeOfReport, myCashbox, myMenu);
//
//	//SetConsoleCP(1251);
//	//SetConsoleOutputCP(1251);
//
//	//ifstream menuF;
//	//ifstream cashboxF;
//	//ifstream kitchenF;
//
//	//string date1;
//	//string  date2;
//	//string nameFile;
//	//int dd2, mm2, yy2;
//	//bool firstOperation = false;
//	//int counterOfDay = 0;
//
//	//date1 = myPeriod.firstDay.getDate();
//	//date2 = myPeriod.lastDay.getDate();
//
//	//dd2 = myPeriod.lastDay.getDD();
//	//mm2 = myPeriod.lastDay.getMM();
//	//yy2 = myPeriod.lastDay.getYY();
//
//	//ofstream fileOfReport;
//
//	//if (date1 == date2) {
//	//	if (typeOfReport == 1)
//	//		nameFile = "stolenDishes-" + myPeriod.firstDay.getDate() + ".txt";
//
//	//	if (typeOfReport == 2)
//	//		nameFile = "statisticsOfOrders-" + myPeriod.firstDay.getDate() + ".txt";
//
//	//	if (typeOfReport == 3)
//	//		nameFile = "priceDynamics-" + myPeriod.firstDay.getDate() + ".txt";
//	//}
//
//	//else {
//	//	if (typeOfReport == 1)
//	//		nameFile = "stolenDishes-" + myPeriod.firstDay.getDate() + '-' + myPeriod.lastDay.getDate() + ".txt";
//
//	//	if (typeOfReport == 2)
//	//		nameFile = "statisticsOfOrders-" + myPeriod.firstDay.getDate() + '-' + myPeriod.lastDay.getDate() + ".txt";
//
//	//	if (typeOfReport == 3)
//	//		nameFile = "priceDynamics-" + myPeriod.firstDay.getDate() + '-' + myPeriod.lastDay.getDate() + ".txt";
//	//}
//	//fileOfReport.open(nameFile);
//
//	//fileOfReport << "«а указанный период:" << myPeriod.firstDay.getDate() << '-' << myPeriod.lastDay.getDate() << endl;
//
//	//while ((date1 != date2)||(!firstOperation)){
//
//	//	counterOfDay++;
//	//	string nameMenu, nameCashbox, nameKitchen;
//
//	//	nameMenu = "menu-" + date1 + ".txt";
//	//	nameCashbox = "cashbox-" + date1 + ".txt";
//	//	nameKitchen = "kitchen-" + date1 + ".txt";
//
//	//	menuF.open(nameMenu);
//	//	cashboxF.open(nameCashbox);
//	//	kitchenF.open(nameKitchen);
//	//	//добавить цикл дл€ недельки
//	//	try {
//	//		myMenu.inputMenu(menuF);
//	//		myKitchen.inputKitchen(kitchenF);
//	//		myCashbox.inputCashbox(cashboxF);
//	//		myMenu.checkDishes(myKitchen.allCookedDish, myCashbox.allChecks);
//	//		//checkDishInCashbox(myKitchen.allCookedDish, myMenu, myCashbox.allChecks);
//	//		//myCafe.myCashbox.outputResult();
//	//		//myCafe.myCashbox.inputFindDish();
//	//		//fileOfReport << date2<< '\n';
//	//		if (typeOfReport == 3) priceBehavior(myPeriod);
//	//		else {
//	//			reportGeneration(typeOfReport, myMenu, myCashbox, myKitchen, fileOfReport);
//	//			fileOfReport << "\n==========================================================================================" << "\n";
//	//		}
//	//		//myCafe.myReport.reportSelection(myCafe.myCashbox, myCafe.myMenu, fileOfReport);
//
//	//		if ((typeOfReport == 3) && (counterOfDay != 7)) firstOperation = false;
//	//		//if (typeOfReport == 2) firstOperation = true;
//	//		if (date1 == date2) firstOperation = true;
//	//		else {
//	//			changeDate(dd2, mm2, yy2);
//	//			date2.clear();
//	//			date2 = to_string(yy2) + to_string(mm2) + to_string(dd2);
//	//			firstOperation = false;
//	//		}
//	//		if (typeOfReport == 3) firstOperation = true;
//	//		menuF.close();
//	//		cashboxF.close();
//	//		kitchenF.close();
//	//	}
//	//	catch (int i) {
//	//		outputErrors.outputErrors(i, nameMenu, nameCashbox, nameKitchen);
//	//		break;
//	//	}
//	//}
//	////myCafe.myMenu.deleteMenu(myCafe.myMenu);
//	//fileOfReport.close();
//}

Menu Cafe::getMyMenu() {
	return myMenu;
}
Cashbox Cafe::getMyCashbox() {
	return myCashbox;
}
Kitchen Cafe::getMyKitchen() {
	return myKitchen;
}
Error Cafe::getOutputErrors() {
	return outputErrors;
}
//Report Cafe::getMyReport() {
//	return myReport;
//}
void Cafe::setMyMenu(Menu thisMenu) {
	myMenu = thisMenu;
}
void Cafe::setMyCashbox(Cashbox thisCashbox) {
	myCashbox = thisCashbox;
}
void Cafe::setMyKitchen(Kitchen thisKitchen) {
	myKitchen = thisKitchen;
}
//void Cafe::setMyReportn(Report thisReport) {
//	myReport = thisReport;
//}