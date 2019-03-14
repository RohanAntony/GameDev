#pragma once

#include <string>

using std::string;

class LogBase {
public:
	virtual void debug(string message) = 0;
	virtual void error(string message) = 0;
};