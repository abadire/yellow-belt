#include <vector>
#include <iostream>

using namespace std;

int main()
{
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	int n;
	uint64_t density, x, y, z, sum = 0;
	cin >> n >> density;
	for (int i = 0; i != n; ++i)
	{
		cin >> x >> y >> z;
		sum += x*y*z*density;
	}
	cout << sum;
	return 0;
}