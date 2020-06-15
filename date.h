#pragma once

#include <iostream>
#include <iomanip>
#include <tuple>


class Date {
public:
    Date(int year, int month, int day);
    Date();

    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;

private:
    int Year;
    int Month;
    int Day;
};

Date ParseDate(std::istream &is);

std::ostream &operator<<(std::ostream &os, const Date &d);

bool operator<(const Date &lhs, const Date &rhs);
bool operator<=(const Date &lhs, const Date &rhs);
bool operator>(const Date &lhs, const Date &rhs);
bool operator>=(const Date &lhs, const Date &rhs);
bool operator==(const Date &lhs, const Date &rhs);
bool operator!=(const Date &lhs, const Date &rhs);
