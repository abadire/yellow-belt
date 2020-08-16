#include <vector>
#include <iostream>

using namespace std;

int main()
{
#ifdef LOCAL
  	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	int n, in;
	int64_t avg = 0;
	vector<int> temps;
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		cin >> in;
		avg += in;
		temps.emplace_back(in);
	}

	avg /= static_cast<int>(temps.size());

	int count = 0;
	vector<int> days;
	for (size_t i = 0; i != temps.size(); ++i)
	{
		if (temps[i] > avg)
		{
			++count;
			days.emplace_back(i);
		}
	}

	cout << count << endl;
	for (vector<int>::size_type i = 0;  i != days.size(); ++i)
	{
		if (i != 0) cout << ' ';
		cout << days[i];
	}

	return 0;
}