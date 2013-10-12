//
//  Thread.cpp
//  App
//
//  Created by Liu Enze on 10/12/13.
//  Copyright (c) 2013 Liu Enze. All rights reserved.
//

#include "Thread.h"

Thread::Thread()
{
}

void* THREAD_CALL Thread::ThreadFunc( void* aArg )
{
    Thread* self = static_cast<Thread*>( aArg );
    
    self->run();
    
    return NULL;
}


void Thread::start()
{
    pthread_create( &_tid, NULL, ThreadFunc, this);
    
    return;
}

