//
//  Queue.h
//  App
//
//  Created by Liu Enze on 10/11/13.
//  Copyright (c) 2013 Liu Enze. All rights reserved.
//

#ifndef __App__Queue__
#define __App__Queue__

#include <deque>
#include <iostream>
#include "Mutex.h"
#include "Condition.h"

using namespace std;

static int DEFAULT_SIZE = 10000000;

template <typename Msg>
class Fifo
{
private:
    deque<Msg*> m_deque;
    int m_size = 0;
    int m_maxSize = 0;
protected:
    ~Fifo()
    {
        m_deque.clear();
        m_size = 0;
        m_maxSize = 0;
    }
    
    Fifo(int size)
    {
        m_maxSize = size;
    }
    
    void push(Msg* msg)
    {
        if (msg==NULL) {
            return;
        }
        //if the size is larger than limit
        //throw it away
        if(m_size<m_maxSize)
        {
            m_deque.push_back(msg);
            m_size++;
        }
        else
        {
            printf("the queue is over flow");
        }
    }
    
    Msg* pop()
    {
        Msg* cur = m_deque.front();
        if(cur != NULL)
        {
            m_deque.pop_front();
            m_size--;
        }
        return cur;
    }

public:
    int size()
    {
        return m_size;
    }
};

template <typename Msg>
class BlockingQueue:public Fifo<Msg>
{
private:
    Mutex mutex;
    Condition notEmpty;
public:
    BlockingQueue(int size = DEFAULT_SIZE):Fifo<Msg>(size)
    {
    }
    
    Msg* pop()
    {
        Lock lock(mutex);
        
        while (Fifo<Msg>::size()==0) {
            notEmpty.wait(mutex);
        }
        
        return Fifo<Msg>::pop();
    }
    
    void push(Msg* msg)
    {
        if (msg==NULL) {
            return;
        }
        Lock lock(mutex);
        
        Fifo<Msg>::push(msg);
        
        if(Fifo<Msg>::size()==1)
        notEmpty.notify();
        
        return;
    }
    
    bool isEmpty()
    {
        Lock lock(mutex);
        return Fifo<Msg>::size()==0;
    }
};

#endif /* defined(__App__Queue__) */
