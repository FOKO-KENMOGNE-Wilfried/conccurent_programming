#ifndef TIMERCONTROLLER_H
#define TIMERCONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QTime>

class TimerController : public QObject {
    Q_OBJECT

public:
    explicit TimerController(QObject *parent = nullptr);
    QTimer* getTimer() const;
    QTime getCurrentTime() const;

signals:
    void timeUpdated(const QTime& time);

public slots:
    void startTimer();
    void stopTimer();
    void updateTime();

private:
    QTimer* timer;
    QTime currentTime;
};

#endif // TIMERCONTROLLER_H
