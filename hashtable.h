#ifndef HASHTABLE_H
#define HASHTABLE_H

// Project Identifier: 2C4A3C53CD5AD45A7BEA3AE5356A3B1622C9D04B

// INSTRUCTIONS:
// fill out the methods in the class below.

// You may assume that the key and value types can be copied and have default
// constructors.

// You can also assume that the key type has (==) and (!=) methods.

// You may assume that Hasher is a functor type with a
// size_t operator()(const Key&) overload.

// The key/value types aren't guaranteed to support any other operations.

// Do not add, remove, or change any of the class's member variables.
// The num_deleted counter is *optional*. You might find it helpful, but it
// is not required to pass the lab assignment.

// Do not change the Bucket type.

// SUBMISSION INSTRUCTIONS:
// Submit this file, by itself, in a .tar.gz.
// Other files will be ignored.

#include <cstdint>
#include <functional> // where std::hash lives
#include <vector>
#include <cassert> // useful for debugging!

// A bucket's status tells you whether it's empty, occupied, 
// or contains a deleted element.
enum class Status : uint8_t {
    Empty,
    Occupied,
    Deleted
};

template<typename K, typename V, typename Hasher = std::hash<K>>
class HashTable {
    // used by the autograder; do not change/remove.
    friend class Verifier;
public:
    // A bucket has a status, a key, and a value.
    struct Bucket {
        // Do not modify Bucket.
        Status status = Status::Empty;
        K key;
        V val;
    };

    HashTable() {
        // TODO: a default constructor (possibly empty).
        buckets.resize(20);
        // You can use the following to avoid implementing rehash_and_grow().
        // However, you will only pass the AG test cases ending in _C.
        // To pass the rest, start with at most 20 buckets and implement rehash_and_grow().
        //    buckets.resize(10000);
    }

    size_t size() const {
        return num_elements;
    }

    // returns a reference to the value in the bucket with the key, if it
    // already exists. Otherwise, insert it with a default value, and return
    // a reference to the resulting bucket.
    
    // takes  a  key,  and  returns  a  reference  to  the  associated  value  in  the  hash  table.
    //If  the  key  was  not previously present in the table, it will be inserted, associated with a default-constructed value.
    V& operator[](const K& key) {
        // TODO
        Hasher hasher;
        size_t bucket_index = hasher(key) % buckets.size();
        if(buckets[bucket_index].status == Status::Empty ||
           buckets[bucket_index].status == Status::Deleted) {
            buckets[bucket_index].val = V();
            insert(key, buckets[bucket_index].val);
            return buckets[bucket_index].val;
//            Bucket& b = buckets[bucket_index];
//            return *b;
        }
        return buckets[bucket_index].val;
    }

    // insert returns whether inserted successfully
    // (if the key already exists in the table, do nothing and return false).
    // insert  takes  a  key  and  a  value,  and  inserts  them  into  the  hash  table.
    // If  the  new  key  is  already  in  the  hash  table,  then the operation has no effect.
    // insert  returns whether  the key was inserted.
    bool insert(const K& key, const V& val) {
        // TODO
        
        
//        size_t bucket_index = hasher(key) % buckets.size();
        Hasher hasher;
        size_t bucket_index = hasher(key) % buckets.size();
        
        if(buckets[bucket_index].status == Status::Occupied &&
           buckets[bucket_index].key == key) {
            return false;
        }
        
        for(uint32_t i = 0; i < buckets.size(); i++) {
            if(buckets[i].status == Status::Occupied &&
               buckets[i].key == key) {
                return false;
            }
        }
        
        if(num_elements == buckets.size()) {
            rehash_and_grow();
        }
        uint32_t b = static_cast<uint32_t>(bucket_index + 1);
        if(buckets[bucket_index].status == Status::Occupied) {
            uint32_t i = 0;
            while(i != bucket_index) {
                if(buckets[i].val == val) {
                    return i;
                }
                if(buckets[i].status == Status::Deleted ||
                   buckets[i].status == Status::Empty) {
                    b = i;
                }
                if(i != (buckets.size() - 1)) {
                    i++;
                }
                if(i == (buckets.size() - 1)) {
                    i = 0;
                }
            }
        }
        buckets[bucket_index].key = key;
        buckets[bucket_index].val = val;
        buckets[bucket_index].status = Status::Occupied;
        
        num_elements++;
        return true;
    }
    // erase returns the number of items remove (0 or 1)
    //  takes  a  key,  and  removes  it  from  the  hash  table.
    // If  the  key  isn’t  already  in  the  hash  table,  then  the  operation has no effect.
    // erase  returns how many items were deleted  (either 0 or 1).
    size_t erase(const K& key) {
        // TODO
        Hasher hasher;
        size_t bucket_index = hasher(key) % buckets.size();
        if(buckets[bucket_index].status == Status::Empty ||
           buckets[bucket_index].status == Status::Deleted) {
            return 0;
        }
        if(buckets[bucket_index].key != key) {
            return 0;
        }
        buckets[bucket_index].status = Status::Deleted;
        num_elements--;
        return 1;
    }

private:
    size_t num_elements = 0;
    size_t num_deleted = 0; // OPTIONAL: you don't need to use num_deleted to pass
    std::vector<Bucket> buckets;

    void rehash_and_grow() {
        // You can avoid implementing rehash_and_grow() by calling
        //    buckets.resize(10000);
        // in the constructor. However, you will only pass the AG test cases ending in _C.
        // To pass the rest, start with at most 20 buckets and implement rehash_and_grow().
        size_t new_size = buckets.size() * 2;
        std::vector<Bucket> new_buckets;
        for(uint32_t i = 0; i < buckets.size(); i++) {
            if(buckets[i].status == Status::Occupied) {
                Hasher hasher;
                size_t new_index = hasher(buckets[i].key) % new_size;
                new_buckets[new_index].val = buckets[i].val;
                new_buckets[new_index].key = buckets[i].key;
            }
        }
        buckets = new_buckets;
    }

    // You can add methods here if you like.
    // TODO
    
//    size_t indexer(const V& val, const K& key) {
//        Hasher hasher;
//        size_t bucket_index = hasher(key) % buckets.size();
//
//        if(buckets[bucket_index].status == Status::Empty) {
//            return bucket_index;
//        }
//        size_t i = bucket_index + 1;
//        size_t b = i;
//        while(i != bucket_index) {
////            if(buckets[i].val == val) {
////                return i;
////            }
//            if(buckets[i].status == Status::Deleted ||
//               buckets[i].status == Status::Empty) {
//                b = i;
//            }
//            if(i != (buckets.size() - 1)) {
//                i++;
//            }
//            if(i == (buckets.size() - 1)) {
//                i = 0;
//            }
//        }
//
//        return b;
//    }
};

#endif // HASHTABLE_H
