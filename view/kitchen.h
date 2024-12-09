#ifndef KITCHEN_H
#define KITCHEN_H

#include <QMainWindow>
#include <QTimer>
#include <QPushButton>
#include <QLineEdit>
#include <QTableWidget>
#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLCDNumber>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <vector>
#include <queue>

#include "dashboard.h"
#include "../model/classDeclaration/Human.h"
#include "../model/graphicElement/classDeclaration/QGraphicElement.h"
#include "../model/classDeclaration/Chief.h"
#include "../model/classDeclaration/Cook.h"
#include "../model/classDeclaration/KitchenAssistant.h"
#include "../model/classDeclaration/RestaurantDiver.h"
#include "../model/classDeclaration/Order.h"
// 
#include "../model/classDeclaration/KitchenCounter.h"
#include "../model/classDeclaration/DirtyDishesStorage.h"
#include "../model/classDeclaration/DishwasherModel.h"
#include "../model/classDeclaration/WashingMachine.h"

namespace Ui {
    class Kitchen;
}

class Kitchen : public QMainWindow
{
    Q_OBJECT

private slots:
    void openDashboard(); // Declare the slot to open the dashboard

public:
    explicit Kitchen(QWidget *parent = nullptr);
    int readyOrderNumber;
    int maxReadyOrder;
    int chiefNumber = 1;
    int cookNumber = 2;
    int cookAssistNumber = 2;
    int restaurantDiverNumber = 1;
    //
    // int kitchenCounterNumber = 1;
    int dirtyDishesStorageNumber = 1;
    int washingMachineNumber = 1;
    int dishwasherModelNumber = 1;
    int stoveNumber = 4;
    //
    vector<QGraphicElement*> kitchenCounterList;
    vector<QGraphicElement*> dirtyDishesStorageList;
    vector<QGraphicElement*> washingMachineList;
    vector<QGraphicElement*> dishwasherModelList;
    //
    vector<Order> restaurantOrders;
    vector<Order> readyOrder;
    KitchenCounter* kitchenCounter = new KitchenCounter(readyOrder, -20, 200);
    DirtyDishesStorage* dirtyDishesStorage = new DirtyDishesStorage();
    WashingMachine* washingMachine = new WashingMachine();
    DishwasherModel* dishwasherModel = new DishwasherModel(10.2, 10.2);

private:
    void setupUi(); // Function to set up the user interface
    void setupKitchenArea();  // Function to configure the kitchen area
    // void setupFridge(); // Function to configure the fridge
    // void setupSink(); // Function to configure the sink
    // void setupStoves(); // Function to configure the stoves
    // void setupDishwasher(); // Function to configure the dishwasher
    // void setupWashingMachine(); // Function to configure the washing machine
    // void setupColdRoom(); // Function to configure the cold room
    // void setupFreezer(); // Function to configure the freezer
    // void setupKitchenUtilities(); // Function to set up other kitchen utilities
    void createResttaurantPersonel(/*Human* human,*/  QGraphicsScene *scene);
    void createKitchenCounter(KitchenCounter* kitchen, QGraphicsScene *scene, bool hasPicture, QSize tableSize, QString tableType);
    void createKitchenDirtyDishesStorage(DirtyDishesStorage* kitchen, QGraphicsScene *scene, bool hasPicture, QSize tableSize, QString tableType);
    void createKitchenWashinMachineModel(WashingMachine* kitchen, QGraphicsScene *scene, bool hasPicture, QSize tableSize, QString tableType);
    void createKitchenDishwasherModel(DishwasherModel* kitchen, QGraphicsScene *scene, bool hasPicture, QSize tableSize, QString tableType);
    // void createKitchenCounter(KitchenCounter* kitchen, QGraphicsScene *scene, bool hasPicture, QSize tableSize, QString tableType);
    // void createKitchenCounter(KitchenCounter* kitchen, QGraphicsScene *scene, bool hasPicture, QSize tableSize, QString tableType);
    // void createKitchenCounter(KitchenCounter* kitchen, QGraphicsScene *scene, bool hasPicture, QSize tableSize, QString tableType);
    // void createKitchenCounter(KitchenCounter* kitchen, QGraphicsScene *scene, bool hasPicture, QSize tableSize, QString tableType);

    // Private members
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QGraphicsView *kitchenView; // Replacing QFrame with QGraphicsView
    QGraphicsScene *kitchenScene; // Scene associated with the view
    QTimer *timer; // General-purpose timer
    QTimer *moveTimer; // Timer for movement-related operations

    QPointF targetPosition; // Position for movement targeting

    QPushButton *startButton;
    QPushButton *pauseButton;
    QPushButton *speedButton;
    QPushButton *normalSpeedButton;
    QPushButton *dashboardButton; // Button to navigate to the dashboard
    QComboBox *timeComboBox;
    QLineEdit *clientInput; // Input field for client information
    QTableWidget *plateServedTable; // Table displaying served plates
    QTableWidget *menuTable; // Table displaying the menu
    QTableWidget *ingredientsTable; // Table displaying ingredients
    QLCDNumber *clientLCD; // Displays the number of clients

    Dashboard *dashboardWindow; // Pointer to the Dashboard window
};

#endif // KITCHEN_H
