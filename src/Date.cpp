#ifndef DATE_CPP
#define DATE_CPP

#include <string>
#include <sstream>
#include "../include/Date.hpp"


Date::Date() {
    m_year = 0;
    m_month = 0;
    m_day = 0;
    m_hour = 0;
    m_minute = 0;
}

Date::Date(int y, int m, int d, int h, int mi) {
    m_year = y;
    m_month = m;
    m_day = d;
    m_hour = h;
    m_minute = mi;
}
Date::Date(std::string dateString) {
    bool whetherValid = true;
    //valid?
    // length
    if (16 != dateString.length()) { whetherValid = false; }
    //subtract
    int subtract_counter = 0;
    for (int i = 0; i < 16; i++) {
        if ('-' == dateString[i]) { subtract_counter++; }
    }
    if (2 != subtract_counter) { whetherValid = false; }
    // operator position
    if (dateString[4] != '-' || dateString[7] != '-' || dateString[10] != '/' || dateString[13] != ':') {
        whetherValid = false;
    }
    int index[12] = { 0, 1, 2, 3, 5, 6, 8, 9, 11, 12, 14, 15 };
    for (int i = 0; i < 12; i++) {
        if (!(dateString[index[i]] >= '0' && dateString[index[i]] <= '9')) {
            whetherValid = false;
        }
    }

    if (whetherValid == false) {
        *this = Date(0, 0, 0, 0, 0);
    } else {
        std::stringstream ss;

        char hold;
        ss << dateString;
        int year, month, day, hour, min;
        ss >> year >> hold >>
            month >> hold >>
            day >> hold >>
            hour >> hold >>
            min;
        *this = Date(year, month, day, hour, min);
    }
}

int Date::getYear(void) const {
    return m_year;
}
void Date::setYear(int year) {
    m_year = year;
}
int Date::getMonth(void) const {
    return m_month;
}
void Date::setMonth(int month) {
    m_month = month;
}
int Date::getDay(void) const {
    return m_day;
}
void Date::setDay(int day) {
    m_day = day;
}
int Date::getHour(void) const {
    return m_hour;
}
void Date::setHour(int hour) {
    m_hour = hour;
}
int Date::getMinute(void) const {
    return m_minute;
}
void Date::setMinute(int minute) {
    m_minute = minute;
}
bool Date::isValid(Date date) {
    if (date.m_year < 1000 || date.m_year > 9999) { return false; }
    if (date.m_minute < 0 || date.m_minute > 59) return false;
    if (date.m_hour < 0 || date.m_hour > 23) return false;
    if (date.m_month < 1 || date.m_month > 12) return false;
    if (date.m_month == 2) { // 是2月
        if ((date.m_year % 4 == 0 && date.m_year % 100 != 0) || (date.m_year % 400 == 0)) { // 闰年
            if (date.m_day < 1 || date.m_day > 29) return false;
        } else { // 平年
            if (date.m_day < 1 || date.m_day > 28) return false;
        }
    }
    else { // 不是2月
        if (date.m_month == 4 || date.m_month == 6 || date.m_month == 9 || date.m_month == 11) { // 小月
            if (date.m_day < 1 || date.m_day > 30) return false;
        } else { // 大月
            if (date.m_day < 1 || date.m_day > 31) return false;
        }
    };
    return true;
}
Date Date::stringToDate(std::string dateString) {
    bool whetherValid = true;
    //valid?
    // length
    if (16 != dateString.length()) { whetherValid = false; }
    //subtract
    int subtract_counter = 0;
    for (int i = 0; i < 16; i++) {
        if ('-' == dateString[i]) { subtract_counter++; }
    }
    if (2 != subtract_counter) { whetherValid = false; }
    // operator position
    if (dateString[4] != '-' || dateString[7] != '-' || dateString[10] != '/' || dateString[13] != ':') {
        whetherValid = false;
    }
    int index[12] = { 0, 1, 2, 3, 5, 6, 8, 9, 11, 12, 14, 15 };
    for (int i = 0; i < 12; i++) {
        if (!(dateString[index[i]] >= '0' && dateString[index[i]] <= '9')) {
            whetherValid = false;
        }
    }

    if (whetherValid == false) {
        return Date(0, 0, 0, 0, 0);
    } else {
        std::stringstream ss;

        char hold;
        ss << dateString;
        int year, month, day, hour, min;
        ss >> year >> hold >>
            month >> hold >>
            day >> hold >>
            hour >> hold >>
            min;
        Date dateToOut(year, month, day, hour, min);
        return dateToOut;
    }
}
std::string Date::dateToString(Date date) {
    if (false == isValid(date)) {
        return std::string("0000-00-00/00:00");
    }
    std::stringstream ss;
    ss.fill('0');
    ss.width(4);
    ss << date.getYear() << '-';
    ss.width(2);
    ss << date.getMonth() << '-';
    ss.width(2);
    ss << date.getDay();
    ss << '/';
    ss.width(2);
    ss << date.getHour() << ':';
    ss.width(2);
    ss << date.getMinute();
    return ss.str();
}
Date & Date::operator=(const Date & date) {
    this -> m_year = date.m_year;
    this -> m_month = date.m_month;
    this -> m_day = date.m_day;
    this -> m_hour = date.m_hour;
    this->m_minute = date.m_minute;
    return *this;
}
bool Date::operator==(const Date & date) const {
    return (m_year == date.m_year && m_month == date.m_month && m_day == date.m_day
        && m_hour == date.m_hour && m_minute == date.m_minute);
}
bool Date::operator>(const Date & date) const {
    if (m_year > date.m_year) {
        return true;
    } else if (m_year < date.m_year){
        return false;
    } else {
        if (m_month > date.m_month) {
            return true;
        } else if (m_month < date.m_month) {
            return false;
        } else {
            if (m_day > date.m_day) {
                return true;
            } else if (m_day < date.m_day) {
                return false;
            } else {
                if (m_hour > date.m_hour) {
                    return true;
                } else if (m_hour < date.m_hour) {
                    return false;
                } else {
                    if (m_minute > date.m_minute) {
                        return true;
                    } else if (m_minute < date.m_minute) {
                        return false;
                    } else {
                        return false;
                    }
                }
            }
        }
    }
}
bool Date::operator<(const Date & date) const {
    if (*this == date || *this > date) {
        return false;
    } else {
        return true;
    }
}
bool Date::operator>=(const Date & date) const {
    if (*this == date || *this > date) {
        return true;
    } else {
        return false;
    }
}
bool Date::operator<=(const Date & date) const {
    if (*this < date || *this == date) {
        return true;
    } else {
        return false;
    }
}
#endif
