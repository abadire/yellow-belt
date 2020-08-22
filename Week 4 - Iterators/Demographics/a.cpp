#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

#ifdef LOCAL
enum class Gender {
  FEMALE,
  MALE
};

struct Person {
  int age;  // возраст
  Gender gender;  // пол
  bool is_employed;  // имеет ли работу
};

template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
  if (range_begin == range_end) {
    return 0;
  }
  vector<typename InputIt::value_type> range_copy(range_begin, range_end);
  auto middle = begin(range_copy) + range_copy.size() / 2;
  nth_element(
      begin(range_copy), middle, end(range_copy),
      [](const Person& lhs, const Person& rhs) {
        return lhs.age < rhs.age;
      }
  );
  return middle->age;
}
#endif

void PrintStats(vector<Person> persons)
{
	cout << "Median age = " << ComputeMedianAge(begin(persons), end(persons)) << endl;
	
	auto itFemaleMale = partition(begin(persons), end(persons), [](const Person& x) {
		return x.gender == Gender::FEMALE;
	});
	cout << "Median age for females = " << ComputeMedianAge(begin(persons), itFemaleMale) << endl;
	cout << "Median age for males = " << ComputeMedianAge(itFemaleMale, end(persons)) << endl;

	auto itEmployedFemale = partition(begin(persons), itFemaleMale, [](const Person& x) {
		return x.is_employed;
	});
	auto itEmployedMale = partition(itFemaleMale, end(persons), [](const Person& x) {
		return x.is_employed;
	});

	cout << "Median age for employed females = " << ComputeMedianAge(begin(persons), itEmployedFemale) << endl;
	cout << "Median age for unemployed females = " << ComputeMedianAge(itEmployedFemale, itFemaleMale) << endl;
	cout << "Median age for employed males = " << ComputeMedianAge(itFemaleMale, itEmployedMale) << endl;
	cout << "Median age for unemployed males = " << ComputeMedianAge(itEmployedMale, end(persons)) << endl;
}

#ifdef LOCAL
int main() {
  vector<Person> persons = {
      {31, Gender::MALE, false},
      {40, Gender::FEMALE, true},
      {24, Gender::MALE, true},
      {20, Gender::FEMALE, true},
      {80, Gender::FEMALE, false},
      {78, Gender::MALE, false},
      {10, Gender::FEMALE, false},
      {55, Gender::MALE, true},
  };
  PrintStats(persons);

  return 0;
}
#endif
