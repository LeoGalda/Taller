#ifndef SERVER_THREAD_H
#define SERVER_THREAD_H

#include <iostream>
#include <vector>
#include <thread>

class Thread {
private:
    std::thread thread;
    
public:     
//constructor del thread    
    Thread();    
    
//metodo que da comienzo a la ejecucion de los thread y llama a run    
    void start();

// hace el join de los thread,     
    void join();    
    
//corre el run de las hijas derivadas    
    virtual void run() = 0;

//destructor del thread    
    virtual ~Thread();
    
//de esta manera evitamos que se copien los hilos
    Thread(const Thread&) = delete;
    Thread& operator=(const Thread&) = delete;
    
//de esta manera permitimos que se muevan los hilos    
    Thread(Thread&& other);
    Thread& operator=(Thread&& other);
};

#endif

