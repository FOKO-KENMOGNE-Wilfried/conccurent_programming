//
// Created by darkwall on 12/2/24.
//

#ifndef COOK_H
#define COOK_H

#include <queue>
#include "Order.h"
#include "./Human.h"

using namespace std;

/**
 * @class Cook
 *
 * @brief this class is for the person in charge of cooking the dishes
 */
class Cook : public Human {
    queue<Order> rcipe_queue_;
public:
    double abscise;
    double intercept;

    void cookRecipe(vector<Order> orders);
    Cook(double abscise, double intercept) : abscise(abscise), intercept(intercept){};
    // ~Cook();
};
#endif //COOK_H
