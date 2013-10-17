//
//  UdpSocket.h
//  App
//
//  Created by Liu Enze on 10/12/13.
//  Copyright (c) 2013 Liu Enze. All rights reserved.
//

#ifndef __App__UdpSocket__
#define __App__UdpSocket__

#include <iostream>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "UdpConst.h"

class UdpSocket
{
private:
    int sockfd;
    struct sockaddr_in host_addr;
public:
    UdpSocket();
    ~UdpSocket();
    void init(const char * ip,int port);
    void send(char* buff,int length,const char * ip,int port);
    void receive(char* buff, int* length,char *ip, int* port);
};

#endif /* defined(__App__UdpSocket__) */
