//
// Created by darkwall on 12/2/24.
//

#ifndef CHUEF_H
#define CHUEF_H

#include "CardModel.h"
#include "Human.h"
#include "Order.h"

#include <iostream>

using namespace std;

/**
 * @class Chief
 *
 * @brief the actuel class to manage the chief
 */
class Chief : public Human {
  public:
        double abscise;
        double intercept;
      /**
       * @brief the constructor of the class Chief
       *
       * @param actual_card
       * @param order_list
       * @param organised_order_list
       * @param invalid_order_list
       */
      Chief(double adscise, double intercept)
          : abscise(abscice), intercept(intercept){}
      // Chief();
      // ~Chief();

      /**
       * @brief the function to change the actual card
       *
       * @param card the actual card use by clients
       */
      void setCurrentCard(CardModel card); // maybe this should have a return statement

      /**
       *
       * @return organiseListOrders
       */
      void organiseOrders(std::vector<Order*> order);

      /**
       *
       * @return orderList (maybe)
       */
      Order* checkOrderlist();

      void sayHello();

      /**
       * @brief to distribute task to others
       */
      void DistributeTask();

  private:
      // CardModel actualCard;
      vector<Order> orderList;
      vector<Order> organisedOrderList;
      vector<Order> invalidOrderList;

};
#endif //CHUEF_H
