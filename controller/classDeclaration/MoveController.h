//
// Created by wolverine on 12/2/24.
//

#ifndef MOVECONTROLLER_H
#define MOVECONTROLLER_H
#include "../../Models/classDeclaration/headWaiter.h"
#include "../../Models/classDeclaration/RestaurantDiver.h"
#include "../../Models/classDeclaration/Server.h"
using namespace std;
class MoveController {
public:
    void moveServe(Server server);
    void moveHeadWaiter(HeadWaiter headWaiter);
    void moveRestaurantDiver(RestaurantDiver restaurantDiver);
    // TODO: add the rest of the move method
};
#endif //MOVECONTROLLER_H
