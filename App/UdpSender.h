//
//  UdpSender.h
//  App
//
//  Created by Liu Enze on 10/18/13.
//  Copyright (c) 2013 Liu Enze. All rights reserved.
//

#ifndef __App__UdpSender__
#define __App__UdpSender__

#include <iostream>
#include "Thread.h"
#include "Queue.h"
#include "UdpSlice.h"
#include "UdpSocket.h"
#include "UdpMsg.h"

class UdpSender:public Thread
{
private:
    UdpSocket& socket;
    BlockingQueue<UdpSlice> sendQueue;
    void send(UdpSlice& slice);
public:
    UdpSender(UdpSocket& socket):socket(socket)
    {
    }
    
    void send(UdpMsg& udpMsg);
    
    void run()
    {
        UdpSlice* slice = NULL;
        while (isRunning) {
            slice = sendQueue.pop();
            if (slice != NULL) {
                send(*slice);
                usleep(1);
                delete slice;
                slice = NULL;
            }
        }
    }
    
private:
    char buff[BUFF_SIZE];
};
#endif /* defined(__App__UdpSender__) */
