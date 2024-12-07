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

#include "../model/classDeclaration/ClientModel.h"

View::View(QWidget *parent, std::list<Human*> humanList) : QMainWindow(parent), dashboardWindow(nullptr) {
    this->humanList = humanList;
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

    // Top layout for the button
    QHBoxLayout *topLayout = new QHBoxLayout();

    // Start button with icon
    startButton = new QPushButton();
    startButton->setIcon(QIcon(":/assets/start.png")); // Remplacez par le chemin de votre icône
    startButton->setIconSize(QSize(28, 28));

    // Pause button with icon
    pauseButton = new QPushButton();
    pauseButton->setIcon(QIcon(":/assets/pause.png"));
    pauseButton->setIconSize(QSize(28, 28));

    // Up Speed button with icon
    speedButton = new QPushButton();
    speedButton->setIcon(QIcon(":/assets/speed.png"));
    speedButton->setIconSize(QSize(28, 28));

    // Normal Speed button with icon
    normalSpeedButton = new QPushButton();
    normalSpeedButton->setIcon(QIcon(":/assets/normal.png"));
    normalSpeedButton->setIconSize(QSize(28, 28));

    // Dashboard button with icon
    dashboardButton = new QPushButton();
    dashboardButton->setIcon(QIcon(":/assets/dashboard.png"));
    dashboardButton->setIconSize(QSize(28, 28));

    // Input to show the time
    timeComboBox = new QComboBox();
    timeComboBox->addItem("00:00");

    // Add buttons
    topLayout->addWidget(startButton);
    topLayout->addWidget(pauseButton);
    topLayout->addWidget(speedButton);
    topLayout->addWidget(normalSpeedButton);
    topLayout->addWidget(dashboardButton);

    // Add space between
    topLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    topLayout->addWidget(timeComboBox);

    mainLayout->addLayout(topLayout);

    // Define the QGraphicsView
    gameView = new QGraphicsView(centralWidget);
    gameView->setRenderHint(QPainter::Antialiasing);
    gameView->setRenderHint(QPainter::SmoothPixmapTransform);
    gameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Create scene
    scene = new QGraphicsScene(this);
    gameView->setScene(scene);
    mainLayout->addWidget(gameView);

    // Bottom layout
    QHBoxLayout *bottomLayout = new QHBoxLayout();

    // Client section
    QVBoxLayout *clientLayout = new QVBoxLayout();
    QLabel *clientLabel = new QLabel("Client Number");

    // Create an QLCDNumber
    clientLCD = new QLCDNumber();
    clientLCD->setDigitCount(3); // Définit le nombre de chiffres affichés (3 pour 999 maximum)
    clientLCD->setSegmentStyle(QLCDNumber::Flat); // Style visuel (Flat, Filled, etc.)
    clientLCD->display(0); // Valeur initiale à afficher

    // Add the label and the LCDNumber at the layout
    clientLayout->addWidget(clientLabel);
    clientLayout->addWidget(clientLCD);
    bottomLayout->addLayout(clientLayout);


    // Plate section
    QVBoxLayout *plateServedLayout = new QVBoxLayout();
    QLabel *plateServedLabel = new QLabel("Plate Served");
    plateServedTable = new QTableWidget(2, 1);
    plateServedTable->setHorizontalHeaderLabels(QStringList() << "Plates");
    plateServedTable->setItem(0, 0, new QTableWidgetItem("Koki"));
    plateServedTable->setItem(1, 0, new QTableWidgetItem("Eru"));
    plateServedLayout->addWidget(plateServedLabel);
    plateServedLayout->addWidget(plateServedTable);
    bottomLayout->addLayout(plateServedLayout);

    // Menu section
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

    // Ingredients section
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
    setupCounter();
    setupTables();
    setupPerson();

    moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, [this]() {
        moveToPosition(person, targetPosition);
    });
    moveTimer->start(16); // Update every 16 miliseconds (approximately 60IPS)
}

