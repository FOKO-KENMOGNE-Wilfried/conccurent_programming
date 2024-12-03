#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QTimer>
#include <QPushButton>
#include <QLineEdit>
#include <QTableWidget>
#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

class View : public QMainWindow {
    Q_OBJECT

public:
    explicit View(QWidget *parent = nullptr);

private:
    void setupUi();
    void setupReceptionArea();
    void setupCounter();
    void setupTables();
    void setupPerson();
    void moveToPosition(QGraphicsEllipseItem* item, QPointF destination);
    void displayPositions();

    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QFrame *gameFrame;
    QGraphicsView *receptionAreaView;
    QGraphicsScene *scene;
    QGraphicsRectItem *counter;
    QList<QGraphicsRectItem*> tables;
    QGraphicsEllipseItem *person;
    QTimer *timer;
    QTimer *moveTimer;
    
    QPointF targetPosition;

    QPushButton *startButton;
    QPushButton *pauseButton;
    QPushButton *speedButton;
    QPushButton *normalSpeedButton;
    QPushButton *kitchenButton;
    QPushButton *dashboardButton;
    QComboBox *timeComboBox;
    QLineEdit *clientInput;
    QTableWidget *plateServedTable;
    QTableWidget *menuTable;
    QTableWidget *ingredientsTable;
};

#endif // VIEW_H
