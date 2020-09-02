#include "node.h"

bool EmptyNode::Evaluate(const Date& date, const string& event)
{
	return true;
}

LogicalOperationNode::LogicalOperationNode(const LogicalOperation& op, shared_ptr<Node> left, shared_ptr<Node> right)
  : op_(op)
  , left_(left)
  , right_(right)
  {}

bool LogicalOperationNode::Evaluate(const Date& date, const string& event)
{
	if (op_ == LogicalOperation::And)
	{
		return left_->Evaluate(date, event) && right_->Evaluate(date, event);
	}
	else if (op_ == LogicalOperation::Or)
	{
		return left_->Evaluate(date, event) || right_->Evaluate(date, event);
	}
	else
	{
		throw logic_error("Unknown logical operator in LogicalOperationNode");
	}
}

DateComparisonNode::DateComparisonNode(const Comparison& cmp, const Date& date)
  : cmp_(cmp)
  , date_(date)
  {}

bool DateComparisonNode::Evaluate(const Date& date, const string& event)
{
	switch (cmp_)
	{
		case Comparison::Less:
			return date < date_;
			break;
		case Comparison::LessOrEqual:
			return date <= date_;
			break;
		case Comparison::Greater:
			return date > date_;
			break;
		case Comparison::GreaterOrEqual:
			return date >= date_;
			break;
		case Comparison::Equal:
			return date == date_;
			break;
		case Comparison::NotEqual:
			return date != date_;
			break;
		default:
			throw logic_error("Unknown comparison token in DateComparisonNode");
	}
}

EventComparisonNode::EventComparisonNode(const Comparison& cmp, const string& event)
  : cmp_(cmp)
  , event_(event)
  {}

bool EventComparisonNode::Evaluate(const Date& date, const string& event)
{
	switch (cmp_)
	{
	case Comparison::Less:
		return event < event_;
		break;
	case Comparison::LessOrEqual:
		return event <= event_;
		break;
	case Comparison::Greater:
		return event > event_;
		break;
	case Comparison::GreaterOrEqual:
		return event >= event_;
		break;
	case Comparison::Equal:
		return event == event_;
		break;
	case Comparison::NotEqual:
		return event != event_;
		break;
	default:
		throw logic_error("Unknown comparison token in EventComparisonNode");
	}
}