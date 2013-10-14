//
//  Test.h
//  App
//
//  Created by Liu Enze on 10/12/13.
//  Copyright (c) 2013 Liu Enze. All rights reserved.
//

#ifndef __App__Test__
#define __App__Test__

#include <iostream>
#include "Queue.h"
#include "Thread.h"
#include <unistd.h>
#include <ctime>

void testQueue(int testSize);
void testMutilQueue(int testSize );

class Container:public Thread
{
private:
    BlockingQueue<string> m_queue;
    bool isRunning = true;
public:
    void onMsg(string* msg)
    {
        m_queue.push(msg);
    }
    void run()
    {
        while (isRunning) {
            string * msg = m_queue.pop();
            cout<<*msg<<endl;
            delete msg;
            msg = NULL;
        }
    }
    void stop()
    {
        isRunning = false;
    }
};

class Sender
{
private:
    Container& m_owner;
    int num=0;
public:
    Sender(Container& container):m_owner(container)
    {
    }
    
    void send(string& msg)
    {
        char s_num[16];
        snprintf(s_num, 16, "%d",num);
        msg.append(s_num);
        m_owner.onMsg(&msg);
        num++;
    }
};


#endif /* defined(__App__Test__) */
