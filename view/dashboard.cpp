#include "../view/dashboard.h"
#include "../model/classDeclaration/DashboardModel.h"
#include "../controller/classDeclaration/DashboardController.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QGroupBox>
#include <QTableWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QFile>
#include <QTimer>
#include <QTextStream>
#include <QProgressBar>

Dashboard::Dashboard(QWidget *parent) : QMainWindow(parent), stackedWidget(new QStackedWidget(this)) {
    controller = new DashboardController(this);
    model = new DashboardModel();

    model->initializeTables();  // Ensure this is called to initialize equipment data
    model->initializeEquipments();  // Ensure this is called to initialize equipment data
    model->initializeStaffs();  // Ensure this is called to initialize equipment data
    model->initializeIngredients();  // Ensure this is called to initialize equipment data

    setupUi();

    logUpdateTimer = new QTimer(this);
    connect(logUpdateTimer, &QTimer::timeout, this, &Dashboard::readLogAndUpdate);
    logUpdateTimer->start(2000);
}

Dashboard::~Dashboard() {
    logUpdateTimer->stop();
    delete controller;
    delete model;
}

DashboardModel *Dashboard::getModel() const {
    return model;
}

void Dashboard::setupUi() {
    setWindowTitle("Dashboard");
    resize(1200, 800);

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

    QVBoxLayout *navigationLayout = new QVBoxLayout();
    QPushButton *globalViewButton = new QPushButton("Global View");
    QPushButton *kitchenViewButton = new QPushButton("Kitchen");
    QPushButton *staffViewButton = new QPushButton("Staff");
    QPushButton *ingredientsViewButton = new QPushButton("Ingredients");

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

    createGlobalView();
    createKitchenView();
    createStaffView();
    createIngredientsView();

    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->addWidget(navigationWidget);
    mainLayout->addWidget(stackedWidget);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    connect(globalViewButton, &QPushButton::clicked, [=]() { stackedWidget->setCurrentIndex(0); });
    connect(kitchenViewButton, &QPushButton::clicked, [=]() { stackedWidget->setCurrentIndex(1); });
    connect(staffViewButton, &QPushButton::clicked, [=]() { stackedWidget->setCurrentIndex(2); });
    connect(ingredientsViewButton, &QPushButton::clicked, [=]() { stackedWidget->setCurrentIndex(3); });
}

void Dashboard::createGlobalView() {
    // Implementation remains the same for global view

    QList<TableInfo> tables = model->getTable();

    QWidget *globalTab = new QWidget();
    QGridLayout *layout = new QGridLayout(globalTab);

    // Section for the global summary
    QGroupBox *summaryBox = new QGroupBox("Global Summary");
    QVBoxLayout *summaryLayout = new QVBoxLayout(summaryBox);

    // Section for table details
    QGroupBox *tableBox = new QGroupBox("Table Details");
    QVBoxLayout *tableLayout = new QVBoxLayout(tableBox);

    globalTable = new QTableWidget(tables.size(), 3, globalTab); // Ensure globalTable is properly assigned
    globalTable->setHorizontalHeaderLabels({"Table Number", "Status", "Client Count"});

    for (int i = 0; i < tables.size(); ++i) {
        globalTable->setItem(i, 0, new QTableWidgetItem(tables[i].tableNumber));
        globalTable->setItem(i, 1, new QTableWidgetItem(tables[i].status));
        globalTable->setItem(i, 2, new QTableWidgetItem(QString::number(tables[i].clientCount)));
    }
    tableLayout->addWidget(globalTable);
    layout->addWidget(tableBox, 0, 1); // Place the table box in the top-right

    stackedWidget->addWidget(globalTab);
}

void Dashboard::createKitchenView() {
    QList<EquipmentInfo> equipments = model->getEquipments();

    QWidget *kitchenTab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(kitchenTab);

    QLabel *title = new QLabel("Kitchen - Equipment Status");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 20px; color: #28a745;");
    layout->addWidget(title);

    QGroupBox *equipmentBox = new QGroupBox("Equipment List");
    QGridLayout *gridLayout = new QGridLayout(equipmentBox);

    equipmentLabelsMap.clear();

    for (int i = 0; i < equipments.size(); ++i) {
        QLabel *equipmentLabel = new QLabel(equipments[i].name);
        QLabel *statusLabel = new QLabel(equipments[i].status);

        QString color = (equipments[i].status == "Available") ? "green" : "red";
        statusLabel->setStyleSheet(
            QString("color: white; background-color: %1; padding: 5px 10px; border-radius: 5px;").arg(color));

        QLabel *totalLabel = new QLabel(QString("Total: %1").arg(equipments[i].total));
        QLabel *usedLabel = new QLabel(QString("Used: %1").arg(equipments[i].used));
        QLabel *unusedLabel = new QLabel(QString("Unused: %1").arg(equipments[i].unused));

        equipmentLabelsMap[equipments[i].name] = {statusLabel, usedLabel, unusedLabel};

        gridLayout->addWidget(equipmentLabel, i, 0);
        gridLayout->addWidget(statusLabel, i, 1);
        gridLayout->addWidget(totalLabel, i, 2);
        gridLayout->addWidget(usedLabel, i, 3);
        gridLayout->addWidget(unusedLabel, i, 4);
    }

    layout->addWidget(equipmentBox);
    stackedWidget->addWidget(kitchenTab);
    stackedWidget->setCurrentWidget(kitchenTab);
}

