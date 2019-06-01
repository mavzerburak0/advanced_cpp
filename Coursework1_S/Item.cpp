#include <utility>

//
// Created by root on 5/14/19.
//

#include "Item.h"
#include <stdio.h>
#include <cstring>
#include <fstream>
#include <vector>
#include <iterator>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <random>

Item::Item() {
    vector<string> names = {"Ashly", "Morton","Garrett","Azalee","Chaya","Myung","Gus","Sanora","Felicia","Trista","Renate","Ricki","Sook","Valentina",
                            "Isabell","Vivienne","Nellie","Alison","Melaine","Guillermo","Bronwyn","Kyoko","Shane","Curtis","Joellen","Elodia",
            "Monica","Jefferson","Leighann","Eugenio"};
    this->Group = static_cast<char>(random() % 26 + 65);
    this->Subgroup = static_cast<int>(random() % 99);
    this->Name = names.at(random() % names.size());
    Date * dateOne = new Date(1, 1, 1960);
    Date * dateTwo = new Date(31, 5, 2019);
    this->Timestamp = Date::CreateRandomDate(*dateOne, *dateTwo);

}


Item::Item(char group, int subgroup, string name, Date timeStamp) {

    this->Group = group;
    this->Subgroup = subgroup;
    this->Name = name;
    this->Timestamp = timeStamp;

}

ostream &operator<<(ostream &os, const Item &item) {
    os << "Group: " << item.Group << " Subgroup: " << item.Subgroup << " Name: " << item.Name << " Timestamp: "
       << item.Timestamp.ToString();
    return os;
}

Item::~Item() = default;




char Item::getGroup() const {
    return Group;
}

void Item::setGroup(char Group) {
    Item::Group = Group;
}

int Item::getSubgroup() const {
    return Subgroup;
}

void Item::setSubgroup(int Subgroup) {
    Item::Subgroup = Subgroup;
}

const string &Item::getName() const {
    return Name;
}

void Item::setName(const string &Name) {
    Item::Name = Name;
}

const Date &Item::getTimestamp() const {
    return Timestamp;
}

void Item::setTimestamp(const Date &Timestamp) {
    Item::Timestamp = Timestamp;
}
