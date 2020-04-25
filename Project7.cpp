/*
 * Name:
 * EID:
 * Project 7, CRM part 2
 * EE 312, Fall 2019
 */

#include <stdio.h>
#include <iostream>
#include "UTString.h"
#include "Customer.h"
#include "CustomerDB.h"

using namespace std;

void readString(UTString&);
void readNum(int&);

CustomerDB database;

int num_bottles = 0;
int num_rattles = 0;
int num_diapers = 0;

/* clear the inventory and reset the customer database to empty */
void reset(void) {
    database.clear();
    num_bottles = 0;
    num_rattles = 0;
    num_diapers = 0;
}

/*
 * selectInventItem is a convenience function that allows you
 * to obtain a pointer to the inventory record using the item type name
 * word must be "Bottles", "Diapers" or "Rattles"
 * for example the expression *selectInventItem("Bottles") returns the
 * current global variable for the number of bottls in the inventory
 */
int* selectInventItem(UTString word) {
    if (word == "Bottles") {
        return &num_bottles;
    } else if (word == "Diapers") {
        return &num_diapers;
    } else if (word == "Rattles") {
        return &num_rattles;
    }

    /* NOT REACHED */
    return 0;
}

/*
 * this overload of selectInventItem is similar to selectInventItem above, however
 * this overload takes a Customer as a second argument and selects the data member
 * of that Customer that matches "word". The function returns a pointer to one of the three data
 * members from the specified customer.
 */
int* selectInventItem(UTString word, Customer& cust) {
    if (word == "Bottles") {
        return &cust.bottles;
    } else if (word == "Diapers") {
        return &cust.diapers;
    } else if (word == "Rattles") {
        return &cust.rattles;
    }

    /* NOT REACHED */
    return 0;
}

/*
 * findMax searches through the CustomerDB "database" and returns the Customer
 * who has purchased the most items of the specified type.
 * type must be one of "Bottles", "Rattles" or "Diapers".
 *
 * Note: if two or more Customers are tied for having purchased the most of that item type
 * then findMax returns the first Customer in the CustomerDB who has purchased that maximal
 * quantity.
 *
 * Note: in the special case (invalid case) where there are zero Customers in the
 * CustomerDB, fundMax returns a null pointer (0)
 */
Customer* findMax(UTString type) {
    Customer* result = 0;
    int max = 0;
    for (int k = 0; k < database.size(); k += 1) {
        Customer& cust = database[k];
        int *p = selectInventItem(type, cust);
        if (*p > max) {
            max = *p;
            result = &cust;
        }
    }

    return result;
}

void processPurchase() {
    UTString cname;
    UTString item_name;
    int purchase;

    readString(cname);
    readString(item_name);
    readNum(purchase);

    if(purchase < 0) {

    }
    else {
        int* item = selectInventItem(item_name);
        if(*item < purchase) {
            std::cout << "Sorry " << cname.c_str() << " we only have " << *item << " " << item_name.c_str() << endl;
        }
        else {
            *item -= purchase;
            *selectInventItem(item_name, database[cname]) += purchase;
        }
    }
}

void printZero(UTString item_name) {
    std::cout << "no one has purchased any " << item_name.c_str() << endl;
}

void summarizeHelper(UTString item_name) {
    if(database.size() == 0) {
        printZero(item_name);
    }
    else {
        Customer max = database[0];
        for(int i = 1; i < database.size(); i++) {
            if(*selectInventItem(item_name, database[i]) > *selectInventItem(item_name, max)) {
                max = database[i];
            }
        }
        if(*selectInventItem(item_name, max) == 0) {
            printZero(item_name);
        }
        else {
            std::cout << max.name.c_str() << " has purchased the most " << item_name.c_str()
            << " (" << *selectInventItem(item_name, max) << ")" << endl;
        }
    }
}

void processSummarize() {
    std::cout << "There are " << num_bottles << " Bottles, "
    << num_diapers << " Diapers, and " << num_rattles << " Rattles in inventory" << endl;
    std::cout << "we have a total of " << database.size() << " different customers" << endl;

    summarizeHelper("Bottles");
    summarizeHelper("Diapers");
    summarizeHelper("Rattles");


}

void processInventory() {
    UTString item_name;
    int new_stock;

    readString(item_name);
    readNum(new_stock);

    if(new_stock >= 0) {
        int* item = selectInventItem(item_name);
        *item += new_stock;
    }
}
