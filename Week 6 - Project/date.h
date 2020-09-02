#pragma once

#include <iostream>

using namespace std;

class Date
{
public:
	
	Date(int year, int month, int day);
	bool operator==(const Date& rhs) const;
	bool operator!=(const Date& rhs) const;
	bool operator<(const Date& rhs) const;
	bool operator<=(const Date& rhs) const;
	bool operator>(const Date& rhs) const;
	bool operator>=(const Date& rhs) const;
	Date& operator=(const Date& rhs);

	int GetDay() const;
	int GetMonth() const;
	int GetYear() const;

private:
	int year_;
	int month_;
	int day_;
};

Date ParseDate(istream& is);

ostream& operator<<(ostream& os, const Date& date);

// void TestParseDate();