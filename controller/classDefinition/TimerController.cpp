#include "../../controller/classDeclaration/TimerController.h"

TimerController::TimerController(QObject *parent)
    : QObject(parent), timer(new QTimer(this)), currentTime(QTime(0, 0, 0)) {
    connect(timer, &QTimer::timeout, this, &TimerController::updateTime);
}

QTimer* TimerController::getTimer() const {
    return timer;
}

QTime TimerController::getCurrentTime() const {
    return currentTime;
}

void TimerController::startTimer() {
    if (!timer->isActive()) {
        timer->start(1000); // Update every second
    }
}

void TimerController::stopTimer() {
    if (timer->isActive()) {
        timer->stop();
    }
}

void TimerController::updateTime() {
    currentTime = currentTime.addSecs(1);
    emit timeUpdated(currentTime);
}
