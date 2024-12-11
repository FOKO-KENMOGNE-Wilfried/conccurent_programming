//
// Created by darkwall on 12/2/24.
//
#include "../classDeclaration/ClientGroupCreator.h"
#include "../classDeclaration/ClientModel.h"
#include <cstdlib>
#include <ctime>

void ClientGroupCreator::createGroup() {
    clientGroups.clear();

    // TODO: a function that create randoms groups
    for (int i=0; i < clientNumber; i++){
        int randomCapacity = (rand() % 10) + 1;
        ClientModel client(100.0, 99.0, "COOL", i+1, randomCapacity);
        clientGroups.push_back(client);
    }
}

/* vector<ClientModel>& ClientGroupCreator::getClientGroups(){
    return clientGroups;
} */
