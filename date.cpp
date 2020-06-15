#include "date.h"

Date::Date(int year, int month, int day)
    : Year(year), Month(month), Day(day) {}

Date::Date()
    : Year(0), Month(0), Day(0) {}


int Date::GetYear() const {
    return Year;
}

int Date::GetMonth() const {
    return Month;
}

int Date::GetDay() const {
    return Day;
}

Date ParseDate(std::istream &is) {
    std::string date;
    is >> date;
    std::istringstream date_stream(date);
    bool ok = true;

    int year;
    ok = ok && (date_stream >> year);
    ok = ok && (date_stream.peek() == '-');
    date_stream.ignore(1);

    int month;
    ok = ok && (date_stream >> month);
    ok = ok && (date_stream.peek() == '-');
    date_stream.ignore(1);

    int day;
    ok = ok && (date_stream >> day);
    ok = ok && date_stream.eof();

    if (!ok) {
        throw std::logic_error("Wrong date format: " + date);
    }

    return {year, month, day};
}

std::ostream &operator<<(std::ostream &os, const Date &d) {
    os << std::setfill('0');
    return os << std::setw(4) << d.GetYear() << '-'
              << std::setw(2) << d.GetMonth() << '-'
              << std::setw(2) << d.GetDay();
}

bool operator<(const Date &lhs, const Date &rhs) {
    return std::make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) <
           std::make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator<=(const Date &lhs, const Date &rhs) {
    return !(rhs < lhs);
}

bool operator>(const Date &lhs, const Date &rhs) {
    return rhs < lhs;
}

bool operator>=(const Date &lhs, const Date &rhs) {
    return !(lhs < rhs);
}

bool operator==(const Date &lhs, const Date &rhs) {
    return !((lhs < rhs) || (rhs < lhs));
}

bool operator!=(const Date &lhs, const Date &rhs) {
    return !(lhs == rhs);
}
