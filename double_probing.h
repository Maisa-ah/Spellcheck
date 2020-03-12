//Maisa Ahmad
//File will implement double probing to handle collisions. Will rehash to a table size that is positive and prime and at least twice the size of the old table size. File edited from quadratic probing to accomidate double probing instead. Changed function will be FindPos() because double probing handles probing and finding positions differently so we will override. Added
#ifndef DOUBLE_PROBING_H
#define DOUBLE_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>

//Double hashing implementation.
template <typename HashedObj>
class HashTableDouble : public HashTable <HashedObj>
{
    
protected:
    
    //inherited functions, overridden FindPos() for different probing method
    //finds a position to place element x, probes til empty place for x found
    size_t FindPos(const HashedObj & x) const override {
        size_t offset = InternalHash2(x);//call double hash function r - (x mod r)
        size_t current_pos = this->InternalHash(x);
        
        this->probe_count_ ++; //count first probe done
        
        while (this->array_[current_pos].info_ != this->EMPTY &&
               this->array_[current_pos].element_ != x) {
            this->probe_count_++;//count probes til position of x found
            this->collision_count_++;//counts collisions we run into before position of x found
            current_pos +=offset;
            if (current_pos >= this->array_.size())
                current_pos -= this->array_.size();
        }
        return current_pos;
    }

    //73 best so far, smallest num of collisions
    //89 57 71 79
    //threshold around 107
    size_t InternalHash2(const HashedObj & x) const {
        static std::hash<HashedObj> hf;
        return 73 - (hf(x) % 73);
        //double hash function r - (x mod r)
    }
    
};

#endif  // DOUBLE_PROBING_H
