#include "stdafx.h"
#include "Header.h"

PeriodOfDate Report::periodOfTheReport(int i) {
	int period;
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
		cout << "Введите дату" << endl;
		cout << "Число (например: 01 или 27): ";
		cin >> dd1;
		cout << "Месяц (например: Январь - 01): ";
		cin >> mm1;
		cout << "Год(например: 2016): ";
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
		cout << "Введите начальную дату" << endl;
		cout << "Число (например: 01 или 27): ";
		cin >> dd1;
		cout << "Месяц (например: Январь - 01): ";
		cin >> mm1;
		cout << "Год(например: 2016): ";
		cin >> yy1;

		cout << "Введите конечную дату" << endl;
		cout << "Число (например: 01 или 27): ";
		cin >> dd2;
		cout << "Месяц (например: Январь - 01): ";
		cin >> mm2;
		cout << "Год(например: 2016): ";
		cin >> yy2;
		myPeriod.firstDay.setDate(dd1, mm1, yy1);
		myPeriod.lastDay.setDate(dd2, mm2, yy2);
	}

	return myPeriod;
}


void Report::statisticsOfOrders() {

}

void Report::reportSelection() {
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
			cout << "Неккоректный символ! Введите ещё раз." << endl;
		}
		else cout << "Отчета с таким номером нет! Введите ещё раз." << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> numberOfReport;
	}
	periodOfTheReport(numberOfReport);
}
