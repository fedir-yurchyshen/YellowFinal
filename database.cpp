#include "database.h"


void Database::Add(const Date &date, const std::string &event) {
    if (unique_data[date].insert(event).second) {
        data[date].push_back(event);
    }
}


void Database::Print(std::ostream &os) const {
    for (const auto &day : data) {
        for (const auto &event : day.second) {
            os << day.first << " " << event << std::endl;
        }
    }
}


std::pair<Date, std::string> Database::Last(const Date &date) const {
    auto it = data.upper_bound(date);

    if (it != data.begin()) {
        --it;
        
            return {it->first, it->second.back()};
        
    }
    throw std::invalid_argument("");
}


std::ostream &operator<<(std::ostream &os, const std::pair<Date, std::string> &day) {
    os << day.first << " " << day.second;
}