void Dashboard::createStaffView() {
    // Implementation remains the same for staff view
    QList<StaffInfo> staffs = model->getStaff();

    QWidget *staffTab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(staffTab);

    QLabel *title = new QLabel("Staff - Status Tracking");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 20px; color: #ffc107;");
    layout->addWidget(title);

    // Group box pour l'état des employés
    QGroupBox *statusBox = new QGroupBox("Employee Status");
    QGridLayout *statusLayout = new QGridLayout(statusBox);

    // Map to store QLabel pointers for easy updating
    staffLabelsMap.clear();

    // Affichage dynamique de l'état du personnel à partir de la liste "staffs"
    for (int i = 0; i < staffs.size(); ++i) {
        QLabel *nameLabel = new QLabel(staffs[i].name);
        QLabel *statusLabel = new QLabel(staffs[i].status);

        QString color = (staffs[i].status == "Active") ? "green" : "red";
        statusLabel->setStyleSheet(QString("color: white; background-color: %1; padding: 5px 10px; border-radius: 5px;").arg(color));

        // Store labels in the map for easy updating
        staffLabelsMap[staffs[i].name] = statusLabel;

        statusLayout->addWidget(nameLabel, i, 0);
        statusLayout->addWidget(statusLabel, i, 1);
    }

    layout->addWidget(statusBox);
    stackedWidget->addWidget(staffTab);
}

void Dashboard::createIngredientsView() {

    QList<IngredientInfo> ingredients = model->getIngredient();

    QWidget *ingredientsTab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(ingredientsTab);

    QLabel *title = new QLabel("Ingredients - Stock Management");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 20px; color: #e83e8c;");
    layout->addWidget(title);

    // Group box pour l'état du stock
    QGroupBox *stockBox = new QGroupBox("Stock Status");
    QGridLayout *gridLayout = new QGridLayout(stockBox);

    // Create a map to store QProgressBar pointers for easy updating
    ingredientBarsMap.clear();

    // Affichage dynamique des ingrédients et de leurs niveaux de stock
    for (int i = 0; i < ingredients.size(); ++i) {
        QLabel *ingredientLabel = new QLabel(ingredients[i].name);
        QProgressBar *stockBar = new QProgressBar();
        stockBar->setValue(ingredients[i].stockLevel);
        stockBar->setStyleSheet("height: 15px;");

        // Store progress bars in the map for easy updating
        ingredientBarsMap[ingredients[i].name] = stockBar;

        gridLayout->addWidget(ingredientLabel, i, 0);
        gridLayout->addWidget(stockBar, i, 1);
    }

    layout->addWidget(stockBox);
    stackedWidget->addWidget(ingredientsTab);
}

