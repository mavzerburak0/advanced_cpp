//
// Created by root on 6/10/19.
//


#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>
#include <regex>
#include <cmath>
#include "Client.h"


Client::Client() {

}

Client::~Client() {

}

void Client::writeReady() {
    fd = open(myfifo, O_WRONLY);
    write(fd, "ready", 6);
    state = 1;
}

std::string Client::readText() {
    fd = open(myfifo, O_RDONLY);
    read(fd, buf, MAX_BUF);
    printf("Received: %s\n", buf);
    std::string buf_string = buf;

    return buf_string;
}

Item Client::constructItem(std::string buf_string) {
    std::regex my_regex (R"(([\w])\s([\d]+)\s<(.+)>\s(\d*)\s(\w+)\s(\d*))");
    std::smatch match;
    regex_match(buf_string, match, my_regex);

    std::string rand_str = match[1].str();
    int subgroup = std::atoi (match[2].str().c_str());
    std::string name = match[3].str();
    int day = std::atoi (match[4].str().c_str() );

    std::string month_name = match[5].str();

    std::vector<std::string> months = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    auto itr = std::find(months.begin(), months.end() - 1, month_name);
    int index = static_cast<int>(std::distance(months.begin(), itr));
    // std::cout << index << std::endl;
    int year = std::atoi (match[6].str().c_str());
    Item * newItem = new Item();
    if (index == 0) {
        Date * newDate = new Date(day, index + 1, year);
        newItem->setTimestamp(*newDate);
    } else if (day == 0) {
        Date * newDate = new Date(day + 1, index, year);
        newItem->setTimestamp(*newDate);
    } else {
        Date * newDate = new Date(day, index, year);
        newItem->setTimestamp(*newDate);
    }


    newItem->setName(name);
    newItem->setGroup(rand_str[0]);
    newItem->setSubgroup(subgroup);

    state = 0;

    return * newItem;
}

void Client::closeAndExit() {
    write(fd, "exit", 5);
    close(fd);
    unlink(myfifo);
    exit(1);
}



