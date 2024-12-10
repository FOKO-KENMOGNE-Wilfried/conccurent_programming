//
// Created by darkwall on 12/2/24.
//

#ifndef HEADWAITER_H
#define HEADWAITER_H
#include "Order.h"
#include "Table.h"
#include "ClientModel.h"
#include "Human.h"
#include <queue>
/**
 * @class HeadWaiter
 *
 * @brief the guys who lead the client to his table
 */
<<<<<<< HEAD
class HeadWaiter: public Human {
    queue<Order> orderQueue;
public:
    double abscice, intercept;
=======
class HeadWaiter : public Human{
    queue<Order> orderQueue;
public:
    double x, y;
    /**
     * @brief Constructor of the HeadWaiter Class
     * 
     * @param x
     * @param y
     */
    HeadWaiter(double x, double y) : Human(x, y){}

>>>>>>> b992104 (Dining room characters constructor updated)
    /**
     * @brief the function to lead the clients to their table
     *
     * @param table
     * @param clients
     */
<<<<<<< HEAD
    void leadClients(double abscice, double intercept,Table &table, vector<ClientModel> &clients);
    HeadWaiter();
=======
    void leadClients(Table &table, vector<ClientModel> &clients);
>>>>>>> b992104 (Dining room characters constructor updated)
    // ~HeadWaiter();

    /**
     * @brief the function to take order and pass it to the chief
     */
    void passOrdersTochief();
};
#endif //HEADWAITER_H
