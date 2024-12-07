#ifndef QGRAPHICELEMENT_H
#define QGRAPHICELEMENT_H

#include "../../classDeclaration/Human.h"
#include <QGraphicsEllipseItem>
#include <QTimer>
#include <QObject>
#include <QPointF>
#include <QSize>
#include <QString>
#include <QGraphicsPixmapItem>
#include "../../classDeclaration/Table.h"

class QGraphicElement : public QObject
{
    Q_OBJECT
private:
    Human* human;
    Table* table;
    QGraphicsPixmapItem* graphicTable;
    QGraphicsEllipseItem* graphicsElement;
    QTimer *moveTimer;
    bool hasPicture = false;
    float width, height;
public:
    QGraphicElement(/* args */);
    QGraphicElement(Human* human);
    QGraphicElement(Table* table, bool hasPicture, QSize elementSize, QString elemenntType);
    ~QGraphicElement();
    QGraphicsEllipseItem* getRepresentation();
    Human* getElement();
    QGraphicsPixmapItem* getTable();
    Table* getTableInstance();
    void move(QPointF destination);
};

#endif