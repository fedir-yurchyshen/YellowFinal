#pragma once

#include "date.h"

#include <memory>

enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

enum class LogicalOperation {
    Or,
    And
};


class Node {
public:
    Node();
    virtual bool Evaluate(const Date &date, const std::string &event) const = 0;

};


class DateComparisonNode : public Node {
public:
    DateComparisonNode(const Comparison &cmp, const Date &date); 
    bool Evaluate(const Date &date, const std::string &event) const override;
private:
    const Comparison _cmp;
    const Date _date;
    
};


class EventComparisonNode : public Node {
public:
    EventComparisonNode(const Comparison &cmp, const std::string &event);
    bool Evaluate(const Date &date, const std::string &event) const override;
private:
    const Comparison _cmp;
    const std::string _event;

};


class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(const LogicalOperation &op,
        std::shared_ptr<const Node> left, std::shared_ptr<const Node> right);
    bool Evaluate(const Date &date, const std::string &event) const override;

private:
    const LogicalOperation _op;
    std::shared_ptr<const Node> _left, _right;
};


class EmptyNode : public Node {
public:
    EmptyNode();
    bool Evaluate(const Date &date, const std::string &event) const override;
};