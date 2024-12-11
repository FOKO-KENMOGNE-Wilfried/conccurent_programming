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
#include <QString>

Kitchen::Kitchen(QWidget *parent) : QMainWindow(parent), dashboardWindow(nullptr) {
    setupUi();

    // Call the function to configure the reception area (tables, character, etc.)
    setupKitchenArea();

    dashboardWindow = new Dashboard(this); // Initialize the dashboard window
    connect(dashboardButton, &QPushButton::clicked, this, &Kitchen::openDashboard); // Connect the button
}

/**
 * @brief The function to display the kitchen
 */
void Kitchen::setupUi() {
    setWindowTitle("Kitchen");
    centralWidget = new QWidget(this);
    mainLayout = new QVBoxLayout(centralWidget);

    // Top layout (for buttons)
    QHBoxLayout *topLayout = new QHBoxLayout();
    // Start button with an icon
    startButton = new QPushButton();
    startButton->setIcon(QIcon(":/assets/start.png")); // Replace with the path to your icon
    startButton->setIconSize(QSize(28, 28));

    // Pause button with an icon
    pauseButton = new QPushButton();
    pauseButton->setIcon(QIcon(":/assets/pause.png"));
    pauseButton->setIconSize(QSize(28, 28));

    // Speed button with an icon
    speedButton = new QPushButton();
    speedButton->setIcon(QIcon(":/assets/speed.png"));
    speedButton->setIconSize(QSize(28, 28));

    // Normal Speed button with an icon
    normalSpeedButton = new QPushButton();
    normalSpeedButton->setIcon(QIcon(":/assets/normal.png"));
    normalSpeedButton->setIconSize(QSize(28, 28));

    // Dashboard button with an icon
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

    // Add a flexible space to push the combo box to the right
    topLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    topLayout->addWidget(timeComboBox);

    mainLayout->addLayout(topLayout);

    // Set QGraphicsView instead of QFrame for the game
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

    // Create the scene
    kitchenScene = new QGraphicsScene(this);
    kitchenView->setScene(kitchenScene);
    mainLayout->addWidget(kitchenView);

    // Bottom layout
    QHBoxLayout *bottomLayout = new QHBoxLayout();

    // Client section
    QVBoxLayout *clientLayout = new QVBoxLayout();
    QLabel *clientLabel = new QLabel("Client Number");

    // Create a QLCDNumber
    clientLCD = new QLCDNumber();
    clientLCD->setDigitCount(3); // Set the number of digits displayed (3 for a maximum of 999)
    clientLCD->setSegmentStyle(QLCDNumber::Flat); // Visual style (Flat, Filled, etc.)
    clientLCD->display(0); // Initial value to display

    // Adjust layout margins to reduce space between the label and the LCD
    clientLayout->setSpacing(5); // Reduce vertical spacing to 5 pixels (adjust as needed)
    clientLayout->setContentsMargins(0, 0, 0, 0); // Reduce margins around the layout

    // Add the label and the LCDNumber to the layout
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

    // Debugging the stylesheet loading
    QFile file("C:/Users/user/Documents/Programmation concurrente/ProjetConc/conccurent_programming/view/assets/style.css");
    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(file.readAll());
        qApp->setStyleSheet(styleSheet);
        qDebug() << "Kitchen Stylesheet loaded successfully!";
    } else {
        qWarning() << "Unable to load CSS file: " << file.errorString();
    }
}

/**
 * @brief The function to display the differents elements of the kitchen
 */
