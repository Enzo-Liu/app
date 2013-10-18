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
#include "UdpSocket.h"
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

class Receive:public Thread
{
    UdpSocket& m_udp;
public:
    Receive(UdpSocket& udpSocket):m_udp(udpSocket)
    {
    }
    void run()
    {
        while (true) {
            char buff[BUFF_SIZE];
            int length = 0;
            char ip[IP_SIZE];
            int port = 0;
            
            m_udp.receive(buff, &length, ip, &port);
            
            
            if (length!=-1) {
                cout<<"buff is "<<buff<<" length is "<<length<<endl<<"ip is "<<ip<<",port is "<<port<<endl;
            }
            
        }
    }
};


void test();

#endif /* defined(__App__Test__) */
