#include "Lock.h"

Lock::Lock(std::mutex &mute) : mute(mute) {
    mute.lock();
}

Lock::~Lock() {
    mute.unlock();
}