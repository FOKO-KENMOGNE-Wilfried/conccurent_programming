#include "view.h"
#include <QFile>
#include <QTextStream>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QApplication>
#include <QGraphicsScene>
#include <QtMath>
#include <QDebug>

View::View(QWidget *parent) : QMainWindow(parent) {
    setupUi();
    setupReceptionArea();
    displayPositions();
}

void View::setupUi() {
    centralWidget = new QWidget(this);
    mainLayout = new QVBoxLayout(centralWidget);

    // Layout du haut (pour les boutons)
    QHBoxLayout *topLayout = new QHBoxLayout();
    startButton = new QPushButton("Start");
    pauseButton = new QPushButton("Pause");
    speedButton = new QPushButton("Speed");
    normalSpeedButton = new QPushButton("Normal speed");
    kitchenButton = new QPushButton("Kitchen");
    dashboardButton = new QPushButton("Dashboard");
    timeComboBox = new QComboBox();
    timeComboBox->addItem("00:00");

    // Ajouter les boutons
    topLayout->addWidget(startButton);
    topLayout->addWidget(pauseButton);
    topLayout->addWidget(speedButton);
    topLayout->addWidget(normalSpeedButton);
    topLayout->addWidget(kitchenButton);
    topLayout->addWidget(dashboardButton);
    topLayout->addWidget(timeComboBox);

    mainLayout->addLayout(topLayout);

    // Frame du jeu
    gameFrame = new QFrame(centralWidget);
    gameFrame->setObjectName("gameFrame");
    QVBoxLayout *gameLayout = new QVBoxLayout(gameFrame);
    
    receptionAreaView = new QGraphicsView(gameFrame);
    gameLayout->addWidget(receptionAreaView);
    
    mainLayout->addWidget(gameFrame);

    // Layout du bas
    QHBoxLayout *bottomLayout = new QHBoxLayout();

    // Section client
    QVBoxLayout *clientLayout = new QVBoxLayout();
    QLabel *clientLabel = new QLabel("Client Number");
    clientInput = new QLineEdit();
    clientLayout->addWidget(clientLabel);
    clientLayout->addWidget(clientInput);
    bottomLayout->addLayout(clientLayout);

    // Section plats servis
    QVBoxLayout *plateServedLayout = new QVBoxLayout();
    QLabel *plateServedLabel = new QLabel("Plate Served");
    plateServedTable = new QTableWidget(2, 1);
    plateServedTable->setHorizontalHeaderLabels(QStringList() << "Plates");
    plateServedTable->setItem(0, 0, new QTableWidgetItem("Koki"));
    plateServedTable->setItem(1, 0, new QTableWidgetItem("Eru"));
    plateServedLayout->addWidget(plateServedLabel);
    plateServedLayout->addWidget(plateServedTable);
    bottomLayout->addLayout(plateServedLayout);

    // Section menu
    QVBoxLayout *menuLayout = new QVBoxLayout();
    QLabel *menuLabel = new QLabel("Menu");
    menuTable = new QTableWidget(3, 1);
    menuTable->setHorizontalHeaderLabels(QStringList() << "Menu");
    menuTable->setItem(0, 0, new QTableWidgetItem("Koki"));
    menuTable->setItem(1, 0, new QTableWidgetItem("Eru"));
    menuTable->setItem(2, 0, new QTableWidgetItem("Tomatoes"));
    menuLayout->addWidget(menuLabel);
    menuLayout->addWidget(menuTable);
    bottomLayout->addLayout(menuLayout);

    // Section ingrédients
    QVBoxLayout *ingredientsLayout = new QVBoxLayout();
    QLabel *ingredientsLabel = new QLabel("Ingredients Used");
    ingredientsTable = new QTableWidget(2, 1);
    ingredientsTable->setHorizontalHeaderLabels(QStringList() << "Ingredients");
    ingredientsTable->setItem(0, 0, new QTableWidgetItem("Tomatoes"));
    ingredientsTable->setItem(1, 0, new QTableWidgetItem("Cabbages"));
    ingredientsLayout->addWidget(ingredientsLabel);
    ingredientsLayout->addWidget(ingredientsTable);
    bottomLayout->addLayout(ingredientsLayout);

    mainLayout->addLayout(bottomLayout);

    setCentralWidget(centralWidget);

    QFile file(":/assets/style.css");
    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(file.readAll());
        qApp->setStyleSheet(styleSheet);
    } else {
        qWarning() << "Impossible de charger le fichier CSS.";
    }
}

