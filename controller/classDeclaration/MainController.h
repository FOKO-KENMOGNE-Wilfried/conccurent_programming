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
#include "../../model/classDeclaration/ThreadPool.h"
#include "../../model/graphicElement/classDeclaration/QGraphicElement.h"
#include "../../view/view.h"
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
        ThreadPool threadPool;
        RecipeBook recipeBook;
        QGraphicElement* chief;
        vector<QGraphicElement*> kitchenCounterList;
        vector<QGraphicElement*> dirtyDishesStorageList;
        vector<QGraphicElement*> washingMachineList;
        vector<QGraphicElement*> dishwasherModelList;
        vector<QGraphicsPixmapItem*> stoveItemList;
        int init(int argc, char *argv[], QApplication a);
        MainController();
        ~MainController();

        /**
         * @brief Function use to initialize the dining room threads and processes
         */
        void Restaurant();

        vector<QGraphicElement*> createGraphicElements();
};

#endif //MAINCONTROLLER_H
