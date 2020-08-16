#include <vector>
#include <map>

using namespace std;

bool operator<(const Region& lhs, const Region& rhs)
{
	return tie(lhs.std_name, lhs.parent_std_name, lhs.names, lhs.population) < 
		   tie(rhs.std_name, rhs.parent_std_name, rhs.names, rhs.population);
}

int FindMaxRepetitionCount(const vector<Region>& regions)
{
	map<Region, int> counts;

	int ret = 0;

	for (const auto& item : regions)
	{
		ret = max(ret, ++counts[item]);
	}

	return ret;
}