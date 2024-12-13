//
// Created by darkwall on 12/2/24.
//
#include <iostream>
#include <QDebug>
#include "../classDeclaration/HeadWaiter.h"
#include "../classDeclaration/Table.h"

void HeadWaiter::passOrdersToChief() {
    // TODO: Add order processing logic
    qDebug() << "Passing orders to the chief...";
}

void HeadWaiter::leadClients() {
    while (true) {
        auto task = butler->getTask();
        Table table = task.first;
        ClientModel client = task.second;

        // Lead clients to the assigned table
        {
            std::lock_guard<std::mutex> lock(taskMutex);
            qDebug() << "Leading clients to Table ID: " << table.getTableId();

            // Once clients are seated, pass their orders to the Chief
            passOrdersToChief();
        }
    }
}