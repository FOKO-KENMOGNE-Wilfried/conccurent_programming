#include "view.h"
#include "DisplayInterfacesClass.h"
#include <QApplication>

int DisplayInterfacesClass::DisplayApp(int argc, char *argv[])
{
    QApplication a(argc, argv);
    View w;
    w.show();
    return a.exec();
}
