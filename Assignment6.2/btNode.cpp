/* 
 * File:   btNode.cpp
 * Author: Anneka Bath
 * 
 * Created on March 28, 2018, 6:40 PM
 */

#include "btNode.h"
#include <cassert>

void dumpToArrayInOrder(btNode* bst_root, int* dumpArray)
{
   if (bst_root == 0) return;
   int dumpIndex = 0;
   dumpToArrayInOrderAux(bst_root, dumpArray, dumpIndex);
}

void dumpToArrayInOrderAux(btNode* bst_root, int* dumpArray, int& dumpIndex)
{
   if (bst_root == 0) return;
   dumpToArrayInOrderAux(bst_root->left, dumpArray, dumpIndex);
   dumpArray[dumpIndex++] = bst_root->data;
   dumpToArrayInOrderAux(bst_root->right, dumpArray, dumpIndex);
}

void tree_clear(btNode*& root)
{
   if (root == 0) return;
   tree_clear(root->left);
   tree_clear(root->right);
   delete root;
   root = 0;
}

int bst_size(btNode* bst_root)
{
   if (bst_root == 0) return 0;
   return 1 + bst_size(bst_root->left) + bst_size(bst_root->right);
}
void bst_insert(btNode*& bst_root, int insInt)
{   
    if (bst_root == 0)
    {   
        btNode *newNode = new btNode;
        newNode->data = insInt;
        newNode->left = 0;
        newNode->right = 0;
        bst_root = newNode;
        return;
    }
    btNode *cursor = bst_root;
    while (cursor != 0)
    {
        if (insInt == cursor->data)
        {
            cursor->data = insInt;
            return;
        }
        else if(insInt < cursor->data)
            {
                if (cursor->left == 0)
                {
                    btNode* newNode = new btNode;
                    newNode->data = insInt;
                    newNode->left = 0;
                    newNode->right = 0;
                    cursor->left = newNode;
                    return;
                }
                else
                {
                    cursor = cursor->left;
                    continue; 
                }
            }
        else if (insInt > cursor->data)
            {
                if (cursor->right == 0)
                {
                    btNode* newNode = new btNode;
                    newNode->data = insInt;
                    newNode->left = 0;
                    newNode->right = 0;
                    cursor->right = newNode;

                    return;
                }
                else
                {
                    cursor = cursor->right;
                    continue; 
                }
            }
        }    
}
        
bool bst_remove(btNode*& bst_root, int remInt)
{
    if(bst_root == 0) 
        return false;
    else if(remInt < bst_root->data) 
        return bst_remove(bst_root->left, remInt);
    else if(remInt > bst_root->data) 
        return bst_remove(bst_root->right, remInt);
    else if(remInt == bst_root->data)
    {
        if(bst_root->left == 0)
        { 
            btNode* temp = bst_root;
            bst_root = bst_root->right;
            delete temp;
            return true;
        }
        else
        {
            bst_remove_max(bst_root->left, bst_root->data);
            return true;
        }
    }
    return false;

}
void  bst_remove_max(btNode*& bst_root, int& remInt)
{
    if(bst_root->right != 0) 
        return bst_remove_max(bst_root->right, remInt);
    remInt = bst_root->data;
    bst_root = bst_root->left;
    return;
}

