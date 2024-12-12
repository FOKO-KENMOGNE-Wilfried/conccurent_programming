//
// Created by darkwall on 12/2/24.
//
#include "../classDeclaration/MainController.h"
#include "../../view/DisplayInterfacesClass.h"
#include "../../model/classDeclaration/ClientGroupCreator.h"
#include "../../model/classDeclaration/Butler.h"
#include "../../model/classDeclaration/ClientModel.h"
#include "../../model/classDeclaration/HeadWaiter.h"
#include "../../model/classDeclaration/Table.h"
#include "../../view/view.h"
#include <QApplication>
#include <cstdlib>
#include <thread>

void MainController::init(int argc, char *argv[]){
    humanList.push_front(new Human(1000.0, 250.0));
    ClientModel* client2 = new ClientModel(200.0, 99.0, "COOL", 2, 5);
    
    // humanQueue.front()->saysHello();
    DisplayInterfacesClass displayInterfacesClass;
    displayInterfacesClass.DisplayApp(QApplication(argc, argv), humanList);
}

void MainController::Restaurant(){
/*     ClientModel* client1 = new ClientModel(100.0, 99.0, "COOL", 1, 5);
    Butler* butler = new Butler(100.0, 151.0);
    HeadWaiter* waiter1 = new HeadWaiter(500.0, 151.0);
    HeadWaiter* waiter2 = new HeadWaiter(1000.0, 151.0); */

    
    // Table table;
    // table.addTables();
    // Number of clients groups
    // int numGroups = 5;
    // Create the client group
    // ClientGroupCreator groupCreator({}, numGroups);
    // groupCreator.createGroup();

    /* int numPeople = (rand() % 10) + 1;
    butler.assignTable(table, numPeople); */

    /* if (!groupCreator.getClientGroups().empty()) {
        ClientModel firstClient = groupCreator.getClientGroups().front();
        butler.notifyHeadWaiter(table, firstClient);
    } */

    /* Butler butler;
    HeadWaiter headWaiter(&butler);

    std::thread butlerThread([&butler]() {
        ClientModel client(100.0, 99.0, "COOL", 1, 5);     
        Table table;
        table.add_tables();
        butler.assignTable(table, client);

        butler.notifyHeadWaiter(table, client);
    });

    std::thread headWaiterThread([&headWaiter]() {
        headWaiter.leadClients();
    });

    butlerThread.join();
    headWaiterThread.join(); */
}

MainController::~MainController(){}
MainController::MainController(){}
