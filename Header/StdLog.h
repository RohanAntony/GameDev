#ifndef GALIB_STDLOG_HEADER
#define GALIB_STDLOG_HEADER

#include <iostream>
#include "LogBase.h"

using std::cout;
using std::cerr;
using std::endl;

namespace GaLib {
	class StdLog : public LogBase {
	public:
		void debug(string message) {
			cout << "DEBUG: " << message << endl;
		}

		void error(string message) {
			cerr << "Error: " << message << endl;
		}
	};
}

#endif