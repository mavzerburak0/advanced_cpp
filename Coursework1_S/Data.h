//
// Created by root on 6/1/19.
//



#ifndef COURSEWORK1_S_DATA_H
#define COURSEWORK1_S_DATA_H


#include <ostream>
#include "Item.h"

class Data {
private:
    std::vector<Item> items;
    std::vector<Item> * groupMatch;
public:
    // Constructs the object and fills the container with n random items.
    explicit Data(int n);
    // Destructs the object and releases all the memory occupied by the container and the items in it.
    ~Data();
    /*
     * Prints all the items stored in the container in command prompt window in easily readable
     * format. Items from the same group and subgroup must be ordered by their names.
    */
    void printAll();
    // Returns the total number of items in the container.
    int countAll();
    /**
     * Returns a container or pointer to container of all the items from group g. The type of output
     * value is the student’s choice. The method must in some way (exception, nullptr on
     * output, etc.) inform the user was the group found or not
     */
    vector<Item> * getGroup(char g);
    /**
     * Prints all the items from group g in command prompt window in easily readable format. Items
     * from the same subgroup must be ordered by their names. Return value: false if the group does
     * not exist.
     */
    bool printGroup(char g);
    // Returns the number of items in group g.
    int countGroup (char g);
    /**
     * Returns a container or pointer to container of all the items from group g and subgroup sg. The
     * type of output value (here void) is the student’s choice. The method must in some way
     * (exception, nullptr on output, etc.) inform the user was the subgroup found or not
     */
    void getSubGroup(char g, int sg);
    /**
     * Prints all the items from group g and subgroup sg in command prompt window in easily
     * readable format. Items must be ordered by their names. Return value: false if the subgroup
     * does not exist.
     */
     bool printSubGroupByDates(char g, int sg);
     // Returns the number if items from group g and subgroup sg.
     int countSubGroup(char g, int sg);
     /*
      * Returns the pointer to the first of items specified by group g, subgroup sg and name n. If the
      * item was not found returns nullptr.
      */
     Item * getItem(char g, int sg, string n);
     /*
      * Returns the pointer to the first of items specified by group g, subgroup sg and timesatmp d. If
      * the item was not found returns nullptr.
      */
     Item * getItem(char g, int sg, Date d);
     /*
      * Prints the first of items specified by group g, subgroup sg and name n in command prompt
      * window in easily readable format. If the item was not found returns false.
      */
    bool printItem(char g, int sg, string n);
    /*
     * Prints the first of items specified by group g, subgroup sg and timestamp d in command prompt
     * window in easily readable format. If the item was not found returns false.
     */
    bool printItem(char g, int sg, Date d);
    /*
     * Destructs the subgroup sg from group g and releases all the memory occupied by the items in it.
     * If the group was not found returns false
     */
    bool removeSubGroup(char g, int sg);
    /*
     * Removes the first of items specified by group g, subgroup sg and name n. If the item was not
     * found returns false.
     */
    bool removeItem(char g, int sg, string n);
    /*
     * Removes the first of items specified by group g, subgroup sg and timestamp d. If the item was
     * not found returns false.
     */
    bool removeItem(char g, int sg, Date d);

    friend ostream &operator<<(ostream &os, const Data &data);
};


#endif //COURSEWORK1_S_DATA_H
