//
// Created by root on 6/1/19.
//

// Avoid using for loops. Instead of that apply STL algorithms.

#include <iostream>
#include <algorithm>
#include "Data.h"

using namespace std;

Data::Data(int n) {
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
            [] (Item * item) {std::cout << item << " ";}
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

vector<Item> * Data::getGroup(char g) {
    // for_each algorithm used to avoid for loops
    try {
        std::for_each(
                items.cbegin(),
                items.cend(),
                [g, this](Item *item) {
                    if (item->getGroup() == g) {
                        this->groupMatch.push_back(*item);
                    }
                }
        );

    }  catch (exception &e) {
        std::cout << e.what() << std::endl;
    };

    return groupMatch;
}




