#include "view.h"
#include <QFile>
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
#include "../controller/classDeclaration/TimerController.h"

View::View(QWidget *parent, std::list<Human*> humanList, TimerController* controller)
    : QMainWindow(parent), dashboardWindow(nullptr), controller(controller) {
    this->humanList = humanList;

    qDebug() << "Starting View setup...";
    setupUi();
    qDebug() << "UI setup complete. Setting up reception area...";
    setupReceptionArea();
    qDebug() << "Reception area setup complete.";

    dashboardWindow = new Dashboard(this); // Initialize dashboard window

    // Connect buttons and signals
    connect(dashboardButton, &QPushButton::clicked, this, &View::openDashboard);
    connect(controller->getTimer(), &QTimer::timeout, this, &View::updateTime);
    connect(startButton, &QPushButton::clicked, controller, &TimerController::startTimer);
    connect(pauseButton, &QPushButton::clicked, controller, &TimerController::stopTimer);

    qDebug() << "View setup completed successfully.";
}

void View::setupUi() {
    setWindowTitle("Restaurant");
    centralWidget = new QWidget(this);
    mainLayout = new QVBoxLayout(centralWidget);

    // Top layout for the button
    QHBoxLayout *topLayout = new QHBoxLayout();

    // Start button with icon
    startButton = new QPushButton();
    startButton->setIcon(QIcon(":/assets/start.png"));
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

    // Add buttons
    topLayout->addWidget(startButton);
    topLayout->addWidget(pauseButton);
    topLayout->addWidget(speedButton);
    topLayout->addWidget(normalSpeedButton);
    topLayout->addWidget(dashboardButton);

    // Beautiful timer (QLCDNumber)
    timerDisplay = new QLCDNumber();
    timerDisplay->setDigitCount(8); // Format: hh:mm:ss
    timerDisplay->setSegmentStyle(QLCDNumber::Flat);
    timerDisplay->display("00:00:00");

    topLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    topLayout->addWidget(timerDisplay);

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
    clientLCD->setDigitCount(3);
    clientLCD->setSegmentStyle(QLCDNumber::Flat);
    clientLCD->display(0);

    // Add the label and the LCDNumber at the layout
    clientLayout->addWidget(clientLabel);
    clientLayout->addWidget(clientLCD);
    bottomLayout->addLayout(clientLayout);

    // Combined table
    QVBoxLayout *combinedLayout = new QVBoxLayout();
    QLabel *combinedLabel = new QLabel("Report");
    QTableWidget *combinedTable = new QTableWidget(6, 3);
    combinedTable->setHorizontalHeaderLabels(QStringList() << "Plates Served" << "Menu" << "Ingredients");

    // Fill the columns with existing data
    combinedTable->setItem(0, 0, new QTableWidgetItem("Koki"));
    combinedTable->setItem(1, 0, new QTableWidgetItem("Eru"));
    combinedTable->setItem(0, 1, new QTableWidgetItem("Koki"));
    combinedTable->setItem(1, 1, new QTableWidgetItem("Eru"));
    combinedTable->setItem(2, 1, new QTableWidgetItem("Tomatoes"));
    combinedTable->setItem(0, 2, new QTableWidgetItem("Tomatoes"));
    combinedTable->setItem(1, 2, new QTableWidgetItem("Cabbages"));

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

// Slot: Update time
void View::updateTime() {
    timerDisplay->display(controller->getCurrentTime().toString("hh:mm:ss"));
}


/**
 * @brief The function to display the differents elements of the restaurant
 */
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
    int counterWidth = 100;  // Width of the counter
    int counterHeight = 50;  // Height of the counter
    int sceneWidth = 550;    // Fixed width of the scene
    int sceneHeight = 570;   // Fixed height of the scene
    int counterY = 80;       // Common vertical position for both counters
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
    // person->setBrush(Qt::red);
    // person->setPos(0, 0);
    // scene->addItem(person);

    //targetPosition = QPointF(300, 200);
    //createThings(humanList.front(), scene);

    ClientModel* Client1 = new ClientModel(150.0, 150.0, "COOL", 1);
    ClientModel* Client2 = new ClientModel(200.0, 200.0, "COOL", 2);
    ClientModel* butler = new ClientModel(100.0, 100.0, "COOL", 3);
    createThings(Client1, scene, Qt::red);
    createThings(Client2, scene, Qt::red);
    createThings(butler, scene, Qt::green);
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

    //element->move(QPointF(500, 210));
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
    tables.append(element->getObject());
    scene->addItem(element->getObject());
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
