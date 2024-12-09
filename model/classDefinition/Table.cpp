//
// Created by darkwall on 12/2/24.
//
#include "../classDeclaration/Table.h"

#include <vector>
#include <iostream>
using namespace std;

void Table::add_tables() {
    vector<vector<int>> tables; // Each row: {id, capacity, isOccupied}
    int tableId = 1; // Unique ID for each table

    // Add 10 tables for 2 people
    for (int i = 0; i < 10; ++i) {
        tables.push_back({tableId++, 2, 0}); // 0 means not occupied
    }

    // Add 10 tables for 4 people
    for (int i = 0; i < 10; ++i) {
        tables.push_back({tableId++, 4, 0});
    }

    // Add 5 tables for 6 people
    for (int i = 0; i < 5; ++i) {
        tables.push_back({tableId++, 6, 0});
    }

    // Add 5 tables for 8 people
    for (int i = 0; i < 5; ++i) {
        tables.push_back({tableId++, 8, 0});
    }

    // Add 2 tables for 10 people
    for (int i = 0; i < 2; ++i) {
        tables.push_back({tableId++, 10, 0});
    }
}


void Table::releaseClients() {
    // TODO: add a method to move the clients after the have finished eating
}

// void Table::setAbscice(double abscice) {
//     this->abscice = abscice;
// }
// void Table::setIntercept(double intercept) {
//     this->intercept = intercept;
// }
void Table::setOccuped(int occuped) {
    this->occuped = occuped;
}
void Table::addClientsToTable(vector<ClientModel> clients) {
    // TODO: add a method for adding client on the table
    setClientList(clients);
}
void Table::setClientList(vector<ClientModel> clientList) {
    this->clientList = clientList;
}





