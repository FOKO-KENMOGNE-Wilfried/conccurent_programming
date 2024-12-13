#ifndef DISPLAYINTERFACESCLASS_H
#define DISPLAYINTERFACESCLASS_H
#include <QApplication>
#include <queue>
#include <list>

#include "../model/classDeclaration/Human.h"
#include "../controller/classDeclaration/TimerController.h"

class DisplayInterfacesClass {
private:

public:
    // DisplayInterfacesClass();
    // ~DisplayInterfacesClass();
    int DisplayApp(QApplication a, std::list<Human*> humanList, TimerController* controller);
    int DisplayKitchen(QApplication a, std::vector<Order*>, TimerController* controller);
};

#endif
