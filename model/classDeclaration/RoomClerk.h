//
// Created by darkwall on 12/2/24.
//

#ifndef ROOMCLERK_H
#define ROOMCLERK_H

#include "Server.h"
#include "Human.h"

using namespace std;

/**
 * @class RoomClerk
 *
 * @brief a subsitute server
 */
class RoomClerk : Human{
public:
    double abscice, intercept;
    /**
     * @brief the RoomClerk constructor
     *
     * @param area
     * @param max_ready_order
     * @param dirty_dishes_collected
     * @param type
     */
    RoomClerk(double abscise, double intercept)
    : abscice(abscice),
    intercept(intercept){}
    ~RoomClerk();
    /**
     * @brief the function to serve apero(bread and drink)
     * TODO: Retoucher cette méthode(enlever todo une fois fait)
     */
    void serveApero();

private:
    string type;

};
#endif //ROOMCLERK_H
