#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <random>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

int GetQuadraticRoots(double a, double b, double c)
{
	int D = b * b - 4 * a * c;
	if (D > 0) return 2;
	else if (D == 0) return 1;
	else return 0;
}

int GetLinearRoots(double b, double c)
{
	return (0 != b) ? 1 : 0;
}

int GetDistinctRealRootCount(double a, double b, double c) {
	if (a != 0)
	{
		return GetQuadraticRoots(a, b, c);
	}
	else 
	{
		return GetLinearRoots(b, c);
	}
}

void testRootCount()
{
	uniform_real_distribution<> unif(-10, 10);
	mt19937 gen;

	for (auto i = 0; i != 100; ++i)
	{
		const auto a = unif(gen);
		const auto b = unif(gen);
		const auto c = unif(gen);

		const auto count = GetDistinctRealRootCount(a, b, c);
		Assert(0 <= count && count <= 2,
			   "Quadratic quations have only 2, 1 or 0 real roots.");
	}
}

void testOneRoot()
{
	uniform_real_distribution<> unif(-10, 10);
	mt19937 gen;

	for (auto i = 0; i != 100; ++i)
	{
		const auto x = unif(gen);

		const auto b = x + x;
		const auto c = x * x;

		const auto count = GetDistinctRealRootCount(1, b, c);
		stringstream description;
		description << showpos << "x^2" << b << "x" << c << "= 0 has 1 real root.";

		Assert(count == 1, description.str());

	}
}

void TestNoRoots() {
	AssertEqual(GetDistinctRealRootCount(1, 0, 1), 0,
		"x^2+1 = 0 has 0 real roots.");
	AssertEqual(GetDistinctRealRootCount(1, 3, 4), 0,
		"x^2+3x+4 = 0 has 0 real roots.");
	AssertEqual(GetDistinctRealRootCount(1, -2, 10), 0,
		"x^2-2x+10 = 0 has 0 real roots.");
}

void TestLinearEquation() {
	AssertEqual(GetDistinctRealRootCount(0, 2, 1), 1,
		"2x+1 = 0 has 1 real root.");
	AssertEqual(GetDistinctRealRootCount(0, -1, 0), 1,
		"-x = 0 has 1 real root.");
	AssertEqual(GetDistinctRealRootCount(0, 120, -10), 1,
		"120x - 10 = 0 has 1 real root.");
}

void TestConstant() {
	AssertEqual(GetDistinctRealRootCount(0, 0, 1), 0,
		"c = 0, where c = 1 has 0 real roots.");
	AssertEqual(GetDistinctRealRootCount(0, 0, -10), 0,
		"c = 0, where c = -10 has 0 real roots.");
	AssertEqual(GetDistinctRealRootCount(0, 0, 189238910), 0,
		"c = 0, where c = 189238910 has 0 real roots.");
}

void testGetDistinctRealRootCount()
{
	AssertEqual(GetDistinctRealRootCount(5, 6, 1), 2, "Two roots");
	AssertEqual(GetDistinctRealRootCount(5, 2, 1), 0, "No roots");
	AssertEqual(GetDistinctRealRootCount(0, 2, 1), 1, "One root");
}

void testGetLinearRoots()
{
	AssertEqual(GetLinearRoots(1, 2), 1, "One root in linear");
	AssertEqual(GetLinearRoots(0, 2), 0, "No roots in linear");
}

void testGetQuadraticRoots()
{
	AssertEqual(GetQuadraticRoots(5, 6, 1), 2, "Two roots");
	AssertEqual(GetQuadraticRoots(5, 2, 1), 0, "No roots");
}

int main() {
  TestRunner runner;
  runner.RunTest(testGetDistinctRealRootCount, "testGetDistinctRealRootCount");
  runner.RunTest(testRootCount, "testRootCount");
  runner.RunTest(testGetLinearRoots, "testGetLinearRoots");
  runner.RunTest(testGetQuadraticRoots, "testGetQuadraticRoots");
  runner.RunTest(testOneRoot, "testOneRoot");
  runner.RunTest(TestNoRoots, "TestNoRoots");
  runner.RunTest(TestLinearEquation, "TestLinearEquation");
  runner.RunTest(TestConstant, "TestConstant");
  return 0;
}