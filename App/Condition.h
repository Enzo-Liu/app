//
//  Condition.h
//  App
//
//  Created by Liu Enze on 10/12/13.
//  Copyright (c) 2013 Liu Enze. All rights reserved.
//

#ifndef App_Condition_h
#define App_Condition_h

#include "Mutex.h"

class Condition
{
private:
    pthread_cond_t m_cond;
public:
    Condition()
    {
        pthread_cond_init(&m_cond,nullptr);
    }
    
    ~Condition()
    {
        pthread_cond_destroy(&m_cond);
    }
    
    void wait(Mutex& mutex)
    {
        pthread_cond_wait(&m_cond, mutex.getMutex());
    }
    
    void notify()
    {
        pthread_cond_broadcast(&m_cond);
    }
};

#endif
