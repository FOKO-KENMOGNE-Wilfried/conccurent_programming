//
// Created by darkwall on 12/2/24.
//

#ifndef ORDER_H
#define ORDER_H

#include <utility>
#include <vector>

#include "Recipe.h"
#include "ClientModel.h"

/**
 *@class Order
 *@brief the Order class is use to save the differents order of the clients
 */
class Order {
public:
    /**
     *@brief Order class constructor
     *
     * @param order_recipes
     * @param client
     */
    Order(vector<Recipe*> order_recipes)
        : orderRecipes(order_recipes){}
    Order();
    ~Order();
    /**
     * @brief this method create cutlery for the current order
     *
     */
    void CreateCutlery();
    std::vector<Recipe*> getOrderRecipes();

private:
    // declare a table attribute type : table
    vector<Recipe*> orderRecipes;
    int id;
    // ClientModel client;

};
#endif //ORDER_H
