#ifndef GALIB_LOGBASE_HEADER
#define GALIB_LOGBASE_HEADER

#include <string>

using std::string;

namespace {
	class LogBase {
	public:
		virtual void debug(string message) = 0;
		virtual void error(string message) = 0;
	};
}

#endif