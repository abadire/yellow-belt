#include "phone_number.h"

#include <stdexcept>
#include <sstream>
#include <iostream>

PhoneNumber::PhoneNumber(const string &international_number)
{
	istringstream is(international_number);

	char sign = is.get();
	getline(is, country_code_, '-');
	getline(is, city_code_, '-');
	getline(is, local_number_);

	if (sign != '+' || country_code_.empty() ||
	city_code_.empty() || local_number_.empty())
	throw invalid_argument("Error!");
}

string PhoneNumber::GetCountryCode() const
{
	return country_code_;
}

string PhoneNumber::GetCityCode() const
{
	return city_code_;
}

string PhoneNumber::GetLocalNumber() const
{
	return local_number_;
}

string PhoneNumber::GetInternationalNumber() const
{
	return "+" + country_code_ + "-" + city_code_ + "-" + local_number_;
}

int main()
{
	PhoneNumber a("+7-1233");
	cout << a.GetInternationalNumber();
	return 0;
}