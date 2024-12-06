//
// Created by darkwall on 12/2/24.
//

#ifndef MOVECONTROLLER_H
#define MOVECONTROLLER_H
#include "../../model/classDeclaration/HeadWaiter.h"
#include "../../model/classDeclaration/RestaurantDiver.h"
#include "../../model/classDeclaration/Server.h"
using namespace std;
class MoveController {
public:
    void moveServe(Server server);
    void moveHeadWaiter(HeadWaiter headWaiter);
    void moveRestaurantDiver(RestaurantDiver restaurantDiver);
    // TODO: add the rest of the move method
};
#endif //MOVECONTROLLER_H
