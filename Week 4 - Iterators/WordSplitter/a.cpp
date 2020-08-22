#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

vector<string> SplitIntoWords(const string& s)
{
	auto beg = cbegin(s);
	vector<string> ret;
	while (beg < cend(s))
	{
		auto end = find(beg, cend(s), ' ');
		ret.emplace_back(beg, end);
		beg = end + 1;
	}

	return ret;
}

int main() {
  string s = "C Cpp Java Python";

  vector<string> words = SplitIntoWords(s);
  cout << words.size() << " ";
  for (auto it = begin(words); it != end(words); ++it) {
    if (it != begin(words)) {
      cout << "/";
    }
    cout << *it;
  }
  cout << endl;
  
  return 0;
}
