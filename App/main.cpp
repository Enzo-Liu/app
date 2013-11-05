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
private:
    int size = 0;
public:
    void onMsg(UdpMsg* msg)
    {
        size++;
        if(size%100==99)
        cout<<"msgId is "<<msg->msgId<<"size is "<<size<<endl;
        delete msg;
        msg = NULL;
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
    msg.data = "test send Msg with size more than 1k:";
    for (int i=0; i<1000; i++) {
        msg.data.append("buff to set again and again;");
    }
    msg.ipAddr = "0.0.0.0:38080";
    msg.userAccount = "liu";
    msg.code = 1;
    time_t t1 = clock();
    for (int i=0; i<300000; i++) {
        msg.msgId = i;
        se.send(msg);
    }
    time_t t2 = clock();
    cout<<"send cost time is "<<t2-t1<<endl;
    sleep(200);
    
    return 0;
}

