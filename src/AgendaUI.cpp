#ifndef AGENDAUI_CPP
#define AGENDAUI_CPP

#include "../include/AgendaService.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include "../include/AgendaUI.hpp"



#endif

AgendaUI::AgendaUI() {
    m_userName = "";
    m_userPassword = "";
}

void AgendaUI::OperationLoop(void) {
    // m_agendaService.startAgenda();
    while (true) {
        if (m_userName == "") {
            std::cout << "------------------------- Agenda -------------------------" << std::endl;
            std::cout << "Action :" << std::endl;
            std::cout << "l   - log in agenda by user name and password" << std::endl;
            std::cout << "r   - register an Agenda account" << std::endl;
            std::cout << "q   - quit Agenda" << std::endl;
            std::cout << "----------------------------------------------------------" << std::endl << std::endl;
            std::cout << "Agenda : ~$ ";
        } else {
            std::cout << "------------------------- Agenda -------------------------" << std::endl;
            std::cout <<"Action :" << std::endl;
            std::cout << "o   - log out Agenda" << std::endl;
            std::cout << "dc  - delete Agenda account" << std::endl;
            std::cout << "lu  - list all Agenda user" << std::endl;
            std::cout << "cm  - create a meeting" << std::endl;
            std::cout << "la  - list all meetings" << std::endl;
            std::cout << "las - list all sponsor meetings" << std::endl;
            std::cout << "lap - list all participate meetings" << std::endl;
            std::cout << "qm  - query meeting by title" << std::endl;
            std::cout << "qt  - query meeting by time interval" << std::endl;
            std::cout << "dm  - delete meeting by title" << std::endl;
            std::cout << "da  - delete all meetings" << std::endl;
            // std::cout << "更改密码" << std::endl;
            // std::cout << "更改会议议程" << std::endl;
            std::cout << "----------------------------------------------------------" << std::endl << std::endl;
            std::cout << std::endl;
            std::cout << "Agenda@" << m_userName << " # ";
        }
        std::string ope;
        std::cin >> ope;
        if (ope == "q") {
            break;
        } else if (false == executeOperation(ope)) {
            std::cout << std::endl << std::endl;
          // std::cout << "执行失败" << std::endl << std::endl;
        }
    }
    m_agendaService.quitAgenda();
}

void AgendaUI::startAgenda(void) {
    m_agendaService.startAgenda();
}

std::string AgendaUI::getOperation() {
    std::cout << "------------------------- Agenda -------------------------" << std::endl;
    std::cout << "Action :" << std::endl;
    std::cout << "o   - log out Agenda" << std::endl;
    std::cout << "dc  - delete Agenda account" << std::endl;
    std::cout << "lu  - list all Agenda user" << std::endl;
    std::cout << "cm  - create a meeting" << std::endl;
    std::cout << "la  - list all meetings" << std::endl;
    std::cout << "las - list all sponsor meetings" << std::endl;
    std::cout << "lap - list all participate meetings" << std::endl;
    std::cout << "qm  - query meeting by title" << std::endl;
    std::cout << "qt  - query meeting by time interval" << std::endl;
    std::cout << "dm  - delete meeting by title" << std::endl;
    std::cout << "da  - delete all meetings" << std::endl;
    // std::cout << "更改密码" << std::endl;
    // std::cout << "更改会议议程" << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl << std::endl;
    std::cout << std::endl;
    std::cout << "Agenda@" << m_userName << " # ";

    std::string out_ope;
    std::cin >> out_ope;
    std::cout << std::endl;
    return out_ope;
}

bool AgendaUI::executeOperation(std::string op) {
    if (m_userName == "" /* && (op == "用户登录" || op == "用户注册") */ ) {
        // 无密码，未登录
        if (op == "l") {
            userLogIn();
        } else if (op == "r"){
            userRegister();
        } else {
            // std::cout << "亲，请按提示操作哦~" << std::endl;
            return false;
        }
    } else if (m_userName != ""){
        // 有密码，已登录
        if (op == "o") {
            userLogOut();
        } else if (op == "dc") {
            deleteUser();
        } else if (op == "lu") {
            listAllUsers();
        } else if (op == "cm") {
            createMeeting();
        } else if (op == "la") {
            listAllMeetings();
        } else if (op == "las") {
            listAllSponsorMeetings();
        } else if (op == "lap") {
            listAllParticipateMeetings();
        } else if (op == "qm") {
            queryMeetingByTitle();
        } else if (op == "qt") {
            queryMeetingByTimeInterval();
        } else if (op == "dm") {
            deleteMeetingByTitle();
        } else if (op == "da") {
            deleteAllMeetings();
        }/* else if (op == "更改密码") {
            userChangePassword();
        } else if (op == "更改会议日程") {
            changeMeetingInterval();
        } */else {
            // std::cout << "亲，请按提示操作哦~" << std::endl;
            return false;
        }
    }
    return true;
}

