//
//  UdpSender.cpp
//  App
//
//  Created by Liu Enze on 10/18/13.
//  Copyright (c) 2013 Liu Enze. All rights reserved.
//

#include "UdpSender.h"

void UdpSender::send(UdpSlice &slice)
{
    memset(buff, 0, BUFF_SIZE);
    
    slice.encode(buff);
    int length = (int)strlen(buff);
    socket.send(buff, length, slice.ip, slice.port);
}

void UdpSender::send(UdpMsg& udpMsg)
{
    UdpSlice** slices = udpMsg.makeSlice();
    int total = slices[0]->totalNum;
    for (int i=0; i<total; i++) {
        sendQueue.push(slices[i]);
    }
}