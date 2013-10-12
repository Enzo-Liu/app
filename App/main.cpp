//
//  main.cpp
//  App
//
//  Created by Liu Enze on 8/23/13.
//  Copyright (c) 2013 Liu Enze. All rights reserved.
//

#include <iostream>
#include "Queue.h"
#include "Thread.h"
#include <unistd.h>

using namespace std;

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



int main(int argc, const char * argv[])
{
    Container container;
    container.start();
    Sender sender(container);
    for (int i=0; i<10; i++) {
        string* msg = new string("the msg is number");
        sender.send(*msg);
        sleep(1);
    }
    container.stop();
    return 0;
}

