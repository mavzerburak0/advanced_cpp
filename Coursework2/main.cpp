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
#include "Item.h"
#include "Client.h"
#include "Data.h"

#define MAX_BUF 1024




int main() {

    Data * data = new Data(100);
    char * myfifo = const_cast<char *>("/tmp/myfifo");
    mkfifo(myfifo, 0666);
//    char buf[MAX_BUF];
    int state = 0;
    Client * client = new Client();
    std::vector<Item> items;
    // Named pipe creation with read-write permissions


    int input;
    std::cout << "1. Connect" << std::endl;
    std::cout << "2. Exit" << std::endl;
    std::cin >> input;

    switch(input) {
        case 1:
            switch(state) {
                case 0:
                    client->writeReady();
                case 1:
                    std::string buf_string = client->readText();
                    std::cout << "Size of received data: " << sizeof(buf_string) << " bytes" << std::endl;
                    items.push_back(client->constructItem(buf_string));

            }
            main();
        case 2:
            break;
        default:
            break;
    }

    for (auto const & item : items) {
        std::cout << item.getGroup() << " " << item.getSubgroup() <<
        " " << item.getName() << " " << item.getTimestamp().ToString() << std::endl;
    }


    return 0;

}