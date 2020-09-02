#include "date.h"

#include <tuple>
#include <sstream>
#include <iomanip>

using namespace std;

Date::Date(int year, int month, int day)
	  : year_(year)
	  , month_(month)
	  , day_(day)
	  {}

bool Date::operator==(const Date& rhs) const
{
	return tie(day_, month_, year_)
	    == tie(rhs.day_, rhs.month_, rhs.year_);
}

bool Date::operator!=(const Date& rhs) const
{
	return !(*this == rhs);
}

bool Date::operator<(const Date& rhs) const
{
	ostringstream left, right;
	left << *this;
	right << rhs;

	return left.str() < right.str();
}

bool Date::operator<=(const Date& rhs) const
{
	ostringstream left, right;
	left << *this;
	right << rhs;

	return left.str() <= right.str();
}

bool Date::operator>(const Date& rhs) const
{
	return !(*this <= rhs);
}

bool Date::operator>=(const Date& rhs) const
{
	return !(*this < rhs);
}

int Date::GetDay() const
{
	return day_;
}

int Date::GetMonth() const
{
	return month_;
}

int Date::GetYear() const
{
	return year_;
}

Date ParseDate(istream& is)
{
	int year, month, day;
	is >> ws >> year;
	is.get();
	is >> month;
	is.get();
	is >> day;
	return Date{year, month, day};
}

ostream& operator<<(ostream& os, const Date& date)
{
	os << date.GetYear() << "-"
	   << setfill('0') << setw(2) << date.GetMonth() << "-"
	   << setfill('0') << setw(2) << date.GetDay();
	return os;
}