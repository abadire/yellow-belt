#include "database.h"
#include "test_runner.h"
#include "condition_parser.h"

void AssertEqualDb(const string& input, const string& output, const string& hint)
{
	istringstream is(input);
	Database db;
	ostringstream print;
	for (string line; getline(is, line);)
	{
		istringstream isInner(line);
		string command;
		isInner >> command;
		if (command == "Add") {
			const auto date = ParseDate(isInner);
			const auto event = ParseEvent(isInner);
			db.Add(date, event);
		}
		else if (command == "Del")
		{
			auto condition = ParseCondition(isInner);
			auto predicate = [condition](const Date &date, const string &event) {
				return condition->Evaluate(date, event);
			};
			int count = db.RemoveIf(predicate);
			print << "Removed " << count << " entries" << endl;
		}
		else if (command == "Find")
		{
			auto condition = ParseCondition(isInner);
			auto predicate = [condition](const Date &date, const string &event) {
				return condition->Evaluate(date, event);
			};

			const auto entries = db.FindIf(predicate);
			for (const auto &entry : entries)
			{
				print << entry << endl;
			}
			print << "Found " << entries.size() << " entries" << endl;
		}
		else if (command == "Last")
		{
			try
			{
				print << db.Last(ParseDate(isInner)) << endl;
			}
			catch (invalid_argument &)
			{
				print << "No entries" << endl;
			}
		}
		else if (command.empty()) break;
	}
	db.Print(print);
	AssertEqual(print.str(), output, hint);
}

void TestDatabaseAdd()
{
		AssertEqualDb("Add 2017-06-01 1st of June\n"
					  "Add 2017-07-08 8th of July\n"
					  "Add 2017-07-08 Someone's birthday",

					  "2017-06-01 1st of June\n"
					  "2017-07-08 8th of July\n"
					  "2017-07-08 Someone's birthday\n",

					  "Db test add different");

		AssertEqualDb("Add 2017-06-01 1st of June\n"
					  "Add 2017-06-01 1st of June\n"
					  "Add 2017-06-01 1st of June\n",

					  "2017-06-01 1st of June\n",

					  "Db test add duplicate");

		AssertEqualDb("Add 2017-06-01 1st of June\n"
					  "Add 2017-06-01 2st of June\n"
					  "Add 2017-06-01 3st of June\n",

					  "2017-06-01 1st of June\n"
					  "2017-06-01 2st of June\n"
					  "2017-06-01 3st of June\n",

					  "Db test add one date");

		AssertEqualDb("Add 2017-06-01 1st of June\n"
					  "Add 2017-06-02 1st of June\n"
					  "Add 2017-06-03 1st of June\n",

					  "2017-06-01 1st of June\n"
					  "2017-06-02 1st of June\n"
					  "2017-06-03 1st of June\n",

					  "Db test add one event");

		AssertEqualDb("Add 2017-06-01 1st of June\n"
					  "Add 2017-06-02 1st of June\n"
					  "Add 2017-06-01 1st of June\n",

					  "2017-06-01 1st of June\n"
					  "2017-06-02 1st of June\n",

					  "Db test add mixed 1");

		AssertEqualDb("Add 2017-06-04 4st of June\n"
					  "Add 2017-06-02 2st of June\n"
					  "Add 2017-06-01 1st of June\n",

					  "2017-06-01 1st of June\n"
					  "2017-06-02 2st of June\n"
					  "2017-06-04 4st of June\n",

					  "Db test add reverse order");
}

