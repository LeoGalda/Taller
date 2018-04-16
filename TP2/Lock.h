#ifndef LOCK_H
#define LOCK_H

class Lock {
    private:
        std::mutex &mute;

    public:
        Lock(std::mutex &mute) : mute(mute) {
            mute.lock();
        }

        ~Lock() {
            mute.unlock();
        }

    private:
        Lock(const Lock&) = delete;
        Lock& operator=(const Lock&) = delete;
        Lock(Lock&&) = delete;
        Lock& operator=(Lock&&) = delete;

};

#endif 

