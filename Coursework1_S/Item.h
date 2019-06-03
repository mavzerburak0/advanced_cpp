//
// Created by root on 5/14/19.
//

#ifndef COURSEWORK1_S_ITEM_H
#define COURSEWORK1_S_ITEM_H


#include <string>
#include <vector>
#include <ostream>
#include "Date.h"


using namespace std;

class Item {
private:

    char Group; // Any from range 'A'...'Z'
    int Subgroup; // Any from range 0...99
    string Name;
    Date Timestamp;
public:
    Item();
    Item(char, int, string, Date);
    ~Item();
    char getGroup() const;
    void setGroup(char Group);
    int getSubgroup() const;
    void setSubgroup(int Subgroup);
    const string &getName() const;
    void setName(const string &Name);
    const Date &getTimestamp() const;
    void setTimestamp(const Date &Timestamp);

    int returnRandomInt();
    string returnRandomName();
    char returnRandomChar();


    friend ostream &operator<<(ostream &os, const Item &item);

};

#endif //COURSEWORK1_S_ITEM_H
