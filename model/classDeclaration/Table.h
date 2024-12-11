//
// Created by darkwall on 12/2/24.
//

#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <vector>

#include "ObjectModel.h"
#include "ClientModel.h"

struct TableStruct{
    int id;
    int capacity;
    bool isOccupied;
    int clientId;
};

/**
 * @class Table
 *
 * @brief the class table for the management of all the table of
 * the dinning room
 */
class Table {

private:
    int id;
    int capacity;
    int occuped;
    ClientModel clientList;
    int breadCartNeeded;
    vector<TableStruct> tables;

public:
    double abscice;
    double intercept;
    
    /**
     * @brief Function to return list of tables
     */
    vector<TableStruct>& getTables();

    /**
     * @brief Default constructor
     */
    /* Table() 
        : abscice(0.0), intercept(0.0), capacity(0) {} */

    /**
     * @brief Constructor of the class Table
     *
     * @param abscice
     * @param intercept
     * @param capacity
     * @param occuped
     * @param client_list
     * @param bread_cart_needed
     */
    Table(double abscice, double intercept, int capacity)
        : capacity(capacity),
          abscice(abscice),
          intercept(intercept) {}
    // ~Table();

    /**
     * @brief a function to create list of tables
     */
    void add_tables();

    vector<int> getTableIds() const;

    int getTableId();
    void setTableId(int id);

    /**
     * @brief a function to add clients on the table
     *
     * @param clients
     */
    void addClientsToTable(TableStruct& table, ClientModel& client);

    /**
     * @brief to move the client when they have finished eating
     */
    void releaseClients(TableStruct& table);

    // void setAbscice(double abscice);
    // void setIntercept(double intercept);
    void setOccuped(int occuped);
    void setClientList(ClientModel clientList);

};
#endif //TABLE_H
