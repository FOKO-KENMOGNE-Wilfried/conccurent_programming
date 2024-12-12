#include "../controller/classDeclaration/MainController.h"
// #include "../view/DisplayInterfacesClass.h"
// #include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    qDebug() << "Test debug message";
    MainController* mainController = new MainController();
    // mainController->Restaurant();
    mainController->init(argc, argv);
    // DisplayInterfacesClass::DisplayApp(QApplication(argc, argv));

    return 0;
}
