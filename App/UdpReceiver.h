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
#include "UdpSlice.h"
#include "Thread.h"
#include "UdpContainer.h"
#include <unordered_map>

class UdpReceiver:public Thread
{
private:
    UdpSocket& udpSocket;
    UdpContainer& container;
    unordered_map<string, UdpSlice**> sliceMap;
    void analyseSlice(UdpSlice* slice);
public:
    UdpReceiver(UdpSocket& socket,UdpContainer& container):udpSocket(socket),container(container)
    {
    }
    
    UdpSlice * decode(char*buff,int length,char*ip,int port);
    
    void receive();
    
    void run()
    {
        while (isRunning) {
            receive();
        }
    }
};
#endif /* defined(__App__UdpReceiver__) */