void AgendaUI::userLogIn(void) {
    std::cout << std::endl;
    std::cout << "[log in] [user name] [password]" << std::endl;
    std::cout << "[log in] ";
    std::string userName;
    std::cin >> userName;
    std::string password;
    std::cin >> password;
    if (true == m_agendaService.userLogIn(userName, password)) {
        m_userName = userName;
        m_userPassword = password;
        std::cout << "[log in] succeed!" << std::endl << std::endl;
    } else {
        std::cout << "[error] log in fail！" << std::endl << std::endl;
    }
}

void AgendaUI::userRegister(void) {
    std::cout << std::endl;
    std::cout << "[register] [user name] [password] [email] [phone]" << std::endl;
    std::cout << "[register] ";
    std::string userName;
    std::cin >> userName;
    std::string password;
    std::cin >> password;
    std::string email;
    std::cin >> email;
    std::string phone;
    std::cin >> phone;
    if (true == m_agendaService.userRegister(userName, password, email, phone)) {
        std::cout << "[register] succeed!" << std::endl;
    } else {
        std::cout << "[error] register fail!" << std::endl;
    }
    std::cout << std::endl;
}
/*
void AgendaUI::userChangePassword(void) {
    std::cout << "输入你原来的密码之后点击回车键" << std::endl;
    std::string old_passward;
    std::cin >> old_passward;
    if (old_passward != m_userPassword) {
        std::cout << "更改密码失败" << std::endl;
    } else {
        std::cout << "输入你的新密码之后点击回车键" << std::endl;
        std::string new_password;
        std::cin >> new_password;
        if (true == m_agendaService.user_change_password(m_userName, new_password)) {
            m_userPassword = new_password;
            std::cout << "更改密码成功" << std::endl;
        } else {
            std::cout << "更改密码失败" << std::endl;
        }
    }
}
*/
void AgendaUI::deleteMeetingByTitle(void) {
    std::cout << "[delete meeting] [title]" << std::endl;
    std::cout << "[delete meeting] ";
    std::string title_to_del;
    std::cin >> title_to_del;
    if (true == m_agendaService.deleteMeeting(m_userName, title_to_del)) {
        std::cout << "[delete meeting by title] succeed!" << std::endl;
    } else {
        std::cout << "[error] delete meeting fail!" << std::endl;
    }
    std::cout << std::endl;
}

void AgendaUI::deleteAllMeetings(void) {
    if (true == m_agendaService.deleteAllMeetings(m_userName)) {
        std::cout << "[delete all meetings] succeed!" << std::endl;
    } else {
        std::cout << "[error] delete fail!" << std::endl;
    }
    std::cout << std::endl;
}
/*
void AgendaUI::changeMeetingInterval(void) {
    std::cout << "输入你想改变的会议标题" << std::endl;
    std::string title_to_change;
    std::cin >> title_to_change;
    std::cout << "输入你重新设置的开始日期后轻敲回车键" << std::endl;
    std::string new_startDate;
    std::cin >> new_startDate;
    std::cout << "输入你重新设置的结束日期后轻敲回车键" << std::endl;
    std::string new_endDate;
    std::cin >> new_endDate;
    if (true == m_agendaService.meeting_change_interval(title_to_change, new_startDate, new_endDate)) {
        std::cout << "会议更改成功" << std::endl;
    } else {
        std::cout << "会议更改失败" << std::endl;
    }
}
*/
void AgendaUI::printMeetings(std::list<Meeting> meetings) {
    std::cout << std::left << std::setw(16) << "title";
    std::cout << std::left << std::setw(18) << "sponsor";
    std::cout << std::left << std::setw(20) << "start time";
    std::cout << std::left << std::setw(20) << "end time";
        std::cout << std::left << "participator" << std::endl;
    for (auto i = meetings.begin(); i != meetings.end(); i++) {
        std::cout << std::left << std::setw(16) << i->getTitle();
        std::cout << std::left << std::setw(18) << i->getSponsor();
        std::cout << std::left << std::setw(20) << Date::dateToString(i->getStartDate());
        std::cout << std::left << std::setw(20) << Date::dateToString(i->getEndDate());
        auto parOfMeeting = i->getParticipator();
        for (auto j = parOfMeeting.begin(); j != parOfMeeting.end(); j++) {
            if (j != parOfMeeting.begin()) {
                std::cout << ',';
            }
            std::cout << *j;
        }
        std::cout << std::endl;
    }
}
/*
void AgendaUI::printEmptyLine() {
    std::cout << std::endl;
}

void AgendaUI::printHead() {
    std::cout << "------------------------- Agenda -------------------------" << std::endl;
}

void AgendaUI::printTail() {
    std::cout << "----------------------------------------------------------" << std::endl;
    std::cout << std::endl;
}
*/
void AgendaUI::quitAgenda(void) {
    m_agendaService.quitAgenda();
}

