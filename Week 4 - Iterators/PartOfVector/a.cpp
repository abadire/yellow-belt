#include <vector>
#include <iostream>

using namespace std;

void PrintVectorPart(const vector<int>& numbers)
{
	auto it = numbers.cbegin();
	while(it != numbers.cend())
	{
		if (*it < 0) break;
		++it;
	}

	while (it != numbers.cbegin())
	{
		--it;
		cout << *it << ' ';
	}
}

int main()
{
  PrintVectorPart({6, 1, 8, -5, 4});
  cout << endl;
  PrintVectorPart({-6, 1, 8, -5, 4});  // ничего не выведется
  cout << endl;
  PrintVectorPart({6, 1, 8, 5, 4});
  cout << endl;
  return 0;
}
