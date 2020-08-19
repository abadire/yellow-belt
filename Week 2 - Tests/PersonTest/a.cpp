#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

// class Person {
// public:
//   void ChangeFirstName(int year, const string& first_name) {
// 	  first_names[year] = first_name;
//   }
//   void ChangeLastName(int year, const string& last_name) {
// 	  last_names[year] = last_name;
//   }
//   string GetFullName(int year) {
// 	  if (first_names.lower_bound(year) == first_names.end() && last_names.lower_bound(year) == last_names.end())
// 	  {
// 		  return "Incognito";
// 	  }
// 	  else if (first_names.lower_bound(year) == first_names.end())
// 	  {
// 		  stringstream ret;
// 		  ret << last_names.lower_bound(year)->second << " with unknown first name";
// 		  return ret.str();
// 	  }
// 	  else if (last_names.lower_bound(year) == last_names.end())
// 	  {
// 		  stringstream ret;
// 		  ret << first_names.lower_bound(year)->second << " with unknown last name";
// 		  return ret.str();
// 	  }
// 	  else
// 	  {
// 		  return first_names.lower_bound(year)->second + " " + last_names.lower_bound(year)->second;
// 	  }
//   }
// private:
// 	map<int, string> first_names, last_names;
// };

string generateName(const int& len = 10)
{
	auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    mt19937 generator(seed);
   //modify range according to your need "A-Z","a-z" or "0-9" or whatever you need.
    uniform_int_distribution<int> distribution{'A', 'z'};

    string rand_str(len, '\0');
    for(auto& dis: rand_str)
        dis = distribution(generator);

	return rand_str;
}

void testEmptyIncognito()
{
	Person p;
	mt19937 gen;
	uniform_int_distribution<> unif(0, 2000);
	for (auto i = 0; i != 100; ++i)
	{
		const auto year = unif(gen);
		AssertEqual(p.GetFullName(year), "Incognito", "Check empty Person.");
	}
}

void testNonEmptyIncognito()
{
	Person p;
	mt19937 gen;
	uniform_int_distribution<> unif(0, 2000);
	set<int> years;
	for (auto i = 0; i != 2000; ++i)
	{
		const auto year = unif(gen);
		years.insert(year);

		p.ChangeFirstName(year, generateName());
		p.ChangeLastName(year, generateName());
	}

	for (auto i = 0; i != 2000; ++i)
	{
		if (years.lower_bound(i) == years.end())
		{
			AssertEqual(p.GetFullName(i), "Incognito", "Returns Incognito in unchanged years in partially filled Person.");
		}
	}
}

void testFirstName()
{
	Person p;
	mt19937 gen;
	uniform_int_distribution<> unif(0, 2000);
	map<int, string> names;
	for (auto i = 0; i != 100; ++i)
	{
		const auto year = unif(gen);
		names[year] = generateName();

		p.ChangeFirstName(year, names[year]);
		// p.ChangeLastName(year, generateName());
	}

	for (const auto& name : names)
	{
		stringstream s;
		s << name.second << " with unknown last name";
		AssertEqual(p.GetFullName(name.first), s.str(), "If only the first name has changed.");
	}
}

void testLastName()
{
	Person p;
	mt19937 gen;
	uniform_int_distribution<> unif(0, 2000);
	map<int, string> names;
	for (auto i = 0; i != 100; ++i)
	{
		const auto year = unif(gen);
		names[year] = generateName();

		// p.ChangeFirstName(year, names[year]);
		p.ChangeLastName(year, names[year]);
	}

	for (const auto& name : names)
	{
		stringstream s;
		s << name.second << " with unknown first name";
		AssertEqual(p.GetFullName(name.first), s.str(), "If only the last name has changed.");
	}
}

void testFullName()
{
	Person p;
	mt19937 gen;
	uniform_int_distribution<> unif(0, 2000);
	map<int, string> names;
	for (auto i = 0; i != 100; ++i)
	{
		const auto year = unif(gen);
		string fname{generateName()};
		string lname{generateName()};
		names[year] = fname + " " + lname;

		p.ChangeFirstName(year, fname);
		p.ChangeLastName(year, lname);
	}

	for (const auto& name : names)
	{
		AssertEqual(p.GetFullName(name.first), name.second, "If both names have changed.");
	}
}

int main() {
  TestRunner runner;
  runner.RunTest(testEmptyIncognito, "testEmptyIncognito");
  runner.RunTest(testNonEmptyIncognito, "testNonEmptyIncognito");
  runner.RunTest(testFirstName, "testFirstName");
  runner.RunTest(testLastName, "testLastName");
  runner.RunTest(testFullName, "testFullName");
  return 0;
}