void View::setupCounter() {
    int counterWidth = 100;  // Largeur du comptoir
    int counterHeight = 50;  // Hauteur du comptoir
    int sceneWidth = 550;    // Largeur de la scène (taille fixe)
    int sceneHeight = 570;   // Hauteur de la scène (taille fixe)
    int counterY = 80;       // Position verticale commune pour les deux comptoirs
    int spacingX = 150;      // Espacement entre les comptoirs

    // Position X pour chaque comptoir (séparés pour donner une impression réaliste)
    int leftCounterX = 60;   // Position X pour le comptoir de la caisse
    int rightCounterX = 1370; // Position X pour le comptoir de prise des plats

    // Charger les images des comptoirs
    QPixmap counterPixmapLeft(":/assets/comptoir.png");  // Remplacez par votre image pour le comptoir de caisse
    QPixmap counterPixmapRight(":/assets/cuisine.png");  // Remplacez par votre image pour le comptoir des plats

    // Redimensionner les images selon les dimensions du comptoir
    QPixmap counterScaledLeft = counterPixmapLeft.scaled(counterWidth, counterHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QPixmap counterScaledRight = counterPixmapRight.scaled(counterWidth, counterHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // Comptoir gauche (pour la caisse)
    QGraphicsPixmapItem *counterLeft = new QGraphicsPixmapItem(counterScaledLeft);
    counterLeft->setPos(leftCounterX, counterY); // Position du comptoir de la caisse
    scene->addItem(counterLeft);
    qDebug() << "Comptoir gauche (Caisse) ajouté aux coordonnées (" << leftCounterX << "," << counterY << ")";

    // Comptoir droit (pour la prise des plats)
    QGraphicsPixmapItem *counterRight = new QGraphicsPixmapItem(counterScaledRight);
    counterRight->setPos(rightCounterX, counterY); // Position du comptoir de prise des plats
    scene->addItem(counterRight);
    qDebug() << "Comptoir droit (Cuisine) ajouté aux coordonnées (" << rightCounterX << "," << counterY << ")";

    // Ajuster la scène pour inclure tous les objets sans débordement
    scene->setSceneRect(0, 0, sceneWidth, sceneHeight); // Dimensions fixes de la scène
}

void View::setupTables() {
    // Space and size
    int startX = 60;
    int startY = 200;
    int spaceX = 100;
    int spaceY = 150;
    int squareOffsetX = 800;
    QSize tableSize(90, 90);
    int currentTableIndex = 0;

    // Table type and quality
    QList<QPair<QString, int>> tableData = {
        {":/assets/table2.png", 10},  // 10 tables type table2
        {":/assets/table4.png", 10},  // 10 tables type table4
        {":/assets/table6.png", 5},   // 5 tables type table6
        {":/assets/table8.png", 5},   // 5 tables type table8
        {":/assets/table10.png", 2}   // 2 tables type table10
    };

    // Function to collect the next table type
    auto getNextTableType = [&]() -> QString {
        while (currentTableIndex < tableData.size()) {
            int &remainingTables = tableData[currentTableIndex].second;
            if (remainingTables > 0) {
                remainingTables--;
                return tableData[currentTableIndex].first;
            }
            currentTableIndex++;
        }
        return QString();
    };

    // Table organization in 2 squares
    for (int square = 0; square < 2; ++square) {
        int currentX = startX + square * squareOffsetX; // Décalage horizontal pour le carré
        int currentY = startY;

        // 02 columns of 06 tables
        for (int row = 0; row < 2; ++row) {
            for (int col = 0; col < 6; ++col) {
                QString tableType = getNextTableType();
                if (!tableType.isEmpty()) {
                    // QPixmap originalPixmap(tableType);
                    // QPixmap scaledPixmap = originalPixmap.scaled(tableSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                    // QGraphicsPixmapItem *table = new QGraphicsPixmapItem(scaledPixmap);
                    // table->setPos(currentX + col * spaceX, currentY);
                    // tables.append(table);
                    // scene->addItem(table);

                    Table* table = new Table(currentX + col * spaceX, currentY, 10);
                    createTable(table, scene, true, tableSize, tableType);

                    // Debug : Display position
                    qDebug() << "Table (" << tableType << ") Position: ("
                             << (currentX + col * spaceX) << "," << currentY << ")";
                }
            }
            currentY += spaceY; // Go to the next column
        }

        // 01 colums of 04 table in the middle
        currentX = startX + square * squareOffsetX + spaceX; // Décalage pour centrer les 4 tables
        for (int col = 0; col < 4; ++col) {
            QString tableType = getNextTableType();
            if (!tableType.isEmpty()) {
                // QPixmap originalPixmap(tableType);
                // QPixmap scaledPixmap = originalPixmap.scaled(tableSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                // QGraphicsPixmapItem *table = new QGraphicsPixmapItem(scaledPixmap);
                // table->setPos(currentX + col * spaceX, currentY);
                // tables.append(table);
                // scene->addItem(table);

                Table* table = new Table(currentX + col * spaceX, currentY, 10);
                createTable(table, scene, false, tableSize, tableType);

                // Debug : Display position
                qDebug() << "Table (" << tableType << ") Position: ("
                         << (currentX + col * spaceX) << "," << currentY << ")";
            }
        }
        currentY += spaceY; // Avancer à la prochaine rangée
    }

    // Add the scene to include all objects
    scene->setSceneRect(scene->itemsBoundingRect());
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
    createThings(humanList.front(), scene);

    ClientModel* newClient = new ClientModel(150.0, 150.0, "COOL", 1);
    createThings(newClient, scene);
}

/**
 * @brief A function to create an graphic
 * instance for all displayable type of object instead of human
 * objects and more
 * @param human, scene
 */
void View::createThings(Human* human, QGraphicsScene *scene){
    QGraphicElement* element = new QGraphicElement(human);
    scene->addItem(element->getRepresentation());

    element->move(QPointF(200, 200));
}
/**
 * @brief A function to create en graphic instance of an table
 * @param table The table instance
 * @param scene The scene to add the graphic element
 * @param hasPicture To say if the graphic element has a picture
 * @param tableSize To set the size of the graphic element
 * @param tableType to set the type of the graphic element
 */
void View::createTable(Table* table, QGraphicsScene *scene, bool hasPicture, QSize tableSize, QString tableType){
    QGraphicElement* element = new QGraphicElement(table, hasPicture, tableSize, tableType);
    tables.append(element->getTable());
    scene->addItem(element->getTable());
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