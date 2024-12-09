//
// Created by darkwall on 12/2/24.
//

#ifndef KITCHENASSISTANT_H
#define KITCHENASSISTANT_H

#include <utility>

#include "KitchenCounter.h"
#include "Human.h"

using namespace std;

/**
 * @class KitchenAssistant
 *
 * @brief assist the cook by Preparing the ingredients
 * and place the ready dishes on the counter.
 */
class KitchenAssistant : public Human {
public:
    double abscise;
    double intercept;
    explicit KitchenAssistant(double abscise, double intercept, KitchenCounter* kitchen_counter)
        : kitchen_counter_(std::move(kitchen_counter)),
        abscise(abscise), intercept(intercept) {}
    // KitchenAssistant();
    // ~KitchenAssistant();
    /**
     * @brief to put a dishes on the counter
     */
    void sendToCounter();
    void prepareIngredients();

private:
    KitchenCounter* kitchen_counter_;
};
#endif //KITCHENASSISTANT_H
