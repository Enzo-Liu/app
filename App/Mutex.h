//
//  Mutex.h
//  App
//
//  Created by Liu Enze on 10/11/13.
//  Copyright (c) 2013 Liu Enze. All rights reserved.
//

#ifndef __App__Mutex__
#define __App__Mutex__

#include <iostream>

class Mutex
{
private:
    pthread_mutex_t mutex;
public:
    Mutex()
    {
        pthread_mutex_init(&mutex, nullptr);
    }
    ~Mutex()
    {
        pthread_mutex_destroy(&mutex);
    }
    void lock()
    {
        pthread_mutex_trylock(&mutex);
    }
    void unlock()
    {
        pthread_mutex_unlock(&mutex);
    }
    
    pthread_mutex_t* getMutex()
    {
        return &mutex;
    }
};

class Lock
{
private:
    Mutex* m_mutex=nullptr;
public:
    Lock(Mutex &mutex)
    {
        m_mutex = &mutex;
        m_mutex->lock();
    }
    ~Lock()
    {
        m_mutex->unlock();
        m_mutex=nullptr;
    }
};

#endif /* defined(__App__Mutex__) */
