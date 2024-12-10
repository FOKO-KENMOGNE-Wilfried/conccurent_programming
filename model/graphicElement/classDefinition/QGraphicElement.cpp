#include "../classDeclaration/QGraphicElement.h"

#include <QGraphicsView>
#include <iostream>

/**
 * @brief The constructor to initialize the graphic instance for the human class
 * @param human The human instance to initialize
 */
// QGraphicElement::QGraphicElement(Human* human, Qt::GlobalColor color){
//     this->human = human;
//     this->graphicsElement = new QGraphicsEllipseItem(0, 0, 10, 10);
//     this->graphicsElement->setBrush(color);
//     this->graphicsElement->setPos(human->abscice, human->intercept);
// }
QGraphicElement::QGraphicElement(Butler* butler, Qt::GlobalColor color){
    this->butler = butler;
    this->graphicsElement = new QGraphicsEllipseItem(0, 0, 10, 10);
    this->graphicsElement->setBrush(color);
    this->graphicsElement->setPos(butler->abscice, butler->intercept);
}
QGraphicElement::QGraphicElement(Chief* chief, Qt::GlobalColor color){
    this->chief = chief;
    this->graphicsElement = new QGraphicsEllipseItem(0, 0, 10, 10);
    this->graphicsElement->setBrush(color);
    this->graphicsElement->setPos(chief->abscice, chief->intercept);
}
QGraphicElement::QGraphicElement(ClientModel* clientModel, Qt::GlobalColor color){
    this->clientModel = clientModel;
    this->graphicsElement = new QGraphicsEllipseItem(0, 0, 10, 10);
    this->graphicsElement->setBrush(color);
    this->graphicsElement->setPos(clientModel->abscice, clientModel->intercept);
}
QGraphicElement::QGraphicElement(HeadWaiter* headWaiter, Qt::GlobalColor color){
    this->headWaiter = headWaiter;
    this->graphicsElement = new QGraphicsEllipseItem(0, 0, 10, 10);
    this->graphicsElement->setBrush(color);
    this->graphicsElement->setPos(headWaiter->abscice, headWaiter->intercept);
}
QGraphicElement::QGraphicElement(Cook* cook, Qt::GlobalColor color){
    this->cook = cook;
    this->graphicsElement = new QGraphicsEllipseItem(0, 0, 10, 10);
    this->graphicsElement->setBrush(color);
    this->graphicsElement->setPos(cook->abscice, cook->intercept);
}
QGraphicElement::QGraphicElement(KitchenAssistant* kitchenAssistant, Qt::GlobalColor color){
    this->kitchenAssistant = kitchenAssistant;
    this->graphicsElement = new QGraphicsEllipseItem(0, 0, 10, 10);
    this->graphicsElement->setBrush(color);
    this->graphicsElement->setPos(kitchenAssistant->abscice, kitchenAssistant->intercept);
}
QGraphicElement::QGraphicElement(RestaurantDiver* restaurantDiver, Qt::GlobalColor color){
    this->restaurantDiver = restaurantDiver;
    this->graphicsElement = new QGraphicsEllipseItem(0, 0, 10, 10);
    this->graphicsElement->setBrush(color);
    this->graphicsElement->setPos(restaurantDiver->abscice, restaurantDiver->intercept);
}
QGraphicElement::QGraphicElement(RoomClerk* roomClerk, Qt::GlobalColor color){
    this->roomClerk = roomClerk;
    this->graphicsElement = new QGraphicsEllipseItem(0, 0, 10, 10);
    this->graphicsElement->setBrush(color);
    this->graphicsElement->setPos(roomClerk->abscice, roomClerk->intercept);
}
QGraphicElement::QGraphicElement(Server* server, Qt::GlobalColor color){
    this->server = server;
    this->graphicsElement = new QGraphicsEllipseItem(0, 0, 10, 10);
    this->graphicsElement->setBrush(color);
    this->graphicsElement->setPos(server->abscice, server->intercept);
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
    this->graphicObject = new QGraphicsPixmapItem(scaledPixmap);
    this->graphicObject->setPos(table->abscice, table->intercept);
}

