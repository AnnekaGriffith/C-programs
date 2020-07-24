/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cnPtrQueue.cpp
 * Author: Anneka Bath
 * 
 * Created on March 1, 2018, 6:28 PM
 */

#include "cnPtrQueue.h"
#include "cnPtrQueue.h"
#include <cassert>
using namespace std;

namespace CS3358_SP18_A5P2
{
    cnPtrQueue::cnPtrQueue() 
    {
        numItems = 0;
    }
    
    void cnPtrQueue::push(CNode* cnPtr)
    {
        inStack.push(cnPtr);
        numItems++;
    }
    
    void cnPtrQueue:: pop()
    {
        assert( !inStack.empty() || !outStack.empty() ); 
        if(outStack.empty()) 
        {
            while ( !inStack.empty() ) 
                outStack.push(inStack.top()); 
                inStack.pop(); 
        }
        outStack.pop();
        numItems--;
    }
    
    CNode* cnPtrQueue:: front() 
    {
        assert(!inStack.empty() || !outStack.empty()); 
        if (outStack.empty())
        { 
            while ( !inStack.empty() ) 
            {
                outStack.push(inStack.top()); 
                inStack.pop();
            }
        }
        return outStack.top();
    }

    bool cnPtrQueue::empty() const
    {
        return outStack.empty() && inStack.empty();
    }
}
