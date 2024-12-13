#include "../classDeclaration/DashboardController.h"
#include "../../view/Dashboard.h"
#include "../../model/classDeclaration/DashboardModel.h"

#include <QFile>
#include <QTextStream>

DashboardController::DashboardController(Dashboard *dashboard) : dashboard(dashboard) {}

void DashboardController::readLogAndUpdate() {
    QFile file("/view/restaurant.log");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Erreur d'ouverture du fichier log";
        return;
    }

    QTextStream in(&file);
    QString line;

    while (!in.atEnd()) {
        line = in.readLine();

        if (line.startsWith("Table")) {
            //dashboard->getModel()->updateTable(line);
        }

        if (line.startsWith("Equipment")) {
           // dashboard->getModel()->updateEquipment(line);
        }

        if (line.startsWith("Staff")) {
            //dashboard->getModel()->updateStaff(line);
        }

        if (line.startsWith("Stock")) {
           // dashboard->getModel()->updateStock(line);
        }
    }

    file.close();
}
