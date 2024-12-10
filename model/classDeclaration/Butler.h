//
// Created by darkwall on 12/2/24.
//

#ifndef BUTLE_H
#define BUTLE_H
#include <vector>
#include "Table.h"
#include "ClientModel.h"
using namespace std;

/**
 * @class Butler
 *
 * the class of the butler (he is supposed to welcome the client at thier
 * entry)
 */
class Butler : public Human {
public:
    double abscice, intercept;
    /**
     * @brief Constructor of the class Butler
     *
     * @param client_n_umber
     * @param priority_table
     */
    Butler(double abscice, double intercet, const int client_n_umber, const vector<int> &priority_table)
        : clientNumber(client_n_umber),
          priorityTable(priority_table),
          abscice(abscice), intercept(intercept) {
    }
    // Butler();
    // ~Butler();

    /**
     * @brief to create an instance of a butler on the scene
     * 
     * @param x
     * @param y
     */
    void ButlerModel(double x, double y);

    /**
     * @brief to assign a table to a client
     */
    void assignTable(Table& table, int numPeople);

    /**
     * @brief to notify a headwaiter that he has to take a client
     * to his table
     *
     * @param table
     * @param client
     */
    void notifyHeadWaiter(Table table, ClientModel client);

private:
    int clientNumber;
    vector<int> priorityTable;
};
#endif //BUTLE_H
