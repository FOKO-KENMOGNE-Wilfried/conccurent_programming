#include "dashboard.h"

#include <QWidget>
#include <QGroupBox>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QAbstractItemView>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QHeaderView>
#include <QTimer>

// Constructor for the Dashboard class
Dashboard::Dashboard(QWidget *parent) : QMainWindow(parent), stackedWidget(new QStackedWidget(this)) {

    // Initialisation des données avant de configurer l'interface
    initializeTables();        // Initialisation des tables avec des valeurs par défaut
    initializeEquipments();    // Initialisation des équipements avec des valeurs par défaut
    initializeStaffs();        // Initialisation du personnel avec des valeurs par défaut
    initializeIngredients();

    setupUi();

    // Configurer le timer pour lire les logs toutes les 2 secondes
    logUpdateTimer = new QTimer(this);
    //connect(logUpdateTimer, &QTimer::timeout, this, &Dashboard::readLogAndUpdate);
    logUpdateTimer->start(2000); // Démarrer le timer avec un intervalle de 2 secondes

}

// Destructor for the Dashboard class
Dashboard::~Dashboard() {
    logUpdateTimer->stop();
}

void Dashboard::setupUi() {
    // Set window title and size
    setWindowTitle("Dashboard");
    resize(1200, 800);

    // Global style for the application
    setStyleSheet(R"(
        QMainWindow {
            background-color: #f4f6f9;
        }
        QPushButton {
            background-color: #007BFF;
            color: white;
            font-weight: bold;
            padding: 10px 15px;
            border-radius: 5px;
            border: none;
        }
        QPushButton:hover {
            background-color: #0056b3;
        }
        QLabel {
            font-size: 18px;
            font-weight: bold;
        }
        QGroupBox {
            background-color: white;
            border: 1px solid #ddd;
            border-radius: 8px;
            padding: 10px;
        }
    )");

    // Vertical navigation layout
    QVBoxLayout *navigationLayout = new QVBoxLayout();
    QPushButton *globalViewButton = new QPushButton("Global View");
    QPushButton *kitchenViewButton = new QPushButton("Kitchen");
    QPushButton *staffViewButton = new QPushButton("Staff");
    QPushButton *ingredientsViewButton = new QPushButton("Ingredients");

    // Navigation label
    QLabel *navigationLabel = new QLabel("Navigation");
    navigationLabel->setStyleSheet("font-size: 20px; color: #333;");
    navigationLayout->addWidget(navigationLabel);
    navigationLayout->addWidget(globalViewButton);
    navigationLayout->addWidget(kitchenViewButton);
    navigationLayout->addWidget(staffViewButton);
    navigationLayout->addWidget(ingredientsViewButton);
    navigationLayout->addStretch();

    QWidget *navigationWidget = new QWidget(this);
    navigationWidget->setLayout(navigationLayout);
    navigationWidget->setFixedWidth(200);

    // Create individual pages for each section
    createGlobalView();
    createKitchenView();
    createStaffView();
    createIngredientsView();

    // Main layout combining the navigation and the stacked views
    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->addWidget(navigationWidget);
    mainLayout->addWidget(stackedWidget);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // Connect buttons to the corresponding views in the stacked widget
    connect(globalViewButton, &QPushButton::clicked, [=]() { stackedWidget->setCurrentIndex(0); });
    connect(kitchenViewButton, &QPushButton::clicked, [=]() { stackedWidget->setCurrentIndex(1); });
    connect(staffViewButton, &QPushButton::clicked, [=]() { stackedWidget->setCurrentIndex(2); });
    connect(ingredientsViewButton, &QPushButton::clicked, [=]() { stackedWidget->setCurrentIndex(3); });

}

void Dashboard::initializeTables() {
    // Initialisation des tables avec des valeurs par défaut
    for (int i = 1; i <= 32; ++i) {
        TableInfo table;
        table.tableNumber = "Table " + QString::number(i); // Corrigé ici
        table.status = "Not Occupied";   // Valeur par défaut
        table.clientCount = 0;    // Valeur par défaut
        tables.append(table);
    }
}

