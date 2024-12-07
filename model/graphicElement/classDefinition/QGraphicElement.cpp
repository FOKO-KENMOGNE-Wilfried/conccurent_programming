#include "../classDeclaration/QGraphicElement.h"
#include <QGraphicsView>

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
QGraphicElement::QGraphicElement(Table* table, bool hasPicture, QSize tableSize, QString tableType){
    this->table = table;
    this->hasPicture = hasPicture;
    QPixmap originalPixmap(tableType);
    QPixmap scaledPixmap = originalPixmap.scaled(tableSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    graphicTable = new QGraphicsPixmapItem(scaledPixmap);
    graphicTable->setPos(table->abscice, table->intercept);
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
QGraphicsPixmapItem* QGraphicElement::getTable() {
    return this->graphicTable;
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
Table* QGraphicElement::getTableInstance() {
    return this->table;
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
