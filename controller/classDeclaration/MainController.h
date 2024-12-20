//
// Created by darkwall on 12/2/24.
//

#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

// #include <queue>
#include <list>
#include <vector>
#include <QApplication>
#include <mutex>
#include <unistd.h>
#include <QPointF>

#include "../../model/classDeclaration/ClientModel.h"
#include "../../model/classDeclaration/Human.h"
#include "../../model/classDeclaration/Order.h"
#include "../../model/classDeclaration/Recipe.h"
#include "../../model/classDeclaration/ThreadPool.h"
#include "../../model/graphicElement/classDeclaration/QGraphicElement.h"
#include "../../view/view.h"
#include "../../model/classDeclaration/ThreadPool.h"
#include "../../model/graphicElement/classDeclaration/QGraphicElement.h"
#include "../../model/classDeclaration/ThreadPool.h"
#include "DBController.h"
#include "MotionlessElementController.h"
using namespace std;

class MainController {
    vector<QGraphicElement*> graphicPersonel;
    vector<QGraphicElement*> graphicClients;
    vector<ClientModel> clientList;
    DBController dbController;
    mutex lock;
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
        KitchenCounter* kitchenCounter = new KitchenCounter(readyOrder, -20, 200);
        DirtyDishesStorage* dirtyDishesStorage = new DirtyDishesStorage();
        WashingMachine* washingMachine = new WashingMachine();
        DishwasherModel* dishwasherModel = new DishwasherModel(10.2, 10.2);
        vector<QGraphicElement*> cookNumber {
            new QGraphicElement(new Cook(200.0, 250.0), Qt::blue),
            new QGraphicElement(new Cook(200.0, 250.0), Qt::blue)
        };
        vector<QGraphicElement*> cookAssistNumber {
            new QGraphicElement(new KitchenAssistant(200.0, 300.0, kitchenCounter), Qt::blue),
            new QGraphicElement(new KitchenAssistant(200.0, 300.0, kitchenCounter), Qt::blue)
        };
        int init(int argc, char *argv[], QApplication& a, View* view);
        const vector<QGraphicElement*> getGraphicPersonel() const { return graphicPersonel; }
        const vector<QGraphicElement*> getGraphicClients() const { return graphicClients; }
        const vector<ClientModel> getClientModelList() const { return clientList; }
        MainController();
        ~MainController();

        /**
         * @brief Function use to initialize the dining room threads and processes
         */
        void Restaurant();

        /**
         * @brief Function to move each graphic instance of the personnel
         */
        void movePersonel(int elementIndex, QPointF destination);

        /**
         * @brief Function to move each graphic instance of the clients
         */
        void moveClient(int elementIndex, QPointF destination);

        vector<QGraphicElement*> createGraphicPersonel();
        vector<QGraphicElement*> createGraphicClients();

};

#endif //MAINCONTROLLER_H
