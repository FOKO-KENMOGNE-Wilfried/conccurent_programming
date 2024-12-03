//
// Created by wolverine on 12/2/24.
//
#include "../classDeclaration/Table.h"

void Table::releaseClients() {
    // TODO: add a method to move the clients after the have finished eating
}

void Table::setAbscice(double abscice) {
    this->abscice = abscice;
}
void Table::setIntercept(double intercept) {
    this->intercept = intercept;
}
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