void Dashboard::initializeEquipments() {
    // Initialisation des équipements avec des valeurs par défaut
    QStringList equipmentNames = {
        "Cooking Burners", "Pots", "Pans", "Oven", "Wooden Spoons",
        "Blender", "Salad Bowls", "Pressure Cooker", "Juicer", "Sieve",
        "Funnels", "Kitchen Knives", "Work Fridge", "Dishwasher", "Washing Machine", "Sink"
    };

    // Nombre d'équipements par type (exemple)
    QList<int> totalEquipments = {5, 10, 10, 1, 10, 1, 5, 2, 1, 1, 1, 5, 1, 1, 1, 1};

    // Vérifier que la taille des listes totalEquipments et equipmentNames est la même
    if (equipmentNames.size() != totalEquipments.size()) {
        qWarning() << "Mismatch between number of equipment names and total equipment count!";
        return;
    }

    for (int i = 0; i < equipmentNames.size(); ++i) {
        EquipmentInfo equipment;
        equipment.name = equipmentNames[i];
        equipment.status = "Available"; // Valeur par défaut
        equipment.total = totalEquipments[i]; // Initialiser le nombre total d'équipements
        equipment.used = 0; // Initialiser à 0 équipements utilisés
        equipment.unused = equipment.total; // Tous les équipements sont non utilisés au début
        equipments.append(equipment);
    }
}

void Dashboard::initializeStaffs() {
    // Initialisation du staff avec des valeurs par défaut
    QStringList staffNames = {"Head waiter", "Casseroles", "Waiter1", "Waiter2", "Room Attendant1", "Room Attendant2", "Head Chef", "Cook1", "Cook2", "Kitchen Assistant1", "Kitchen Assistant2", "Dishwasher"};
    for (const QString &name : staffNames) {
        StaffInfo staff;
        staff.name = name;
        staff.status = "Not active";  // Valeur par défaut
        staffs.append(staff);
    }
}

void Dashboard::initializeIngredients() {
    QStringList ingredientNames = {"Tomatoes", "Onions", "Chili", "Salt", "Pepper", "Oil"};
    QList<int> stockLevels = {100, 80, 50, 100, 70, 90};

    for (int i = 0; i < ingredientNames.size(); ++i) {
        IngredientInfo ingredient;
        ingredient.name = ingredientNames[i];
        ingredient.stockLevel = stockLevels[i];
        ingredients.append(ingredient);
    }
}

void Dashboard::createGlobalView() {
    // Create a new QWidget for the global view
    QWidget *globalTab = new QWidget();
    QGridLayout *layout = new QGridLayout(globalTab);

    // Section for the global summary
    QGroupBox *summaryBox = new QGroupBox("Global Summary");
    QVBoxLayout *summaryLayout = new QVBoxLayout(summaryBox);

    // Create labels for each line
    QLabel *occupiedTablesLabel = new QLabel("Occupied Tables: <b>12/20</b>");
    QLabel *numberOfClientsLabel = new QLabel("Number of Clients: <b>45</b>");

    // Set alignment and word-wrap for all labels
    occupiedTablesLabel->setAlignment(Qt::AlignLeft);
    occupiedTablesLabel->setWordWrap(true);

    numberOfClientsLabel->setAlignment(Qt::AlignLeft);
    numberOfClientsLabel->setWordWrap(true);

    // Add labels to the vertical layout
    summaryLayout->addWidget(occupiedTablesLabel);
    summaryLayout->addWidget(numberOfClientsLabel);



    // Increase the minimum height of the summary box
    summaryBox->setMinimumHeight(200); // Adjust this value as needed
    summaryBox->setMinimumWidth(400);
    layout->addWidget(summaryBox, 0, 0); // Place the summary box in the top-left

    // Section for table details
    QGroupBox *tableBox = new QGroupBox("Table Details");
    QVBoxLayout *tableLayout = new QVBoxLayout(tableBox);

    QTableWidget *table = new QTableWidget(tables.size(), 3, globalTab);
    table->setHorizontalHeaderLabels({"Table Number", "Status", "Client Count"});

    for (int i = 0; i < tables.size(); ++i) {
        table->setItem(i, 0, new QTableWidgetItem(tables[i].tableNumber));
        table->setItem(i, 1, new QTableWidgetItem(tables[i].status));
        table->setItem(i, 2, new QTableWidgetItem(QString::number(tables[i].clientCount)));
    }
    tableLayout->addWidget(table);
    layout->addWidget(tableBox, 0, 1); // Place the table box in the top-right

    stackedWidget->addWidget(globalTab);
}


