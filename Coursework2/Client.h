//
// Created by root on 6/10/19.
//

#ifndef COURSEWORK2_CLIENT_H
#define COURSEWORK2_CLIENT_H

#include <string>
#include "Item.h"

#define MAX_BUF 1024


class Client {
private:
    int fd;
    char * myfifo = const_cast<char *>("/tmp/myfifo");
    char buf[MAX_BUF];
    int state = 0;
public:
    Client();
    ~Client();
    void writeReady();
    std::string readText();
    Item constructItem(std::string buf_string);
    void closeAndExit();

};


#endif //COURSEWORK2_CLIENT_H
