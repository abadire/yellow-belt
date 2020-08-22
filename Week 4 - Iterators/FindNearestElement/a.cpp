#include <set>
#include <iostream>
#include <algorithm>

using namespace std;

set<int>::const_iterator FindNearestElement(
    const set<int>& numbers,
    int border)
{
	if (numbers.empty())
	{
		return end(numbers);
	}
	else{
		auto up = numbers.upper_bound(border);

		if (up == end(numbers))
		{
			return prev(end(numbers));
		}
		else if (up == begin(numbers))
		{
			return begin(numbers);
		}
		else
		{
			if (*up - border >= border - *prev(up))
			{
				return prev(up);
			}
			else
			{
				return up;
			}
		}
	}


}

#ifdef LOCAL
int main() {
  set<int> numbers = {1, 4, 6};
  cout <<
      *FindNearestElement(numbers, 0) << " " <<
      *FindNearestElement(numbers, 3) << " " <<
      *FindNearestElement(numbers, 5) << " " <<
      *FindNearestElement(numbers, 6) << " " <<
      *FindNearestElement(numbers, 100) << endl;
      
  set<int> empty_set;
  
  cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;
  return 0;
}

#endif
