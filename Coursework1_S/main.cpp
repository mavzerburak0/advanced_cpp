#include <iostream>
#include "Date.h"
#include "Item.h"
#include "Data.h"

int main() {

    // *** Create 20 random items *** //
    Data * data = new Data(15);

    // *** Print them all *** //
    std::cout << "Printing data..." << std::endl;
    data->printAll();
    std::cout << std::endl;

    // *** Count them all *** //
    std::cout << "Number of items: " << std::endl;
    std::cout << data->countAll() << std::endl;
    std::cout << std::endl;

    // *** Get all items belonging to a specific group *** //
    std::cout << "Displaying all items belonging to group R" << std::endl;
    // Next 4 lines only here for demonstration purposes...
    std::vector<Item> groupR = data->getGroup('R');
    for (const auto &i : groupR) {
        std::cout << i << std::endl;
    }

    std::cout << std::endl;

    // *** Print all the items matching the given group *** //
    std::cout << "Print all items in group A" << std::endl;
    data->printGroup('A');
    std::cout << std::endl;

    // *** Print the number of items belonging to the given group *** //
    std::cout << "Number of items belonging to group R" << std::endl;
    std::cout << data->countGroup('R') << std::endl;
    std::cout << std::endl;

    // *** Get all items belonging to a specific group and subgroup *** //
    std::cout << "Get all items belonging to group R and subgroup 23" << std::endl;
    std::vector<Item> groupRsg = data->getSubGroup('R', 23);
    // This is here for demonstration purposes
    for (const auto &i : groupRsg) {
        std::cout << i << std::endl;
    }
    std::cout << std::endl;

    // *** Print all items belonging to a specific group and subgroup *** //
    std::cout << "Print all items belonging to group R and subgroup 23" << std::endl;
    data->printSubGroup('R', 23);
    std::cout << std::endl;

    // *** Number of items in a specific group and subgroup *** //
    std::cout << "Number of items belonging to group I and subgroup 60" << std::endl;
    std::cout << data->countSubGroup('I', 60) << std::endl;
    std::cout << std::endl;

    // *** Get item by name *** //
    std::cout << "Get group N, subgroup 43 and name Jefferson" << std::endl;
    Item * g = data->getItemByName('N', 43, "Jefferson");
    std::cout << *g << std::endl;
    std::cout << std::endl;

    // *** Get item by date *** //
    // As dates are generated randomly every time the program is executed,
    // we need to set the date to a constant value  from Item.cpp
    // to test this function
    std::cout << "Get group A, subgroup 25, 1.1.1960" << std::endl;
    Item * d = data->getItemByDate('A', 25, Date(1, 1, 2019));
    // Demonstration
    std::cout << *d << std::endl;
    std::cout << std::endl;

    // *** Print item by name *** //
    std::cout << "Print item with group M, subgroup 39 and name Trista" << std::endl;
    data->printItemByName('M', 39, "Trista");
    std::cout << std::endl;

    // *** Print item by date *** //
    std::cout << "Print item with group K, subgroup 55 and date 01.01.1960" << std::endl;
    data->printItemByDate('K', 55, Date(1,1,2019));
    std::cout << std::endl;

    // *** Removing a subgroup *** //
    std::cout << "Remove group M, subgroup 39" << std::endl;
    data->printSubGroup('M', 39);
    data->removeSubGroup('M', 39);
    std::cout << std::endl;

    // *** Removing by name *** //
    std::cout << "Removing group O, subgroup 42, name Curtis" << std::endl;
    data->removeItemByName('O', 42, "Curtis");
    std::cout << std::endl;

    // *** Removing by date *** //
    std::cout << "Removing group I, subgroup 60, date 01 Jan 1960" << std::endl;
    data->removeItemByDate('I', 60, Date(1, 1, 2019));
    std::cout << std::endl;

    // *** Data vector after operations *** //
    std::cout << "All data after operations completed" << std::endl;
    data->printAll();
    std::cout << std::endl;
    
}