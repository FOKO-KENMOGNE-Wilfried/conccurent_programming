//
// Created by darkwall on 12/2/24.
//
#include "../classDeclaration/Butler.h"

void Butler::assignTable(Table& table, int numPeople) {
    // TODO: add a suite of instruction for the assignements of a table
    // probably should pass a table list in params
    const vector<vector<int>>& tables = table.getTables();

    for (auto t : tables){
        if (numPeople <= t[1] && t[2] == 0) {
            cout << "Assigning Table ID: " << t[0] << " with capacity: " << t[1] << endl;
            // Mark the table as occupied
            t[2] = 1;
        }        
    }
}

void Butler::notifyHeadWaiter(Table table, ClientModel client) {
    /* TODO: add a condition variable for notify the headwaiter
     * add few instructions to also pass the client list/group
     */
}
