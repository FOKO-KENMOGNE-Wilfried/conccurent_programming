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
#include <queue>
#include "../model/classDeclaration/Human.h"
#include "../model/graphicElement/classDeclaration/QGraphicElement.h"
#include <QGraphicsPixmapItem>  // Ajout de l'importation pour QGraphicsPixmapItem
#include <QLCDNumber>

#include "dashboard.h"  // Inclure le fichier Dashboard

class View : public QMainWindow {
    Q_OBJECT

public:
    View(QWidget *parent, std::list<Human*> humanList);
    std::list<Human*> humanQueue;
    // explicit View(QWidget *parent = nullptr);
private slots:
    void openDashboard();  // Slot pour ouvrir le Dashboard

private:
    void setupUi();
    void setupReceptionArea();
    void setupCounter();
    void setupTables();
    void setupPerson();
    void moveToPosition(QGraphicsEllipseItem* item, QPointF destination);
    void displayPositions();
    void createPerson(Human* human, QGraphicsScene *scene);
    void setupUi();  // Fonction pour initialiser l'interface utilisateur
    void setupReceptionArea();  // Fonction pour configurer la zone de réception
    void setupCounter();  // Fonction pour configurer le comptoir
    void setupTables();  // Fonction pour configurer les tables

    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QFrame *gameFrame;
    QGraphicsView *receptionAreaView;
    QGraphicsScene *scene;
    QGraphicsRectItem *counter;
    QList<QGraphicsRectItem*> tables;
    QGraphicsEllipseItem *person;
    QGraphicsEllipseItem *thisPersonInstance;
    QTimer *timer;
    QTimer *moveTimer;
    
    QPointF targetPosition;
    QWidget *centralWidget;  // Widget central de l'interface
    QVBoxLayout *mainLayout;  // Layout principal
    QGraphicsView *gameView;  // Vue pour afficher la scène de jeu
    QGraphicsScene *scene;  // Scène de la vue
    QGraphicsRectItem *counter;  // Élément de comptoir
    QList<QGraphicsPixmapItem*> tables;  // Liste des tables
    QGraphicsEllipseItem *person;  // Personnage à déplacer
    QTimer *timer;  // Timer général
    QTimer *moveTimer;  // Timer pour le déplacement du personnage

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

    Dashboard *dashboardWindow;  // Pointeur vers la fenêtre Dashboard
};

#endif // VIEW_H
