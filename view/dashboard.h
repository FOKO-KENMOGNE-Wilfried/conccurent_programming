#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QTableWidget>
#include <QMap>
#include <QProgressBar>
#include <QLabel>


class DashboardController;
class DashboardModel;

class Dashboard : public QMainWindow {
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = nullptr);
    ~Dashboard();
    DashboardModel* getModel() const; // Add this getter for model

private:
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

    QStackedWidget *stackedWidget;
    QTableWidget *globalTable;
    QTimer *logUpdateTimer;

    QMap<QString, QList<QLabel*>> equipmentLabelsMap;
    QMap<QString, QProgressBar*> ingredientBarsMap;
    QMap<QString, QLabel*> staffLabelsMap;

    DashboardController *controller;
    DashboardModel *model;
};

#endif // DASHBOARD_H
