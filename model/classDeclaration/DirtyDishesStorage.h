//
// Created by wolverine on 12/2/24.
//

#ifndef DIRTYDISHESSTORAGE_H
#define DIRTYDISHESSTORAGE_H
using namespace std;

/**
 * @class DirtyDishesStorage
 */
class DirtyDishesStorage {
public:
    /**
     * @brief
     *
     * @param dirty_plates_number
     * @param dirty_glasses_number
     * @param dirty_cutlery_number
     */
    DirtyDishesStorage(int dirty_plates_number, int dirty_glasses_number, int dirty_cutlery_number)
        : dirtyPlatesNumber(dirty_plates_number),
          dirtyGlassesNumber(dirty_glasses_number),
          dirtyCutleryNumber(dirty_cutlery_number) {
    }

    void sendToDishWasher(int platesNumber, int glassesNumber, int cutleryNumber);
    int getdirtyPlatesNumber() const;
    int getdirtyGlassesNumber() const;
    int getdirtyCutleryNumber() const;
    void setdirtyCutleryNumber(int cutleryNumber);
    void setdirtyGlassesNumber(int glassesNumber);
    void setdirtyPlatesNumber(int platesNumber);

private:
    int dirtyPlatesNumber;
    int dirtyGlassesNumber;
    int dirtyCutleryNumber;

};
#endif //DIRTYDISHESSTORAGE_H
