#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{
	if (range_end - range_begin > 1)
	{
	vector<typename RandomIt::value_type> elements{range_begin, range_end};
	auto one_third = begin(elements) + elements.size() / 3;
	auto two_thirds = begin(elements) + 2 * elements.size() / 3;
	MergeSort(begin(elements), one_third);
	MergeSort(one_third, two_thirds);
	MergeSort(two_thirds, end(elements));

	vector<typename RandomIt::value_type> temp;
	merge(begin(elements), one_third,
		  one_third, two_thirds,
		  back_inserter(temp));
	merge(begin(temp), end(temp),
		  two_thirds, end(elements),
		  range_begin);
	}
}

#ifdef LOCAL
int main() {
  vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
  MergeSort(begin(v), end(v));
  for (int x : v) {
    cout << x << " ";
  }
  cout << endl;
  return 0;
}

#endif
