#include "kitchen.h"
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

Kitchen::Kitchen(QWidget *parent) : QMainWindow(parent), dashboardWindow(nullptr) {
    setupUi();

    // Appel de la fonction pour configurer la zone de réception (tables, personnage, etc.)
    setupKitchenArea();

    dashboardWindow = new Dashboard(this); // Initialisation de la fenêtre dashboard
    connect(dashboardButton, &QPushButton::clicked, this, &Kitchen::openDashboard); // Connecte le bouton
}

void Kitchen::setupUi() {
    setWindowTitle("Kitchen");
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
    kitchenView = new QGraphicsView(centralWidget);
    kitchenView->setRenderHint(QPainter::Antialiasing);
    kitchenView->setRenderHint(QPainter::SmoothPixmapTransform);
    kitchenView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    kitchenView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    kitchenView->setStyleSheet(
        "QGraphicsView {"
            "background-image: url(:/assets/tiles.jpg);"
            "border-radius: 15px;"
            "background-size: cover;"
            "background-position: center;"
            "border: 2px solid #ccc;"
            "box-shadow: 0 4px 8px rgba(0, 0, 0, 0.2);"
            "min-width: 550px;"
            "min-height: 570px;"
            "margin: 10px auto;"
        "}"
        );


    // Créer la scène
    kitchenScene = new QGraphicsScene(this);
    kitchenView->setScene(kitchenScene);
    mainLayout->addWidget(kitchenView);


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

    // Debugging the stylesheet loading
    QFile file(":/assets/style.css");
    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(file.readAll());
        qApp->setStyleSheet(styleSheet);
        qDebug() << "Kitchen Stylesheet loaded successfully!";
    } else {
        qWarning() << "Impossible de charger le fichier CSS: " << file.errorString();
    }
}

void Kitchen::setupKitchenArea() {
    // Ajoutez ici la logique pour positionner vos éléments graphiques (tables, personnages, etc.)
    setupFridge();
    setupSink();
    // setupStoves();
    // setupDishwasher();
    // setupWashingMachine();
    // setupColdRoom();
    // setupFreezer();

    // moveTimer = new QTimer(this);
    // connect(moveTimer, &QTimer::timeout, [this]() {
    //     moveToPosition(person, targetPosition);
    // });
    // moveTimer->start(16); // Met à jour toutes les 16 ms (environ 60 FPS)
}

void Kitchen::setupFridge() {
    int fridgeWidth = 200;
    int fridgeHeight = 150;
    int fridgeY = 20;
    int sceneWidth = 550;    // Largeur de la scène (taille fixe)
    int sceneHeight = 570;   // Hauteur de la scène (taille fixe)

    // Position X pour chaque comptoir (séparés pour donner une impression réaliste)
    int fridgeX = 20;   // Position X pour le comptoir de la caisse

    // Charger les images des comptoirs
    QPixmap fridgePixmapLeft(":/assets/frigo.png");

    // Redimensionner les images selon les dimensions du comptoir
    QPixmap fridgeScaledLeft = fridgePixmapLeft.scaled(fridgeWidth, fridgeHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // Comptoir gauche (pour la caisse)
    QGraphicsPixmapItem *fridge = new QGraphicsPixmapItem(fridgeScaledLeft);
    fridge->setPos(fridgeX, fridgeY); // Position du comptoir de la caisse
    kitchenScene->addItem(fridge);
    qDebug() << "Comptoir gauche (Caisse) ajouté aux coordonnées (" << fridgeX << "," << fridgeY << ")";

    // Ajuster la scène pour inclure tous les objets sans débordement
    kitchenScene->setSceneRect(0, 0, sceneWidth, sceneHeight); // Dimensions fixes de la scène
}

void Kitchen::setupSink() {
    int sinkWidth = 200;
    int sinkHeight = 150;
    int sinkY = 20;
    int sceneWidth = 550;    // Largeur de la scène (taille fixe)
    int sceneHeight = 570;   // Hauteur de la scène (taille fixe)

    // Position X pour chaque comptoir (séparés pour donner une impression réaliste)
    int sinkX = 140;   // Position X pour le comptoir de la caisse

    // Charger les images des comptoirs
    QPixmap sinkPixmapLeft(":/assets/frigo.png");

    // Redimensionner les images selon les dimensions du comptoir
    QPixmap sinkScaledLeft = sinkPixmapLeft.scaled(sinkWidth, sinkHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // Comptoir gauche (pour la caisse)
    QGraphicsPixmapItem *sink = new QGraphicsPixmapItem(sinkScaledLeft);
    sink->setPos(sinkX, sinkY); // Position du comptoir de la caisse
    kitchenScene->addItem(sink);
    qDebug() << "Comptoir gauche (Caisse) ajouté aux coordonnées (" << sinkX << "," << sinkY << ")";

    // Ajuster la scène pour inclure tous les objets sans débordement
    kitchenScene->setSceneRect(0, 0, sceneWidth, sceneHeight); // Dimensions fixes de la scène
}

/**
 * @brief The function to display the dashboard
 */
void Kitchen::openDashboard() {
    if (!dashboardWindow) {
        qWarning() << "Kitchen window is null!";
        return;
    }
    this->dashboardWindow->show();
}





