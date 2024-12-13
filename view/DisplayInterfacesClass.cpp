#include "view.h"
#include "kitchen.h"
#include "DisplayInterfacesClass.h"

int DisplayInterfacesClass::DisplayApp(QApplication a, std::list<Human*> humanList)
                                                                                {
    // // QApplication a(argc, argv);
    // View w(nullptr, humanList);
    // w.show();
    // return a.exec();
}

int DisplayInterfacesClass::DisplayKitchen(QApplication a, std::vector<Order*> order)
{
    // Kitchen k(nullptr, order);
    // k.show();
    // return a.exec();
}