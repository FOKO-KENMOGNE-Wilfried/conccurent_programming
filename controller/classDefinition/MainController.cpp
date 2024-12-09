//
// Created by darkwall on 12/2/24.
//
#include "../classDeclaration/MainController.h"
#include "../../view/DisplayInterfacesClass.h"
#include <QApplication>

void MainController::init(int argc, char *argv[]){
    humanList.push_front(new Human(1000.0, 250.0));
    // humanQueue.front()->saysHello();
    DisplayInterfacesClass displayInterfacesClass;
    displayInterfacesClass.DisplayApp(QApplication(argc, argv), humanList);
}
MainController::~MainController(){}
MainController::MainController(){}
