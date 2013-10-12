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

static int DEFAULT_SIZE = 10000;

template <typename Msg>
class Fifo
{
private:
    deque<Msg*>* m_deque=NULL;
    int m_size = 0;
    int m_maxSize = 0;
protected:
    ~Fifo()
    {
        m_deque->clear();
        delete m_deque;
        m_deque = NULL;
        m_size = 0;
        m_maxSize = 0;
    }
    
    Fifo(int size)
    {
        m_deque = new deque<Msg*>();
        m_maxSize = size;
    }
    
    void push(Msg* msg)
    {
        //if the size is larger than limit
        //throw it away
        if(m_size<m_maxSize)
        {
            m_deque->push_front(msg);
            m_size++;
        }
    }
    
    Msg* pop()
    {
        Msg* cur = m_deque->back();
        if(cur != NULL)
        {
            m_deque->pop_back();
            m_size--;
        }
        return cur;
    }

public:
    int size()
    {
        return m_size;
    }
    
    bool isEmpty()
    {
        return m_size==0;
    }
};

template <typename Msg>
class BlockingQueue:public Fifo<Msg>
{
private:
    Mutex mutex;
    Condition condition;
public:
    BlockingQueue(int size = DEFAULT_SIZE):Fifo<Msg>(size)
    {
    }
    
    Msg* pop()
    {
        Lock lock(mutex);
        if (Fifo<Msg>::isEmpty()) {
            condition.wait(mutex);
        }
        return Fifo<Msg>::pop();
    }
    
    void push(Msg* msg)
    {
        Lock lock(mutex);
        
        if (Fifo<Msg>::isEmpty()) {
            condition.notify();
        }
        
        Fifo<Msg>::push(msg);
        return;
    }
};

#endif /* defined(__App__Queue__) */
