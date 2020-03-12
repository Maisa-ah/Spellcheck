//Maisa Ahmad
//File will implement quadratic probing to handle collisions. Will rehash to a table size that is positive and prime and at least twice the size of the old table size. Added functions to count the number of elements collisions, probes and table size.

#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>


namespace {
    
    // Internal method to test if a positive number is prime.
    bool IsPrime(size_t n) {
        if( n == 2 || n == 3 )
            return true;
        
        if( n == 1 || n % 2 == 0 )//1 or even #s
            return false;
        
        for( int i = 3; i * i <= n; i += 2 )//prime can only be divided by itself and 1, adds 2 traverse odd #s
            if( n % i == 0 )
                return false;
        
        return true;
    }
    
    
    // Internal method to return a prime number at least as large as n.
    int NextPrime(size_t n) {
        if (n % 2 == 0)
            ++n;//change to odd #
        while (!IsPrime(n)) n += 2;//add 2 to stay odd
        return n;
    }
    
}  // namespace


// Quadratic probing implementation.
template <typename HashedObj>
class HashTable {
public:
    enum EntryType {ACTIVE, EMPTY, DELETED};//table info is active, empty or deleted (deleted not the same as empty so can't insert)
    
    explicit HashTable(size_t size = 101) : array_(NextPrime(size))
    {
        MakeEmpty();//makes table info empty (not active)
        collision_count_ = 0;//initialize counts when table created
        probe_count_ = 0;
    }
    
    bool Contains(const HashedObj & x) const {
        probe_count_ = 0; //probe count should reset each time we check contains
        return IsActive(FindPos(x));
    }
    
    void MakeEmpty() {
        current_size_ = 0;//when made empty, size will be 0
        for (auto &entry : array_)
            entry.info_ = EMPTY;//set info to empty
    }
    
    bool Insert(const HashedObj & x) {
        // Insert x as active
        size_t current_pos = FindPos(x);//current position is a empty space for element x (hashed and no collision)
        if (IsActive(current_pos))
            return false;
        
        array_[current_pos].element_ = x;//place x
        array_[current_pos].info_ = ACTIVE;//sets to active where x placed
        
        // Rehash; see Section 5.5
        if (++current_size_ > array_.size() / 2)
            Rehash();
        return true;
    }
    
    bool Insert(HashedObj && x) {
        // Insert x as active
        size_t current_pos = FindPos(x);//current position is a empty space for element x (hashed and no collision)
        if (IsActive(current_pos))
            return false;
        
        array_[current_pos] = std::move(x);
        array_[current_pos].info_ = ACTIVE;
        
        // Rehash; see Section 5.5
        if (++current_size_ > array_.size() / 2)
            Rehash();
        
        return true;
    }
    
    bool Remove(const HashedObj & x) {
        size_t current_pos = FindPos(x);
        if (!IsActive(current_pos))
            return false;
        
        array_[current_pos].info_ = DELETED;
        return true;
    }
    
    //returns total number of elements
    int NumOfElements() const{
        return current_size_;
    }
    //returns size of table through array size
    int TableSize() const{
        return array_.size();
    }

    //returns total collisions
    int NumOfCollisions() const{
        return collision_count_;
    }
   //return probe count
    int NumOfProbes() const{
        return probe_count_;
    }
    
    
    //changed from private to protected to inherit in derived class
protected:
    struct HashEntry {
        HashedObj element_;
        EntryType info_;
        
        HashEntry(const HashedObj& e = HashedObj{}, EntryType i = EMPTY)
        :element_{e}, info_{i} { }
        
        HashEntry(HashedObj && e, EntryType i = EMPTY)
        :element_{std::move(e)}, info_{ i } {}
    };
    
    
    std::vector<HashEntry> array_;
    size_t current_size_;
    //mutable does not effect external "costness", collision count and probe count can change even in const functions
    mutable size_t collision_count_;
    mutable size_t probe_count_;
    
    bool IsActive(size_t current_pos) const
    { return array_[current_pos].info_ == ACTIVE; }
    
    //quadratic probing formula used - hash(x) + p(i)
    //p(i) = i^2 (becomes exponential by adding offset by 2)
    //ex: curr=3 -- 3, 4, 7, 12, 19, 28, 39, 52 shows 3 added by i^2
    
    //finds a position to place element x, probes til empty place for x found
    virtual size_t FindPos(const HashedObj & x) const {
        size_t offset = 1;
        size_t current_pos = InternalHash(x);
        
        probe_count_ ++; //count first probe done
        
        while (array_[current_pos].info_ != EMPTY &&
               array_[current_pos].element_ != x) {
            probe_count_++;//count probes til position of x found
            collision_count_++;//counts collisions we run into before position of x found
            //count should be done before continued traversal - moving to next position
            current_pos += offset;  // Compute ith probe.
            offset += 2; // used to have probing function of i^2
            if (current_pos >= array_.size())
                current_pos -= array_.size();
        }
        return current_pos;
    }
    
    void Rehash() {
        std::vector<HashEntry> old_array = array_;
        
        // Create new double-sized, empty table.
        array_.resize(NextPrime(2 * old_array.size()));//double table size
        for (auto & entry : array_)
            entry.info_ = EMPTY;
        
        // Copy table over.
        current_size_ = 0;
        for (auto & entry :old_array)
            if (entry.info_ == ACTIVE)
                Insert(std::move(entry.element_));
    }
    
    size_t InternalHash(const HashedObj & x) const {
        static std::hash<HashedObj> hf;
        return hf(x) % array_.size( );
    }
};

#endif  // QUADRATIC_PROBING_H
