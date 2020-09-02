#pragma once

#include "date.h"

#include <map>
#include <string>
#include <list>
#include <vector>
#include <ostream>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

class Database
{
public:
	void Add(const Date& date, const string& event);
	void Print(ostream& os) const;

	template <typename Predicate>
	int RemoveIf(Predicate pred)
	{
		int count = 0;

		auto dateToEventIter = begin(dateToEvent);

		while (dateToEventIter != end(dateToEvent))
		{
			const Date& date = dateToEventIter->first;
			list<string>& eventList = dateToEventIter->second;
			list<string>::iterator eventListIter = stable_partition(begin(eventList), end(eventList),
								  [date, pred](auto& event) {
									  return !pred(date, event);
								  });

			if (eventListIter == begin(eventList))
			{
				count += eventList.size();
				dateToEventIter = dateToEvent.erase(dateToEventIter);
			}
			else
			{
				++dateToEventIter;
				auto eventsToDeleteIter = eventListIter;
				while (eventsToDeleteIter != end(eventList))
				{
					eventsToDeleteIter = eventList.erase(eventsToDeleteIter);
					++count;
				}
			}
		}

		return count;
	}

	template <typename Predicate>
	vector<string> FindIf(Predicate pred) const
	{
		vector<string> res{};
		for (const auto& [date, eventList] : dateToEvent)
		{
			for (const auto& event : eventList)
			{
				if (pred(date, event))
				{
					ostringstream os;
					os << date << " " << event;
					res.emplace_back(os.str());
				}
			}
		}
		return res;
	}

	string Last(const Date& date) const;

private:
	map<Date, list<string>> dateToEvent;
};

// void TestDatabaseAdd();
// void TestDatabaseDel();
// void TestDatabaseFind();
// void TestDatabaseLast();

string ParseEvent(istream& is);