void Dashboard::createKitchenView() {
    // Créer le widget de vue de la cuisine
    QWidget *kitchenTab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(kitchenTab);

    QLabel *title = new QLabel("Kitchen - Equipment Status");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 20px; color: #28a745;");
    layout->addWidget(title);

    // Group box pour la liste des équipements
    QGroupBox *equipmentBox = new QGroupBox("Equipment List");
    QGridLayout *gridLayout = new QGridLayout(equipmentBox);

    // Affichage de l'état des équipements à partir de la liste "equipments"
    for (int i = 0; i < equipments.size(); ++i) {
        QLabel *equipmentLabel = new QLabel(equipments[i].name);
        QLabel *statusLabel = new QLabel(equipments[i].status);

        QString color = (equipments[i].status == "Available") ? "green" : "red";
        statusLabel->setStyleSheet(QString("color: white; background-color: %1; padding: 5px 10px; border-radius: 5px;").arg(color));

        // Affichage des informations "Total", "Used", "Unused"
        QLabel *totalLabel = new QLabel(QString("Total: %1").arg(equipments[i].total));
        QLabel *usedLabel = new QLabel(QString("Used: %1").arg(equipments[i].used));
        QLabel *unusedLabel = new QLabel(QString("Unused: %1").arg(equipments[i].unused));

        // Ajouter les widgets dans le layout
        gridLayout->addWidget(equipmentLabel, i, 0);
        gridLayout->addWidget(statusLabel, i, 1);
        gridLayout->addWidget(totalLabel, i, 2);
        gridLayout->addWidget(usedLabel, i, 3);
        gridLayout->addWidget(unusedLabel, i, 4);
    }

    layout->addWidget(equipmentBox);

    stackedWidget->addWidget(kitchenTab);
}


void Dashboard::createStaffView() {
    // Créer le widget de vue du personnel
    QWidget *staffTab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(staffTab);

    QLabel *title = new QLabel("Staff - Status Tracking");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 20px; color: #ffc107;");
    layout->addWidget(title);

    // Group box pour l'état des employés
    QGroupBox *statusBox = new QGroupBox("Employee Status");
    QGridLayout *statusLayout = new QGridLayout(statusBox);

    // Affichage dynamique de l'état du personnel à partir de la liste "staffs"
    for (int i = 0; i < staffs.size(); ++i) {
        QLabel *nameLabel = new QLabel(staffs[i].name);
        QLabel *statusLabel = new QLabel(staffs[i].status);

        QString color = (staffs[i].status == "Active") ? "green" : "red";
        statusLabel->setStyleSheet(QString("color: white; background-color: %1; padding: 5px 10px; border-radius: 5px;").arg(color));

        statusLayout->addWidget(nameLabel, i, 0);
        statusLayout->addWidget(statusLabel, i, 1);
    }

    layout->addWidget(statusBox);

    stackedWidget->addWidget(staffTab);
}
void Dashboard::createIngredientsView() {
    // Créer le widget de vue des ingrédients
    QWidget *ingredientsTab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(ingredientsTab);

    QLabel *title = new QLabel("Ingredients - Stock Management");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 20px; color: #e83e8c;");
    layout->addWidget(title);

    // Group box pour l'état du stock
    QGroupBox *stockBox = new QGroupBox("Stock Status");
    QGridLayout *gridLayout = new QGridLayout(stockBox);

    // Affichage dynamique des ingrédients et de leurs niveaux de stock
    for (int i = 0; i < ingredients.size(); ++i) {
        QLabel *ingredientLabel = new QLabel(ingredients[i].name);
        QProgressBar *stockBar = new QProgressBar();
        stockBar->setValue(ingredients[i].stockLevel);
        stockBar->setStyleSheet("height: 15px;");

        gridLayout->addWidget(ingredientLabel, i, 0);
        gridLayout->addWidget(stockBar, i, 1);
    }

    layout->addWidget(stockBox);
    stackedWidget->addWidget(ingredientsTab);
}