void Kitchen::setupKitchenArea() {
    // Adjusted scene size to avoid scrolling
    int sceneWidth = 1200;
    int sceneHeight = 570;

    kitchenScene->setSceneRect(0, 0, sceneWidth, sceneHeight);

    // Dimensions of elements
    int elementWidth = 90;
    int elementHeight = 90;

    // Images of elements
    QList<QString> elementImages = {
        ":/assets/frigo.png",        // Fridge
        ":/assets/lave_vaisselle.png", // Dishwasher
        ":/assets/machine.png",     // Washing machine
        ":/assets/sink.png",        // Sink
        ":/assets/stove.png",       // Stove
        ":/assets/chambre_froide.png", // Cold room
        ":/assets/freezer.png",     // Freezer
        ":/assets/counter.png"      // Countertop
    };

    // --- Stoves (at the top in the middle) ---
    int stoveStartX = 450; // Starting horizontal position
    int stoveY = 5;        // Fixed vertical position
    for (int i = 0; i <= stoveNumber; ++i) {
        QPixmap pixmap(elementImages[4]); // Stove
        QPixmap scaledPixmap = pixmap.scaled(elementWidth, elementHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QGraphicsPixmapItem *stoveItem = new QGraphicsPixmapItem(scaledPixmap);
        int posX = stoveStartX + i * (elementWidth + 10);
        stoveItem->setPos(posX, stoveY); // Spacing between stoves
        kitchenScene->addItem(stoveItem);
        qDebug() << "Stove " << i + 1 << " position: (" << posX << ", " << stoveY << ")";
    }

    // --- Fridge and freezer (to the right of the stoves) ---
    int fridgeX = stoveStartX + 5 * (elementWidth + 10) + 20;
    int fridgeY = 15;
    QPixmap fridgePixmap(elementImages[0]); // Fridge
    QPixmap scaledFridge = fridgePixmap.scaled(elementWidth, elementHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QGraphicsPixmapItem *fridgeItem = new QGraphicsPixmapItem(scaledFridge);
    fridgeItem->setPos(fridgeX, fridgeY);
    kitchenScene->addItem(fridgeItem);
    qDebug() << "Fridge position: (" << fridgeX << ", " << fridgeY << ")";

    QPixmap freezerPixmap(elementImages[6]); // Freezer
    QPixmap scaledFreezer = freezerPixmap.scaled(elementWidth, elementHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QGraphicsPixmapItem *freezerItem = new QGraphicsPixmapItem(scaledFreezer);
    freezerItem->setPos(fridgeX + elementHeight + 10, fridgeY);
    kitchenScene->addItem(freezerItem);
    qDebug() << "Freezer position: (" << fridgeX + elementHeight + 10 << ", " << fridgeY << ")";

    // --- Cold room (bottom right) ---
    int coldRoomX = sceneWidth - elementWidth - 10;
    int coldRoomY = 450;
    QPixmap coldRoomPixmap(elementImages[5]); // Cold room
    QPixmap scaledColdRoom = coldRoomPixmap.scaled(elementWidth, elementHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QGraphicsPixmapItem *coldRoomItem = new QGraphicsPixmapItem(scaledColdRoom);
    coldRoomItem->setPos(coldRoomX, coldRoomY);
    kitchenScene->addItem(coldRoomItem);
    qDebug() << "Cold room position: (" << coldRoomX << ", " << coldRoomY << ")";

    // --- Counter top (top left) ---
    int prepX = -20; // Top left
    int prepY = 200;
    kitchenCounter = new KitchenCounter(readyOrder, prepX, prepY);
    createKitchenCounter(kitchenCounter, kitchenScene, true, QSize(elementWidth, elementHeight), elementImages[7]);
    qDebug() << "KitchenCounter table position: (" << prepX << ", " << prepY << ")";

    // --- Sink (in the middle) ---
    int sinkX = sceneWidth / 2 - elementWidth / 2;
    int sinkY = sceneHeight / 2 - elementHeight / 2;
    QPixmap sinkPixmap(elementImages[3]); // Sink
    QPixmap scaledSink = sinkPixmap.scaled(elementWidth, elementHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QGraphicsPixmapItem *sinkItem = new QGraphicsPixmapItem(scaledSink);
    sinkItem->setPos(sinkX, sinkY);
    kitchenScene->addItem(sinkItem);
    qDebug() << "Sink position: (" << sinkX << ", " << sinkY << ")";

    // --- Dishwasher and washing machine (bottom middle) ---
    int dishwasherX = sinkX - 100; // Dishwasher to the left of the sink
    int washerX = sinkX + 100;     // Washing machine to the right of the sink
    int applianceY = 450;

    // DishWasherModel
    dishwasherModel = new DishwasherModel(dishwasherX, applianceY);
    createKitchenDishwasherModel(dishwasherModel, kitchenScene, true, QSize(elementWidth, elementHeight), elementImages[1]);
    qDebug() << "Dishwasher position: (" << dishwasherX << ", " << applianceY << ")";

    // Initialize the WasherMachine
    washingMachine = new WashingMachine(washerX, applianceY);
    createKitchenWashinMachineModel(washingMachine, kitchenScene, true, QSize(elementWidth, elementHeight), elementImages[2]);
    qDebug() << "Washer position: (" << washerX << ", " << applianceY << ")";

    createResttaurantPersonel(kitchenScene);
}

void Kitchen::createKitchenCounter(KitchenCounter* kitchenCounter, QGraphicsScene *scene, bool hasPicture, QSize tableSize, QString tableType){
    QGraphicElement* element = new QGraphicElement(kitchenCounter, hasPicture, tableSize, tableType);
    kitchenCounterList.push_back(element);
    scene->addItem(element->getObject());
}

void Kitchen::createKitchenDirtyDishesStorage(DirtyDishesStorage* dirtyDishesStorage, QGraphicsScene *scene, bool hasPicture, QSize tableSize, QString tableType){
    QGraphicElement* element = new QGraphicElement(dirtyDishesStorage, hasPicture, tableSize, tableType);
    dirtyDishesStorageList.push_back(element);
    scene->addItem(element->getObject());
}
void Kitchen::createKitchenWashinMachineModel(WashingMachine* washingMachine, QGraphicsScene *scene, bool hasPicture, QSize tableSize, QString tableType){
    QGraphicElement* element = new QGraphicElement(washingMachine, hasPicture, tableSize, tableType);
    washingMachineList.push_back(element);
    scene->addItem(element->getObject());
}
void Kitchen::createKitchenDishwasherModel(DishwasherModel* dishwasherModel, QGraphicsScene *scene, bool hasPicture, QSize tableSize, QString tableType){
    QGraphicElement* element = new QGraphicElement(dishwasherModel, hasPicture, tableSize, tableType);
    dishwasherModelList.push_back(element);
    scene->addItem(element->getObject());
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

void Kitchen::createResttaurantPersonel(/*Human* human,*/ QGraphicsScene *scene){
    for (int i = 0; i < chiefNumber; i++) {
        QGraphicElement* element = new QGraphicElement(
            new Chief(0, 0), Qt::blue);
        scene->addItem(element->getRepresentation());
        element->move(QPointF(
            kitchenCounterList[0]->graphicObject->pos().x(),
            kitchenCounterList[0]->graphicObject->pos().y()
        ));
    }
    for (int i = 0; i < cookNumber; i++) {
        QGraphicElement* element = new QGraphicElement(new Cook(200.0, 250.0), Qt::blue);
        scene->addItem(element->getRepresentation());
        if(i == 0) {
            element->move(QPointF(250, 270));
        } else {
            element->move(QPointF(200, 220));
        }
    }
    for (int i = 0; i < cookAssistNumber; i++) {
        QGraphicElement* element = new QGraphicElement(new KitchenAssistant(200.0, 300.0, kitchenCounter), Qt::blue);
        scene->addItem(element->getRepresentation());
        if(i == 0) {
            element->move(QPointF(200, 300));
        } else {
            element->move(QPointF(200, 320));
        }
    }
    for (int i = 0; i < restaurantDiverNumber; i++) {
        QGraphicElement* element = new QGraphicElement(new RestaurantDiver(200.0, 350.0, dirtyDishesStorage, washingMachine, dishwasherModel), Qt::blue);
        scene->addItem(element->getRepresentation());
        element->move(QPointF(200, 350));
    }
}