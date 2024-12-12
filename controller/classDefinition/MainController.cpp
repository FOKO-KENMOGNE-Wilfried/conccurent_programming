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

    RecipeBook recipeBook;
    auto ingredientsForSauceTomate = recipeBook.getIngredientEnums(Recette::SauceTomate);

    // DisplayInterfacesClass displayInterfacesClass;void
    // displayInterfacesClass.DisplayApp(
    //     QApplication(argc, argv),
    //     humanList
    // );
    // displayInterfacesClass.DisplayKitchen(
    //     QApplication(argc, argv),
    //     readyOrder
    // );
    // QApplication(argc, argv) a;

    // View w(nullptr, humanList);
    // w.show();

    Kitchen k(nullptr, readyOrder);
    k.show();
    return a.exec();
}
MainController::~MainController(){}
MainController::MainController(){}
