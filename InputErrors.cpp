#include "stdafx.h"
#include "Header.h"

void checkDishes(map <string, float> menuMap, vector <cookedDish> kitchen, vector <check> cashbox){
	map <string, float>::iterator itMap;
	for (int i = 0; i < kitchen.size(); i++){
		itMap = menuMap.find(kitchen[i].nameDish);
		if (itMap == menuMap.end()) 
			throw 7;
	}

	for (int i = 0; i < cashbox.size(); i++){
		for (int j = 0; j < cashbox[i].Dish.size(); j++){
			itMap = menuMap.find(cashbox[i].Dish[j].nameDish);
			if (itMap == menuMap.end()) 
				throw 8;
		}
	}  
}

map <string, float> inputErrors(string str, int idetidentifierFile) {
	int i;
	float number;
	string nameOfTheDish;
	int counterOfPoint = 0;
	map <string, float> correctString;
	size_t countPoint, countEqual, countNum;
	bool flagNumber = false, flagError = false;
	
	countEqual = count(str.begin(), str.end(), '=');
	if ((countEqual == 1) && (str.find("Заказ") == string::npos)) {//если "=" - 1 и это не заказ
		nameOfTheDish = str.substr(0, str.find("="));//подстрока входящей строки с начала и до "="
		if (nameOfTheDish.empty()) 
			throw 1;
		i = 0;
		while (nameOfTheDish[i] == ' ') 
			i++;
		nameOfTheDish.erase(0, i);
		i = nameOfTheDish.size();
		while (nameOfTheDish[i - 1] == ' ') 
			i--;
		nameOfTheDish.erase(i, nameOfTheDish.size());//удалили пробелы до и после названия
		countPoint = count(str.begin(), str.end(), '.');
		if (countPoint == 0 || countPoint == 1) {
			str.erase(0, str.find('=') + 1);//обрезаем все до "=" включительно
			counterOfPoint = 0;
			flagNumber = false;
			flagError = false;
			for (int i = 0; i < str.size() && !flagError; i++) {
				if ((str[i] == ' ') && (!flagNumber)) {//пропускаем пробелы после "="
					while (str[i] == ' ') 
						i++;
				}
				else if ((str[i] >= '0') && (str[i] <= '9') && ((counterOfPoint == 0) || (counterOfPoint == 1)) && (idetidentifierFile == 1)) {//если встретили число и количество точек допустимое, тогда флаг true и в числе не может быть пробелов
					flagNumber = true;
				}
				else if ((str[i] >= '0') && (str[i] <= '9') && ((idetidentifierFile == 2) || (idetidentifierFile == 3))) {
					flagNumber = true;
				}
				else if ((str[i] == '.') && (idetidentifierFile == 1)) counterOfPoint++;
				else throw idetidentifierFile;
			}

			if ((!flagError) && (!str.empty())) {//если ошибок не обнаружено
				stringstream stream;
				stream << str;
				stream >> number;
				correctString[nameOfTheDish] = number;
				return correctString;
			}
			else throw idetidentifierFile;
		}
		else throw idetidentifierFile;
	}

	else if (countEqual > 1) 
			throw 1;
		 else {//знака "=" нет
			countPoint = count(str.begin(), str.end(), ':');
			if ((countPoint == 1) && (idetidentifierFile == 3) && (countEqual == 0)) {
				if (str.find("total") != string::npos) {
					nameOfTheDish = str.substr(0, str.find(":"));
					if (nameOfTheDish.empty()) 
						throw 1;
					nameOfTheDish.erase(nameOfTheDish.find("total"), nameOfTheDish.find("total") + 5);
					while (nameOfTheDish.find(' ') != string::npos) nameOfTheDish.erase(nameOfTheDish.find(' '), ' ');
					if (nameOfTheDish.empty()) {
						str.erase(0, str.find(':') + 1);//оставили только число
						counterOfPoint = 0;
						flagNumber = false;
						flagError = false;
						for (int i = 0; i < str.size() && !flagError; i++) {
							if ((str[i] == ' ') && (!flagNumber)) {
								while (str[i] == ' ') 
									i++;
							}
							else if ((str[i] >= '0') && (str[i] <= '9') && ((counterOfPoint == 0) || (counterOfPoint == 1))) {
								flagNumber = true;
							}
							else if ((str[i] == '.') && (i != 0)) 
								counterOfPoint++;
								else flagError = true;
						}
						if ((!flagError) && (!str.empty())) {
							stringstream stream;
							stream << str;
							stream >> number;
							correctString[nameOfTheDish] = number;
							return correctString;
						}
						else throw idetidentifierFile;
					}
					else throw idetidentifierFile;
				}
				else  throw idetidentifierFile;
			}
		countNum = count(str.begin(), str.end(), '№');
		if ((countNum == 1) && (idetidentifierFile == 3) && (countEqual == 0) && (countPoint == 0)) {
			if (str.find("Заказ" || "заказ") == string::npos) {
				nameOfTheDish = str.substr(0, str.find('№'));
				nameOfTheDish.erase(nameOfTheDish.find("Заказ"), nameOfTheDish.find("Заказ") + 5);
				while (nameOfTheDish.find(' ') != string::npos) 
					nameOfTheDish.erase(nameOfTheDish.find(' '), ' ');
				if (nameOfTheDish.empty()) {
					str.erase(0, str.find('№') + 1);
					flagNumber = false;
					flagError = false;
					for (int i = 0; i < str.size() && !flagError; i++) {
						if ((str[i] == ' ') && (!flagNumber)) {
							while (str[i] == ' ') 
								i++;
						}
						else if ((str[i] >= '0') && (str[i] <= '9')) {
							flagNumber = true;
						}
						else throw idetidentifierFile;
					}
					if ((!flagError) && (!str.empty())) {
						stringstream stream;
						stream << str;
						stream >> number;
						correctString[nameOfTheDish] = number;
						return correctString;
					}
					else throw idetidentifierFile;
				}
				else throw idetidentifierFile;
			}
			else throw idetidentifierFile;
		}
		else throw idetidentifierFile;
	}
}