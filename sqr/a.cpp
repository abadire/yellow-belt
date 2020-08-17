#include <map>
#include <vector>
#include <iostream>

using namespace std;

template <typename T> T Sqr(T container);

template <typename First, typename Second>
pair<First, Second> operator* (const pair<First, Second>& left, const pair<First, Second>& right);

template <typename T>
vector<T> operator* (const vector<T>& left, const vector<T>& right);

template <typename Key, typename Value>
map<Key, Value> operator* (const map<Key, Value>& left, const map<Key, Value>& right);



template <typename T>
T Sqr(T container)
{
	return container * container;
}

template <typename First, typename Second>
pair<First, Second> operator* (const pair<First, Second>& left, const pair<First, Second>& right)
{
	return make_pair(left.first * right.first, left.second * right.second);
}

template <typename T>
vector<T> operator* (const vector<T>& left, const vector<T>& right)
{
	vector<T> ret;
	for (size_t i = 0; i != left.size(); ++i)
	{
		ret.push_back(left[i] * right[i]);
	}
	return ret;
}

template <typename Key, typename Value>
map<Key, Value> operator* (const map<Key, Value>& left, const map<Key, Value>& right)
{
	map<Key, Value> ret;
	for (auto el : left)
	{
		ret[el.first] = el.second * right.at(el.first);
	}
	return ret;
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

	map<int, pair<int, int>> map_of_pairs = {
	{4, {2, 2}},
	{7, {4, 3}}
	};
	cout << "map of pairs:" << endl;
	for (const auto& x : Sqr(map_of_pairs)) {
	cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
	}
}
#endif