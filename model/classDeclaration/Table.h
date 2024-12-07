//
// Created by darkwall on 12/2/24.
//

#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <vector>

#include "ObjectModel.h"
#include "ClientModel.h"

/**
 * @class Table
 *
 * @brief the class table for the management of all the table of
 * the dinning room
 */
class Table {
public:
    double abscice;
    double intercept;
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
          occuped(occuped),
          abscice(abscice),
          intercept(intercept) {}
    // ~Table();
    /**
     * @brief a function to add clients on the table
     *
     * @param clients
     */
    void addClientsToTable(vector<ClientModel> clients);

    /**
     * @brief to move the client when they have finished eating
     */
    void releaseClients();

    // void setAbscice(double abscice);
    // void setIntercept(double intercept);
    void setOccuped(int occuped);
    void setClientList(vector<ClientModel> clientList);


private:
    int capacity;
    int occuped;
    vector<ClientModel> clientList;
    int breadCartNeeded;

};
#endif //TABLE_H
