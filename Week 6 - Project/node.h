#pragma once

#include <memory>

#include "date.h"

using namespace std;

enum class LogicalOperation
{
	And,
	Or
};

enum class Comparison
{
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual
};

class Node
{
public:
	virtual bool Evaluate(const Date& date, const string& event) = 0;
};

class EmptyNode : public Node
{
public:
	virtual bool Evaluate(const Date& date, const string& event) override;
};

class LogicalOperationNode : public Node
{
public:
	LogicalOperationNode(const LogicalOperation& op, shared_ptr<Node> left, shared_ptr<Node> right);

	virtual bool Evaluate(const Date& date, const string& event) override;
private:
	const LogicalOperation op_;
	shared_ptr<Node> left_, right_;
};

class DateComparisonNode : public Node
{
public:
	DateComparisonNode(const Comparison& cmp, const Date& date);

	virtual bool Evaluate(const Date& date, const string& event) override;
private:
	const Comparison cmp_;
	const Date date_;
};

class EventComparisonNode : public Node
{
public:
	EventComparisonNode(const Comparison& cmp, const string& event);

	virtual bool Evaluate(const Date& date, const string& event) override;
private:
	const Comparison cmp_;
	const string event_;
};

