#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QMainWindow>
#include <QTabWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QProgressBar>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <QTimer>
#include <QList>

namespace Ui {
class Dashboard;
}

struct TableInfo {
    QString tableNumber;    // Numéro de la table
    QString status;     // Statut de la table : Libre, Occupée, etc.
    int clientCount;    // Nombre de clients
};

struct EquipmentInfo {
    QString name;            // Nom de l'équipement
    QString status;          // Statut de l'équipement (Disponible, En panne, En utilisation, etc.)
    int total;               // Nombre total d'équipements
    int used;                // Nombre d'équipements utilisés
    int unused;              // Nombre d'équipements non utilisés

    EquipmentInfo() : total(0), used(0), unused(0) {}
};


struct StaffInfo {
    QString name;       // Nom de l'équipement
    QString status;     // Statut : Disponible, En utilisation, En panne
};


class Dashboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = nullptr);
    ~Dashboard();

private:
    void setupUi(); // Function to set up the user interface
    void setupGlobalTab();
    void setupKitchenTab();
    void setupStaffTab();

    // void processLogLine(const QString &line);
    // void updateTableStatus(int tableNumber, const QString &status, int clientCount);
    // void updateEquipmentStatus(const QString &name, const QString &status, int used, int unused);
    // void updateStock(int stock);

    void initializeTables();
    void initializeEquipments();
    void initializeStaffs();
    void readLogAndUpdate();
    void updateTotalClients();
    void onCellChanged(int row, int column);

    QTabWidget *tabWidget;

    QWidget *globalTab;

    QProgressBar *stockProgress;
    QTableWidget *equipmentTable;
    QTableWidget *globalTable;
    QTableWidget *staffTable;
    QWidget *kitchenTab;
    QWidget *staffTab;

    QList<TableInfo> tables;
    QList<EquipmentInfo> equipments;
    QList<StaffInfo> staffs;

    QTimer *logUpdateTimer;
    // Déclaration de lastReadPosition
    qint64 lastFilePosition = 0;  // Initialisez la position de lecture à 0
};

#endif // DASHBOARD_H
