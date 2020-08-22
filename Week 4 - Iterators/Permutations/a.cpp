#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

ostream& operator<<(ostream& os, const vector<int>& v)
{
	bool first = true;
	for (auto el : v)
	{
		if (!first)
		{
			os << " ";
		}
		first = false;
		os << el;
	}
	return os;
}

int Fact(const int& n)
{
	int res = 1;
	for (int i = 2; i <= n; ++i) res *= i;
	return res;
}

void Permute(const int& a)
{
	vector<int> v(a);
	iota(begin(v), end(v), 1);
	int count = Fact(a);
	for (int i = 0; i != count; ++i)
	{
		prev_permutation(begin(v), end(v));
		cout << v << endl;
	}
}

int main() {
  int a;
  cin >> a;
  Permute(a);

  return 0;
}

