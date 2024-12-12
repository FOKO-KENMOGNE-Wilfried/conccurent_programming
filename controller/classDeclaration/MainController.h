//
// Created by darkwall on 12/2/24.
//

#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

// #include <queue>
#include <list>
#include <vector>
#include <QApplication>

#include "../../model/classDeclaration/Human.h"
#include "../../model/classDeclaration/Order.h"
#include "../../model/classDeclaration/Recipe.h"
#include "DBController.h"
#include "MotionlessElementController.h"
using namespace std;

class MainController {
    DBController dbController;
    MotionlessElementController motionlessElementController;
    vector<Recipe> dailyRestaurantCard {
        // new Recipe("Roti de tomate", "PLAT_DE_RESISTENCE", 60, )
    };
    vector<Recipe*> restaurantOrders {
        new Recipe(Recette::SauceTomate),
        new Recipe(Recette::CurryLegumes),
        new Recipe(Recette::GateauChocolat)
    };
    vector<Order*> readyOrder {
        new Order(restaurantOrders)
    };
    list<Human*> humanList;
    Human human;

    public:
        int init(int argc, char *argv[], QApplication a);
        MainController();
        ~MainController();

        /**
         * @brief Function use to initialize the dining room threads and processes
         */
        void Restaurant();
};

#endif //MAINCONTROLLER_H
