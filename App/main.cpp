//
//  main.cpp
//  App
//
//  Created by Liu Enze on 8/23/13.
//  Copyright (c) 2013 Liu Enze. All rights reserved.
//

#include <iostream>
#include "Test.h"
#include "UdpSocket.h"
#include "UdpSender.h"
#include "UdpReceiver.h"

using namespace std;


class Con:public UdpContainer
{
public:
    void onMsg(UdpMsg* msg)
    {
        cout<<msg->data<<endl;
    }
};

int main(int argc, const char * argv[])
{
    UdpSocket socket1;
    UdpSocket socket2;
    socket1.init("0.0.0.0", 38080);
    
    socket2.init("0.0.0.0", 38081);
    Con con;
    UdpReceiver re(socket1,con);
    UdpSender se(socket2);
    se.start();
    re.start();
    UdpMsg msg;
    msg.data = "test send Msg";
    msg.ipAddr = "0.0.0.0:38080";
    msg.userAccount = "liu";
    msg.code = 1;
    se.send(msg);
    sleep(200);
    return 0;
}