void Dashboard::readLogAndUpdate() {
    QFile file(":/restaurant.log");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Erreur d'ouverture du fichier log";
        return;
    }

    QTextStream in(&file);
    QString line;

    while (!in.atEnd()) {
        line = in.readLine();

        // Mise à jour des tables
        QList<TableInfo> tables = model->getTable();
        if (line.startsWith("Table")) {
            QStringList parts = line.split(": ");
            if (parts.size() < 2) continue;  // Ensure parts have the expected size

            QString tableStr = parts[0].trimmed(); // "Table 2"
            QString statusAndClients = parts[1].trimmed(); // "Available, 0 clients"

            QStringList statusAndClientsParts = statusAndClients.split(", ");
            if (statusAndClientsParts.size() < 2) continue;  // Ensure parts have the expected size

            QString status = statusAndClientsParts[0].trimmed(); // "Available"
            int clientCount = statusAndClientsParts[1].split(' ')[0].toInt(); // "0"

            qDebug() << "Updating" << tableStr << "with status:" << status << "and client count:" << clientCount;

            for (int i = 0; i < tables.size(); ++i) {
                if (tables[i].tableNumber == tableStr) {
                    tables[i].status = status;
                    tables[i].clientCount = clientCount;

                    // Ensure the index is valid before accessing globalTable
                    if (globalTable && i < globalTable->rowCount() && globalTable->item(i, 1) && globalTable->item(i, 2)) {
                        globalTable->item(i, 1)->setText(status);
                        globalTable->item(i, 2)->setText(QString::number(clientCount));
                    } else {
                        qWarning() << "Unable to update table item at index" << i;
                    }
                }
            }
        }

        // Mise à jour des équipements
        QList<EquipmentInfo> equipments = model->getEquipments();

        if (line.startsWith("Equipment")) {
            QStringList parts = line.split(", ");
            if (parts.size() < 4) continue;  // Ensure parts have the expected size

            QString equipmentName = parts[0].section(':', 1).trimmed(); // "Blender"
            QString status = parts[1].trimmed(); // "Available"
            int used = parts[2].split(' ')[0].toInt(); // "1"
            int unused = parts[3].split(' ')[0].toInt(); // "0"

            qDebug() << "Updating" << equipmentName << "with status:" << status << ", used:" << used << "and unused:" << unused;

            for (int i = 0; i < equipments.size(); ++i) {
                if (equipments[i].name == equipmentName) {
                    equipments[i].status = (equipments[i].total == used) ? "Unavailable" : status;
                    equipments[i].used = used;
                    equipments[i].unused = unused;

                    // Mise à jour de l'interface des équipements (kitchenView)
                    if (equipmentLabelsMap.contains(equipmentName)) {
                        auto labels = equipmentLabelsMap[equipmentName];
                        QLabel *statusLabel = labels[0];
                        QLabel *usedLabel = labels[1];
                        QLabel *unusedLabel = labels[2];

                        statusLabel->setText(equipments[i].status);
                        usedLabel->setText(QString("Used: %1").arg(used));
                        unusedLabel->setText(QString("Unused: %1").arg(unused));

                        QString color = (equipments[i].status == "Available") ? "green" : "red";
                        statusLabel->setStyleSheet(QString("color: white; background-color: %1; padding: 5px 10px; border-radius: 5px;").arg(color));
                    } else {
                        qWarning() << "Unable to find labels for equipment:" << equipmentName;
                    }
                }
            }
        }

        // Mise à jour du personnel
        QList<StaffInfo> staffs = model->getStaff();
        if (line.startsWith("Staff")) {
            QStringList parts = line.split(": ");
            if (parts.size() < 2) continue;  // Ensure parts have the expected size

            QString staffName = parts[1].section(',', 0, 0).trimmed(); // "Head waiter"
            QString status = parts[1].section(',', 1, 1).trimmed(); // "Active"

            qDebug() << "Updating" << staffName << "with status:" << status;

            for (int i = 0; i < staffs.size(); ++i) {
                if (staffs[i].name == staffName) {
                    staffs[i].status = status;

                    // Mise à jour de l'interface du personnel (staffView)
                    if (staffLabelsMap.contains(staffName)) {
                        QLabel *statusLabel = staffLabelsMap[staffName];
                        statusLabel->setText(status);

                        QString color = (status == "Active") ? "green" : "red";
                        statusLabel->setStyleSheet(QString("color: white; background-color: %1; padding: 5px 10px; border-radius: 5px;").arg(color));
                    } else {
                        qWarning() << "Unable to find labels for staff:" << staffName;
                    }
                }
            }
        }

        // Mise à jour des ingrédients
        QList<IngredientInfo> ingredients = model->getIngredient();
        if (line.startsWith("Stock")) {
            QRegularExpression regex(R"(Stock\s+([\w\s]+):\s*(\d+)%?)");
            QRegularExpressionMatch match = regex.match(line);

            if (match.hasMatch()) {
                QString ingredientName = match.captured(1).trimmed(); // Nom de l'ingrédient
                int stockLevel = match.captured(2).toInt(); // Niveau de stock

                qDebug() << "Updating stock for" << ingredientName << "to" << stockLevel;

                // Mise à jour des données
                for (int i = 0; i < ingredients.size(); ++i) {
                    if (ingredients[i].name == ingredientName) {
                        ingredients[i].stockLevel = stockLevel;

                        // Mise à jour de l'interface
                        if (ingredientBarsMap.contains(ingredientName)) {
                            QProgressBar *stockBar = ingredientBarsMap[ingredientName];
                            stockBar->setValue(stockLevel);

                            if (stockLevel <= 20) {
                                stockBar->setStyleSheet("QProgressBar { height: 15px; background-color: red; }");
                            } else {
                                stockBar->setStyleSheet("QProgressBar { height: 15px; }");
                            }
                        } else {
                            qWarning() << "Unable to find progress bar for ingredient:" << ingredientName;
                        }
                    }
                }
            }
        }
        file.close();
    }
}