void TestDatabaseDel()
{
	AssertEqualDb("Add 2017-06-01 1st of June\n"
				  "Add 2017-07-08 8th of July\n"
				  "Add 2017-07-08 Someone's birthday\n"
				  "Del date == 2017-07-08",

				  "Removed 2 entries\n"
				  "2017-06-01 1st of June\n",

				  "Db test del 1");

	AssertEqualDb("Add 2017-06-01 1st of June\n"
				  "Add 2017-07-08 8th of July\n"
				  "Add 2017-07-08 Someone's birthday\n"
				  "Add 2017-07-08 Someone's birthday2\n"
				  "Del date == 2017-07-08",

				  "Removed 3 entries\n"
				  "2017-06-01 1st of June\n",

				  "Db test del 2");

	AssertEqualDb("Add 2017-07-01 1st of July\n"
				  "Add 2017-07-01 2th of July\n"
				  "Add 2017-07-01 2th of July\n"
				  "Add 2017-07-01 3th of July\n"
				  "Del event == \"3th of July\"",

				  "Removed 1 entries\n"
				  "2017-07-01 1st of July\n"
				  "2017-07-01 2th of July\n",

				  "Db test del 3");

	AssertEqualDb("Del event == \"3th of July\"",

				  "Removed 0 entries\n",

				  "Db test del 4");

				  

	AssertEqualDb("Add 2017-07-01 1st of July\n"
				  "Add 2017-07-01 2th of July\n"
				  "Add 2017-07-01 3th of July\n"
				  "Del event == \"3th of July\"\n"
				  "Del event == \"1st of July\"\n"
				  "Del event == \"2th of July\"\n",

				  "Removed 1 entries\n"
				  "Removed 1 entries\n"
				  "Removed 1 entries\n",

				  "Db test del 5");
}

void TestDatabaseFind()
{
	AssertEqualDb("Add 2017-01-01 Holiday\n"
				  "Add 2017-03-08 Holiday\n"
				  "Add 2017-01-01 New Year\n"
				  "Find event != \"working day\"\n"
				  "Add 2017-05-09 Holiday\n",

				  "2017-01-01 Holiday\n"
				  "2017-01-01 New Year\n"
				  "2017-03-08 Holiday\n"
				  "Found 3 entries\n"
				  "2017-01-01 Holiday\n"
				  "2017-01-01 New Year\n"
				  "2017-03-08 Holiday\n"
				  "2017-05-09 Holiday\n",

				  "Db test find 1");
				  
	AssertEqualDb("Add 2017-01-01 Holiday\n"
				  "Add 2017-01-01 Holiday2\n"
				  "Add 2017-01-01 Holiday2\n"
				  "Find event != \"Holiday\"\n",

				  "2017-01-01 Holiday2\n"
				  "Found 1 entries\n"
				  "2017-01-01 Holiday\n"
				  "2017-01-01 Holiday2\n",

				  "Db test find 2");
}

void TestDatabaseLast()
{
	AssertEqualDb("Add 2017-01-01 New Year\n"
				  "Add 2017-03-08 Holiday\n"
				  "Add 2017-01-01 Holiday\n"
				  "Last 2016-12-31\n"
				  "Last 2017-01-01\n"
				  "Last 2017-06-01\n"
				  "Add 2017-05-09 Holiday\n",

				  "No entries\n"
				  "2017-01-01 Holiday\n"
				  "2017-03-08 Holiday\n"
				  "2017-01-01 New Year\n"
				  "2017-01-01 Holiday\n"
				  "2017-03-08 Holiday\n"
				  "2017-05-09 Holiday\n",

				  "Db test last 1");

	AssertEqualDb("Add 2017-01-01 New Year\n"
				  "Add 2017-03-08 Holiday\n"
				  "Add 2017-01-01 Holiday\n"
				  "Del event == \"Holiday\"\n"
				  "Last 2017-01-01\n",

				  "Removed 2 entries\n"
				  "2017-01-01 New Year\n"
				  "2017-01-01 New Year\n",

				  "Db test last 2");

	AssertEqualDb("Add 2017-01-01 New Year\n"
				  "Add 2017-03-08 Holiday\n"
				  "Add 2017-01-01 Holiday\n"
				  "Del event == \"New Year\"\n"
				  "Last 2017-01-01\n",

				  "Removed 1 entries\n"
				  "2017-01-01 Holiday\n"
				  "2017-01-01 Holiday\n"
				  "2017-03-08 Holiday\n",

				  "Db test last 4");

	AssertEqualDb("Last 2017-01-01\n",

				  "No entries\n",

				  "Db test last 3");
}