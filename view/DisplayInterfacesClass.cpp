#include "view.h"
#include "kitchen.h"
#include "DisplayInterfacesClass.h"
#include "../controller/classDeclaration/TimerController.h"

int DisplayInterfacesClass::DisplayApp(QApplication a, std::list<Human*> humanList, TimerController* controller)
                                                                                {
    // QApplication a(argc, argv);
    View w(nullptr, humanList, controller);
    w.show();
    return a.exec();
}

int DisplayInterfacesClass::DisplayKitchen(QApplication a, std::vector<Order*> order, TimerController* controller)
{
    Kitchen k(nullptr, order, controller);
    k.show();
    return a.exec();
}
