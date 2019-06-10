//
// Created by root on 6/10/19.
//

#include <utility>
#include <iostream>
#include <algorithm>
#include <ctime>
#include "Data.h"

using namespace std;

Data::Data(int n) {
    // If items in table are required to be random:
    // srand(time(NULL));
    items = {};
    for(int i = 0; i < n; i++) {

        Item * item = new Item();
        items.push_back(*item);
    }

}

Data::~Data() = default;

void Data::printAll() {
    // for_each loop to avoid for loops
    std::for_each(
            items.cbegin(),
            items.cend(),
            [] (Item item) {std::cout << item << std::endl;}
    );
}


ostream &operator<<(ostream &os, const Data &data) {
    for (const auto &item : data.items) {
        os << "items: " << item;
    }
    return os;
}

int Data::countAll() {
    return static_cast<int>(items.size());
}

vector<Item> Data::getGroup(char g) {
    // for_each algorithm used to avoid for loops
    auto * group = new std::vector<Item>;
    try {
        std::for_each(
                items.cbegin(),
                items.cend(),
                [g, group](Item item) {
                    if (item.getGroup() == g) {
                        group->push_back(item);
                    }
                }
        );

        return *group;


    }  catch (exception &e) {
        std::cout << e.what() << std::endl;
    };


}


void Data::printGroup(char g) {

    for (const auto &item : getGroup(g)) {
        std::cout << item << std::endl;
    }

}

int Data::countGroup(char g) {

    return static_cast<int>(getGroup(g).size());

}

vector<Item> Data::getSubGroup(char g, int sg) {
    auto * subgroup = new std::vector<Item>;
    try {
        std::for_each(
                items.cbegin(),
                items.cend(),
                [g, sg, subgroup](Item item) {
                    if (item.getGroup() == g && item.getSubgroup() == sg) {
                        subgroup->push_back(item);
                    }
                }
        );

        return *subgroup;


    }  catch (exception &e) {
        std::cout << e.what() << std::endl;
    };
    return * subgroup;
}

void Data::printSubGroup(char g, int sg) {

    for (const auto &item : getSubGroup(g, sg)) {
        std::cout << item << std::endl;
    }
}

int Data::countSubGroup(char g, int sg) {

    return static_cast<int>(getSubGroup(g, sg).size());

}



Item *Data::getItemByName(char g, int sg, string n) {

    auto * filtered = new std::vector<Item>;
    try {
        std::for_each(
                items.cbegin(),
                items.cend(),
                [g, sg, n, filtered](Item item) {
                    if (item.getGroup() == g && item.getSubgroup() == sg && item.getName() == n) {
                        filtered->push_back(item);
                    }
                }
        );

        return &filtered->at(0);


    }  catch (exception &e) {
        std::cout << "No match found." << std::endl;
        std::cout << e.what() << std::endl;
    };

    return nullptr;
}

Item *Data::getItemByDate(char g, int sg, Date d) {

    auto * filtered = new std::vector<Item>;
    try {
        std::for_each(
                items.cbegin(),
                items.cend(),
                [g, sg, d, filtered](Item item) {
                    if (item.getGroup() == g && item.getSubgroup() == sg && item.getTimestamp() == d) {
                        filtered->push_back(item);
                    }
                }
        );

        return &filtered->at(0);


    }  catch (exception &e) {
        std::cout << "No match found." << std::endl;
        std::cout << e.what() << std::endl;
    };

    return nullptr;
}

bool Data::printItemByName(char g, int sg, string n) {
    Item * itemByName = getItemByName(g, sg, n);
    if (itemByName) {
        std::cout << *itemByName << std::endl;
    } else {
        return false;
    }

}

bool Data::printItemByDate(char g, int sg, Date d) {
    Item * itemByDate = getItemByDate(g, sg, d);
    if (getItemByDate(g, sg, d)) {
        std::cout << *itemByDate << std::endl;
    } else {
        return false;
    }

}


bool Data::removeSubGroup(char g, int sg) {

    if (sg) {
        items.erase(
                std::remove_if(
                        items.begin(),
                        items.end(),
                        [sg] (const Item & o) {
                            return o.getSubgroup() == sg;

                        })
        ),

                items.end();
    } else {
        return false;
    }

}

bool Data::removeItemByName(char g, int sg, string n) {
    if (!n.empty()) {
        items.erase(
                std::remove_if(
                        items.begin(),
                        items.end(),
                        [n] (const Item & o) {
                            return o.getName() == n;

                        })
        ),

                items.end();
    } else {
        return false;
    }
}

bool Data::removeItemByDate(char g, int sg, Date d) {

    if (d.ToString()) {
        items.erase(
                std::remove_if(
                        items.begin(),
                        items.end(),
                        [d] (const Item & o) {
                            return o.getTimestamp() == d;

                        })
        ),

                items.end();
    } else {
        return false;
    }
}

