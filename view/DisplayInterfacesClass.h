#ifndef DISPLAYINTERFACESCLASS_H
#define DISPLAYINTERFACESCLASS_H
#include <QApplication>
#include <queue>
#include <list>

#include "../model/classDeclaration/Human.h"

class DisplayInterfacesClass {
private:

public:
    // DisplayInterfacesClass();
    // ~DisplayInterfacesClass();
    int DisplayApp(QApplication a, std::list<Human*> humanList);
};

#endif