#pragma once
#include "stdafx.h"
#include "header.h"

class Cafe {
	Menu myMenu;
	Cashbox myCashbox;
	Kitchen myKitchen;
	Error outputErrors;
	Report myReport;
public:
	Menu getMyMenu();
	Cashbox getMyCashbox();
	Kitchen getMyKitchen();
	Error getOutputErrors();
	Report getMyReport();
	void setMyMenu(Menu thisMenu);
	void setMyCashbox(Cashbox thisCashbox);
	void setMyKitchen(Kitchen thisKitchen);
	void setMyReportn(Report thisReport);
};