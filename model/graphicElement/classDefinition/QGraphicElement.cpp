#include "../classDeclaration/QGraphicElement.h"
#include <QGraphicsView>

QGraphicElement::QGraphicElement(Human* human){
    this->human = human;
    this->graphicsElement = new QGraphicsEllipseItem(0, 0, 10, 10);
    graphicsElement->setBrush(Qt::red);
    graphicsElement->setPos(human->getAbscice(), human->getIntercept());
}

QGraphicElement::QGraphicElement(){}

QGraphicElement::~QGraphicElement(){

}

QGraphicsEllipseItem* QGraphicElement::getRepresentation(){
    return this->graphicsElement;
}

Human* QGraphicElement::getElement(){
    return this->human;
}

void QGraphicElement::move(){
    moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, [this]() {
        human->move();
        graphicsElement->setPos(human->getAbscice(), human->getIntercept());
    });
    moveTimer->start(16);
}
