#ifndef DASHBOARDCONTROLLER_H
#define DASHBOARDCONTROLLER_H

#include <QObject>
#include "../../view/dashboard.h"

class DashboardController : public QObject {
    Q_OBJECT

public:
    explicit DashboardController(Dashboard *dashboard);

public slots:
    void readLogAndUpdate();

private:
    Dashboard *dashboard;
};

#endif // DASHBOARDCONTROLLER_H
