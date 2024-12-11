#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QMainWindow>
#include <QTableWidget>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QProgressBar>
#include <QScrollArea>

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
    int unused;              // Nombre d'équipements inutilisés
};



struct StaffInfo {
    QString name;       // Nom de l'équipement
    QString status;     // Statut : Disponible, En utilisation, En panne
};

struct IngredientInfo {
    QString name;
    int stockLevel;
};

class Dashboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = nullptr);
    ~Dashboard();

private:
    QStackedWidget *stackedWidget;
    QProgressBar *stockBar;
    QScrollArea *scrollArea;

    void setupUi();
    void createGlobalView();
    void createKitchenView();
    void createStaffView();
    void createIngredientsView();

    void initializeTables();
    void initializeEquipments();
    void initializeStaffs();
    void initializeIngredients();
    void readLogAndUpdate();

    QList<TableInfo> tables;
    QList<EquipmentInfo> equipments;
    QList<StaffInfo> staffs;
    QList<IngredientInfo> ingredients;

    QTimer *logUpdateTimer;
};

#endif // DASHBOARD_H
