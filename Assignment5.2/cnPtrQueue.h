/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cnPtrQueue.h
 * Author: Anneka Bath
 *
 * Created on March 1, 2018, 6:28 PM
 */

#ifndef CNPTRQUEUE_H
#define CNPTRQUEUE_H

#include <cstdlib>        // for size_t
#include <stack>          // for STL stack template
#include "nodes_LLoLL.h"  // for CNode

namespace CS3358_SP18_A5P2
{
   class cnPtrQueue
   {
   public:
      typedef std::size_t size_type;
      cnPtrQueue();
      bool empty() const;
      size_type size() const; // returns # of items in queue
      CNode* front();
      void push(CNode* cnPtr);
      void pop();
   private:
      std::stack<CNode*> inStack;
      std::stack<CNode*> outStack;
      size_type numItems;     // # of items in queue
   };
}

#endif


