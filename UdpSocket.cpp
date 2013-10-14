//
//  UdpSocket.cpp
//  App
//
//  Created by Liu Enze on 10/12/13.
//  Copyright (c) 2013 Liu Enze. All rights reserved.
//

#include "UdpSocket.h"

void UdpSocket::init(const char *ip, int port)
{
    if( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1 )
    {
        printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);
        exit(0);
    }
    bzero((char *)&host_addr, sizeof(host_addr));
    host_addr.sin_family = AF_INET;
    host_addr.sin_addr.s_addr = inet_addr(ip);
    host_addr.sin_port = htons(port);
    
    if( bind(sockfd, (struct sockaddr*)&host_addr, sizeof(host_addr)) == -1){
        printf("bind socket error: %s(errno: %d)\n",strerror(errno),errno);
        exit(0);
    }
    
    int socket_buf_size = 10000;
    if(setsockopt( sockfd, SOL_SOCKET,SO_SNDBUF, &socket_buf_size , sizeof(socket_buf_size) )< 0)
    {
        perror("setsockopt()");
    }

    
}

void UdpSocket::receive(char** buff, int* length,char **ip, int* port)
{
    struct sockaddr_in addr;
    int addr_len =sizeof(struct sockaddr_in);
    long size = recvfrom(sockfd, *buff, sizeof(*buff), 0, (struct sockaddr *)&addr, (socklen_t *)&addr_len);
    if (size==-1) {
        * length = -1;
        return;
    }
    snprintf(*ip, sizeof(*ip),"%s",inet_ntoa(addr.sin_addr));

}

void UdpSocket::send(char *buff, int length, const char *ip, int port)
{
    struct sockaddr_in dest_addr;
    bzero((char *)&dest_addr, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_addr.s_addr = inet_addr(ip);
    dest_addr.sin_port = htons(port);
    
    if(sendto(sockfd,buff,length,0,(struct sockaddr *)&dest_addr,sizeof(dest_addr))==-1)
    {
        printf("send msg error: %s(errno: %d)\n",strerror(errno),errno);
    }
}

