#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <memory>
#include <cmath>

using namespace std;

class Figure
{
public:
	virtual const string Name() const = 0;
	virtual const double Perimeter() const = 0;
	virtual const double Area() const = 0;
};

class Circle : public Figure
{
public:
	Circle(const int& r) : r_(r) {}
	virtual const string Name() const override
	{
		return "CIRCLE";
	}

	virtual const double Perimeter() const override
	{
		return 2 * 3.14 * r_;
	}

	virtual const double Area() const override
	{
		return 3.14 * r_ * r_;
	}

private:
	const double r_;
};

class Rect : public Figure
{
public:
	Rect(const int& w, const int& h) : w_(w), h_(h) {}
	virtual const string Name() const override
	{
		return "RECT";
	}

	virtual const double Perimeter() const override
	{
		return 2 * (w_ + h_);
	}

	virtual const double Area() const override
	{
		return w_ * h_;
	}
	
private:
	const double w_, h_;
};

class Triangle : public Figure
{
public:
	Triangle(const int& a, const int& b, const int& c) : a_(a), b_(b), c_(c) {}
	virtual const string Name() const override
	{
		return "TRIANGLE";
	}

	virtual const double Perimeter() const override
	{
		return a_ + b_ + c_;
	}

	virtual const double Area() const override
	{
		double p = Perimeter() / 2;
		return sqrt(p * (p - a_) * (p - b_) * (p - c_));
	}
	
private:
	const double a_, b_, c_;
};

shared_ptr<Figure> CreateFigure(istream& is)
{
	string type;
	is >> type;
	if (type == "CIRCLE")
	{
		double r;
		is >> r;
		return make_shared<Circle>(Circle(r));
	}
	else if (type == "RECT")
	{
		double w, h;
		is >> w >> h;
		return make_shared<Rect>(Rect(w, h));
	}
	else if (type == "TRIANGLE")
	{
		double a, b, c;
		is >> a >> b>> c;
		return make_shared<Triangle>(Triangle(a, b, c));
	}
}

	#ifdef LOCAL
int main() {
	freopen("input.txt", "r", stdin);
  vector<shared_ptr<Figure>> figures;
  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "ADD") {
      // Пропускаем "лишние" ведущие пробелы.
      // Подробнее об std::ws можно узнать здесь:
      // https://en.cppreference.com/w/cpp/io/manip/ws
      is >> ws;
      figures.push_back(CreateFigure(is));
    } else if (command == "PRINT") {
      for (const auto& current_figure : figures) {
        cout << fixed << setprecision(3)
             << current_figure->Name() << " "
             << current_figure->Perimeter() << " "
             << current_figure->Area() << endl;
      }
    }
  }
	fclose(stdin);
  return 0;
}
	#endif