//
//  UdpReceiver.cpp
//  App
//
//  Created by Liu Enze on 10/17/13.
//  Copyright (c) 2013 Liu Enze. All rights reserved.
//

#include "UdpReceiver.h"

void UdpReceiver::analyseSlice(UdpSlice* slice)
{
    int total=slice->totalNum;
    int cur = slice->sliceId;
    
    if (total==1) {
        //TODO it is a full udpMsg
        return;
    }
    string key;
    slice->genKey(key);
    UdpSlice** slices = sliceMap[key];
    if (slices==NULL) {
        slices = new UdpSlice*[total];
        sliceMap.insert(make_pair(key,slices));
        slices[cur]=slice;
        return;
    }
    slices[cur]=slice;
    for (int i = 0; i<total; i++) {
        if (slices[i]==NULL) {
            return;
        }
    }
    //TODO it has collected all the right msg
    for (int i = 0; i<total; i++) {
        return;
    }
};

void UdpReceiver::receive()
{
    char buff[BUFF_SIZE];
    memset(buff, 0, BUFF_SIZE);
    int length = 0;
    char ip[IP_SIZE];
    memset(ip, 0, IP_SIZE);
    int port = 0;
    udpSocket.receive(buff, &length, ip, &port);
    
    if (length==-1 || length==BUFF_SIZE)
        return;
    
    UdpSlice *slice = decode(buff,length,ip,port);
    if (slice==NULL) return;
    
    analyseSlice(slice);
};

UdpSlice* UdpReceiver::decode(char *buff, int length, char *ip, int port)
{
    if(*buff++ != 0x0d&&*buff++!= 0x0a&&*buff++!= 0x0d&&*buff++!= 0x0a)
        return NULL;
    if (*buff++!= 'l') return NULL;
    int total=*buff++;
    int cur = *buff++;
    if (cur>total) return NULL;
    int msgId = 0;
    msgId += (*(buff+3)<<24)+(*(buff+2)<<16)+(*(buff+1)<<8)+*buff;
    buff = buff+4;
    
    UdpSlice* slice = new UdpSlice();
    slice->msgId = msgId;
    slice->sliceId = cur;
    slice->totalNum = total;
    slice->port = port;
    snprintf(slice->ip, IP_SIZE, "%s",ip);
    snprintf(slice->data, strlen(buff), "%s",buff);
    return slice;
}

