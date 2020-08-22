#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

int main() {
	freopen("input.txt", "r", stdin);
	vector<int> v1{1, 2, 3, 10, 8, 3};
	auto it = is_sorted_until(begin(v1), end(v1));
	auto it2 = is_sorted_until(rbegin(v1), rend(v1));
	cout << *it << ' ' << *it2;
  return 0;
}
