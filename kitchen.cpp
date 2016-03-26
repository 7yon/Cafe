#include "stdafx.h"
#include "Header.h"


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
			dishes.setNameDish(match.str(1)); 
			dishes.setCount(stoi(match.str(2)));
			allCookedDish.push_back(dishes);
			dishes.getNameDish().clear();
			dishes.setCount(0);
			checksyntax = true;
		}
		if (!checksyntax)
			throw 2;
	}
}

string cookedDish::getNameDish() {
	return nameDish;
}
int cookedDish::getCount() {
	return count;
}
string cookedDish::setNameDish(string myNameDish) {
	nameDish = myNameDish;
}
int cookedDish::setCount(int myCount) {
	count = myCount;
}

vector <cookedDish> Kitchen::getAllCookedDish() {
	return allCookedDish;
}
void Kitchen::setAllCookedDish(cookedDish myCookedDish) {
	allCookedDish.push_back(myCookedDish);
}
void Kitchen::clearAllCookedDish() {
	allCookedDish.clear();
}