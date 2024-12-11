//
// Created by darkwall on 12/2/24.
//
#include "../classDeclaration/Table.h"

#include <vector>
#include <iostream>
#include <QDebug>
using namespace std;

void Table::add_tables() {
    int tableId = 1; // Unique ID for each table

    // Add 10 tables for 2 people
    for (int i = 0; i < 10; ++i) {
        tables.push_back({tableId++, 2, false});
    }

    // Add 10 tables for 4 people
    for (int i = 0; i < 10; ++i) {
        tables.push_back({tableId++, 4, false});
    }

    // Add 5 tables for 6 people
    for (int i = 0; i < 5; ++i) {
        tables.push_back({tableId++, 6, false});
    }

    // Add 5 tables for 8 people
    for (int i = 0; i < 5; ++i) {
        tables.push_back({tableId++, 8, false});
    }

    // Add 2 tables for 10 people
    for (int i = 0; i < 2; ++i) {
        tables.push_back({tableId++, 10, false});
    }
}


vector<TableStruct>& Table::getTables(){
    return tables;
}

vector<int> Table::getTableIds() const{
    std::vector<int> ids;
    ids.reserve(tables.size()); // Reserve space for efficiency

    for (const auto& table : tables) {
        ids.push_back(table.id); // Collect table IDs
    }

    return ids;
}

int Table::getTableId(){
    return id;
};

void Table::setTableId(int id){
        this->id = id;
}


void Table::addClientsToTable(TableStruct& table, ClientModel& client) {
    // TODO: add a method for adding client on the table
    
}

void Table::releaseClients(TableStruct& table) {
    // TODO: add a method to move the clients after the have finished eating

}

void Table::setOccuped(int occuped) {
    this->occuped = occuped;
}
void Table::setClientList(ClientModel clientList) {
    this->clientList = clientList;
}





