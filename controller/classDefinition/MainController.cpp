//
// Created by darkwall on 12/2/24.
//
#include "../classDeclaration/MainController.h"
#include "../../view/DisplayInterfacesClass.h"
#include "../../enum/RecipeBook.cpp"
#include "../../view/kitchen.h"
#include "../../view/view.h"

#include <QApplication>
#include <iostream>

int MainController::init(int argc, char *argv[], QApplication a){


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

MainController::~MainController(){}
MainController::MainController(){}
