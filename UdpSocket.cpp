//
//  UdpSocket.cpp
//  App
//
//  Created by Liu Enze on 10/12/13.
//  Copyright (c) 2013 Liu Enze. All rights reserved.
//

#include "UdpSocket.h"

UdpSocket::UdpSocket()
{
    if( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1 )
    {
        printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);
        exit(0);
    }
    
    int err = -1;        /* 返回值 */
    int snd_size = 0;   /* 发送缓冲区大小 */
    int rcv_size = 0;    /* 接收缓冲区大小 */
    socklen_t optlen;    /* 选项值长度 */
    
    /*
     * 先读取缓冲区设置的情况
     * 获得原始发送缓冲区大小
     */
    optlen = sizeof(snd_size);
    err = getsockopt(sockfd, SOL_SOCKET, SO_SNDBUF,&snd_size, &optlen);
    if(err<0){
        printf("获取发送缓冲区大小错误\n");
    }
    /*
     * 打印原始缓冲区设置情况
     */
    
    /*
     * 获得原始接收缓冲区大小
     */
    optlen = sizeof(rcv_size);
    err = getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &rcv_size, &optlen);
    if(err<0){
        printf("获取接收缓冲区大小错误\n");
    }
    
    /*
     * 设置发送缓冲区大小
     */
    snd_size = SOCKET_BUFF_SIZE;    /* 发送缓冲区大小为400K */
    optlen = sizeof(snd_size);
    err = setsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &snd_size, optlen);
    if(err<0){
        printf("设置发送缓冲区大小错误\n");
    }
    
    /*
     * 设置接收缓冲区大小
     */
    rcv_size = SOCKET_BUFF_SIZE;    /* 接收缓冲区大小为400K */
    optlen = sizeof(rcv_size);
    err = setsockopt(sockfd,SOL_SOCKET,SO_RCVBUF, (char *)&rcv_size, optlen);
    if(err<0){
        printf("设置接收缓冲区大小错误\n");
    }
    
}

UdpSocket::~UdpSocket()
{
    close(sockfd);
}

void UdpSocket::init(const char *ip, int port)
{
    bzero((char *)&host_addr, sizeof(host_addr));
    host_addr.sin_family = AF_INET;
    host_addr.sin_addr.s_addr = htonl(inet_addr(ip));
    host_addr.sin_port = htons(port);
    
    if( bind(sockfd, (struct sockaddr*)&host_addr, sizeof(host_addr)) == -1){
        printf("bind socket error: %s(errno: %d)\n",strerror(errno),errno);
        exit(0);
    }
}

void UdpSocket::receive(char *buff,int *length,char* ip, int* port)
{
    memset(buff, 0, BUFF_SIZE);
    memset(ip, 0, IP_SIZE);
    struct sockaddr_in addr;
    int addr_len =sizeof(struct sockaddr_in);
    long size = recvfrom(sockfd, buff, BUFF_SIZE, 0, (struct sockaddr *)&addr, (socklen_t *)&addr_len);
    if (size==-1||size==BUFF_SIZE) {
        * length = -1;
        return;
    }
    *length=(int)size;
    snprintf(ip, IP_SIZE,"%s",inet_ntoa(addr.sin_addr));
    *port = ntohs(addr.sin_port);
}

void UdpSocket::send(char *buff, int length, const char *ip, int port)
{
    struct sockaddr_in dest_addr;
    bzero((char *)&dest_addr, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_addr.s_addr = htonl(inet_addr(ip));
    dest_addr.sin_port = htons(port);
    
    if(sendto(sockfd,buff,length,0,(struct sockaddr *)&dest_addr,sizeof(dest_addr))==-1)
    {
        printf("send msg error: %s(errno: %d)\n",strerror(errno),errno);
    }
}

