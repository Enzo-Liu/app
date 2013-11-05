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
    key += "ip:";
    char temp[16];
    key += ip;
    memset(temp,0,16);
    snprintf(temp, 16, ";%s%d","p:",port);
    key += temp;
    memset(temp,0,16);
    snprintf(temp, 16, ";%s%d","m:",msgId);
    key += temp;
    memset(temp,0,16);
    snprintf(temp, 16, ";%s%d","t:",totalNum);
    key += temp;
}

UdpSlice* UdpSlice::decode(char *buff, int length, char *ip, int port)
{
    if(*buff++ != 0x0d||*buff++!= 0x0a||*buff++!= 0x0d||*buff++!= 0x0a)
        return NULL;
    if (*buff++!= 'l') return NULL;
    int total=(unsigned char)*buff++;
    int cur = (unsigned char)*buff++;
    if (cur>total) return NULL;
    int msgId = 0;
    msgId = (((unsigned char)*(buff+3))<<24)+(((unsigned char)*(buff+2))<<16)+(((unsigned char)*(buff+1))<<8)+((unsigned char)*buff);
    buff = buff+4;
    
    UdpSlice* slice = new UdpSlice();
    slice->msgId = msgId;
    slice->sliceId = cur;
    slice->totalNum = total;
    slice->port = port;
    snprintf(slice->ip, IP_SIZE, "%s",ip);
    if (cur==1) {
        int i = 0;
        while (i<SLICE_DATA_SIZE) {
            *(slice->data+i) = *(buff+i);
            i++;
        }
    }
    else
    {
        snprintf(slice->data, SLICE_DATA_SIZE, "%s",buff);
    }
    return slice;
}

void UdpSlice::encode(char *buff)
{
    (*buff++)=0x0d;
    (*buff++)=0x0a;
    (*buff++)=0x0d;
    (*buff++)=0x0a;
    (*buff++)='l';
    (*buff++)=(unsigned char)totalNum;
    (*buff++)=(unsigned char)sliceId;
    int t_msgId = this->msgId;
    for (int i=0; i<4; i++) {
        (*buff++) = (unsigned char)t_msgId;
        t_msgId=t_msgId>>8;
    }
    if (sliceId==1) {
        int i = 0;
        while (i<SLICE_DATA_SIZE) {
            *(buff+i)=*(data+i);
            i++;
        }
        return;
    }
    snprintf(buff, SLICE_DATA_SIZE, "%s",data);
}
