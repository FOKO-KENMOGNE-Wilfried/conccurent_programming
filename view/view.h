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
#include <QGraphicsPixmapItem>  // Ajout de l'importation pour QGraphicsPixmapItem
#include <QLCDNumber>

#include "dashboard.h"  // Inclure le fichier Dashboard

class View : public QMainWindow {
    Q_OBJECT

public:
    explicit View(QWidget *parent = nullptr);  // Constructeur de la classe View

private slots:
    void openDashboard();  // Slot pour ouvrir le Dashboard

private:
    void setupUi();  // Fonction pour initialiser l'interface utilisateur
    void setupReceptionArea();  // Fonction pour configurer la zone de réception
    void setupCounter();  // Fonction pour configurer le comptoir
    void setupTables();  // Fonction pour configurer les tables
    void setupPerson();  // Fonction pour configurer le personnage
    void moveToPosition(QGraphicsEllipseItem* item, QPointF destination);  // Déplacer un élément
    void displayPositions();  // Afficher les positions des éléments

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
