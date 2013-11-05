//
//  UdpMsg.cpp
//  App
//
//  Created by Liu Enze on 10/17/13.
//  Copyright (c) 2013 Liu Enze. All rights reserved.
//

#include "UdpMsg.h"

UdpSlice** UdpMsg::makeSlice()
{

    int index = (int)ipAddr.find(':');
    const char* ip = ipAddr.substr(0,index).c_str();
    int port = atoi(ipAddr.substr(index+1,ipAddr.length()-index-1).c_str());
    
    const char* c_data = data.c_str();
    const char* c_userAccount = userAccount.c_str();
    
    //c:code;u:useraccount;data
    int expandSize=(int)userAccount.length()+10;
    int length = expandSize+(int)data.length();
    int sliceNum =(int) length/(SLICE_DATA_SIZE-1);
    sliceNum = (sliceNum*(SLICE_DATA_SIZE-1)==length)?sliceNum:sliceNum+1;
    
    UdpSlice** slices = new UdpSlice*[sliceNum]();
    UdpSlice* slice = NULL;
    int cur = 0;
    for (int i=0; i<sliceNum; i++) {
        slice = new UdpSlice();
        snprintf(slice->ip, IP_SIZE, "%s",ip);
        slice->port = port;
        slice->totalNum = sliceNum;
        slice->sliceId = i+1;
        slice->msgId = msgId;
        if (i==0) {
            snprintf(slice->data, expandSize, "c:%c%c%c%c;u:%s",(char)code,(char)code>>8,(char)code>>16,(char)code>>24,c_userAccount);
            slice->data[expandSize-1]=';';
            snprintf(slice->data+expandSize, SLICE_DATA_SIZE-expandSize-1,"%s",c_data+cur);
            cur = SLICE_DATA_SIZE-expandSize-1;
        }
        else
        {
            snprintf(slice->data, SLICE_DATA_SIZE-1, "%s",c_data+cur);
            cur+=SLICE_DATA_SIZE-1;
        }
        
        slices[i] = slice;
    }
    return slices;
}

UdpMsg* UdpMsg::combineSlice(UdpSlice **slices)
{
    UdpSlice* slice = slices[0];
    int total = slice->totalNum;
    char * t_data = slice->data;
    if (!(t_data[0]=='c'&&t_data[1]==':'&&t_data[6]==';'&&t_data[7]=='u'&&t_data[8]==':')) {
        return NULL;
    }
    UdpMsg& msg = *(new UdpMsg());
    
    msg.code = (((unsigned char)t_data[5])<<24)+(((unsigned char)t_data[4])<<16)+(((unsigned char)t_data[3])<<8)+((unsigned char)t_data[2]);
    msg.msgId = slice->msgId;
    
    char port[16]={0};
    snprintf(port, 15, "%d",slice->port);
    msg.ipAddr = slice->ip;msg.ipAddr+=":";msg.ipAddr+=port;
    
    t_data += 8;
    char * realData = strchr(t_data, ';');
    *realData = 0;realData++;
    msg.userAccount = t_data+1;
    
    msg.data.resize(SLICE_DATA_SIZE*total);
    msg.data = realData;
    
    for (int i =1; i<total; i++) {
        slice = slices[i];
        msg.data +=slice->data;
    }
    return &msg;
}
