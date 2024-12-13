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

vector<QGraphicElement*> MainController::createGraphicClients(){
    for (int clientId = 1; clientId <= 5; ++clientId){
        // Create a Client graphical representation
        QGraphicElement* client = new QGraphicElement(new ClientModel(100.0, 91.0, clientId), Qt::red);
        graphicClients.push_back(client);
    }

    return graphicClients;
}

vector<QGraphicElement*> MainController::createGraphicPersonel(){
    // Create a Butler graphical representation
    QGraphicElement* graphicButler = new QGraphicElement(new Butler(100.0, 151.0), Qt::blue);
    graphicPersonel.push_back(graphicButler);

    // Create HeadWaiter graphical representations
    QGraphicElement* waiter1 = new QGraphicElement(new HeadWaiter(500.0, 151.0), Qt::black);
    graphicPersonel.push_back(waiter1);

    QGraphicElement* waiter2 = new QGraphicElement(new HeadWaiter(1000.0, 151.0), Qt::white);
    graphicPersonel.push_back(waiter2);

    return graphicPersonel;
}

void MainController::movePersonel(int elementIndex, QPointF destination) {
    // Access the specific element from the vector
    QGraphicElement* element = graphicPersonel[elementIndex];

    // Call the move method with the destination point
    element->move(destination);
}

int MainController::init(int argc, char *argv[], QApplication& a, View* v){
    vector<QGraphicElement*> graphicPersonel = createGraphicPersonel();
    v->setupPersonel(graphicPersonel);

    // vector<QGraphicElement*> graphicClients = createGraphicClients();
    // v->setupClients(graphicClients);

    RecipeBook recipeBook;
    auto ingredientsForSauceTomate = recipeBook.getIngredientEnums(Recette::SauceTomate);

    // moveElement(0, QPointF(800.0, 600.0));

    // moveElement(1, QPointF(300.0, 400.0));

    v->show();

    return a.exec();
}

void MainController::Restaurant(){
    // int numPeople = (rand() % 10) + 1;
    // butler.assignTable(table, numPeople);

    // Butler butler;
    // HeadWaiter headWaiter(&butler);

    // std::thread butlerThread([&butler]() {
    //     ClientModel client(100.0, 99.0, "COOL", 1, 5);     
    //     Table table;
    //     butler.assignTable(table, client);

    //     butler.notifyHeadWaiter(table, client);
    // });

    // std::thread headWaiterThread([&headWaiter]() {
    //     headWaiter.leadClients();
    // });

    // butlerThread.join();
    // headWaiterThread.join();
}

MainController::~MainController(){}
MainController::MainController(){}