void AgendaUI::userLogOut(void) {
    m_userName = "";
    m_userPassword = "";
    // std::cout << "用户注销成功" << std::endl;
}

void AgendaUI::deleteUser(void) {
    std::cout << std::endl;
    if (true == m_agendaService.deleteUser(m_userName, m_userPassword)) {
        std::cout << "[delete agenda account] succeed!" << std::endl;
        userLogOut();
    } else {
        std::cout << "[error] No such user!" << std::endl;
    }
}

void AgendaUI::listAllUsers(void) {
    std::cout << std::endl;
    std::cout << "[list all users]" << std::endl;
    std::cout << std::endl;
    std::cout << std::left << std::setw(8) << "name";
    std::cout << std::left << std::setw(16) << "email";
    std::cout << std::left << std::setw(11) << "phone" << std::endl;
    auto all_users = m_agendaService.listAllUsers();
    for (auto i = all_users.begin(); i != all_users.end(); i++) {
        std::cout << std::left << std::setw(8) << i->getName();
        std::cout << std::left << std::setw(16) << i->getEmail();
        std::cout << std::left << std::setw(11) << i->getPhone() << std::endl;
    }
}

void AgendaUI::createMeeting(void) {
    std::cout << std::endl;
    
    // read participator
    std::cout << "[creat meeting] [the number of participators]" << std::endl;
    std::cout << "[creat meeting] ";
    int number_of_par = 0;
    std::cin >> number_of_par;
    // test number_of_par
    // std::cout << "number_of_par:" << number_of_par << std::endl;
    //

    std::vector<std::string> participators;
    std::string par_name;
    for (int i = 1; i <= number_of_par; i++) {
        std::cout << "[creat meeting] [please enter the participator " << i << " ]" << std::endl;
        std::cout << "[creat meeting] ";
        std::cin >> par_name;
        participators.push_back(par_name);
    }

    // test participators in
    /*
    std::cout << std::endl;
    std::cout << "all pars" << std::endl;
    for (auto i = participators.begin(); i != participators.end(); i++) {
        std::cout << "\t" << *i << std::endl;
    }
    */
    
    //

    // other info
    std::cout << "[create meeting] [title] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]" << std::endl;
    std::cout << "[create meeting] ";
    std::string title, startDate, endDate;
    std::cin >> title >> startDate >> endDate;
    if (true == m_agendaService.createMeeting(m_userName, title, startDate, endDate, participators)) {
        std::cout << "[create meeting] succeed!" << std::endl;
    } else {
        std::cout << "[create meeting] error!" << std::endl;
    }
}

void AgendaUI::listAllMeetings(void) {
    std::cout << std::endl;
    std::cout << "[list all meeting]";
    std::cout << std::endl;
    printMeetings(m_agendaService.listAllMeetings(m_userName));
}

void AgendaUI::listAllSponsorMeetings(void) {
    std::cout << std::endl;
    std::cout << "[list all sponsor meetings]";
    std::cout << std::endl;
    printMeetings(m_agendaService.listAllSponsorMeetings(m_userName));
}

void AgendaUI::listAllParticipateMeetings(void) {
    std::cout << std::endl;
    std::cout << "[list all participate meetings]";
    std::cout << std::endl;
    printMeetings(m_agendaService.listAllParticipateMeetings(m_userName));
}

void AgendaUI::queryMeetingByTitle(void) {
    std::cout << std::endl;
    std::cout << "[quert meetings] [title]:" << std::endl;
    std::cout << "[query meetings] ";
    std::string title;
    std::cin >> title;
    std::cout << std::endl;
    //std::cout << "[query meetings]" << std::endl;
    auto all_req_meeting = m_agendaService.meetingQuery(m_userName, title);
    printMeetings(all_req_meeting);
}

void AgendaUI::queryMeetingByTimeInterval(void) {
    std::cout << "[query meetings] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]";
    std::cout << "[query meetings] ";
    std::string startDate;
    std::cin >> startDate;
    std::string endDate;
    std::cin >> endDate;
    std::cout << std::endl;
    std::cout << "[query meetings]" << std::endl;;
    printMeetings(m_agendaService.meetingQuery(m_userName, startDate, endDate));
}
