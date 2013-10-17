//
//  UdpSlice.h
//  App
//
//  Created by Liu Enze on 10/12/13.
//  Copyright (c) 2013 Liu Enze. All rights reserved.
//

#ifndef __App__UdpSlice__
#define __App__UdpSlice__

#include <iostream>

using namespace std;

class UdpSlice
{
public:
    int msgId;
    int sliceId;
    int totalNum;
    char ip[16];
    int port;
    char data[1000]={0};
    void genKey(string& key);
    void encode(char* buff,char * ip,int port);
    bool decode(char*buff,int length,char * ip,int port);
};

#endif /* defined(__App__UdpSlice__) */
