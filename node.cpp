#include "node.h"

template<typename T>
bool foo(const Comparison &cmp, const T &lhs, const T &rhs) {
    switch (cmp) {
    case Comparison::Less:
        return lhs < rhs;
    case Comparison::LessOrEqual:
        return lhs <= rhs;
    case Comparison::Greater:
        return lhs > rhs;
    case Comparison::GreaterOrEqual:
        return lhs >= rhs;
    case Comparison::Equal:
        return lhs == rhs;
    default:
        return lhs != rhs;
    }
}


Node::Node() {}


DateComparisonNode::DateComparisonNode(const Comparison &cmp, const Date &date)
        : _cmp(cmp), _date(date) {}


bool DateComparisonNode::Evaluate(const Date &date, const std::string &event) const {
    return foo(_cmp, date, _date);
}


EventComparisonNode::EventComparisonNode(const Comparison &cmp, const std::string &event)
        : _cmp(cmp), _event(event) {}


bool EventComparisonNode::Evaluate(const Date &date, const std::string &event) const {
    return foo(_cmp, event, _event);
}


LogicalOperationNode::LogicalOperationNode(const LogicalOperation &op,
    std::shared_ptr<const Node> left, std::shared_ptr<const Node> right) 
    : _op(op), _left(left), _right(right) {}


bool LogicalOperationNode::Evaluate(const Date &date, const std::string &event) const {
    if (_op == LogicalOperation::Or) {
        return _left->Evaluate(date, event) ||
               _right->Evaluate(date, event);
    } else if (_op == LogicalOperation::And) {
        return _left->Evaluate(date, event) &&
               _right->Evaluate(date, event);
    }
}


EmptyNode::EmptyNode() {}


bool EmptyNode::Evaluate(const Date &date, const std::string &event) const {
    return true;
}
