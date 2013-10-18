//
//  UdpMsg.h
//  App
//
//  Created by Liu Enze on 10/17/13.
//  Copyright (c) 2013 Liu Enze. All rights reserved.
//

#ifndef __App__UdpMsg__
#define __App__UdpMsg__

#include <iostream>
#include "UdpSlice.h"

using namespace std;

class UdpMsg
{
public:
    int code;
    string ipAddr;
    string data;
    string userAccount;
public:
    UdpSlice** makeSlice();
    static UdpMsg* combineSlice(UdpSlice** slices);
};

#endif /* defined(__App__UdpMsg__) */
