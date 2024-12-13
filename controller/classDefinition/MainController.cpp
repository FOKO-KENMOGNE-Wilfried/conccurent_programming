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
    graphicClients.reserve(3);
    for (int clientId = 1; clientId <= 3; clientId++){
        int capacity = (rand() % 10) + 1;
        // Log client creation
        qDebug() << "Creating " << capacity <<" clients with ID:" << clientId ;

        // Create a Client graphical representation
        QGraphicElement* client = new QGraphicElement(new ClientModel(100.0, 99.0, capacity, clientId), Qt::red);
        graphicClients.push_back(client);

        // Populating ClienModelList
        ClientModel clientModel(100.0, 99.0, capacity, clientId);
        clientList.push_back(clientModel);
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

void MainController::moveClient(int elementIndex, QPointF destination){
    // Access the specific element from the vector
    QGraphicElement* element = graphicClients[elementIndex];

    // Call the move method with the destination point
    element->move(destination);    
}

int MainController::init(int argc, char *argv[], QApplication& a, View* v){
    vector<QGraphicElement*> graphicPersonel;
    vector<QGraphicElement*> graphicClients;

    std::thread personelThread([&]() {
        graphicPersonel = createGraphicPersonel();
    });

    std::thread clientsThread([&]() {
        graphicClients = createGraphicClients();
    });

    personelThread.join();
    clientsThread.join();

    v->setupPersonel(graphicPersonel);
    v->setupClients(graphicClients);

    // ------------------------------------------------------
    Butler butler;
    // HeadWaiter headWaiter(&butler);

    // std::thread butlerThread([&]() {
    MainController controller;
    Table table;
    butler.assignTable(table, controller.getClientModelList());

    movePersonel(1, QPointF(200, 198));
    movePersonel(2, QPointF(500,500));
    moveClient(1, QPointF(200,200));
    moveClient(2, QPointF(500,500));

    //     butler.notifyHeadWaiter(table, controller.getClientModelList());
    // });

    // std::thread headWaiterThread([&]() {
    //     headWaiter.leadClients();
    // });

    // butlerThread.join();
    // headWaiterThread.join();
    // -------------------------------------------------------

    // auto ingredientsForSauceTomate = recipeBook.getIngredientEnums(Recette::SauceTomate);

    // View w(nullptr, humanList);
    // w.show();

    Kitchen k(
        nullptr,
        readyOrder,
        kitchenCounterList,
        dirtyDishesStorageList,
        washingMachineList,
        dishwasherModelList,
        stoveItemList,
        chief
    );
    // std::cout << "--------------------------------" << std::endl;
    // std::cout << chief->getChief()->abscise << std::endl;
    k.show();
    return a.exec();
}

/* void MainController::Restaurant(){
    Butler butler;
    HeadWaiter headWaiter(&butler);

    std::thread butlerThread([&]() {
        MainController controller;
        Table table;
        butler.assignTable(table, controller.getClientModelList());
        v->movePersonel(0, QPointF(500.0, 500.0));
        butler.notifyHeadWaiter(table, controller.getClientModelList());
    });

    std::thread headWaiterThread([&]() {
        headWaiter.leadClients();
    });

    butlerThread.join();
    headWaiterThread.join();
} */

MainController::~MainController(){}
MainController::MainController(){}
