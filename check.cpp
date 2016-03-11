#include "stdafx.h"
#include "Header.h"

void checkDish(vector <check> cashbox, vector <cookedDish> kitchen, map <string, float> menuMap, map<string, int> &calculation, float &totalCheck, float &loss) {//проверка и вывод на консоль
	bool flag = false;
	map <string, int>::iterator it;

	for (int i = 0; i < kitchen.size(); i++){
		if (calculation[kitchen[i].nameDish]){
			calculation[kitchen[i].nameDish] = calculation[kitchen[i].nameDish] + kitchen[i].count;
		}
	    else calculation[kitchen[i].nameDish] = kitchen[i].count;
	}

	for (int i = 0; i < cashbox.size(); i++) {//сравниваем количество блюд на кухне и на кассе
		for (int j = 0; j < cashbox[i].Dish.size(); j++) {
			for (it = calculation.begin(); it!= calculation.end() && !flag; it++) {
				if (cashbox[i].Dish[j].nameDish == it->first) {
					it->second = it->second - cashbox[i].Dish[j].count;
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
	cout << "Количество потерянных блюд:" << endl;
	cout << endl;

	for (it = calculation.begin(); it != calculation.end() && !flag; it++) {
		loss = loss + it->second * menuMap[it->first];
	}

	for (int i = 0; i < cashbox.size(); i++) {//ошибка в расчете total
		for (int j = 0; j < cashbox[i].Dish.size(); j++) {
			totalCheck = totalCheck + cashbox[i].Dish[j].count * menuMap[cashbox[i].Dish[j].nameDish];
		}
		totalCheck = cashbox[i].total - totalCheck;
	}
}
