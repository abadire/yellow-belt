#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
    RandomIt range_begin, RandomIt range_end,
    const string& prefix)
{
	if (prefix.empty()) return {range_begin, range_begin};

	const auto low = lower_bound(range_begin, range_end, prefix, [](const string& a, const string& b){
		if (b.size() >= a.size()) return a < b;
		return string{begin(a), begin(a) + b.size()} < b;
	});

	const auto up = upper_bound(range_begin, range_end, prefix, [](const string& a, const string& b){
		if (a.size() >= b.size()) return a < b;
		return a < string{begin(b), begin(b) + a.size()};
	});

	return {low, up};
}

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWithExtra(
    RandomIt range_begin, RandomIt range_end,
    const string& prefix)
{
	auto low = lower_bound(range_begin, range_end, prefix);

	string upper_bound = prefix;
	++upper_bound[upper_bound.size() - 1];

	auto up = lower_bound(range_begin, range_end, upper_bound);

	return {low, up};
}

#ifdef LOCAL
int main() {
  const vector<string> sorted_strings = {"moscow", "motovilikha", "murmansk"};
  const auto mo_result =
      FindStartsWithExtra(begin(sorted_strings), end(sorted_strings), "mo");
  for (auto it = mo_result.first; it != mo_result.second; ++it) {
    cout << *it << " ";
  }
  cout << endl;
  
  const auto mt_result =
      FindStartsWithExtra(begin(sorted_strings), end(sorted_strings), "mt");
  cout << (mt_result.first - begin(sorted_strings)) << " " <<
      (mt_result.second - begin(sorted_strings)) << endl;
  
  const auto na_result =
      FindStartsWithExtra(begin(sorted_strings), end(sorted_strings), "na");
  cout << (na_result.first - begin(sorted_strings)) << " " <<
      (na_result.second - begin(sorted_strings)) << endl;


// EMPTY PREFIX
//   const auto empty_pref_result =
//       FindStartsWithExtra(begin(sorted_strings), end(sorted_strings), "");
//   cout << "EMPTY PREFIX " << (empty_pref_result.first - begin(sorted_strings)) << " " <<
//       (empty_pref_result.second - begin(sorted_strings)) << endl;
  
// EMPTY STRINGS
  const vector<string> empty_strings = {};
  const auto empty_result =
      FindStartsWithExtra(begin(empty_strings), end(empty_strings), "a");
  cout << "EMPTY STRINGS " << (empty_result.first - begin(empty_strings)) << " " <<
      (empty_result.second - begin(empty_strings)) << endl;
  
// PREFIX LARGER
  const auto larger_result =
      FindStartsWithExtra(begin(sorted_strings), end(sorted_strings), "motovilia");
  cout << "PREFIX LARGER " << (larger_result.first - begin(sorted_strings)) << " " <<
      (larger_result.second - begin(sorted_strings)) << endl;
  return 0;
}
#endif
