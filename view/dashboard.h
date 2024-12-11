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

    void createGlobalView();
    void createKitchenView();
    void createStaffView();
    void createIngredientsView();
};

#endif // DASHBOARD_H
