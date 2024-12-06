#ifndef QGRAPHICELEMENT_H
#define QGRAPHICELEMENT_H

#include "../../classDeclaration/Human.h"
#include <QGraphicsEllipseItem>
#include <QTimer>
#include <QObject>

class QGraphicElement : public QObject
{
    Q_OBJECT
private:
    Human* human;
    QGraphicsEllipseItem *graphicsElement;
    QTimer *moveTimer;
public:
    QGraphicElement(/* args */);
    QGraphicElement(Human* human);
    ~QGraphicElement();
    QGraphicsEllipseItem* getRepresentation();
    Human* getElement();
    void move();
};

#endif