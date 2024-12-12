//
// Created by darkwall on 12/2/24.
//

#ifndef RESTAURANTDIVER_H
#define RESTAURANTDIVER_H

#include "DirtyDishesStorage.h"
#include "DishwasherModel.h"
#include "WashingMachine.h"
#include "./Human.h"

using namespace std;

/**
 * @class RestaurantDiver
 */
class RestaurantDiver : public Human {
public:
    double abscise;
    double intercept;
    /**
     * @brief
     *
     * @param abscise
     * @param intercept
     * @param dirty_dishes_storage
     * @param washing_machine
     * @param dishwasher_model
     */
    RestaurantDiver(double abscise, double intercept, DirtyDishesStorage* dirty_dishes_storage, WashingMachine* washing_machine,
                    DishwasherModel* dishwasher_model)
        : dirty_dishes_storage_(dirty_dishes_storage),
          washing_machine_(washing_machine),
          dishwasher_model_(dishwasher_model),
          abscise(abscice),
          intercept(intercept) {
    }
    // ~RestaurantDiver();
    void getDirtyDishes();
    void washDishes();
    void getWashedDishes();

private:
    DirtyDishesStorage* dirty_dishes_storage_;
    WashingMachine* washing_machine_;
    DishwasherModel* dishwasher_model_;
};
#endif //RESTAURANTDIVER_H
