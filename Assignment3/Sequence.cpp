// FILE: Sequence.cpp
//  Name: Anneka Bath- CS 3358
//  Date: 2/7/18
// CLASS IMPLEMENTED: sequence (see sequence.h for documentation)
// INVARIANT for the sequence ADT:
//   1. The number of items in the sequence is in the member variable
//      used;
//   2. The actual items of the sequence are stored in a partially
//      filled array. The array is a dynamic array, pointed to by
//      the member variable data. For an empty sequence, we do not
//      care what is stored in any of data; for a non-empty sequence
//      the items in the sequence are stored in data[0] through
//      data[used-1], and we don't care what's in the rest of data.
//   3. The size of the dynamic array is in the member variable
//      capacity.
//   4. The index of the current item is in the member variable
//      current_index. If there is no valid current item, then
//      current_index will be set to the same number as used.
//      NOTE: Setting current_index to be the same as used to
//            indicate "no current item exists" is a good choice
//            for at least the following reasons:
//            (a) For a non-empty sequence, used is non-zero and
//                a current_index equal to used indexes an element
//                that is (just) outside the valid range. This
//                gives us a simple and useful way to indicate
//                whether the sequence has a current item or not:
//                a current_index in the valid range indicates
//                that there's a current item, and a current_index
//                outside the valid range indicates otherwise.
//            (b) The rule remains applicable for an empty sequence,
//                where used is zero: there can't be any current
//                item in an empty sequence, so we set current_index
//                to zero (= used), which is (sort of just) outside
//                the valid range (no index is valid in this case).
//            (c) It simplifies the logic for implementing the
//                advance function: when the precondition is met
//                (sequence has a current item), simply incrementing
//                the current_index takes care of fulfilling the
//                postcondition for the function for both of the two
//                possible scenarios (current item is and is not the
//                last item in the sequence).

#include <cassert>
#include "Sequence.h"
#include <iostream>
using namespace std;

namespace CS3358_SP2018
{
    
   sequence::sequence(size_type initial_capacity): capacity(initial_capacity), used(0), current_index(0)
   {
        assert(initial_capacity > 0);
        this->data = new value_type[capacity];
   }

   sequence::sequence(const sequence& source): used(source.used), current_index(source.current_index),capacity(source.capacity)
   {
        this->data = new value_type[capacity];
        for (size_type i = 0; i < used; i++) {
            this->data[i] = source.data[i];
        }
   }

   sequence::~sequence()
   {
        delete [] data;
   }

   void sequence::resize(size_type new_capacity)
   {
        assert(new_capacity > 0);
        if (new_capacity < 1 || new_capacity < used) 
        {
            if (used > 0)
                new_capacity = used;
            else
                new_capacity = 1;
        }
        else if (new_capacity == capacity)
        {
            this->capacity = new_capacity + 1;            
        }      
        else if (new_capacity != capacity)
        {
            this->capacity = new_capacity;
        }
        value_type *copyData = new value_type[capacity];
        for (size_type i = 0; i < used; i++) 
        {
            copyData[i] = data[i]; 
        }
        delete [] data; 
        this->data = copyData; // connects pointer copyData to data
   }

    void sequence::start() 
    {
        if (used > 0) 
        {
            this->current_index = 0;
        }
    }

   void sequence::advance()
   {
        assert(is_item());
        current_index++;
   }

   void sequence::insert(const value_type& entry)
   {
        if (used == capacity) 
        {
            size_type new_capacity = (int)((capacity * 1.25) + 1);
            resize(new_capacity);
        }
        else if (current_index == used && used == 0) 
        {
            this->data[0] = entry; // insert entry in index 0
            this->used++;
            
            return;
        }
        else if (current_index == used && used > 0) 
        {
            this->current_index = 0; 
        }
        else
        {
            for(int i = used; i > current_index; i--)
            {
                data[i] = data[i - 1];//shifts index space before the last current index
            }
            this->data[current_index] = entry; //inserts entry at current index  
            this->used ++;
        }
    }

   void sequence::attach(const value_type& entry)
   {
        if (used == capacity) 
        {
            size_type new_capacity = (int)((capacity * 1.25) + 1);
            resize(new_capacity);
        }
        else if (used == current_index) 
        {
            this->data[current_index] = entry; 
            this->used++;
            return;
        }
        else
        {
            for(int i = used; i > current_index; i--) 
            {
                data[i] = data[i-1];
            }
            if(used >0)
            {
                this->data[current_index + 1] = entry;//insert after current_index
                this->used ++;
                this->current_index++;//current_index is now entry just inserted
            }
            else
            {
                this->data[current_index] = entry;//insert at hopefully index 0
                this->used ++;  
            }
        }
   }

   void sequence::remove_current()
   {
        assert(is_item());
        for (int i = current_index; i < used; i++) 
        {
            this->data[i] = data[i + 1];
            if (used > 0)
            {
                this->current_index = data[i];//updates current index to next element in data
            }
        }  
        this->used--;
   }

   sequence& sequence::operator=(const sequence& source)
   {
        if (this == &source)
        {
            return *this;
        } 
        if (data == NULL)
        {
            exit(0);
        }
        else 
        { // If sequence is not being set to itself
            this->used = source.used;
            this->current_index = source.current_index;
            this->capacity = source.capacity;
            this->data = new value_type[capacity]; 
            for (size_type i = 0; i < used; i++) 
            {
                this->data[i] = source.data[i];
            }
        }
        
        return *this;
   }

   sequence::size_type sequence::size() const
   {
        return used;
   }

   bool sequence::is_item() const
   {
        if (current_index == used) 
        {
            return false;
        }
        return true;
   }

   sequence::value_type sequence::current() const
    {
        assert(is_item());
        return data[current_index];
    }

}

