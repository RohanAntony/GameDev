#pragma once

#include <iostream>
#include "LogBase.h"

using std::cout;
using std::cerr;
using std::endl;

class StdLog : public LogBase {
public:
	void debug(string message){
		cout << "DEBUG: " << message << endl;
	}

	void error(string message) {
		cerr << "Error: " << message << endl;
	}
};