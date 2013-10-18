//
//  Udp.h
//  App
//
//  Created by Liu Enze on 10/18/13.
//  Copyright (c) 2013 Liu Enze. All rights reserved.
//

#ifndef __App__Udp__
#define __App__Udp__

#include <iostream>

using namespace std;

class Udp
{
private:
    
public:
    Udp(string ip,int port);
    void init();
    void send(string data);
};
#endif /* defined(__App__Udp__) */
