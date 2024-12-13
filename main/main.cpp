#include "../controller/classDeclaration/MainController.h"
#include "../view/view.h"
#include "../controller/classDeclaration/TimerController.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    qDebug() << "Test debug message";
    QApplication app(argc, argv);
    MainController* mainController = new MainController();
    TimerController* controller = new TimerController(); 

    list<Human*> humanList;
    View* view = new View(nullptr, humanList, controller);
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
