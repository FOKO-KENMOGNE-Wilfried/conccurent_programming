//
// Created by darkwall on 12/2/24.
//

#ifndef OBJECTMODEL_H
#define OBJECTMODEL_H

/**
 * @class ObjectModel
 *
 * @brief this class regroup all humans of the structure
 */
class ObjectModel {
public:
    double abscice;/** <L'abscice de chaque humain à un instant T */
    double intercept;/** <L'ordonnée de chaque humain à un instant T */
    /**
     *@brief constructor of the ObjectModel class
     *
     * @param abscice
     * @param intercept
     */
    ObjectModel(double abscice, double intercept);
    ObjectModel();
    // ~ObjectModel();
};

#endif
