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

/* int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // Create the human list (or retrieve it dynamically)
    std::list<Human*> humanList;

    // Create the view and pass the controller
    View view(nullptr, humanList);
    view.show();

    return app.exec();
} */