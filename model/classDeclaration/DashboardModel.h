#ifndef DASHBOARDMODEL_H
#define DASHBOARDMODEL_H

#include <QObject>
#include <QString>
#include <QList>

struct TableInfo {
    QString tableNumber;
    QString status;
    int clientCount;
};

struct EquipmentInfo {
    QString name;
    QString status;
    int total;
    int used;
    int unused;
};

struct StaffInfo {
    QString name;
    QString status;
};

struct IngredientInfo {
    QString name;
    int stockLevel;
};

class DashboardModel : public QObject {
    Q_OBJECT

public:
    explicit DashboardModel(QObject *parent = nullptr);

    void initializeTables();
    void initializeEquipments();
    void initializeStaffs();
    void initializeIngredients();
    void updateTable(const QString &line);
    void updateEquipment(const QString &line);
    void updateStaff(const QString &line);
    void updateStock(const QString &line);

    // Getter for equipments
    QList<EquipmentInfo> getEquipments() const;

    // Getter for equipments
    QList<TableInfo> getTable() const;

    // Getter for equipments
    QList<StaffInfo> getStaff() const;

    // Getter for equipments
    QList<IngredientInfo> getIngredient() const;

signals:
    void tableUpdated();
    void equipmentUpdated();
    void staffUpdated();
    void stockUpdated();

private:
    QList<TableInfo> tables;
    QList<EquipmentInfo> equipments;
    QList<StaffInfo> staffs;
    QList<IngredientInfo> ingredients;
};

#endif // DASHBOARDMODEL_H
