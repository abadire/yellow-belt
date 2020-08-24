#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person
{
public:
	Person(const string& name, const string& job)
	  : name_(name)
	  , job_(job)
	  {}

	const string& GetName() const
	{
		return name_;
	}

	const string& GetJob() const
	{
		return job_;
	}

	const string DoStuff(const string& stuff) const
	{
		return job_ + ": " + name_ + " " + stuff;
	}

    virtual void Walk(string destination) const
	{
        cout << DoStuff("walks to: ") << destination << endl;
	}

	virtual ~Person() = default;

private:
	const string name_;
	const string job_;
};

class Student : public Person {
public:
    Student(string name, string favouriteSong)
	  : Person(name, "Student")
	  , favouriteSong_(favouriteSong)
	  {}

    void Learn() const {
        cout << DoStuff("learns") << endl;
    }

    void SingSong() const {
        cout << DoStuff("sings a song: ") << favouriteSong_ << endl;
    }

    virtual void Walk(string destination) const override {
        Person::Walk(destination);
        SingSong();
    }

private:
    const string favouriteSong_;
};


class Teacher : public Person {
public:

    Teacher(string name, string subject)
	  : Person(name, "Teacher")
	  , subject_(subject)
	{}

    void Teach() const {
        cout << DoStuff("teaches: ") << subject_ << endl;
    }

private:
    const string subject_;
};


class Policeman : public Person {
public:
    Policeman(string name)
	  : Person(name, "Policeman")
	  {}

	void Check(const Person& p) const
	{
		cout << DoStuff("checks: ") << p.GetJob() << ". "
			 << p.GetJob() << "'s name is: " << p.GetName() << endl;
	}
};

void VisitPlaces(const Person& person, vector<string> places) {
    for (auto p : places) {
        person.Walk(p);
    }
}

int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}