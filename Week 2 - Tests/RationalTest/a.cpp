#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

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

// class Rational {
// public:
//   Rational();
//   Rational(int numerator, int denominator);

//   int Numerator() const {
// 	  return num;
//   }

//   int Denominator() const {
// 	  return den;
//   }
// private:
// 	int num, den;
// };

// Rational::Rational(int numerator, int denominator): num(numerator), den(denominator) {
// 	if (num < 0 && den < 0)
// 	{
// 		num = abs(num);
// 		den = abs(den);
// 	}
// 	else if (den < 0)
// 	{
// 		den = abs(den);
// 		num = -num;
// 	}

// 	int a = abs(num), b = abs(den);
// 	while (a != 0 && b != 0)
// 	{
// 		if (a > b)
// 		{
// 			a %= b;
// 		}
// 		else
// 		{
// 			b %= a;
// 		}
// 	}
// 	int res = a + b;
// 	num /= res;
// 	den /= res;
// }
// Rational::Rational(): Rational(0, 1) {}

void testNumeratorDenominator()
{
	Rational r(1, 3);
	AssertEqual(r.Numerator(), 1, "Numerator");
	AssertEqual(r.Denominator(), 3, "Denominator");
}

void testEmpty()
{
	Rational r;
	AssertEqual(r.Numerator(), 0, "Default Numerator equals 1");
	AssertEqual(r.Denominator(), 1, "Default denominator equals 1");
}

void testPrimes()
{
	Rational r1(7, 13);
	AssertEqual(r1.Numerator(), 7, "Prime lesser numerator");
	AssertEqual(r1.Denominator(), 13, "Prime greater denominator");

	Rational r2(13, 7);
	AssertEqual(r2.Numerator(), 13, "Prime greater numerator");
	AssertEqual(r2.Denominator(), 7, "Prime lesser denominator");
}

void testReduction()
{
	Rational r1{0, 15};
	AssertEqual(r1.Numerator(), 0, "Zero numerator");
	AssertEqual(r1.Denominator(), 1, "Reduced denominator");

	Rational r2{5, 15};
	AssertEqual(r2.Numerator(), 1, "Reduced lesser numerator");
	AssertEqual(r2.Denominator(), 3, "Reduced greater denominator");

	Rational r3{15, 5};
	AssertEqual(r3.Numerator(), 3, "Reduced greater numerator");
	AssertEqual(r3.Denominator(), 1, "Reduced lesser denominator");
}

void testNegative()
{
	Rational r1{0, -15};
	AssertEqual(r1.Numerator(), 0, "Zero numerator");
	AssertEqual(r1.Denominator(), 1, "Reduced negative denominator");

	Rational r2{-5, -15};
	AssertEqual(r2.Numerator(), 1, "Reduced negative numerator");
	AssertEqual(r2.Denominator(), 3, "Reduced negative denominator");

	Rational r3{-15, 5};
	AssertEqual(r3.Numerator(), -3, "Reduced negative numerator");
	AssertEqual(r3.Denominator(), 1, "Reduced denominator");
}

int main() {
  TestRunner runner;
  runner.RunTest(testNumeratorDenominator, "testNumeratorDenominator");
  runner.RunTest(testEmpty, "testEmpty");
  runner.RunTest(testPrimes, "testPrimes");
  runner.RunTest(testReduction, "testReduction");
  runner.RunTest(testNegative, "testNegative");
  return 0;
}