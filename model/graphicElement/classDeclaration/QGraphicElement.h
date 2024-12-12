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
#include "../../classDeclaration/Butler.h"
#include "../../classDeclaration/Chief.h"
#include "../../classDeclaration/ClientModel.h"
#include "../../classDeclaration/Cook.h"
#include "../../classDeclaration/HeadWaiter.h"
#include "../../classDeclaration/KitchenAssistant.h"
#include "../../classDeclaration/RestaurantDiver.h"
#include "../../classDeclaration/RoomClerk.h"
#include "../../classDeclaration/Server.h"
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
    Butler* butler;
    Chief* chief;
    ClientModel* clientModel;
    HeadWaiter* headWaiter;
    Cook* cook;
    KitchenAssistant* kitchenAssistant;
    RestaurantDiver* restaurantDiver;
    RoomClerk* roomClerk;
    Server* server;
    Table* table;
    QGraphicsItem* represent;
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
    // QGraphicElement(Human* human, Qt::GlobalColor color);
    Butler *getButler();
    Chief *getChief();
    ClientModel *getClientModel();
    HeadWaiter *getHeadWaiter();
    Cook *getCook();
    KitchenAssistant *getKitchenAssistant();
    RestaurantDiver *getRestaurantDiver();
    RoomClerk *getRoomClerk();
    Server *getServer();
    QGraphicElement(Butler* butler, Qt::GlobalColor color);
    QGraphicElement(Chief* chief, Qt::GlobalColor color);
    QGraphicElement(ClientModel* clientModel, Qt::GlobalColor color);
    QGraphicElement(HeadWaiter* headWaiter, Qt::GlobalColor color);
    QGraphicElement(Cook* cook, Qt::GlobalColor color);
    QGraphicElement(KitchenAssistant* kitchenAssistant, Qt::GlobalColor color);
    QGraphicElement(RestaurantDiver* restaurantDiver, Qt::GlobalColor color);
    QGraphicElement(RoomClerk* roomClerk, Qt::GlobalColor color);
    QGraphicElement(Server* server, Qt::GlobalColor color);
    QGraphicElement(Table* table, bool hasPicture, QSize elementSize, QString elemenntType);
    QGraphicElement(KitchenCounter* object, bool hasPicture, QSize elementSize, QString elemenntType);
    QGraphicElement(DirtyDishesStorage* object, bool hasPicture, QSize elementSize, QString elemenntType);
    QGraphicElement(DishwasherModel* object, bool hasPicture, QSize elementSize, QString elemenntType);
    QGraphicElement(WashingMachine* object, bool hasPicture, QSize elementSize, QString elemenntType);
    ~QGraphicElement();
    QGraphicsEllipseItem* getRepresentation();
    QGraphicsItem* getRepresent() {return represent;};
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