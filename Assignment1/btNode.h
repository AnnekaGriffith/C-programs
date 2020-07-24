/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   btNode.h
 * Author: Anneka Bath
 *
 * Created on April 11, 2018, 8:46 PM
 */

#ifndef BTNODE_H
#define BTNODE_H

struct btNode
{
   int data;
   btNode* left;
   btNode* right;
   int bf;  // balance_factor = height_RST - height_LST
};

int  tree_size(btNode* avl_root);
int  height(btNode* root);
bool isAVL(btNode* root);
void tree_print(btNode* ptr, int level);
void tree_print_aux(btNode* root, btNode* ptr, int level);
void tree_clear(btNode*& root);

void avl_insert(btNode*& avl_root, int insInt);
int  avl_insert_aux(btNode*& avl_root, int insInt);
void rebalanceL(btNode*& avl_root);
void rebalanceR(btNode*& avl_root);
void rotateL(btNode*& avl_root);
void rotateR(btNode*& avl_root);

#endif /* BTNODE_H */

