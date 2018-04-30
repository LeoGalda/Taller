#ifndef COMMON_LOCK_H
#define COMMON_LOCK_H
#include <mutex>

class Lock {
private:
    std::mutex &mute;
    Lock(const Lock&) = delete;
    Lock& operator=(const Lock&) = delete;
    Lock(Lock&&) = delete;
    Lock& operator=(Lock&&) = delete;

public:
    //constructor del Lock el cual recibe un mutex por parametro    
    explicit Lock(std::mutex &mute);

    //destructor del Lock    
    ~Lock();
};

#endif 

