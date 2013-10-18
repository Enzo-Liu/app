//
//  UdpSlice.cpp
//  App
//
//  Created by Liu Enze on 10/12/13.
//  Copyright (c) 2013 Liu Enze. All rights reserved.
//

#include "UdpSlice.h"

void UdpSlice::genKey(string &key)
{
    char t_key[32]={0};
    char t_port[5]={0};
    char t_msgId[5]={0};
    char t_totalNum[5]={0};
    int i_port = port,i_msgId = msgId,i_totalNum=totalNum;
    for (int i=0; i<4; i++) {
        t_port[i] = (char)i_port;i_port=i_port>>8;
        t_msgId[i] = (char)i_msgId;i_msgId=i_msgId>>8;
        t_totalNum[i] = (char)i_totalNum;i_totalNum=i_totalNum>>8;
    }
    snprintf(t_key, 32, "i%sp%sm%st%s",ip,t_port,t_msgId,t_totalNum);
    key=t_key;
}

UdpSlice* UdpSlice::decode(char *buff, int length, char *ip, int port)
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

