/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   llcpInt.h
 * Author: Anneka Bath
 *
 * Created on February 21, 2018, 7:06 PM
 */

#ifndef LLCPINT_H
#define LLCPINT_H
#include <iostream>

struct Node
{
   int data;
   Node *link;
};

int     FindListLength(Node* headPtr);
bool    IsSortedUp(Node* headPtr);
void    InsertAsHead(Node*& headPtr, int value);
void    InsertAsTail(Node*& headPtr, int value);
void    InsertSortedUp(Node*& headPtr, int value);
bool    DelFirstTargetNode(Node*& headPtr, int target);
bool    DelNodeBefore1stMatch(Node*& headPtr, int target);
void    ShowAll(std::ostream& outs, Node* headPtr);
void    FindMinMax(Node* headPtr, int& minValue, int& maxValue);
double  FindAverage(Node* headPtr);
void    ListClear(Node*& headPtr, int noMsg = 0);
void    MakeDistinctMirrorPairs (Node* &headPtr);


#endif /* LLCPINT_H */

