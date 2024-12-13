//
// Created by darkwall on 12/2/24.
//
#include "../classDeclaration/Butler.h"
#include "../classDeclaration/Table.h"
#include <QDebug>

int table_id;

void Butler::assignTable(Table& table, vector<ClientModel> clientList){
    for (int i = 0 ; i < clientList.size() ; i++){
        for (auto& t : table.getTables()){
            if (clientList[i].getCapacity() <= t.capacity && !t.isOccupied) {
            qDebug() << "Assigning Table ID: " << t.id << " with capacity: " << t.capacity;
            t.isOccupied = true;   // Mark the table as occupied
            t.clientId = clientList[i].getClientId();
            table.setTableId(t.id);    // Pass the table id value for future use
            }
        }
    }
}

void Butler::notifyHeadWaiter(Table& table, vector<ClientModel> clientList) {
    {std::lock_guard<std::mutex> lock(queueMutex);
    taskQueue.push({table, clientList});}

    cv.notify_one(); // Notify HeadWaiter
    qDebug() << "Notified HeadWaiter";
}

std::pair<Table, vector<ClientModel>> Butler::getTask() {
    std::unique_lock<std::mutex> lock(queueMutex);
    cv.wait(lock, [this]() { return !taskQueue.empty(); });
    auto task = taskQueue.front();
    taskQueue.pop();
    qDebug() << "Passed the task";
    return task; 
}