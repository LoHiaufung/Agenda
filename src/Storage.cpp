#ifndef AGENDA_STORAGE_CPP
#define AGENDA_STORAGE_CPP

/*
你大爷！！是不是给我自动调用了移动语义？
我找了超久的BUG！
在readFromFile 中
明明STR 是可以读进来的。
但是输出到文件又变成默认值。
*/

#include"../include/Storage.hpp"
#include"../include/Path.hpp"
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <string>
#include <string>
#include <vector>

std::shared_ptr<Storage> Storage::m_instance = std::shared_ptr<Storage>();
bool Storage::readFromFile() {
    // meeting format:
    // ”<sponsor>”,”<participators>”,”<start Datel>”,
    //”<end Date>”,”<title>”
    // read meeting
    // m_meetingList.clear();
    std::ifstream file(Path::meetingPath);
    /* test file read , OK!
    if (file) {
        std::cout << "打开成功" << std::endl;
        std::cout << "file.eof" << file.eof() << std::endl;
        while (!file.eof()) {
            std::string str;
            std::getline(file, str);
            std::cout << str << std::endl;
        }
    }
    */
    // std::cout << "meetingFile " << file.good() << std::endl;
    while (!file.eof()) {
        std::string src;
        std::getline(file, src);
        if (true == src.empty()) { break; }
        // test getline, OK!
        //std::cout << "meeting src: " << src << std::endl;
        //
        int comma_ctr = 0, quot_ctr = 0;
        for (int i = 0; i < src.length(); i++) {
            if (src[i] == ',') { comma_ctr++; }
            if (src[i] == '\"') { quot_ctr++; }
        }
        if (comma_ctr != 4 || quot_ctr != 10) {
            return false;
        }
        //std::cout << "comma:" << comma_ctr << " quot: " <<quot_ctr <<std::endl; 
        int quot[10] = { 0 };
        int quot_in_ptr = 0;
        for (int i = 0; i < src.length(); i++) {
            if (src[i] == '\"') {
                quot[quot_in_ptr] = i;
                quot_in_ptr++;
            }
        }
        std::string sub_str[5];
        int sub_str_ptr = 0;
        for (sub_str_ptr = 0; sub_str_ptr < 5; sub_str_ptr++) {
            for (int index = quot[sub_str_ptr * 2] + 1; index < quot[sub_str_ptr * 2 + 1]; index++) {
                sub_str[sub_str_ptr] += src[index];
            }
        }
        /*
        for (int i = 0; i < 5; i++) {
        std::cout << sub_str[i] << std::endl;
        }
        */
        std::string sponsor = sub_str[0];
        std::string participator_list = sub_str[1];
        std::string startDate = sub_str[2];
        std::string endDate = sub_str[3];
        std::string title = sub_str[4];
        

        // test meeting cut
        // OK!
        /*
        for (int i = 0; i < 5; i++) {
            std::cout << sub_str[i] << ' ';
        }
        std::cout << std::endl;
        */
        //
        int and_ctr = 0;
        for (int i = 0; i < participator_list.length(); i++) {
            if ('&' == participator_list[i]) { and_ctr++; }
        }
        // 	std::cout << "and_ctr: " <<and_ctr << std::endl;
        int equal_and_amount = and_ctr + 2;
        int* and_index = new int[equal_and_amount];
        and_index[0] = -1;
        and_index[equal_and_amount - 1] = participator_list.length();
        int and_index_ptr = 1;
        for (int i = 0; i < participator_list.length(); i++) {
            if (participator_list[i] == '&') {
                and_index[and_index_ptr] = i;
                and_index_ptr++;
            }
        }
        /*
        for (int i = 0; i < equal_and_amount; i++) {
        std::cout << and_index[i] << ' ';

        }
        */
        //std::cout << std::endl;

        //std::cout << participator_list << std::endl;

        std::vector<std::string> participators;
        for (int i = 0; i < equal_and_amount - 1; i++) {

            //	std::cout << i << std::endl;

            std::string hold;
            for (int j = and_index[i] + 1; j < and_index[i + 1]; j++) {
                hold += participator_list[j];
            }

            //	std::cout << hold << std::endl;

            participators.push_back(hold);
            hold.clear();
        }
        //  std::cout << participators.size() << std::endl;
        /*
        for (std::list<std::string>::iterator i = participators.begin(); i != participators.end(); i++) {
            std::cout << *i << std::endl;
        }
        */
        Meeting meeting_to_add(sponsor, 
            participators, 
            Date::stringToDate(startDate), 
            Date::stringToDate(endDate), 
            title);
        delete[] and_index;
       
        m_meetingList.push_back(meeting_to_add);
       // test meetingList push, OK!
       // std::cout << "meetingList size: " << m_meetingList.size() << std::endl;
       //
    }
    // read meeting end;

    // read user begin
    // m_userList.clear();
    std::ifstream userFile(Path::userPath);
    std::string src;
    /* test file read, OK!
    if (userFile) {
        std::cout << "打开成功" << std::endl;
        std::cout << "userFile.eof" << userFile.eof() << std::endl;
        while (!userFile.eof()) {
            std::string str;
            std::getline(userFile, str);
            std::cout << str << std::endl;
        }
    }
    */
    // std::cout << "userFile: " << userFile.good() << std::endl;
    while (!userFile.eof()) {
        std::getline(userFile, src);
        if (true == src.empty()) { break; }
        int comma_ctr = 0, quot_ctr = 0;
        for (int i = 0; i < src.length(); i++) {
            if (src[i] == ',') { comma_ctr++; }
            if (src[i] == '\"') { quot_ctr++; }
        }
        if (comma_ctr != 3 || quot_ctr != 8) {
            return false;
        }
        //std::cout << "comma:" << comma_ctr << " quot: " <<quot_ctr <<std::endl; 
        int quot[8] = { 0 };
        int quot_in_ptr = 0;
        for (int i = 0; i < src.length(); i++) {
            if (src[i] == '\"') {
                quot[quot_in_ptr] = i;
                quot_in_ptr++;
            }
        }
        std::string sub_str[4];
        int sub_str_ptr = 0;
        for (sub_str_ptr = 0; sub_str_ptr < 4; sub_str_ptr++) {
            for (int index = quot[sub_str_ptr * 2] + 1; index < quot[sub_str_ptr * 2 + 1]; index++) {
                sub_str[sub_str_ptr] += src[index];
            }
        }

        /*
        for (int i = 0; i < 4; i++) {
            std::cout << sub_str[i] << std::endl;
        }
        */
        std::string username = sub_str[0];
        std::string password = sub_str[1];
        std::string email = sub_str[2];
        std::string phone = sub_str[3];

        User user_to_add(username, password, email, phone);
        m_userList.push_back(user_to_add);
    }
    // read user finish
    return true;
}
bool Storage::writeToFile() {
   // write meeting
    std::ofstream meetingFile(Path::meetingPath);
    for (auto i = m_meetingList.begin(); i != m_meetingList.end(); i++) {
        // write sponsor
        meetingFile << '"';
        meetingFile << i->getSponsor() << '"';
        // write participators
        meetingFile << ',' << '"';
        auto par_to_mani = i->getParticipator();
        auto j = par_to_mani.begin();
        for (int k = 0; k < par_to_mani.size(); k++) {
            meetingFile << *j;
            if (k != par_to_mani.size() - 1) {
                meetingFile << '&';
            }
            j++;
        }
        meetingFile << '"' << ',';
        // write startDate
        meetingFile << '"' << Date::dateToString(i->getStartDate()) << '"';
        meetingFile << ',';
        // write endDate
        meetingFile << '"' << Date::dateToString(i->getEndDate()) << '"';
        meetingFile << ",";
        // write title
        meetingFile << '"' << i->getTitle() << '"';
        // next line
        meetingFile << std::endl;
    }
    // write meeting end;

    // write user;
    std::ofstream userFile(Path::userPath);
    for (auto i = m_userList.begin(); i != m_userList.end(); i++) {
        // write userName
        userFile << '"' << i->getName() << '"';
        userFile << ',';
        // write password
        userFile << '"' << i->getPassword() << '"';
        userFile << ',';
        // write email
        userFile << '"' << i->getEmail() << '"';
        userFile << ',';
        // write phone
        userFile << '"' << i->getPhone() << '"';
        // nextline
        userFile << std::endl;
    }
    // write user endl
    return true;
}
std::shared_ptr<Storage> Storage::getInstance(void) {
    if (m_instance.get() == nullptr) {
        m_instance = std::shared_ptr<Storage>(new Storage);
    }
    return m_instance;
}
Storage::Storage(){
    readFromFile();
    m_dirty = false;
}
Storage::~Storage() {
    // if (instance_ != nullptr) { delete instance_; }
    writeToFile();
}

