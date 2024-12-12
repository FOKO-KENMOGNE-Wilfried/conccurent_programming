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

void DashboardModel::updateTable(const QString &line) {
    QStringList parts = line.split(": ");
    if (parts.size() < 2) return;

    QString tableStr = parts[0].trimmed();
    QString statusAndClients = parts[1].trimmed();

    QStringList statusAndClientsParts = statusAndClients.split(", ");
    if (statusAndClientsParts.size() < 2) return;

    QString status = statusAndClientsParts[0].trimmed();
    int clientCount = statusAndClientsParts[1].split(' ')[0].toInt();

    for (int i = 0; i < tables.size(); ++i) {
        if (tables[i].tableNumber == tableStr) {
            tables[i].status = status;
            tables[i].clientCount = clientCount;
            emit tableUpdated();
            break;
        }
    }
}

void DashboardModel::updateEquipment(const QString &line) {
    QStringList parts = line.split(", ");
    if (parts.size() < 4) return;

    QString equipmentName = parts[0].section(':', 1).trimmed();
    QString status = parts[1].trimmed();
    int used = parts[2].split(' ')[0].toInt();
    int unused = parts[3].split(' ')[0].toInt();

    for (int i = 0; i < equipments.size(); ++i) {
        if (equipments[i].name == equipmentName) {
            equipments[i].status = (equipments[i].total == used) ? "Unavailable" : status;
            equipments[i].used = used;
            equipments[i].unused = unused;
            emit equipmentUpdated();
            break;
        }
    }
}

void DashboardModel::updateStaff(const QString &line) {
    QStringList parts = line.split(": ");
    if (parts.size() < 2) return;

    QString staffName = parts[1].section(',', 0, 0).trimmed();
    QString status = parts[1].section(',', 1, 1).trimmed();

    for (int i = 0; i < staffs.size(); ++i) {
        if (staffs[i].name == staffName) {
            staffs[i].status = status;
            emit staffUpdated();
            break;
        }
    }
}

void DashboardModel::updateStock(const QString &line) {
    QRegularExpression regex(R"(Stock\s+([\w\s]+):\s*(\d+)%?)");
    QRegularExpressionMatch match = regex.match(line);

    if (match.hasMatch()) {
        QString ingredientName = match.captured(1).trimmed();
        int stockLevel = match.captured(2).toInt();

        for (int i = 0; i < ingredients.size(); ++i) {
            if (ingredients[i].name == ingredientName) {
                ingredients[i].stockLevel = stockLevel;
                emit stockUpdated();
                break;
            }
        }
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
