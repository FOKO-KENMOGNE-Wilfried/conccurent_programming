//
// Created by darkwall on 12/2/24.
//

#ifndef BUTLE_H
#define BUTLE_H

#include <vector>
#include <mutex>
#include <queue>
#include <condition_variable>
#include "Table.h"
#include "ClientModel.h"
using namespace std;

/**
 * @class Butler
 *
 * the class of the butler (he is supposed to welcome the client at their
 * entry)
 */
class Butler : public Human {

private:
    int clientNumber;
    vector<int> priorityTable;
    queue<pair<Table, vector<ClientModel>>> taskQueue;
    mutex queueMutex;
    condition_variable cv;    

public:
    double abscice, intercept;
    /**
     * @brief Constructor of the class Butler
     *
     * @param abscise
     * @param intercept
     */

    Butler(double abscice, double intercept)
        : abscice(abscice), intercept(intercept) {}
    Butler(){}
    // ~Butler();

    /**
     * @brief to assign a table to a client
     */
    void assignTable(Table& table, vector<ClientModel> client);

    /**
     * @brief to notify a headwaiter that he has to take a client
     * to his table
     *
     * @param table
     * @param client
     */
    void notifyHeadWaiter(Table& table, vector<ClientModel> client);
    pair<Table, vector<ClientModel>> getTask();
};
#endif //BUTLE_H
