#ifndef MANAGERS_H
#define MANAGERS_H

#include "../../model/classDeclaration/ThreadPool.h"
#include "../../model/classDeclaration/Chief.h"

#include <atomic>
#include <mutex>

class Managers
{
private:
    ThreadPool* threadPool;
    atomic<bool> running;
    Chief* chief;
    mutex lock;
public:
    Managers(/* args */);
    ~Managers();
    void start(size_t taskcout);

    void stop();
};

// managers::managers(/* args */)
// {
// }

// managers::~managers()
// {
// }


#endif