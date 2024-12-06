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
#include <iostream>

View::View(QWidget *parent, std::list<Human*> humanList) : QMainWindow(parent), dashboardWindow(nullptr) {
    setupUi();

    // Appel de la fonction pour configurer la zone de réception (tables, personnage, etc.)
    setupReceptionArea();

    dashboardWindow = new Dashboard(this); // Initialisation de la fenêtre dashboard
    connect(dashboardButton, &QPushButton::clicked, this, &View::openDashboard); // Connecte le bouton
}

void View::setupUi() {
    setWindowTitle("Restaurant");
    centralWidget = new QWidget(this);
    mainLayout = new QVBoxLayout(centralWidget);

    // Layout du haut (pour les boutons)
    QHBoxLayout *topLayout = new QHBoxLayout();

    // Bouton Start avec une icône
    startButton = new QPushButton();
    startButton->setIcon(QIcon(":/assets/start.png")); // Remplacez par le chemin de votre icône
    startButton->setIconSize(QSize(28, 28));

    // Bouton Pause avec une icône
    pauseButton = new QPushButton();
    pauseButton->setIcon(QIcon(":/assets/pause.png"));
    pauseButton->setIconSize(QSize(28, 28));

    // Bouton Speed avec une icône
    speedButton = new QPushButton();
    speedButton->setIcon(QIcon(":/assets/speed.png"));
    speedButton->setIconSize(QSize(28, 28));

    // Bouton Normal Speed avec une icône
    normalSpeedButton = new QPushButton();
    normalSpeedButton->setIcon(QIcon(":/assets/normal.png"));
    normalSpeedButton->setIconSize(QSize(28, 28));

    // Bouton Dashboard avec une icône
    dashboardButton = new QPushButton();
    dashboardButton->setIcon(QIcon(":/assets/dashboard.png"));
    dashboardButton->setIconSize(QSize(28, 28));

    // Input to show the time
    timeComboBox = new QComboBox();
    timeComboBox->addItem("00:00");

    // Ajouter les boutons
    topLayout->addWidget(startButton);
    topLayout->addWidget(pauseButton);
    topLayout->addWidget(speedButton);
    topLayout->addWidget(normalSpeedButton);
    topLayout->addWidget(dashboardButton);

    // Ajouter un espace flexible pour pousser le combo box à droite
    topLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    topLayout->addWidget(timeComboBox);

    mainLayout->addLayout(topLayout);

    // Définir le QGraphicsView au lieu du QFrame pour le jeu
    gameView = new QGraphicsView(centralWidget);
    gameView->setRenderHint(QPainter::Antialiasing);
    gameView->setRenderHint(QPainter::SmoothPixmapTransform);
    gameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Créer la scène
    scene = new QGraphicsScene(this);
    gameView->setScene(scene);
    mainLayout->addWidget(gameView);

    // Layout du bas
    QHBoxLayout *bottomLayout = new QHBoxLayout();

    // Section client
    QVBoxLayout *clientLayout = new QVBoxLayout();
    QLabel *clientLabel = new QLabel("Client Number");

    // Créer un QLCDNumber
    clientLCD = new QLCDNumber();
    clientLCD->setDigitCount(3); // Définit le nombre de chiffres affichés (3 pour 999 maximum)
    clientLCD->setSegmentStyle(QLCDNumber::Flat); // Style visuel (Flat, Filled, etc.)
    clientLCD->display(0); // Valeur initiale à afficher

    // Ajouter le label et le LCDNumber au layout
    clientLayout->addWidget(clientLabel);
    clientLayout->addWidget(clientLCD);
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

    // Load stylesheet from resource
    QFile file(":/assets/style.css");
    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(file.readAll());
        qApp->setStyleSheet(styleSheet);
        qDebug() << "Kitchen Stylesheet loaded successfully!";
    } else {
        qWarning() << "Impossible de charger le fichier CSS.";
    }

}

void View::setupReceptionArea() {
    // scene = new QGraphicsScene(this);
    // receptionAreaView->setScene(scene);

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
    // humanQueue.front();
    // createPerson(humanQueue.front(), scene);
}

void View::createPerson(Human* human, QGraphicsScene *scene){
    QGraphicElement* element = new QGraphicElement(human);
    scene->addItem(element->getRepresentation());
    
    element->move();
}

/**
 * @brief The function to mange the items movement
 * @param item, human
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

/**
 * @brief The function to display the dashboard
 */
void View::openDashboard() {
    if (!dashboardWindow) {
        qWarning() << "Kitchen window is null!";
        return;
    }
    this->dashboardWindow->show();
}