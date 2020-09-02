#include "date.h"
#include "test_runner.h"

#include <sstream>
using namespace std;

void TestParseDate()
{
	{
		istringstream is{"2000-1-1"};
		AssertEqual(ParseDate(is), Date{2000, 1, 1}, "Correct date");
	}
	{
		istringstream is{"   2000-1-1"};
		AssertEqual(ParseDate(is), Date{2000, 1, 1}, "Correct date with leading spaces");
	}
}