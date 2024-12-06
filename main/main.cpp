#include "../controller/classDeclaration/MainController.h"
// #include "../view/DisplayInterfacesClass.h"
// #include <QApplication>

int main(int argc, char *argv[])
{
    MainController* mainController = new MainController();
    mainController->init(argc, argv);
    // DisplayInterfacesClass::DisplayApp(QApplication(argc, argv));

    return 0;
}
