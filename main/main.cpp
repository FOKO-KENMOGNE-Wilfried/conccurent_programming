#include "../controller/classDeclaration/MainController.h"
#include <QApplication>
#include "../view/view.h"
#include <QDebug>

using namespace std;

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