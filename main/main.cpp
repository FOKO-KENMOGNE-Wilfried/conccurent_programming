#include "../controller/classDeclaration/MainController.h"
#include <QApplication>
#include "../view/view.h"
// #include "../view/DisplayInterfacesClass.h"
// #include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    qDebug() << "Test debug message";
    QApplication app(argc, argv);
    MainController* mainController = new MainController();

    list<Human*> humanList;
    View* view = new View(nullptr, humanList);
    mainController->init(argc, argv, app, view);

    return 0;
}