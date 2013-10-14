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

using namespace std;


class Receive:public Thread
{
    UdpSocket& m_udp;
public:
    Receive(UdpSocket& udpSocket):m_udp(udpSocket)
    {
    }
    void run()
    {
        while (true) {
            char buff[4096];
            int length = 0;
            char ip[16];
            int port = 0;
            
            m_udp.receive((char**)&buff, &length, (char**)&ip, &port);
            
            
            if (length!=-1) {
                cout<<buff<<endl<<"ip is "<<ip<<",port is "<<port<<endl;
            }
            
        }
    }
};

int main(int argc, const char * argv[])
{
    Container container;
    container.start();
    Sender sender(container);
    for (int i=0; i<10; i++) {
        string* msg = new string("the msg is number");
        sender.send(*msg);
    }
    container.stop();
    //int testSize = 1000000;
    //testQueue(testSize);
    //testMutilQueue(testSize);
    UdpSocket socket1;
    UdpSocket socket2;
    socket1.init("0.0.0.0", 18080);
    
    socket2.init("0.0.0.0", 18081);
    Receive re(socket2);
    re.start();
    for (int i=0; i<10000; i++) {
        socket1.send("Hello", sizeof("Hello"), "0.0.0.0", 18081);
    }
   
    sleep(200);
    
    return 0;
}

