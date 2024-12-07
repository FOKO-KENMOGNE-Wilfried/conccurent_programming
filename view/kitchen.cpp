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
    kitchenView->setDragMode(QGraphicsView::NoDrag);
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

    // Ajuster les marges du layout pour réduire l'espace entre le label et le LCD
    clientLayout->setSpacing(5); // Réduire l'espacement vertical à 5 pixels (ajustez selon vos besoins)
    clientLayout->setContentsMargins(0, 0, 0, 0); // Réduire les marges autour du layout

    // Ajouter le label et le LCDNumber au layout
    clientLayout->addWidget(clientLabel);
    clientLayout->addWidget(clientLCD);
    bottomLayout->addLayout(clientLayout);

    // Tableau combiné
    QVBoxLayout *combinedLayout = new QVBoxLayout();
    QLabel *combinedLabel = new QLabel("Rapport");
    QTableWidget *combinedTable = new QTableWidget(6, 3); // 6 lignes (2 + 3 + 2) et 3 colonnes
    combinedTable->setHorizontalHeaderLabels(QStringList() << "Plates Served" << "Menu" << "Ingredients");

    // Remplir les colonnes avec les données existantes

    // Colonne "Plates Served"
    combinedTable->setItem(0, 0, new QTableWidgetItem("Koki"));
    combinedTable->setItem(1, 0, new QTableWidgetItem("Eru"));

    // Colonne "Menu"
    combinedTable->setItem(0, 1, new QTableWidgetItem("Koki"));
    combinedTable->setItem(1, 1, new QTableWidgetItem("Eru"));
    combinedTable->setItem(2, 1, new QTableWidgetItem("Tomatoes"));

    // Colonne "Ingredients"
    combinedTable->setItem(0, 2, new QTableWidgetItem("Tomatoes"));
    combinedTable->setItem(1, 2, new QTableWidgetItem("Cabbages"));

    // Ajuster la disposition
    combinedLayout->addWidget(combinedLabel);
    combinedLayout->addWidget(combinedTable);
    bottomLayout->addLayout(combinedLayout);

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
    // Taille ajustée de la scène pour éviter le défilement
    int sceneWidth = 1200;
    int sceneHeight = 570;

    kitchenScene->setSceneRect(0, 0, sceneWidth, sceneHeight);

    // Dimensions des éléments
    int elementWidth = 90;
    int elementHeight = 90;

    // Images des éléments
    QList<QString> elementImages = {
        ":/assets/frigo.png",     // Frigo
        ":/assets/lave_vaisselle.png", // Lave-vaisselle
        ":/assets/machine.png",  // Machine à laver
        ":/assets/sink.png",     // Évier
        ":/assets/stove.png",    // Cuisinière
        ":/assets/chambre_froide.png", // Chambre froide
        ":/assets/freezer.png",  // Congélateur
        ":/assets/counter.png"   // Plan de travail
    };

    // --- Cuisinières (en haut au milieu) ---
    int stoveStartX = 450; // Position horizontale de départ
    int stoveY = 5;       // Position verticale fixe
    for (int i = 0; i < 5; ++i) {
        QPixmap pixmap(elementImages[4]); // Cuisinière
        QPixmap scaledPixmap = pixmap.scaled(elementWidth, elementHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QGraphicsPixmapItem *stoveItem = new QGraphicsPixmapItem(scaledPixmap);
        int posX = stoveStartX + i * (elementWidth + 10);
        stoveItem->setPos(posX, stoveY); // Espacement entre les cuisinières
        kitchenScene->addItem(stoveItem);
        qDebug() << "Stove " << i + 1 << " position: (" << posX << ", " << stoveY << ")";
    }

    // --- Frigo et congélateur (à droite des cuisinières) ---
    int fridgeX = stoveStartX + 5 * (elementWidth + 10) + 20;
    int fridgeY = 15;
    QPixmap fridgePixmap(elementImages[0]); // Frigo
    QPixmap scaledFridge = fridgePixmap.scaled(elementWidth, elementHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QGraphicsPixmapItem *fridgeItem = new QGraphicsPixmapItem(scaledFridge);
    fridgeItem->setPos(fridgeX, fridgeY);
    kitchenScene->addItem(fridgeItem);
    qDebug() << "Fridge position: (" << fridgeX << ", " << fridgeY << ")";

    QPixmap freezerPixmap(elementImages[6]); // Congélateur
    QPixmap scaledFreezer = freezerPixmap.scaled(elementWidth, elementHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QGraphicsPixmapItem *freezerItem = new QGraphicsPixmapItem(scaledFreezer);
    freezerItem->setPos(fridgeX + elementHeight + 10, fridgeY);
    kitchenScene->addItem(freezerItem);
    qDebug() << "Freezer position: (" << fridgeX + elementHeight + 10 << ", " << fridgeY << ")";

    // --- Chambre froide (en bas à droite) ---
    int coldRoomX = sceneWidth - elementWidth - 10;
    int coldRoomY = 450;
    QPixmap coldRoomPixmap(elementImages[5]); // Chambre froide
    QPixmap scaledColdRoom = coldRoomPixmap.scaled(elementWidth, elementHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QGraphicsPixmapItem *coldRoomItem = new QGraphicsPixmapItem(scaledColdRoom);
    coldRoomItem->setPos(coldRoomX, coldRoomY);
    kitchenScene->addItem(coldRoomItem);
    qDebug() << "Cold room position: (" << coldRoomX << ", " << coldRoomY << ")";

    // --- Plan de travail (en haut à gauche) ---
    int prepX = -20; // En haut à gauche
    int prepY = 200;
    QPixmap prepTablePixmap(elementImages[7]); // Plan de travail
    QPixmap scaledPrepTable = prepTablePixmap.scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QGraphicsPixmapItem *prepTableItem = new QGraphicsPixmapItem(scaledPrepTable);
    prepTableItem->setPos(prepX, prepY);
    kitchenScene->addItem(prepTableItem);
    qDebug() << "Prep table position: (" << prepX << ", " << prepY << ")";

    // --- Évier (au milieu) ---
    int sinkX = sceneWidth / 2 - elementWidth / 2;
    int sinkY = sceneHeight / 2 - elementHeight / 2;
    QPixmap sinkPixmap(elementImages[3]); // Évier
    QPixmap scaledSink = sinkPixmap.scaled(elementWidth, elementHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QGraphicsPixmapItem *sinkItem = new QGraphicsPixmapItem(scaledSink);
    sinkItem->setPos(sinkX, sinkY);
    kitchenScene->addItem(sinkItem);
    qDebug() << "Sink position: (" << sinkX << ", " << sinkY << ")";

    // --- Lave-vaisselle et machine à laver (en bas au milieu) ---
    int dishwasherX = sinkX - 100; // Lave-vaisselle à gauche de l'évier
    int washerX = sinkX + 100;     // Machine à laver à droite de l'évier
    int applianceY = 450;

    QPixmap dishwasherPixmap(elementImages[1]); // Lave-vaisselle
    QPixmap scaledDishwasher = dishwasherPixmap.scaled(elementWidth, elementHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QGraphicsPixmapItem *dishwasherItem = new QGraphicsPixmapItem(scaledDishwasher);
    dishwasherItem->setPos(dishwasherX, applianceY);
    kitchenScene->addItem(dishwasherItem);
    qDebug() << "Dishwasher position: (" << dishwasherX << ", " << applianceY << ")";

    QPixmap washerPixmap(elementImages[2]); // Machine à laver
    QPixmap scaledWasher = washerPixmap.scaled(elementWidth, elementHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QGraphicsPixmapItem *washerItem = new QGraphicsPixmapItem(scaledWasher);
    washerItem->setPos(washerX, applianceY);
    kitchenScene->addItem(washerItem);
    qDebug() << "Washer position: (" << washerX << ", " << applianceY << ")";
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





