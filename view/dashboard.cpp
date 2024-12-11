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

// Constructor for the Dashboard class
Dashboard::Dashboard(QWidget *parent) : QMainWindow(parent), stackedWidget(new QStackedWidget(this)) {
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

// Destructor for the Dashboard class
Dashboard::~Dashboard() {}

void Dashboard::createGlobalView() {
    // Create a new QWidget for the global view
    QWidget *globalTab = new QWidget();
    QGridLayout *layout = new QGridLayout(globalTab);

    // Section for the global summary
    QGroupBox *summaryBox = new QGroupBox("Global Summary");
    QVBoxLayout *summaryLayout = new QVBoxLayout(summaryBox);
    summaryLayout->addWidget(new QLabel("Occupied Tables: <b>12/20</b>"));
    summaryLayout->addWidget(new QLabel("Number of Clients: <b>45</b>"));
    summaryLayout->addWidget(new QLabel("Total Revenue: <b>1500€</b>"));
    summaryLayout->addWidget(new QLabel("Average Time per Table: <b>45 min</b>"));

    // Set the minimum width of the summary box
    summaryBox->setMinimumWidth(400);

    layout->addWidget(summaryBox, 0, 0);

    // Section for table details
    QGroupBox *tableBox = new QGroupBox("Table Details");
    QVBoxLayout *tableLayout = new QVBoxLayout(tableBox);

    // Create a table with 5 rows and 3 columns
    QTableWidget *table = new QTableWidget(5, 3, globalTab);
    table->setHorizontalHeaderLabels({"Table", "Availability", "Clients"});
    table->setStyleSheet(
        "border: 1px solid #ccc; background-color: white; "
        "gridline-color: #ddd; alternating-row-color: #f9f9f9;");
    table->setAlternatingRowColors(true);

    // Set the width of the columns and rows to make the table more readable
    tableBox->setMinimumWidth(500); // Increase the width of the table
    table->setColumnWidth(0, 150);  // Increase the width of the first column (Table)
    table->setColumnWidth(1, 150);  // Increase the width of the second column (Availability)
    table->setColumnWidth(2, 150);  // Increase the width of the third column (Clients)

    // Increase the row height for better visibility
    table->setRowHeight(0, 40);
    table->setRowHeight(1, 40);
    table->setRowHeight(2, 40);
    table->setRowHeight(3, 40);
    table->setRowHeight(4, 40);

    // Make sure columns are resized to fit the content
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    tableLayout->addWidget(table);
    layout->addWidget(tableBox, 0, 1);

    stackedWidget->addWidget(globalTab);
}

void Dashboard::createKitchenView() {
    // Create the kitchen view widget
    QWidget *kitchenTab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(kitchenTab);

    QLabel *title = new QLabel("Kitchen - Equipment Status");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 20px; color: #28a745;");
    layout->addWidget(title);

    // Group box for equipment status
    QGroupBox *equipmentBox = new QGroupBox("Equipment List");
    QGridLayout *gridLayout = new QGridLayout(equipmentBox);

    QStringList equipment = {"Oven", "Fridge", "Blender", "Hot Plate", "Freezer", "Dishwasher"};
    QStringList statuses = {"OK", "OK", "Maintenance", "OK", "Maintenance", "OK"};

    // Display equipment status with different colors for "OK" and "Maintenance"
    for (int i = 0; i < equipment.size(); ++i) {
        QLabel *equipmentLabel = new QLabel(equipment[i]);
        QLabel *statusLabel = new QLabel(statuses[i]);

        QString color = (statuses[i] == "OK") ? "green" : "red";
        statusLabel->setStyleSheet(QString("color: white; background-color: %1; padding: 5px 10px; border-radius: 5px;").arg(color));

        gridLayout->addWidget(equipmentLabel, i, 0);
        gridLayout->addWidget(statusLabel, i, 1);
    }

    layout->addWidget(equipmentBox);

    stackedWidget->addWidget(kitchenTab);
}

void Dashboard::createStaffView() {
    // Create staff view widget
    QWidget *staffTab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(staffTab);

    QLabel *title = new QLabel("Staff - Status Tracking");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 20px; color: #ffc107;");
    layout->addWidget(title);

    // Group box for employee status
    QGroupBox *statusBox = new QGroupBox("Employee Status");
    QGridLayout *statusLayout = new QGridLayout(statusBox);

    QStringList employees = {"Chef", "Waiter 1", "Waiter 2", "Dishwasher"};
    QStringList statuses = {"Active", "Inactive", "Active", "Active"};

    // Display employee status with colors for "Active" and "Inactive"
    for (int i = 0; i < employees.size(); ++i) {
        QLabel *label = new QLabel(employees[i]);
        QLabel *statusLabel = new QLabel(statuses[i]);

        QString color = (statuses[i] == "Active") ? "green" : "red";
        statusLabel->setStyleSheet(QString("color: white; background-color: %1; padding: 5px 10px; border-radius: 5px;").arg(color));

        statusLayout->addWidget(label, i, 0);
        statusLayout->addWidget(statusLabel, i, 1);
    }

    layout->addWidget(statusBox);

    stackedWidget->addWidget(staffTab);
}

void Dashboard::createIngredientsView() {
    // Create the ingredients view widget
    QWidget *ingredientsTab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(ingredientsTab);

    QLabel *title = new QLabel("Ingredients - Stock Management");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 20px; color: #e83e8c;");
    layout->addWidget(title);

    // Group box for stock status
    QGroupBox *stockBox = new QGroupBox("Stock Status");
    QGridLayout *gridLayout = new QGridLayout(stockBox);

    QStringList ingredients = {"Tomatoes", "Onions", "Chili", "Salt", "Pepper", "Oil"};
    QList<int> stockLevels = {90, 70, 30, 100, 50, 80};

    // Display ingredient stock levels with progress bars
    for (int i = 0; i < ingredients.size(); ++i) {
        QLabel *ingredientLabel = new QLabel(ingredients[i]);
        QProgressBar *stockBar = new QProgressBar();
        stockBar->setValue(stockLevels[i]);
        stockBar->setStyleSheet("height: 15px;");
        gridLayout->addWidget(ingredientLabel, i, 0);
        gridLayout->addWidget(stockBar, i, 1);
    }

    layout->addWidget(stockBox);
    stackedWidget->addWidget(ingredientsTab);
}
