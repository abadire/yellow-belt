#include <map>
#include <iostream>
#include <exception>
using namespace std;

template <typename K, typename V>
V& GetRefStrict(map<K, V>& map, const K& key)
{
	if (map.count(key) == 0)
	{
		throw runtime_error("");
	}
	else
	{
		return map[key];
	}
}

#ifdef LOCAL
int main()
{
	// vector<int> v = {1, 2, 3};
	// cout << "vector:";
	// for (int x : Sqr(v)) {
	// cout << ' ' << x;
	// }
	// cout << endl;

	map<int, int> map_of_pairs = {
	{2, 2},
	{4, 3}
	};
	cout << "map of pairs:" << endl;
	cout << (GetRefStrict(map_of_pairs, 0) = 10);
}
#endif