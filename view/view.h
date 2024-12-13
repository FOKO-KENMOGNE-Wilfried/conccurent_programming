#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QTimer>
#include <QPushButton>
#include <QLineEdit>
#include <QTableWidget>
#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <list>
#include <QTime>
#include <queue>
#include <QGraphicsPixmapItem>
#include <QLCDNumber>
#include <QGraphicsPixmapItem>
#include <any>

#include "../model/classDeclaration/Human.h"
#include "../model/graphicElement/classDeclaration/QGraphicElement.h"
#include "dashboard.h"
#include "../model/classDeclaration/Table.h"
#include "../controller/classDeclaration/TimerController.h"
#include "../contract/Observable.h"

class View : public QMainWindow {
    Q_OBJECT
// QApplication a
public:
    explicit View(QWidget *parent, std::list<Human*> humanList, TimerController* controller);
    std::list<Human*> humanList;
    // explicit View(QWidget *parent = nullptr);
private slots:
    void openDashboard();  // Slot pour ouvrir le Dashboard
    void updateTime();

private:
    void setupUi();
    void setupReceptionArea();
    void setupCounter();
    void setupTables();
    void setupPerson();
    void moveToPosition(QGraphicsEllipseItem* item, QPointF destination);
    void displayPositions();
    void createThings(ClientModel* human, QGraphicsScene *scene, Qt::GlobalColor color);
    void createTable(Table* table, QGraphicsScene *scene, bool hasPicture, QSize tableSize, QString tableType);

    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QGraphicsView *gameView;
    // QGraphicsView *receptionAreaView;
    QGraphicsScene *scene;
    QGraphicsRectItem *counter;
    QList<QGraphicsPixmapItem*> tables;
    QGraphicsEllipseItem *person;
    QGraphicsEllipseItem *thisPersonInstance;
    QTimer *timer;
    QTime currentTime;
    QTimer *moveTimer;

    QPointF targetPosition;  // Position cible du personnage
    QPushButton *startButton;  // Bouton pour démarrer
    QPushButton *pauseButton;  // Bouton pour mettre en pause
    QPushButton *speedButton;  // Bouton pour accélérer
    QPushButton *normalSpeedButton;  // Bouton pour vitesse normale
    QPushButton *dashboardButton;  // Bouton pour ouvrir le Dashboard
    QComboBox *timeComboBox;  // ComboBox pour afficher l'heure
    QLineEdit *clientInput;  // Champ de saisie pour le numéro de client
    QTableWidget *plateServedTable;  // Table pour les plats servis
    QTableWidget *menuTable;  // Table pour le menu
    QTableWidget *ingredientsTable;  // Table pour les ingrédients
    QLCDNumber *clientLCD; // Déclarez clientLCD ici
    QLCDNumber *timerDisplay;

    Dashboard *dashboardWindow;  // Pointeur vers la fenêtre Dashboard
    TimerController *controller; // Contrôleur pour gérer le minuteur
};

#endif // VIEW_H
