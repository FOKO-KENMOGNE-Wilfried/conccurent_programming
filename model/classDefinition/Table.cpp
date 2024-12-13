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
    // {int id, int capacity, bool isOccupied, QString path, double x, double y, int squareId, int clientId}

    // Add 10 tables for 2 people
    for (int i = 0; i < 10; ++i) {
        tables.push_back({tableId++, 2, false, ":/assets/table2.png"});
    }

    // Add 10 tables for 4 people
    for (int i = 0; i < 10; ++i) {
        tables.push_back({tableId++, 4, false, ":/assets/table4.png"});
    }

    // Add 5 tables for 6 people
    for (int i = 0; i < 5; ++i) {
        tables.push_back({tableId++, 6, false, ":/assets/table6.png"});
    }

    // Add 5 tables for 8 people
    for (int i = 0; i < 5; ++i) {
        tables.push_back({tableId++, 8, false, ":/assets/table8.png"});
    }

    // Add 2 tables for 10 people
    for (int i = 0; i < 2; ++i) {
        tables.push_back({tableId++, 10, false, ":/assets/table10.png"});
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





