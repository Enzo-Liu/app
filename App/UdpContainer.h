//
//  UdpContainer.h
//  App
//
//  Created by Liu Enze on 10/17/13.
//  Copyright (c) 2013 Liu Enze. All rights reserved.
//

#ifndef App_UdpContainer_h
#define App_UdpContainer_h

#include "UdpMsg.h"

class UdpContainer
{
public:
    virtual void onMsg(UdpMsg *)=0;
};

#endif
