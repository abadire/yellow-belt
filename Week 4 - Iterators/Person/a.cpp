#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

using namespace std;

class Person {
public:
  void ChangeFirstName(int year, const string& first_name) {
	  first_names[year] = first_name;
  }
  void ChangeLastName(int year, const string& last_name) {
	  last_names[year] = last_name;
  }
  string GetFullName(int year) {
	  const auto first_more_f = first_names.upper_bound(year);
	  const auto first_more_l = last_names.upper_bound(year);

	  if (first_more_f == first_names.begin() && first_more_l == last_names.begin())
	  {
		  return "Incognito";
	  }
	  else if (first_more_f == first_names.begin())
	  {
		  return prev(first_more_l)->second + " with unknown first name";
	  }
	  else if (first_more_l == last_names.begin())
	  {
		  return prev(first_more_f)->second + " with unknown last name";
	  }
	  else
	  {
		  return prev(first_more_f)->second + " " + prev(first_more_l)->second;
	  }
  }
private:
	map<int, string> first_names, last_names;
};

#ifdef LOCAL
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

int main() {
  Person person;
  
  person.ChangeFirstName(1965, "Polina");
  person.ChangeLastName(1967, "Sergeeva");
  for (int year : {1900, 1965, 1990}) {
    cout << person.GetFullName(year) << endl;
  }
  
  person.ChangeFirstName(1970, "Appolinaria");
  for (int year : {1969, 1970}) {
    cout << person.GetFullName(year) << endl;
  }
  
  person.ChangeLastName(1968, "Volkova");
  for (int year : {1969, 1970}) {
    cout << person.GetFullName(year) << endl;
  }
  
  return 0;
}
#endif
