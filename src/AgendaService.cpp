#ifndef AGENDASERVICE_CPP
#define AGENDASERVICE_CPP

#include "../include/AgendaService.hpp"
#include "../include/Storage.hpp"
#include "../include/User.hpp"
#include <iostream>

AgendaService::AgendaService() {
    startAgenda();
}

AgendaService::~AgendaService() {
    /*
    if (nullptr != m_storage) {
        delete m_storage;
    }
    */
}

bool AgendaService::userLogIn(std::string userName, std::string password) {
    Storage* p_storage = m_storage.get();
    
    std::list<User> req_uesr_list = p_storage -> queryUser([userName](const User& user) {return userName == user.getName();});
    if (true == req_uesr_list.empty()) {
        return false;
    } else if (password != req_uesr_list.front().getPassword()) {
        return false;
    } else {
        return true;
    }
}

bool AgendaService::userRegister(std::string userName, std::string password, std::string email, std::string phone) {
    Storage* p_storage = m_storage.get();
    
    std::list<User> req_uesr_list = p_storage->queryUser([userName](const User& user) {return userName == user.getName();});
    if (true == req_uesr_list.empty()) {
        User new_user(userName, password, email, phone);
        p_storage -> createUser(new_user);
        return true;
    } else {
        return false;
    }
}

bool AgendaService::deleteUser(std::string userName, std::string password) {
    Storage* p_storage = m_storage.get();
    
    std::list<User> req_uesr_list = p_storage->queryUser([userName](const User& user) {return userName == user.getName();});
    if (true == req_uesr_list.empty()) {
        return false;
    } else if (password != req_uesr_list.front().getPassword()) {
        return false;
    } else {
        m_storage->deleteMeeting([userName](const Meeting& meeting) {
            return (userName == meeting.getSponsor() || true == meeting.isParticipator(userName));});
        p_storage->deleteUser([userName](const User & user_to_del) {return userName == user_to_del.getName();});  
        return true;
    }
}
/*
bool AgendaService::user_change_password(std::string userName, std::string new_password) {
    int be_changed_account = 0;
    be_changed_account = m_storage->updateUser([userName](const User& user) {return userName == user.getName();},
        [new_password](User& user) {user.setPassword(new_password);});
    if (0 == be_changed_account) {
        return false;
    } else {
        return true;
    }
}
*/
std::list<User> AgendaService::listAllUsers(void) const{
    Storage* p_storage = m_storage.get();
    std::list<User> all_user_list = p_storage->queryUser([](const User& user) {return true;});
    return all_user_list;
}

