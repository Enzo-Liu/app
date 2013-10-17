//
//  UdpSlice.cpp
//  App
//
//  Created by Liu Enze on 10/12/13.
//  Copyright (c) 2013 Liu Enze. All rights reserved.
//

#include "UdpSlice.h"

void UdpSlice::genKey(string &key)
{
    char t_key[32]={0};
    char t_port[5]={0};
    char t_msgId[5]={0};
    char t_totalNum[5]={0};
    int i_port = port,i_msgId = msgId,i_totalNum=totalNum;
    for (int i=0; i<4; i++) {
        t_port[i] = (char)i_port;i_port=i_port>>8;
        t_msgId[i] = (char)i_msgId;i_msgId=i_msgId>>8;
        t_totalNum[i] = (char)i_totalNum;i_totalNum=i_totalNum>>8;
    }
    snprintf(t_key, 32, "i%sp%sm%st%s",ip,t_port,t_msgId,t_totalNum);
    key=t_key;
}
