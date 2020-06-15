#pragma once

#include "date.h"

#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <iostream>

class Database {
public:
    void Add(const Date &date, const std::string &event);
    void Print(std::ostream &os) const;

    template <typename Func>
    int RemoveIf(Func predicate) {
        int count = 0;

        for (auto data_it = data.begin(); data_it != data.end();) {
            const auto &date = data_it->first;
            auto &events = data_it->second;
            auto new_end_it = std::stable_partition(events.begin(), events.end(),
                [date, predicate](const std::string &event) {
                    return !predicate(date, event);
                }); 
            auto old_size = events.size();
            events.erase(new_end_it, events.end());
            count += old_size - events.size();

            if (events.empty()) {
                data.erase(data_it++);
            } else {
                ++data_it;
            }
        }

        for (auto data_it = unique_data.begin(); data_it != unique_data.end();) {
            for (auto it = data_it->second.begin(); it != data_it->second.end();) {
                if (predicate(data_it->first, *it)) {
                    data_it->second.erase(it++);
                } else {
                    ++it;
                }
            }
            if (data_it->second.empty()) {
                unique_data.erase(data_it++);
            } else {
                ++data_it;
            }
        }

        return count;
    }

    template <typename Func>
    std::vector<std::pair<Date, std::string>> FindIf(Func predicate) const {
        std::vector<std::pair<Date, std::string>> temp;

        for (const auto &day : data) {
            for (const auto &event : day.second) {
                if (predicate(day.first, event)) {
                    temp.push_back({day.first, event});
                }
            }
        }
        return temp;
    }

    std::pair<Date, std::string> Last(const Date &date) const;

private : 
    std::map<Date, std::vector<std::string>> data;
    std::map<Date, std::set<std::string>> unique_data;
};


std::ostream &operator<<(std::ostream &os, const std::pair<Date, std::string> &day);

