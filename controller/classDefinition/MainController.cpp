//
// Created by darkwall on 12/2/24.
//
#include "../classDeclaration/MainController.h"
#include "../../view/DisplayInterfacesClass.h"
#include "../../enum/RecipeBook.cpp"
#include "../../view/kitchen.h"
#include "../../view/view.h"

#include "../../model/classDeclaration/ClientGroupCreator.h"
#include "../../model/classDeclaration/Butler.h"
#include "../../model/classDeclaration/ClientModel.h"
#include "../../model/classDeclaration/HeadWaiter.h"
#include "../../model/classDeclaration/Table.h"

#include <QApplication>
#include <cstdlib>
#include <thread>
#include <iostream>

MainController controller;

vector<QGraphicElement*> MainController::createGraphicElements(){
    vector<QGraphicElement*> graphicElements;

    // Create a Butler graphical representation
    QGraphicElement* graphicButler = new QGraphicElement(new Butler(100.0, 151.0), Qt::blue);
    graphicElements.push_back(graphicButler);

    // Create HeadWaiter graphical representations
    QGraphicElement* waiter1 = new QGraphicElement(new HeadWaiter(500.0, 151.0), Qt::black);
    graphicElements.push_back(waiter1);

    QGraphicElement* waiter2 = new QGraphicElement(new HeadWaiter(1000.0, 151.0), Qt::white);
    graphicElements.push_back(waiter2);

    return graphicElements;
}

int MainController::init(int argc, char *argv[], QApplication& a, View* v){
    vector<QGraphicElement*> graphicElements = createGraphicElements();
    v->setupPerson(graphicElements);

    humanList.push_front(new Human(1000.0, 250.0));

    RecipeBook recipeBook;
    auto ingredientsForSauceTomate = recipeBook.getIngredientEnums(Recette::SauceTomate);

    v->show();

    return a.exec();
}

/* int MainController::init(int argc, char *argv[], QApplication a){
    humanList.push_front(new Human(1000.0, 250.0));

    RecipeBook recipeBook;
    auto ingredientsForSauceTomate = recipeBook.getIngredientEnums(Recette::SauceTomate);

    View view(nullptr, humanList);
    view.show();

    // Kitchen k(nullptr, readyOrder);
    // k.show();
    return a.exec();
} */

void MainController::Restaurant(View* view){
    // int numPeople = (rand() % 10) + 1;
    // butler.assignTable(table, numPeople);

    // Butler butler;
    // HeadWaiter headWaiter(&butler);

    // std::thread butlerThread([&butler]() {
    //     ClientModel client(100.0, 99.0, "COOL", 1, 5);     
    //     Table table;
    //     table.add_tables();
    //     butler.assignTable(table, client);

    //     butler.notifyHeadWaiter(table, client);
    // });

    // std::thread headWaiterThread([&headWaiter]() {
    //     headWaiter.leadClients();
    // });

    // butlerThread.join();
    // headWaiterThread.join();

    vector<QGraphicElement*> graphicElements = createGraphicElements();

    view->setupPerson(graphicElements);

}

MainController::~MainController(){}
MainController::MainController(){}
