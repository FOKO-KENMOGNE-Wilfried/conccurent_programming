#include "../classDeclaration/QGraphicElement.h"
#include <QGraphicsView>
#include <iostream>

/**
 * @brief The constructor to initialize the graphic instance for the human class
 * @param human The human instance to initialize
 */
QGraphicElement::QGraphicElement(Human* human){
    this->human = human;
    this->graphicsElement = new QGraphicsEllipseItem(0, 0, 10, 10);
    graphicsElement->setBrush(Qt::red);
    graphicsElement->setPos(human->abscice, human->intercept);
}

/**
 * @brief The constructor to initialize the graphic instance for the Table
 * @param table The table instance
 * @param hasPicture To say if the graphic element has a picture
 * @param tableSize To set the size of the graphic element
 * @param tableType to set the type of the graphic element
 */
QGraphicElement::QGraphicElement(Table* table, bool hasPicture, QSize tableSize, QString tableType) {
    this->table = table;
    this->hasPicture = hasPicture;
    QPixmap originalPixmap(tableType);
    QPixmap scaledPixmap = originalPixmap.scaled(tableSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    graphicObject = new QGraphicsPixmapItem(scaledPixmap);
    graphicObject->setPos(table->abscice, table->intercept);
}

QGraphicElement::QGraphicElement(KitchenCounter* kitchenCounter, bool hasPicture, QSize tableSize, QString tableType) {
    this->kitchenCounter = kitchenCounter;
    this->hasPicture = hasPicture;
    QPixmap originalPixmap(tableType);
    QPixmap scaledPixmap = originalPixmap.scaled(tableSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    graphicObject = new QGraphicsPixmapItem(scaledPixmap);
    graphicObject->setPos(kitchenCounter->abscice, kitchenCounter->intercept);
}

QGraphicElement::QGraphicElement(DirtyDishesStorage* dirtyDishesStorage, bool hasPicture, QSize tableSize, QString tableType) {
    this->dirtyDishesStorage = dirtyDishesStorage;
    this->hasPicture = hasPicture;
    QPixmap originalPixmap(tableType);
    QPixmap scaledPixmap = originalPixmap.scaled(tableSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    graphicObject = new QGraphicsPixmapItem(scaledPixmap);
    graphicObject->setPos(dirtyDishesStorage->abscice, dirtyDishesStorage->intercept);
}

QGraphicElement::QGraphicElement(DishwasherModel* dishwasherModel, bool hasPicture, QSize tableSize, QString tableType) {
    this->dishwasherModel = dishwasherModel;
    this->hasPicture = hasPicture;
    QPixmap originalPixmap(tableType);
    QPixmap scaledPixmap = originalPixmap.scaled(tableSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    graphicObject = new QGraphicsPixmapItem(scaledPixmap);
    graphicObject->setPos(dishwasherModel->abscice, dishwasherModel->intercept);
}

QGraphicElement::QGraphicElement(WashingMachine* washingMachine, bool hasPicture, QSize tableSize, QString tableType) {
    this->washingMachine = washingMachine;
    this->hasPicture = hasPicture;
    QPixmap originalPixmap(tableType);
    QPixmap scaledPixmap = originalPixmap.scaled(tableSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    graphicObject = new QGraphicsPixmapItem(scaledPixmap);
    graphicObject->setPos(washingMachine->abscice, washingMachine->intercept);
}
QGraphicElement::QGraphicElement(){}

QGraphicElement::~QGraphicElement(){}

/**
 * @brief Get the human instance
 */
QGraphicsEllipseItem* QGraphicElement::getRepresentation(){
    return this->graphicsElement;
}

/**
 * @brief Get thetable instance
 */
QGraphicsPixmapItem* QGraphicElement::getObject() {
    return this->graphicObject;
}

/**
 * @brief Gets the graphics human instace
 */
Human* QGraphicElement::getElement() {
    return this->human;
}

/**
 * @brief Gets the graphics table instance
 */
Table* QGraphicElement::getObjectInstance() {
    return this->table;
}

KitchenCounter* QGraphicElement::getKitchenInstance() {
    return this->kitchenCounter;
}

DirtyDishesStorage* QGraphicElement::getDirtyDishesStorageInstance(){
    return this->dirtyDishesStorage;
}
DishwasherModel* QGraphicElement::getDishWasherModelInstance(){
    return this->dishwasherModel;
}
WashingMachine* QGraphicElement::getWashingMachineInstance(){
    return this->washingMachine;
}

/**
 * @brief The method to move the graphic element
 * @param destination The destination to go
 */
void QGraphicElement::move(QPointF destination) {
    if (!hasPicture) {
        moveTimer = new QTimer(this);
        connect(moveTimer, &QTimer::timeout, [this, destination]() {
            QPointF currentPosition = graphicsElement->pos();
            if (currentPosition.x() != destination.x()) {
                // Moving on the X axis
                float directionX = (destination.x() - currentPosition.x() > 0) ? 1.0 : -1.0;
                graphicsElement->moveBy(directionX, 0);
                human->abscice = graphicsElement->pos().x();
            } else if (currentPosition.y() != destination.y()) {
                // Moving on the Y axis
                float directionY = (destination.y() - currentPosition.y() > 0) ? 1.0 : -1.0;
                graphicsElement->moveBy(0, directionY);
                human->intercept = graphicsElement->pos().y();
            }
        });
    } else {
        std::cout << "The move method can only been used for the human class instance and her child !!" << std::endl;
    }
    moveTimer->start(16);
}
