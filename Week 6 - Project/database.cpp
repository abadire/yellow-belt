#include "database.h"
#include <exception>

void Database::Add(const Date& date, const string& event)
{
	if (dateToEvent.count(date) == 0)
	{
		dateToEvent[date] = {event};
	}
	else
	{
		auto& eventList = dateToEvent[date];
		if (end(eventList) == 
			find_if(begin(eventList), end(eventList), [event] (const auto& eventFromList) {
				return eventFromList == event;
			}))
		{
			dateToEvent[date].push_back(event);
		}
	}
}

void Database::Print(ostream& os) const
{
	for (const auto [date, eventList] : dateToEvent)
	{
		for (const auto event : eventList)
		{
			os << date << " " << event << endl;
		}
	}
}

string Database::Last(const Date& date) const
{
	auto upper = dateToEvent.upper_bound(date);
	if (upper == begin(dateToEvent))
	{
		throw invalid_argument("No entries");
	}
	else
	{
		ostringstream os;
		os << prev(upper)->first;
		string date{os.str()};
		os << *(prev(upper)->second.crbegin());
		string event{os.str()};
		return date + " " + event;
	}
}

string ParseEvent(istream& is) {
  string ret;
  getline(is >> ws, ret);
  return ret;
}