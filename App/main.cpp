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
            char buff[BUFF_SIZE];
            int length = 0;
            char ip[IP_SIZE];
            int port = 0;
            
            m_udp.receive(buff, &length, ip, &port);
            
            
            if (length!=-1) {
                cout<<"buff is "<<buff<<" length is "<<length<<endl<<"ip is "<<ip<<",port is "<<port<<endl;
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
    socket1.init("0.0.0.0", 38080);
    
    socket2.init("0.0.0.0", 38081);
    Receive re(socket2);
    re.start();
    char content[16];
    snprintf(content, 16, "Hello");
    for (int i=0; i<10; i++) {
        socket1.send(content, 100, "0.0.0.0", 38081);
    }
   
    sleep(200);
    
    return 0;
}

