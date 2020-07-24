/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   nodes_LLoLL.h
 * Author: Anneka Bath
 *
 * Created on March 3, 2018, 1:12 PM
 */

#ifndef NODES_LLOLL_H
#define NODES_LLOLL_H

#include <iostream>    // for ostream

namespace CS3358_SP18_A5P2
{
   // child node
   struct CNode
   {
      int data;
      CNode* link;
   };

   // parent node
   struct PNode
   {
      CNode* data;
      PNode* link;
   };

   // toolkit functions for LLoLL based on above node definitions
   void Destroy_cList(CNode*& cListHead);
   void Destroy_pList(PNode*& pListHead);
   void ShowAll_DF(PNode* pListHead, std::ostream& outs);
   void ShowAll_BF(PNode* pListHead, std::ostream& outs);
}

#endif

