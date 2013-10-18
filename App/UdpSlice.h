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
#include "UdpConst.h"

using namespace std;

class UdpSlice
{
public:
    int msgId=0;
    int sliceId=0;
    int totalNum=0;
    char ip[16]={0};
    int port=0;
    char data[SLICE_DATA_SIZE]={0};
    void genKey(string& key);
    void encode(char* buff);
    static UdpSlice * decode(char*buff,int length,char*ip,int port);
};

#endif /* defined(__App__UdpSlice__) */
