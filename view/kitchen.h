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

#include "dashboard.h"

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

private:
    void setupUi(); // Function to set up the user interface
    void setupKitchenArea();  // Function to configure the kitchen area
    void setupFridge(); // Function to configure the fridge
    void setupSink(); // Function to configure the sink
    void setupStoves(); // Function to configure the stoves
    void setupDishwasher(); // Function to configure the dishwasher
    void setupWashingMachine(); // Function to configure the washing machine
    void setupColdRoom(); // Function to configure the cold room
    void setupFreezer(); // Function to configure the freezer
    void setupKitchenUtilities(); // Function to set up other kitchen utilities

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
