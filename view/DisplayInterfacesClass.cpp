#include "view.h"
#include "kitchen.h"
#include "DisplayInterfacesClass.h"
#include <QApplication>

int DisplayInterfacesClass::DisplayApp(int argc, char *argv[])
{
    QApplication a(argc, argv);
    View w;
    Kitchen k;
    w.show();
    k.show();
    return a.exec();
}
