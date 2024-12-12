#ifndef OBSERVER_H
#define OBSERVER_H


#include <unordered_map>
#include <string>
#include <any>
/**
 * @class Observer
 * @brief la classe (en réalité une interface) pour les observeurs
 */

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const std::unordered_map<std::string, std::any>& data) = 0;
};

#endif