//
//  Thread.h
//  App
//
//  Created by Liu Enze on 10/12/13.
//  Copyright (c) 2013 Liu Enze. All rights reserved.
//

#ifndef App_Thread_h
#define App_Thread_h

#include<pthread.h>

class Runable
{
public:
    virtual ~Runable(){};
    virtual void run()=0;
};

#define THREAD_CALL
typedef void* (*ThreadCall)( void* aArg );

class Thread : public Runable
{
public:
    Thread();
    virtual ~Thread(){};
    
    void start();
    
    pthread_t getId() { return _tid; }
    
    void stop(){isRunning=false;};
protected:
    virtual void run() = 0;
    bool isRunning=true;
    pthread_t      _tid;
private:
    static void* THREAD_CALL ThreadFunc( void* aArg );
};


#endif
