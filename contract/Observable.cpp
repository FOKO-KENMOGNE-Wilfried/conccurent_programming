
#include "Observable.h"

// Attach an observer
void Observable::subscribe(Observer *observer)
{
  observers.push_back(observer);
}

// Detach an observer
void Observable::unsubscribe(Observer *observer)
{
  // remove observer from the vector
}

// Notify all observers
void Observable::notify(const std::unordered_map<std::string, std::any>& data)
{
  for (Observer *observer : observers)
  {
    observer->update(data);
  }
}