bool AgendaService::createMeeting(const std::string userName, const std::string title,
    const std::string startDate, const std::string endDate,
    const std::vector<std::string> participator) {
    // title used?
    auto title_use = m_storage->queryMeeting([title](const Meeting& meeting) {return title == meeting.getTitle();});
    if (false == title_use.empty()) { return false; }
    
    // sponsor registered?
    auto sponsor_reg = m_storage->queryUser([userName](const User& user) {return userName == user.getName();});
    if (true == sponsor_reg.empty()) {
        return false;
    }

    // participator registered?
    if (true == participator.empty()) {
        return false;
    } else {
        for (auto i = participator.begin(); i != participator.end(); i++) {
            std::string parName = *i;
            auto par_reg = m_storage->queryUser([parName](const User& user) {return parName == user.getName();});
            if (true == par_reg.empty()) {
                return false;
            }
        }
    }

    //sponsor in participartors?
    for (auto i = participator.begin(); i != participator.end(); i++) {
        if (userName == *i) { return false; }
    }

    // participators duplicate?
    if (0 == participator.size()) {
        return false;
    } else if (participator.size() > 1) {
        for (auto i = participator.begin(); i != participator.end(); i++) {
            auto j = i;
            j++;
            //compare end;
            if (j == participator.end()) { 
                break;
            } else {
                for (auto k = j; k != participator.end(); k++) {
                    if (*i == *k) {
                        return false;
                    }
                }
            }
        }    
    }

    // 判断起止时间是否合法
    if (false == Date::isValid(Date::stringToDate(startDate))) { return false; }
    if (false == Date::isValid(Date::stringToDate(endDate))) { return false; }
    if (Date::stringToDate(startDate) >= Date::stringToDate(endDate)) { return false; }
    //
    /*test in, OK!
    std::cout << "all pamra in: " << std::endl;
    std::cout << '\t' << userName << ' ' << startDate << ' ' << endDate << std::endl;
    std::cout << "par: ";
    for (auto i = participator.begin(); i != participator.end(); i++) {
        std::cout << *i << ' ';
    }
    std::cout << std::endl;
    // end test in */

    // sponsor time overlap?
    auto meetingOfSponsor = m_storage->queryMeeting(
        [userName](const Meeting& meeting) {
        return ((userName == meeting.getSponsor()) || (true == meeting.isParticipator(userName)));
        }
    );
    if (false == meetingOfSponsor.empty()) {
        // test meetingOfSponsor
        /*
        std::cout << "meeting of sponsor: " << std::endl;
        for (auto i = meetingOfSponsor.begin(); i != meetingOfSponsor.end(); i++) {
            std::cout << '\t'  << "title: "  << i->getTitle();
            std::cout << '\t' << "sponsor: "<<i->getSponsor();
            std::cout << 't' << "startDate: "<<Date::dateToString(i->getStartDate());
            std::cout << 't' << "endDate: "<<Date::dateToString(i->getEndDate());
            auto all_par = i->getParticipator();
            std::cout << "participartor: " << std::endl;
            for (auto j = all_par.begin(); j != all_par.end(); j++) {
                std::cout << *j;
                std::cout << ',';
            }
            std::cout << std::endl;
        }
        */
        //test meetingOfSponsor

        for (auto i = meetingOfSponsor.begin(); i != meetingOfSponsor.end(); i++) {
            if (i->getStartDate() < Date::stringToDate(startDate) && Date::stringToDate(startDate) < i->getEndDate()) {
                return false;
            }
            if (i->getStartDate() < Date::stringToDate(endDate) && Date::stringToDate(endDate) < i->getEndDate()) {
                return false;
            }
            if (Date::stringToDate(startDate) < i->getStartDate() && i->getStartDate() < Date::stringToDate(endDate)) {
                return false;
            }
            if (Date::stringToDate(startDate) < i->getEndDate() && i->getEndDate() < Date::stringToDate(endDate)) {
                return false;
            }
            if (Date::stringToDate(startDate) == i->getStartDate() && Date::stringToDate(endDate) == i->getEndDate()) {
                return false;
            }
        }
    }
    // Sponsor time overlap? end

    //participator time overlap?
    for (auto everyParticipator = participator.begin(); everyParticipator != participator.end(); everyParticipator++) {
        std::string one_par = *everyParticipator;
        auto meetingOfpar = m_storage->queryMeeting(
                [one_par](const Meeting& meeting) {
                return ((one_par == meeting.getSponsor()) || (true == meeting.isParticipator(one_par)));
            }
        );
        if (false == meetingOfpar.empty()) {
            for (auto i = meetingOfpar.begin(); i != meetingOfpar.end(); i++) {
                if (i->getStartDate() < Date::stringToDate(startDate) && Date::stringToDate(startDate) < i->getEndDate()) {
                    return false;
                }
                if (i->getStartDate() < Date::stringToDate(endDate) && Date::stringToDate(endDate) < i->getEndDate()) {
                    return false;
                }
                if (Date::stringToDate(startDate) < i->getStartDate() && i->getStartDate() < Date::stringToDate(endDate)) {
                    return false;
                }
                if (Date::stringToDate(startDate) < i->getEndDate() && i->getEndDate() < Date::stringToDate(endDate)) {
                    return false;
                }
                if (Date::stringToDate(startDate) == i->getStartDate() && Date::stringToDate(endDate) == i->getEndDate()) {
                    return false;
                }
            }
        }
    }

        Meeting meeting_to_add;
        meeting_to_add.setTitle(title);
        meeting_to_add.setSponsor(userName);
        meeting_to_add.setParticipator(participator);
        meeting_to_add.setStartDate(Date::stringToDate(startDate));
        meeting_to_add.setEndDate(Date::stringToDate(endDate));
        m_storage->createMeeting(meeting_to_add);
        return true;
}

std::list<Meeting> AgendaService::meetingQuery(std::string userName, std::string title) const {
    Storage* p_storage = m_storage.get();
    std::list<Meeting> req_meeting = p_storage -> queryMeeting([userName, title](const Meeting& meeting) {
        if ((true == meeting.isParticipator(userName) || userName == meeting.getSponsor()) && 
            title == meeting.getTitle()) {
            return true;
        } else {
            return false;
        }
    });
    return req_meeting;
}

