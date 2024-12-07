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
    void openDashboard(); // Déclarer le slot

public:
    explicit Kitchen(QWidget *parent = nullptr);

private:
    void setupUi();
    void setupKitchenArea();  // Fonction pour configurer la zone de cuisine
    void setupFridge(); // Fonction pour configurer le frigo
    void setupSink(); // Fonction pour configurer la plonge
    void setupStoves(); // Fonction pour configurer les feux de cuisson
    void setupDishwasher(); // Fonction pour configurer le lave-vaisselle
    void setupWashingMachine(); // Fonction pour configurer la machine à laver
    void setupColdRoom(); // Fonction pour configurer la chambre froide
    void setupFreezer(); // Fonction pour configurer le congelateur
    void setupKitchenUtilities();


    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QGraphicsView *kitchenView; // Remplace QFrame par QGraphicsView
    QGraphicsScene *kitchenScene; // Scène associée à la vue
    QTimer *timer;
    QTimer *moveTimer;

    QPointF targetPosition;

    QPushButton *startButton;
    QPushButton *pauseButton;
    QPushButton *speedButton;
    QPushButton *normalSpeedButton;
    QPushButton *dashboardButton;
    QComboBox *timeComboBox;
    QLineEdit *clientInput;
    QTableWidget *plateServedTable;
    QTableWidget *menuTable;
    QTableWidget *ingredientsTable;
    QLCDNumber *clientLCD; // Déclarez clientLCD ici

    Dashboard *dashboardWindow; // Ajouter un pointeur vers Dashboard
};

#endif // KITCHEN_H
