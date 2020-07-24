// FILE: DPQueue.cpp
//  Name: Anneka Bath- CS 3358
// IMPLEMENTS: p_queue (see DPQueue.h for documentation.)
//
// INVARIANT for the p_queue class:
//   1. The number of items in the p_queue is stored in the member
//      variable used.
//   2. The items themselves are stored in a dynamic array (partially
//      filled in general) organized to follow the usual heap storage
//      rules.
//      2.1 The member variable heap stores the starting address
//          of the array (i.e., heap is the array's name). Thus,
//          the items in the p_queue are stored in the elements
//          heap[0] through heap[used - 1].
//      2.2 The member variable capacity stores the current size of
//          the dynamic array (i.e., capacity is the maximum number
//          of items the array currently can accommodate).
//          NOTE: The size of the dynamic array (thus capacity) can
//                be resized up or down where needed or appropriate
//                by calling resize(...).
// NOTE: Private helper functions are implemented at the bottom of
// this file along with their precondition/postcondition contracts.

#include <cassert>   // provides assert function
#include <iostream>  // provides cin, cout
#include <iomanip>   // provides setw
#include <cmath>     // provides log2
#include "DPQueue.h"

using namespace std;

namespace CS3358_SP18A7
{
   // EXTRA MEMBER FUNCTIONS FOR DEBUG PRINTING
    void p_queue::print_tree(const char message[], size_type i) const
    {
        const char NO_MESSAGE[] = "";
        size_type depth;

        if (message[0] != '\0')
            cout << message << endl;
        if (i >= used)
            cout << "(EMPTY)" << endl;
        else
        {
            depth = size_type( log( double(i + 1) ) / log(2.0) + 0.1 );
            if (2 * i + 2 < used)
                print_tree(NO_MESSAGE, 2 * i + 2);
            cout << setw (depth * 3) << "";
            cout << heap[i].data;
            cout << '(' << heap[i].priority << ')' << endl;
            if (2 * i + 1 < used)
                print_tree(NO_MESSAGE, 2 * i + 1);
        }
    }

    void p_queue::print_array(const char message[]) const
    {
        if (message[0] != '\0')
            cout << message << endl;
        if (used == 0)
            cout << "(EMPTY)" << endl;
        else
            for (size_type i = 0; i < used; i++)
                cout << heap[i].data << ' ';
    }

   // CONSTRUCTORS AND DESTRUCTOR

    p_queue::p_queue(size_type initial_capacity): capacity(initial_capacity), used(0)
    {
        assert (initial_capacity > 0);
        this->heap = new ItemType[capacity];   
    }

    p_queue::p_queue(const p_queue& src)
    {
        heap = new ItemType[capacity];
        for (size_type i = 0; i < used; i++) 
            heap[i] = src.heap[i];
    }

    p_queue::~p_queue()
    {     
        delete [] heap;
    }

   // MODIFICATION MEMBER FUNCTIONS
    p_queue& p_queue::operator=(const p_queue& rhs)
    {
        resize(rhs.capacity);
        used = rhs.used;
        for (size_type i = 0; i < rhs.used; i++)
        {
            heap[i] = rhs.heap[i];
        }
        return *this;
    }

    void p_queue::push(const value_type& entry, size_type priority)
    {
        if (used == capacity)
            resize(capacity * 2);
        heap[used].priority = priority;
        heap[used].data = entry;
        used++;
        if (used > 1)
        {
            size_type heap_hieght= 0;
            while (pow(2,heap_hieght) <= (used - 1))
                heap_hieght++;
            if (heap_hieght == (used - 1))
            {
                size_type used_parent = parent_index(used - 1);
                if (heap[used_parent].priority > heap[used_parent / 2].priority)
                    swap_with_parent(used - 1);
                else if (heap[used_parent].data > heap[used_parent / 2].data)
                    swap_with_parent(used - 1);
            }
        }
    }

    void p_queue::pop()
    {
        assert( size() > 0 ); 
        if(used == 1) 
        {
            used--;
            return;
        }
        heap[0].data = heap[used-1].data;
        heap[0].priority = heap[used-1].priority;
        size_type index_child = big_child_index(0);
        size_type priority_child = big_child_priority(0);
        used--;
        if (used > 1)
        {
            if (heap[0].priority < priority_child)
            {
                heap[0].data = heap[index_child].data;
                heap[0].priority = heap[index_child].priority;
            }
            else if (heap[0].data < heap[index_child].data)
            {    
                heap[0].data = heap[index_child].data;
                heap[0].priority = heap[index_child].priority;
            }
        }
        size_type i = 0;
        while (!is_leaf(i) && i <= used) 
        {
           if(heap[i].priority < heap[2 * i + 1].priority)
               swap_with_parent(2 * i + 1);
           else if (heap[i].data < heap[2 * i + 1].data)
               swap_with_parent(2 * i + 1);
           i = 2 * i + 1;
        }
    }

   // CONSTANT MEMBER FUNCTIONS

    p_queue::size_type p_queue::size() const
    {
        return used;
    }

    bool p_queue::empty() const
    {
        return (used == 0);
    }

    p_queue::value_type p_queue::front() const
    {
        assert (size() > 0);
        return heap[0].data; 
    }

   // PRIVATE HELPER FUNCTIONS
    void p_queue::resize(size_type new_capacity)
    {
        ItemType * dataCopy = new ItemType [new_capacity];
        for(size_type i = 0; i < used; i++) 
            dataCopy[i] = heap[i]; 
        delete heap;
        this->capacity = new_capacity;
        this->heap = dataCopy;   
        dataCopy = 0;
    }
   
    bool p_queue::is_leaf(size_type i) const
    {
        assert (i < used);
        return ((i * 2 + 1) >= used);
    }

    p_queue::size_type
    p_queue::parent_index(size_type i) const
    {    
        assert (i > 0 && i < used);
        return ((i - 1) / 2);
    }
    
    p_queue::size_type
    p_queue::parent_priority(size_type i) const
    {
        assert ((i > 0) && (i < used));
        return heap[(i - 1) / 2].priority;
    }

    p_queue::size_type
    p_queue::big_child_index(size_type i) const
    {
        assert(is_leaf(i) == false);
        int left_child = (2 * i) + 1;
        int right_child = (2 * i) + 2;
        if (heap[left_child].priority < heap[right_child].priority)
            return right_child; 
        else if (heap[left_child].data < heap[right_child].data)
            return right_child;
        else
            return left_child;
    }
    
    p_queue::size_type
    p_queue::big_child_priority(size_type i) const
    {
        assert(is_leaf(i) == false);
        int left_child = (2 * i) + 1;
        int right_child = (2 * i) + 2;
        if (heap[left_child].priority < heap[right_child].priority)
            return heap[right_child].priority; 
        else if (heap[left_child].data < heap[right_child].data)
            return heap[right_child].priority; 
        else
            return heap[left_child].priority;
    }

    void p_queue::swap_with_parent(size_type i)
    {
        assert ((i > 0) && (i < used));
        ItemType temp = heap[parent_index(i)];
        temp.data = heap[i].data;
        temp.priority = heap[i].priority;
        heap[i].priority = temp.priority;
        heap[i].data = temp.data;
    }
}


