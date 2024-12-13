//
// Created by darkwall on 12/2/24.
//

#ifndef HEADWAITER_H
#define HEADWAITER_H
#include "Order.h"
#include "Table.h"
#include "Butler.h"
#include "ClientModel.h"
#include "Human.h"
#include <queue>
#include <mutex>
#include <vector>
/**
 * @class HeadWaiter
 *
 * @brief the guys who lead the client to his table
 */
class HeadWaiter : public Human{
    queue<Order> orderQueue;

private:
    Butler* butler; // Pointer to Butler
    mutex taskMutex;

public:
    double x, y;
    int waiterNumber = 2;

    explicit HeadWaiter(Butler* b) : butler(b) {}
    /**
     * @brief Constructor of the HeadWaiter Class
     * 
     * @param x
     * @param y
     */
    HeadWaiter(double x, double y) : Human(x, y){}
    /**
     * @brief the function to lead the clients to their table
     */
    void leadClients();

    /**
     * @brief the function to take order and pass it to the chief
     */
    void passOrdersToChief();
};
#endif //HEADWAITER_H