std::list<Meeting> AgendaService::meetingQuery(std::string userName, std::string startDate, std::string endDate) const {
    if (false == Date::isValid(Date::stringToDate(startDate))) { return std::list<Meeting>(); }
    if (false == Date::isValid(Date::stringToDate(endDate))) { return std::list<Meeting>(); }
    if (Date::stringToDate(startDate) > Date::stringToDate(endDate)) {return std::list<Meeting>();}
    
    Storage* p_storage = m_storage.get();
    std::list<Meeting> req_meeting = p_storage->queryMeeting([userName, startDate, endDate](const Meeting& meeting) {
        if ((true == meeting.isParticipator(userName) || userName == meeting.getSponsor()) &&
            (Date::stringToDate(startDate) <= meeting.getStartDate() && meeting.getStartDate() <= Date::stringToDate(endDate))
            || Date::stringToDate(startDate) <= meeting.getEndDate() && meeting.getEndDate() <= Date::stringToDate(endDate)) {
            return true;
        } else if (true == meeting.isParticipator(userName) && userName == meeting.getSponsor()){
            if (meeting.getStartDate() <= Date::stringToDate(startDate) && Date::stringToDate(startDate) <= meeting.getEndDate()) {
                return true;
            }
            if (meeting.getStartDate() <= Date::stringToDate(endDate) && Date::stringToDate(endDate) <= meeting.getEndDate()) {
                return true;
            } 
        } else {
            return false;
        }
    });
    return req_meeting;
}

std::list<Meeting> AgendaService::listAllMeetings(std::string userName) const {
    Storage* p_storage = m_storage.get();
    std::list<Meeting> req_meeting = p_storage->queryMeeting(
        [userName](const Meeting& meeting) {
        if (userName == meeting.getSponsor() || true == meeting.isParticipator(userName)) {
            return true;
        }
        }
    );
    return req_meeting;
}

std::list<Meeting> AgendaService::listAllSponsorMeetings(std::string userName) const {
    Storage* p_storage = m_storage.get();
    std::list<Meeting> req_meeting = p_storage->queryMeeting(
        [userName](const Meeting& meeting) {
            return (userName == meeting.getSponsor());
        }
    );
    return req_meeting;
}

std::list<Meeting> AgendaService::listAllParticipateMeetings(std::string userName) const {
    Storage* p_storage = m_storage.get();
    std::list<Meeting> req_meeting = p_storage->queryMeeting(
        [userName](const Meeting& meeting) {
        return (true == meeting.isParticipator(userName));
    }
    );
    return req_meeting;
}

bool AgendaService::deleteMeeting(std::string userName, std::string title) {
    Storage* p_storage = m_storage.get();
    std::list<Meeting> req_meeting = meetingQuery(userName, title);
    if (true == req_meeting.empty()) {
        return false;
    } else {
        if (userName != req_meeting.front().getSponsor()) {
            return false;
        } else {
            p_storage->deleteMeeting([userName, title](const Meeting& meeting) {
                return (meeting.getTitle() == title && meeting.getSponsor() == userName);
            });
            return true;
        }
    }
}

bool AgendaService::deleteAllMeetings(std::string userName) {
    Storage* p_storage = m_storage.get();
    auto req_meeting = listAllMeetings(userName);
    if (true == req_meeting.empty()) {
        return false;
    } else {
        p_storage->deleteMeeting([userName](const Meeting& meeting) {return userName == meeting.getSponsor();});
        return true;
    }
}
/*
bool AgendaService::meeting_change_interval(std::string meetingTitle, std::string startDate, std::string endDate) {
    if (Date::stringToDate(startDate) > Date::stringToDate(endDate)) { return false; }
    int be_changed_meetings = m_storage->updateMeeting(
        [meetingTitle](const Meeting& meeting) {return meetingTitle == meeting.getTitle();},
        // filter
        [startDate, endDate](Meeting& meeting) {
            meeting.setStartDate(Date::stringToDate(startDate));
            meeting.setEndDate(Date::stringToDate(endDate));
    });
        // switcher
        if (0 == be_changed_meetings) {
            return false;
        } else {
            return true;
        }
}
*/
/*
bool AgendaService::meeting_whether_time_overlap(std::string userName, std::string startDate, std::string endDate) {
    auto user_all_meeting = listAllMeetings(userName);
    if (true == user_all_meeting.empty()) {
        return false;
    } else {
        for (auto i = user_all_meeting.begin(); i != user_all_meeting.end(); i++) {
            if (i->getStartDate() < Date::stringToDate(startDate) && Date::stringToDate(startDate) < i->getEndDate()) {
                return true;
            }
            if (i->getStartDate() < Date::stringToDate(endDate) && Date::stringToDate(endDate) < i->getEndDate()) {
                return true;
            }
        }
        return false;
    }
}
*/
void AgendaService::startAgenda(void) {
    m_storage = Storage::getInstance();
}

void AgendaService::quitAgenda(void) {
    m_storage->sync();
    m_storage.reset();
}

#endif