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
#include "../model/classDeclaration/Butler.h"
#include "../model/classDeclaration/HeadWaiter.h"
#include "../model/graphicElement/classDeclaration/QGraphicElement.h"

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


    // Combined table
    QVBoxLayout *combinedLayout = new QVBoxLayout();
    QLabel *combinedLabel = new QLabel("Report");
    QTableWidget *combinedTable = new QTableWidget(6, 3); // 6 rows (2 + 3 + 2) and 3 columns
    combinedTable->setHorizontalHeaderLabels(QStringList() << "Plates Served" << "Menu" << "Ingredients");

    // Fill the columns with existing data

    // "Plates Served" column
    combinedTable->setItem(0, 0, new QTableWidgetItem("Koki"));
    combinedTable->setItem(1, 0, new QTableWidgetItem("Eru"));

    // "Menu" column
    combinedTable->setItem(0, 1, new QTableWidgetItem("Koki"));
    combinedTable->setItem(1, 1, new QTableWidgetItem("Eru"));
    combinedTable->setItem(2, 1, new QTableWidgetItem("Tomatoes"));

    // "Ingredients" column
    combinedTable->setItem(0, 2, new QTableWidgetItem("Tomatoes"));
    combinedTable->setItem(1, 2, new QTableWidgetItem("Cabbages"));

    // Adjust layout
    combinedLayout->addWidget(combinedLabel);
    combinedLayout->addWidget(combinedTable);
    bottomLayout->addLayout(combinedLayout);

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

/**
 * @brief The function to display the differents elements of the restaurant
 */
void View::setupReceptionArea() {
    setupCounter();
    setupPerson();
    tableObject.add_tables();
    setupTables();
}

void View::setupCounter() {
    int counterWidth = 100;  // Width of the counter
    int counterHeight = 50;  // Height of the counter
    int sceneWidth = 550;    // Fixed width of the scene
    int sceneHeight = 570;   // Fixed height of the scene
    int counterY = 100;       // Common vertical position for both counters
    int spacingX = 150;      // Horizontal spacing between the counters

    // X positions for each counter (separated to create a realistic layout)
    int leftCounterX = 60;    // X position for the cash counter
    int rightCounterX = 1370; // X position for the serving counter

    // Load the images for the counters
    QPixmap counterPixmapLeft(":/assets/comptoir.png");  // Replace with your cash counter image
    QPixmap counterPixmapRight(":/assets/cuisine.png");  // Replace with your serving counter image

    // Resize the images to match the counter dimensions
    QPixmap counterScaledLeft = counterPixmapLeft.scaled(counterWidth, counterHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QPixmap counterScaledRight = counterPixmapRight.scaled(counterWidth, counterHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // Left counter (for the cash register)
    QGraphicsPixmapItem *counterLeft = new QGraphicsPixmapItem(counterScaledLeft);
    counterLeft->setPos(leftCounterX, counterY); // Position of the cash counter
    scene->addItem(counterLeft);
    qDebug() << "Left counter (Cash Register) added at coordinates (" << leftCounterX << "," << counterY << ")";

    // Right counter (for serving dishes)
    QGraphicsPixmapItem *counterRight = new QGraphicsPixmapItem(counterScaledRight);
    counterRight->setPos(rightCounterX, counterY); // Position of the serving counter
    scene->addItem(counterRight);
    qDebug() << "Right counter (Serving Area) added at coordinates (" << rightCounterX << "," << counterY << ")";

    // Adjust the scene to include all objects without overflow
    scene->setSceneRect(0, 0, sceneWidth, sceneHeight); // Fixed dimensions for the scene
}

void View::setupTables() {
    // Space and size
    int startX = 60;
    int startY = 200;
    int spaceX = 100;
    int spaceY = 150;
    int squareOffsetX = 800;
    QSize tableSize(90, 90);
    int tableIndex = 0;
    vector<TableStruct> tableList = tableObject.getTables();

    // Table organization in 2 squares
    for (int square = 0; square < 2; ++square) {
        int currentX = startX + square * squareOffsetX; // Décalage horizontal pour le carré
        int currentY = startY;

        for (int row = 0; row < 2; ++row) {
            for (int col = 0; col < 6; col++) {
                TableStruct& table = tableList[tableIndex++];
                table.x = currentX + col * spaceX;
                table.y = currentY;
                table.squareId = square + 1;
                createTable(table.x, table.y, table.capacity, scene, true, tableSize, table.path);

                // Debug : Display position
                qDebug() << "Table (" << table.path << ") Position: ("
                        << (currentX + col * spaceX) << "," << currentY << ")";
            }
            currentY += spaceY; // Go to the next column
        }

        currentX = startX + square * squareOffsetX + spaceX; // Décalage pour centrer les 4 tables
        
        for (int col = 0; col < 4; ++col) {
            TableStruct& table = tableList[tableIndex++];
            table.x = currentX + col * spaceX;
            table.y = currentY;
            table.squareId = square;
            createTable(table.x, table.y, table.capacity, scene, true, tableSize, table.path);

            // Debug : Display position
            qDebug() << "Table (" << table.path << ") Position: ("
                    << (currentX + col * spaceX) << "," << currentY << ")";
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
    QGraphicElement* butler = new QGraphicElement(new Butler(100.0, 151.0), Qt::blue);
    scene->addItem(butler->getRepresentation());
    //element->move(QPointF(40,240));
    QGraphicElement* waiter1 = new QGraphicElement(new HeadWaiter(500.0, 151.0), Qt::black);
    scene->addItem(waiter1->getRepresentation());
    //
    QGraphicElement* waiter2 = new QGraphicElement(new HeadWaiter(1000.0, 151.0), Qt::white);
    scene->addItem(waiter2->getRepresentation());
    // TODO: IMPLEMENT THE CLIENT MODEL
}

/**
 * @brief A function to create an graphic
 * instance for all displayable type of object instead of human
 * objects and more
 * @param human, scene
 */
void View::createThings(ClientModel* human, QGraphicsScene *scene, Qt::GlobalColor color){
    QGraphicElement* element = new QGraphicElement(human, color);
    scene->addItem(element->getRepresentation());
    //element->move(QPointF(500, 500));
}
/**
 * @brief A function to create a graphic instance of an table
 * @param table The table instance
 * @param scene The scene to add the graphic element
 * @param hasPicture To say if the graphic element has a picture
 * @param tableSize To set the size of the graphic element
 * @param tableType to set the type of the graphic element
 */     
void View::createTable(double x, double y, int capacity, QGraphicsScene *scene, bool hasPicture, QSize tableSize, QString tableType){
    QGraphicElement* element = new QGraphicElement(x, y, capacity, hasPicture, tableSize, tableType);
    tables.append(element->getObject());
    scene->addItem(element->getObject());
}

/**
 * @brief The function to display all of the positions of the map's elements.
 */
void View::displayPositions() {
    qDebug() << "Position du comptoir: " << counter->pos();
    for (int i = 0; i < tables.size(); ++i) {
        qDebug() << "Position de la table " << i + 1 << ": " << tables[i]->pos();
    }
    // qDebug() << "Position du personnage: " << person->pos();
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
