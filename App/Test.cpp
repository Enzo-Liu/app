//
//  Test.cpp
//  App
//
//  Created by Liu Enze on 10/12/13.
//  Copyright (c) 2013 Liu Enze. All rights reserved.
//

#include "Test.h"

void testQueue(int testSize)
{
    BlockingQueue<string> t_queue(testSize);
    
    char* c_str = new char[1024];
    memset(c_str, 0, 1024);
    string msg(c_str);
    time_t t1 = clock();
    for (int i=0; i<testSize; i++) {
        t_queue.push(&msg);
    }
    time_t t2 = clock();
    for (int i=0; i<testSize; i++) {
        t_queue.pop();
    }
    time_t t3 = clock();
    cout<<"the cost time is" <<t2-t1<<"&"<<t3-t2<<endl;
    cout<<"current size is " << t_queue.size()<<endl;
    delete[] c_str;
    c_str = NULL;
}

class QueueThread:public Thread
{
    BlockingQueue<string>& _queue;
    bool m_isSend;
    int m_repeatTime=0;
    string *m_msg=NULL;
public:
    QueueThread(BlockingQueue<string>& t_queue,bool isSend,int repeatTime,string* msg):
    _queue(t_queue),m_isSend(isSend),m_repeatTime(repeatTime),m_msg(msg)
    {
    }
    void run()
    {
        time_t t1 = clock();
        for (int i=0; i<m_repeatTime; i++) {
            if (m_isSend) {
                _queue.push(m_msg);
            }
            else
            {
                _queue.pop();
            }
        }
        time_t t2 = clock();
        cout<<"the cost time is" <<t2-t1<<endl;
        cout<<"current size is " << _queue.size()<<endl;
    }
};
void testMutilQueue(int testSize )
{
    BlockingQueue<string> t_queue(testSize);
    char* c_str = new char[1024];
    memset(c_str, 0, 1024);
    string msg(c_str);
    QueueThread thread1(t_queue,true,testSize,&msg);
    QueueThread thread2(t_queue,false,testSize,NULL);
    
    thread1.start();
    thread2.start();
    
    sleep(100);
    delete[] c_str;
}

