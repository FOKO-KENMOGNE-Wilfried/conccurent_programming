#ifndef CLIENTMODEL_H
#define CLIENTMODEL_H

#include "Order.h"
#include <iostream>
#include <vector>
#include "Human.h"

using namespace std;
/**
 * @class ClientModel
 * @brief management of the different instance of the client
 *
 * the clientModel class is used to create the different instance of the client,
 * they are the one with the different methods of the client
 */
class ClientModel : public Human
{
private:
    string type;
    int id;
    int capacity;
    bool hasOdered;
    int orderTimeLeft;
    bool hasOrderedEntree;
    bool hasOrderedMainCourse;
    bool hasOrderedDessert;
    vector<Recipe> choices;
public:
    double abscice, intercept;
    /**
     *@brief constructor of the Client class
     *
     * @param abscice
     * @param intercept
     * @param type
     * @param id
     * @param capacity
     * @param has_odered
     * @param order_time_left
     * @param has_ordered_entree
     * @param has_ordered_main_course
     * @param has_ordered_dessert
     */
    ClientModel(double abscise, double intercept, string type,
            int id)
        :   abscice(abscise),
            intercept(intercept),
            type(type) {}
    ClientModel(/* args */);
    ~ClientModel();

    int getCapacity(){
        return capacity;
    }

    int getClientId(){
        return id;
    }

    /**
     * @brief this function is use for the client to make a choice
     *
     * @param recipes
     */

    void makeChoice(vector<Recipe> &recipes);

    /**
     * @brief client method eat
     * @param order
     */
    // void eat(vector<Order> order);

    /**
     * @brief change the hasOrdered state
     */
    void toogleHasOrdered();

    /**
     * C
     */
    void toogleHasOrderedMainCourse();
    void toogleHasOrderedDessert();
    void toogleHasOrderedEntree();

};

#endif