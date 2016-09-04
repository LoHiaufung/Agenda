#ifndef MEETING_CPP
#define MEETING_CPP

#include "../include/Date.hpp"
#include "../include/Meeting.hpp"



/*
Meeting::Meeting() {
    m_sponsor = "";
    m_participators = std::vector<std::string>();
    m_startDate = Date();
    m_endDate = Date();
    m_title = "";
}
*/
Meeting::Meeting(std::string sponsor, std::vector<std::string> t_participator, Date startTime, Date endTime, std::string title) {
    m_sponsor = sponsor;
    m_participators = t_participator;
    m_startDate = startTime;
    m_endDate = endTime;
    m_title = title;
}

Meeting::Meeting(const Meeting & t_meeting) {
    m_sponsor = t_meeting.getSponsor();
    m_participators = t_meeting.getParticipator();
    m_title = t_meeting.getTitle();
    m_startDate = t_meeting.getStartDate();
    m_endDate = t_meeting.getEndDate();
}

std::string Meeting::getSponsor(void) const {
    return m_sponsor;
}

void Meeting::setSponsor(std::string sponsor) {
    m_sponsor = sponsor;
}

std::vector<std::string> Meeting::getParticipator(void) const {
    std::vector<std::string> parToOut;
    for (auto i = m_participators.begin(); i != m_participators.end(); i++) {
        parToOut.push_back(*i);
    }
    return parToOut;
 }

void Meeting::setParticipator(const std::vector<std::string> t_participators) {
    m_participators.clear();
    for (auto i = t_participators.begin(); i != t_participators.end(); i++) {
        m_participators.push_back(*i);
    }
}


Date Meeting::getStartDate(void) const {
    return m_startDate;
}

void Meeting::setStartDate(Date startTime) {
    m_startDate = startTime;
}

Date Meeting::getEndDate(void) const {
    return m_endDate;
}

void Meeting::setEndDate(Date endTime) {
    m_endDate = endTime;
}

std::string Meeting::getTitle(void) const {
    return m_title;
}

void Meeting::setTitle(std::string title) {
    m_title = title;
}

bool Meeting::isParticipator(const std::string t_username) const {
    for (auto i = m_participators.begin(); i != m_participators.end(); i++) {
        if (*i == t_username) {
            return true;
        }
    }
    return false;
}

#endif