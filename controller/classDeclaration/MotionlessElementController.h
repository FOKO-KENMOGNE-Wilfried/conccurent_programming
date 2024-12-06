//
// Created by darkwall on 12/2/24.
//

#ifndef MOTIONLESSELEMENTCONTROLLER_H
#define MOTIONLESSELEMENTCONTROLLER_H
#include "../../model/classDeclaration/DirtyDishesStorage.h"
#include "../../model/classDeclaration/WashingMachine.h"
using namespace std;

/**
 * @class MotionlessElementController
 */
class MotionlessElementController {
public:
    /**
     * @brief
     *
     * @param dirty_dishes_storage
     * @param washing_machine
     */
    MotionlessElementController(const DirtyDishesStorage &dirty_dishes_storage, const WashingMachine &washing_machine)
        : dirty_dishes_storage_(dirty_dishes_storage),
          washing_machine_(washing_machine) {
    }

    void createAllTable();
    void createKitchenElements();
    MotionlessElementController();

private:
    DirtyDishesStorage dirty_dishes_storage_;
    WashingMachine washing_machine_;

};
#endif //MOTIONLESSELEMENTCONTROLLER_H