void View::setupReceptionArea() {
    scene = new QGraphicsScene(this);
    receptionAreaView->setScene(scene);

    setupCounter();
    setupTables();
    setupPerson();

    moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, [this]() {
        moveToPosition(person, targetPosition);
    });
    moveTimer->start(16); // Met à jour toutes les 16 ms (environ 60 FPS)
}

void View::setupCounter() {
    // Place le comptoir en haut au milieu avec plus d'espace
    counter = new QGraphicsRectItem(0, 0, 100, 50);
    counter->setBrush(Qt::gray);
    counter->setPos(150, 20);
    scene->addItem(counter);
}

void View::setupTables() {
    int startXLeft = 60;    // Début des tables de la gauche sur l'axe X
    int startXRight = 300;  // Début des tables de la droite sur l'axe X
    int startYTop = 200;    // Position initiale sur l'axe Y pour la première ligne, avec plus d'espace
    int startYBottom = 280; // Position initiale sur l'axe Y pour la deuxième ligne, avec plus d'espace
    int spaceX = 60;        // Espace entre les tables horizontalement

    // Tables de gauche
    for (int i = 0; i < 3; ++i) {
        QGraphicsRectItem *tableTopLeft = new QGraphicsRectItem(0, 0, 50, 50);
        tableTopLeft->setBrush(Qt::blue);
        tableTopLeft->setPos(startXLeft + (i * spaceX), startYTop);
        tables.append(tableTopLeft);
        scene->addItem(tableTopLeft);
    }
    for (int i = 0; i < 2; ++i) {
        QGraphicsRectItem *tableBottomLeft = new QGraphicsRectItem(0, 0, 50, 50);
        tableBottomLeft->setBrush(Qt::blue);
        tableBottomLeft->setPos(startXLeft + (i * spaceX), startYBottom);
        tables.append(tableBottomLeft);
        scene->addItem(tableBottomLeft);
    }

    // Tables de droite
    for (int i = 0; i < 3; ++i) {
        QGraphicsRectItem *tableTopRight = new QGraphicsRectItem(0, 0, 50, 50);
        tableTopRight->setBrush(Qt::blue);
        tableTopRight->setPos(startXRight + (i * spaceX), startYTop);
        tables.append(tableTopRight);
        scene->addItem(tableTopRight);
    }
    for (int i = 0; i < 2; ++i) {
        QGraphicsRectItem *tableBottomRight = new QGraphicsRectItem(0, 0, 50, 50);
        tableBottomRight->setBrush(Qt::blue);
        tableBottomRight->setPos(startXRight + (i * spaceX), startYBottom);
        tables.append(tableBottomRight);
        scene->addItem(tableBottomRight);
    }
}
/**
 * @brief The function to display the PNJ
 */
void View::setupPerson() {
    person = new QGraphicsEllipseItem(0, 0, 10, 10);
    person->setBrush(Qt::red);
    person->setPos(0, 0);
    scene->addItem(person);

    targetPosition = QPointF(300, 200);
}
/**
 * @brief The function to mange the items movement
 */
void View::moveToPosition(QGraphicsEllipseItem* item, QPointF destination) {
    QPointF currentPosition = item->pos();
    if (currentPosition.x() != destination.x()) {
        // Déplacement sur l'axe X
        float directionX = (destination.x() - currentPosition.x() > 0) ? 1.0 : -1.0;
        item->moveBy(directionX, 0);
    } else if (currentPosition.y() != destination.y()) {
        // Déplacement sur l'axe Y
        float directionY = (destination.y() - currentPosition.y() > 0) ? 1.0 : -1.0;
        item->moveBy(0, directionY);
    }
}
/**
 * @brief The function to display all of the positions of the map's elements.
 */
void View::displayPositions() {
    qDebug() << "Position du comptoir: " << counter->pos();
    for (int i = 0; i < tables.size(); ++i) {
        qDebug() << "Position de la table " << i + 1 << ": " << tables[i]->pos();
    }
    qDebug() << "Position du personnage: " << person->pos();
}