QGraphicElement::QGraphicElement(KitchenCounter* kitchenCounter, bool hasPicture, QSize tableSize, QString tableType) {
    this->kitchenCounter = kitchenCounter;
    this->hasPicture = hasPicture;
    QPixmap originalPixmap(tableType);
    QPixmap scaledPixmap = originalPixmap.scaled(tableSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    this->graphicObject = new QGraphicsPixmapItem(scaledPixmap);
    this->graphicObject->setPos(kitchenCounter->abscice, kitchenCounter->intercept);
}

QGraphicElement::QGraphicElement(DirtyDishesStorage* dirtyDishesStorage, bool hasPicture, QSize tableSize, QString tableType) {
    this->dirtyDishesStorage = dirtyDishesStorage;
    this->hasPicture = hasPicture;
    QPixmap originalPixmap(tableType);
    QPixmap scaledPixmap = originalPixmap.scaled(tableSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    this->graphicObject = new QGraphicsPixmapItem(scaledPixmap);
    this->graphicObject->setPos(dirtyDishesStorage->abscice, dirtyDishesStorage->intercept);
}

QGraphicElement::QGraphicElement(DishwasherModel* dishwasherModel, bool hasPicture, QSize tableSize, QString tableType) {
    this->dishwasherModel = dishwasherModel;
    this->hasPicture = hasPicture;
    QPixmap originalPixmap(tableType);
    QPixmap scaledPixmap = originalPixmap.scaled(tableSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    this->graphicObject = new QGraphicsPixmapItem(scaledPixmap);
    this->graphicObject->setPos(dishwasherModel->abscice, dishwasherModel->intercept);
}

QGraphicElement::QGraphicElement(WashingMachine* washingMachine, bool hasPicture, QSize tableSize, QString tableType) {
    this->washingMachine = washingMachine;
    this->hasPicture = hasPicture;
    QPixmap originalPixmap(tableType);
    QPixmap scaledPixmap = originalPixmap.scaled(tableSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    this->graphicObject = new QGraphicsPixmapItem(scaledPixmap);
    this->graphicObject->setPos(washingMachine->abscice, washingMachine->intercept);
}
QGraphicElement::QGraphicElement(){}

QGraphicElement::~QGraphicElement(){}

/**
 * @brief Get the graphics human instance
 */
QGraphicsEllipseItem* QGraphicElement::getRepresentation(){
    return this->graphicsElement;
}

/**
 * @brief Get the table instance
 */
QGraphicsPixmapItem* QGraphicElement::getObject() {
    return this->graphicObject;
}

/**
 * @brief Gets the human instace
 */
Human* QGraphicElement::getElement() {
    return this->human;
}

/**
 * @brief Gets the butler instace
 */
Butler* QGraphicElement::getButler() {
    return this->butler;
}

/**
 * @brief Gets the chief instace
 */
Chief* QGraphicElement::getChief() {
    return this->chief;
}

/**
 * @brief Gets the clientModel instace
 */
ClientModel* QGraphicElement::getClientModel() {
    return this->clientModel;
}

/**
 * @brief Gets the headWaiter instace
 */
HeadWaiter* QGraphicElement::getHeadWaiter() {
    return this->headWaiter;
}

/**
 * @brief Gets the cook instace
 */
Cook* QGraphicElement::getCook() {
    return this->cook;
}

/**
 * @brief Gets the kitchenAssistant instace
 */
KitchenAssistant* QGraphicElement::getKitchenAssistant() {
    return this->kitchenAssistant;
}

/**
 * @brief Gets the restaurantDiver instace
 */
RestaurantDiver* QGraphicElement::getRestaurantDiver() {
    return this->restaurantDiver;
}

/**
 * @brief Gets the roomClerk instace
 */
RoomClerk* QGraphicElement::getRoomClerk() {
    return this->roomClerk;
}

/**
 * @brief Gets the server instace
 */
Server* QGraphicElement::getServer() {
    return this->server;
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
            QPointF currentPosition = this->graphicsElement->pos();
            if (currentPosition.x() != destination.x()) {
                // Moving on the X axis
                float directionX = (destination.x() - currentPosition.x() > 0) ? 1.0 : -1.0;
                this->graphicsElement->moveBy(directionX, 0);
                // human->abscice = this->graphicsElement->pos().x();
            } else if (currentPosition.y() != destination.y()) {
                // Moving on the Y axis
                float directionY = (destination.y() - currentPosition.y() > 0) ? 1.0 : -1.0;
                this->graphicsElement->moveBy(0, directionY);
                // human->intercept = this->graphicsElement->pos().y();
            }
        });
    } else {
        std::cout << "The move method can only been used for the human class instance and her child !!" << std::endl;
    }
    moveTimer->start(16);
}

/**
 * @brief The function to move a graphic instance for the human class
 * @param human The human instance
 * @param destination The target position
 */
void QGraphicElement::moveElement(Human* human, QPointF destination){
    QPointF currentPosition = represent->pos();

    // Calculate the direction to the destination
    qreal stepSize = 2.0; // Adjust this value for movement speed
    qreal directionX = (destination.x() - currentPosition.x());
    qreal directionY = (destination.y() - currentPosition.y());

    // Normalize the movement
    // qreal length = sqrt(directionX * directionX + directionY * directionY);
    // if (length > 0) {
    //     directionX /= length;
    //     directionY /= length;
    // }

    // Move towards the destination
    qreal nextX = currentPosition.x() + directionX * stepSize;
    qreal nextY = currentPosition.y() + directionY * stepSize;

    // Update the representation's position
    represent->setPos(nextX, nextY);
}
