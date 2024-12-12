#include "../controller/classDeclaration/MainController.h"
#include <QApplication>
// #include "../view/DisplayInterfacesClass.h"
// #include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    qDebug() << "Test debug message";
    MainController* mainController = new MainController();
    mainController->init(argc, argv, QApplication(argc, argv));
    // DisplayInterfacesClass::DisplayApp(QApplication(argc, argv));

    return 0;
}
