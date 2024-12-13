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


int MainController::init(int argc, char *argv[], QApplication& a, View* view){

    humanList.push_front(new Human(1000.0, 250.0));

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

void MainController::Restaurant(){
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

}

MainController::~MainController(){}
MainController::MainController(){}
