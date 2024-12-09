#ifndef QGRAPHICELEMENT_H
#define QGRAPHICELEMENT_H

#include <QGraphicsEllipseItem>
#include <QTimer>
#include <QObject>
#include <QPointF>
#include <QSize>
#include <QString>
#include <QGraphicsPixmapItem>

#include "../../classDeclaration/Human.h"
#include "../../classDeclaration/Table.h"
// #include "../../classDeclaration/ObjectModel.h"
#include "../../classDeclaration/KitchenCounter.h"
#include "../../classDeclaration/DirtyDishesStorage.h"
#include "../../classDeclaration/DishwasherModel.h"
#include "../../classDeclaration/WashingMachine.h"

class QGraphicElement : public QObject
{
    Q_OBJECT
private:
    Human* human;
    Table* table;
    KitchenCounter* kitchenCounter;
    DirtyDishesStorage* dirtyDishesStorage;
    DishwasherModel* dishwasherModel;
    WashingMachine* washingMachine;
    QGraphicsEllipseItem* graphicsElement;
    QTimer *moveTimer;
    bool hasPicture = false;
    float width, height;
public:
    QGraphicsPixmapItem* graphicObject;
    QGraphicElement(/* args */);
    QGraphicElement(Human* human, Qt::GlobalColor color);
    QGraphicElement(Table* table, bool hasPicture, QSize elementSize, QString elemenntType);
    QGraphicElement(KitchenCounter* object, bool hasPicture, QSize elementSize, QString elemenntType);
    QGraphicElement(DirtyDishesStorage* object, bool hasPicture, QSize elementSize, QString elemenntType);
    QGraphicElement(DishwasherModel* object, bool hasPicture, QSize elementSize, QString elemenntType);
    QGraphicElement(WashingMachine* object, bool hasPicture, QSize elementSize, QString elemenntType);
    ~QGraphicElement();
    QGraphicsEllipseItem* getRepresentation();
    Human* getElement();
    QGraphicsPixmapItem* getObject();
    Table* getObjectInstance();
    KitchenCounter* getKitchenInstance();
    DirtyDishesStorage* getDirtyDishesStorageInstance();
    DishwasherModel* getDishWasherModelInstance();
    WashingMachine* getWashingMachineInstance();
    // KitchenCounter* getInstance();
    void move(QPointF destination);
};

#endif