void Storage::createUser(const User & new_user) {
    m_userList.push_back(new_user);
    m_dirty = true;

}

std::list<User> Storage::queryUser(std::function<bool(const User&)> filter) const {
    std::list<User> out;
    for (auto i = m_userList.begin(); i != m_userList.end(); i++) {
        if (true == filter(*i)) {
            out.push_back(*i);
        }
    }
    return out;
}

int Storage::updateUser(std::function<bool(const User&)> filter, std::function<void(User&)> switcher) {
    int counter = 0;
    for (auto i = m_userList.begin(); i != m_userList.end(); i++) {
        if (true == filter(*i)) {
            counter++;
            switcher(*i);
        }
    }
    if (0 != counter) {
        m_dirty = true;
    }
    return counter;
}

// bug?
int Storage::deleteUser(std::function<bool(const User&)> filter) {
    int counter = 0;
    // BUG
    for (auto i = m_userList.begin(); i != m_userList.end();) {
        if (true == filter(*i)) {
            counter++;
            i = m_userList.erase(i);
            if (true == m_userList.empty()) { break; }
        } else {
            i++;
        }
    }
   // BUG
   
    if (0 != counter) {
        m_dirty = true;
    }
    
    return counter;
}

void Storage::createMeeting(const Meeting & new_meeting) {
    m_meetingList.push_back(new_meeting);
    m_dirty = true;
}

std::list<Meeting> Storage::queryMeeting(std::function<bool(const Meeting&)> filter) const{
    std::list<Meeting> out;
    for (auto i = m_meetingList.begin(); i != m_meetingList.end(); i++) {
        if (true == filter(*i)) {
            out.push_back(*i);
        }
    }
    return out;
}

int Storage::updateMeeting(std::function<bool(const Meeting&)> filter, std::function<void(Meeting&)> switcher) {
    int counter = 0;
    for (auto i = m_meetingList.begin(); i != m_meetingList.end(); i++) {
        if (true == filter(*i)) {
            counter++;
            switcher(*i);
        }
    }
    if (0 != counter) {
        m_dirty = true;
    }
    return counter;
}

int Storage::deleteMeeting(std::function<bool(const Meeting&)> filter) {
    int counter = 0;
    for (auto i = m_meetingList.begin(); i != m_meetingList.end();) {
        if (true == filter(*i)) {
            counter++;
            i = m_meetingList.erase(i);
            if (true == m_meetingList.empty()) { break; }
        } else {
            i++;
        }
    }
    if (counter != 0) {
        m_dirty = true;
    }
    return counter;
}

bool Storage::sync(void) {
    if (false == m_dirty) {
        return false;
    } else {
        return writeToFile();
    }
}

#endif