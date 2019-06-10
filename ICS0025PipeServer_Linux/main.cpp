#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>
#include <vector>
#include <cstring>
#include <iostream>
#include <random>
#include "Date.h"

#define MAX_BUF 1024


int main() {

    int fd;
    char * myfifo = const_cast<char *>("/tmp/myfifo");
    char buf[MAX_BUF];
    int state = 0;


    std::cout << "Server ready..." << std::endl;
    switch(state) {
        case 0:
            fd = open(myfifo, O_RDONLY);
            read(fd, buf, MAX_BUF);
            printf("Received: %s\n", buf);
            state = 1;
        case 1:
            fd = open(myfifo, O_WRONLY);
            sleep(4);
            std::string str;
            std::ifstream in;
            in.open("../Birds.txt");
            std::vector<std::string> birds;
            if (!in) {
                std::cerr << "Unable to open file Birds.txt";
                exit(1);
            } else {
                while (std::getline(in, str)) {
                    birds.push_back(str);
                }
            }

            std::random_device random_device;
            std::mt19937 engine{random_device()};
            std::uniform_int_distribution<int> dist(0, birds.size() - 1);
            std::srand(std::time(nullptr));
            int randomInt = static_cast<int>(random() % 99) + 1;
            char randomChar =  static_cast<char>(random() % 26 + 65);
            std::string charToStr;
            charToStr = randomChar;
            Date * dateOne = new Date(1, 1, 1960);
            Date * dateTwo = new Date(1, 1, 2019);
            Date randomDate = Date::CreateRandomDate(*dateOne, *dateTwo);

            std::string strToSend = charToStr + " " +
                    std::to_string(randomInt) + " " + "<" + birds[dist(engine)] + ">" +
                    " " + randomDate.ToString() + "\0";
            strcpy(buf, strToSend.c_str());
            write(fd, buf, sizeof(buf));


    }
    main();
    return 0;
}

