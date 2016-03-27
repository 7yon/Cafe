
#include "stdafx.h"
//#include "header.h"
#include "Cashbox.h"

class Dish {
	string nameDish;
	float price;
public:
	string getNameDish();
	float getPrice();
	void setPrice(int myPrice);
	void setNameDish(string myDishName);
};

class Category {
	int categoryLevel;
	string nameCategory;
	Category *ParentCategory;
	vector <Dish> dishes;
	vector <Category*> subcategory;
public:
	int getCategoryLevel();
	string getNameCategory();
	Category* getParentCategory();
	vector <Dish> getDishes();
	vector <Category*> getSubcategory();
	void setCategoryLevel(int mycategoryLevel);
	void setNameCategory(string myNameCategory);
	void setParentCategory(Category* myParentCategory);
	void setDishes(Dish myDishes);
	void setSubcategory(Category* mySubcategory);
};

class Menu {
	vector <Category*> allCategories;
	map <string, float> menumap;
public:
	vector <Category*> getMenu();
	map <string, float> getMenuMap();
	void clearMenuMap();
public:
	~Menu() {
		//deleteMenu(allCategories);
	}
	Category* findInMenu(string str, vector <Category*> allCategories);
	Dish checkMenuForErrors(string str);
	int numberOfSpace(string str);
	void inputMenu(ifstream &menuF);
	void checkDishes(vector <cookedDish> allCookedDish, vector <Check> allChecks);
	//void deleteMenu(vector <Category*> allCategories);
};