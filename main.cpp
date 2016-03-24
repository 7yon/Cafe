#include "stdafx.h"
#include "Header.h"

int main()
{

	Cafe myCafe;
	myCafe.myReport.createReport(myCafe.myMenu, myCafe.myCashbox, myCafe.myKitchen, myCafe.outputErrors);

	return 0;
}