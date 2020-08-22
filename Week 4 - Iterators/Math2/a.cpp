#include <iostream>
#include <string>
#include <deque>
#include <vector>

using namespace std;

bool Priority(const char& ch)
{
	return ch == '*' || ch == '/';
}

int main() {
#ifdef LOCAL
freopen("input.txt", "r", stdin);
freopen("output.txt", "w", stdout);
#endif
	int num, n;
	char op;
	cin >> num;
	cin >> n;
	deque out{to_string(num)};
	bool flag = false; // LOW
	bool first = true;
	while (n != 0)
	{
		cin >> op;
		cin >> num;
		if (!first && flag < Priority(op))
		{
			out.emplace_front("(");
			out.emplace_back(") " + string{op} + " " + to_string(num));
		}
		else
		{
			out.emplace_back(" " + string{op} + " " + to_string(num));
		}
		--n;
		flag = Priority(op);
		if (first)
		{
			first = false;
		}
	}
	for (const auto& iter : out)
	{
		cout << iter;
	}
}
