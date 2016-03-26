#pragma once

#include "stdafx.h"
#include <windows.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <iterator>
#include <regex>
#include <vld.h> 
#include "conio.h"
#include <cstdlib>
#include <ctime>

#include "Menu.h"
#include "Cashbox.h"
#include "Kitchen.h"
#include "Cafe.h"
#include "Report.h"
#include "Error.h"

using namespace std;

class Interface {
	Cafe myCafe;
public:
	Cafe getMyCafe() {
		return myCafe;
	}
};