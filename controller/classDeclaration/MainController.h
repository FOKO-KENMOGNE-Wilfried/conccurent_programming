//
// Created by darkwall on 12/2/24.
//

#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H
#include "DBController.h"
#include "MotionlessElementController.h"
// #include <queue>
#include <list>
#include "../../model/classDeclaration/Human.h"
using namespace std;

class MainController {
    DBController dbController;
    MotionlessElementController motionlessElementController;
    // queue<Human> humanQueue;
    // TODO: Change humanList to vector
    list<Human*> humanList;
    Human human;

    public:
        void init(int argc, char *argv[]);
        MainController();
        ~MainController();

        /**
         * @brief Function use to initialize the dining room threads and processes
         */
        void Restaurant();
};

#endif //MAINCONTROLLER_H
