#include "../classDeclaration/DashboardModel.h"
#include <QStringList>
#include <QDebug>
#include <QRegularExpression>

DashboardModel::DashboardModel(QObject *parent) : QObject(parent) {}

void DashboardModel::initializeTables() {
    for (int i = 1; i <= 32; ++i) {
        TableInfo table;
        table.tableNumber = "Table " + QString::number(i);
        table.status = "Available";
        table.clientCount = 0;
        tables.append(table);
    }
}

void DashboardModel::initializeEquipments() {
    QStringList equipmentNames = {
        "Cooking Burners", "Pots", "Pans", "Oven", "Wooden Spoons",
        "Blender", "Salad Bowls", "Pressure Cooker", "Juicer", "Sieve",
        "Funnels", "Kitchen Knives", "Work Fridge", "Dishwasher", "Washing Machine", "Sink"
    };

    QList<int> totalEquipments = {5, 10, 10, 1, 10, 1, 5, 2, 1, 1, 1, 5, 1, 1, 1, 1};

    if (equipmentNames.size() != totalEquipments.size()) {
        qWarning() << "Mismatch between number of equipment names and total equipment count!";
        return;
    }

    for (int i = 0; i < equipmentNames.size(); ++i) {
        EquipmentInfo equipment;
        equipment.name = equipmentNames[i];
        equipment.status = "Available";
        equipment.total = totalEquipments[i];
        equipment.used = 0;
        equipment.unused = equipment.total;
        equipments.append(equipment);
    }
}

void DashboardModel::initializeStaffs() {
    QStringList staffNames = {"Head waiter", "Casseroles", "Waiter1", "Waiter2", "Room Attendant1", "Room Attendant2", "Head Chef", "Cook1", "Cook2", "Kitchen Assistant1", "Kitchen Assistant2", "Dishwasher"};
    for (const QString &name : staffNames) {
        StaffInfo staff;
        staff.name = name;
        staff.status = "Not active";
        staffs.append(staff);
    }
}

void DashboardModel::initializeIngredients() {
    QStringList ingredientNames = {"Tomatoes", "Onions", "Chili", "Salt", "Pepper", "Oil"};
    QList<int> stockLevels = {100, 80, 50, 100, 70, 90};

    for (int i = 0; i < ingredientNames.size(); ++i) {
        IngredientInfo ingredient;
        ingredient.name = ingredientNames[i];
        ingredient.stockLevel = stockLevels[i];
        ingredients.append(ingredient);
    }
}

QList<EquipmentInfo> DashboardModel::getEquipments() const {
    return equipments;
}

QList<TableInfo> DashboardModel::getTable() const {
    return tables;
}

QList<StaffInfo> DashboardModel::getStaff() const {
    return staffs;
}

QList<IngredientInfo> DashboardModel::getIngredient() const {
    return ingredients;
}
