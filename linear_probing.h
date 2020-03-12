//Maisa Ahmad
//File will implement linear probing to handle collisions. Will rehash to a table size that is positive and prime and at least twice the size of the old table size. File edited from quadratic probing to accomidate linear probing instead. Changed function will be FindPos() because linear probing handles probing and finding positions differently so we will override.
#ifndef LINEAR_PROBING_H
#define LINEAR_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>

//Linear probing implementation.
template <typename HashedObj>
class HashTableLinear : public HashTable <HashedObj>
{
    
protected:
    //inherited functions, overridden FindPos() for different probing method
    //kept offset at 1 to be linear (previous offset made probing grow exponential (i^2))
    
    //finds a position to place element x, probes til empty place for x found
    size_t FindPos(const HashedObj & x) const override {
        size_t offset = 1;
        size_t current_pos = this->InternalHash(x);
        
        this->probe_count_ ++; //count first probe done
        
        while (this->array_[current_pos].info_ != this->EMPTY &&
               this->array_[current_pos].element_ != x) {
            this->probe_count_++;//count probes til position of x found
            this->collision_count_++;//counts collisions we run into before position of x found
            //count should be done before continued traversal - moving to next position
            current_pos += offset;  // Compute ith probe.
            if (current_pos >= this->array_.size())
                current_pos -= this->array_.size();
        }
        return current_pos;
    }
    
    
};

#endif  // LINEAR_PROBING_H

