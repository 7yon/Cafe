#include "stdafx.h"
#include "Header.h"

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
Report Cafe::getMyReport() {
	return myReport;
}
void Cafe::setMyMenu(Menu thisMenu) {
	myMenu = thisMenu;
}
void Cafe::setMyCashbox(Cashbox thisCashbox) {
	myCashbox = thisCashbox;
}
void Cafe::setMyKitchen(Kitchen thisKitchen) {
	myKitchen = thisKitchen;
}
void Cafe::setMyReportn(Report thisReport) {
	myReport = thisReport;
}