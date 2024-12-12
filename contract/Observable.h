#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include "Observer.h"

#include <vector>

class Observable
{
public:
    virtual ~Observable() = default;
    virtual void subscribe(Observer *observer);
    virtual void unsubscribe(Observer *observer);
    virtual void notify(const std::unordered_map<std::string, std::any>& data);

private:
    std::vector<Observer *> observers;
};

#endif