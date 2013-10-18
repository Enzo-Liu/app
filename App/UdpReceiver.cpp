//
//  UdpReceiver.cpp
//  App
//
//  Created by Liu Enze on 10/17/13.
//  Copyright (c) 2013 Liu Enze. All rights reserved.
//

#include "UdpReceiver.h"

UdpMsg* UdpReceiver::analyseSlice(UdpSlice* slice)
{
    UdpMsg* msg = NULL;
    int total=slice->totalNum;
    int cur = slice->sliceId;
    
    if (total==1) {
        
        msg = UdpMsg::combineSlice(&slice);
        delete slice;
        slice = NULL;
        return msg;
    }
    string key;
    slice->genKey(key);
    UdpSlice** slices = sliceMap[key];
    if (slices==NULL) {
        slices = new UdpSlice*[total];
        sliceMap.insert(make_pair(key,slices));
        slices[cur]=slice;
        return NULL;
    }
    slices[cur]=slice;
    for (int i = 0; i<total; i++) {
        if (slices[i]==NULL) {
            return NULL;
        }
    }
    
    msg = UdpMsg::combineSlice(slices);
    sliceMap.erase(key);
    
    for (int i = 0; i<total; i++) {
        delete slices[i];
        slices[i]=NULL;
    }
    delete[] slices;
    slices = NULL;
    return msg;
};

void UdpReceiver::receive()
{
    
    memset(buff, 0, BUFF_SIZE);
    int length = 0;
    memset(ip, 0, IP_SIZE);
    int port = 0;
    udpSocket.receive(buff, &length, ip, &port);
    
    if (length==-1 || length==BUFF_SIZE)
        return;
    
    UdpSlice *slice = UdpSlice::decode(buff,length,ip,port);
    if (slice==NULL) return;
    
    UdpMsg* msg = analyseSlice(slice);
    if (msg!= NULL) {
        container.onMsg(msg);
    }
};


