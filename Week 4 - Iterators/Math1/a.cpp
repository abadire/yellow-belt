#include <iostream>
#include <string>
#include <deque>

using namespace std;

int main() {
#ifdef LOCAL
freopen("input.txt", "r", stdin);
freopen("output.txt", "w", stdout);
#endif
	int num, n;
	char op;
	cin >> num;
	cin >> n;
	deque<string> out{to_string(num)};
	while (n != 0)
	{
		cin >> op;
		cin >> num;
		out.emplace_front("(");
		out.emplace_back(") " + string{op} + " " + to_string(num));
		--n;
	}
	for (const auto& iter : out)
	{
		cout << iter;
	}
}
