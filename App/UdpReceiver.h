//
//  UdpReceiver.h
//  App
//
//  Created by Liu Enze on 10/17/13.
//  Copyright (c) 2013 Liu Enze. All rights reserved.
//

#ifndef __App__UdpReceiver__
#define __App__UdpReceiver__

#include <iostream>
#include "UdpSocket.h"
#include "UdpMsg.h"
#include "Thread.h"
#include "UdpContainer.h"
#include <unordered_map>

class UdpReceiver:public Thread
{
private:
    UdpSocket& udpSocket;
    UdpContainer& container;
    unordered_map<string, UdpSlice**> sliceMap;
    UdpMsg* analyseSlice(UdpSlice* slice);
public:
    UdpReceiver(UdpSocket& socket,UdpContainer& container):udpSocket(socket),container(container)
    {
    }
    
    void receive();
    
    void run()
    {
        while (isRunning) {
            receive();
        }
    }
    
private:
    char buff[BUFF_SIZE];
    char ip[IP_SIZE];
};
#endif /* defined(__App__UdpReceiver__) */
