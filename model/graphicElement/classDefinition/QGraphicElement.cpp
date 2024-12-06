#include "../classDeclaration/QGraphicElement.h"
#include <QGraphicsView>

QGraphicElement::QGraphicElement(Human* human){
    this->human = human;
    this->graphicsElement = new QGraphicsEllipseItem(0, 0, 10, 10);
    graphicsElement->setBrush(Qt::red);
    graphicsElement->setPos(human->abscice, human->intercept);
}

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

QGraphicsEllipseItem* QGraphicElement::getRepresentation(){
    return this->graphicsElement;
}

QGraphicsPixmapItem* QGraphicElement::getTable() {
    return this->graphicTable;
}

Human* QGraphicElement::getElement(){
    return this->human;
}

Table* QGraphicElement::getTableInstance(){
    return this->table;
}

void QGraphicElement::move(QPointF destination) {
    moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, [this, destination]() {
        // QPointF destination = QPointF(1160 , 500);
        QPointF currentPosition = graphicsElement->pos();
        if (currentPosition.x() != destination.x()) {
            // Déplacement sur l'axe X
            float directionX = (destination.x() - currentPosition.x() > 0) ? 1.0 : -1.0;
            graphicsElement->moveBy(directionX, 0);
            human->abscice = graphicsElement->pos().x();
        } else if (currentPosition.y() != destination.y()) {
            // Déplacement sur l'axe Y
            float directionY = (destination.y() - currentPosition.y() > 0) ? 1.0 : -1.0;
            graphicsElement->moveBy(0, directionY);
            human->intercept = graphicsElement->pos().y();
        }
    });
    moveTimer->start(16);
}
