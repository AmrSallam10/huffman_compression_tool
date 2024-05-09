// File:hashTable.cpp
// hashTable Class implementation file

#include <iostream>
using namespace std;

// Constructor with argument, size is nelements, default is 11
template <class keyType, class dataType>
hashTable<keyType, dataType>::hashTable(int nelements) {
    MaxSize = nelements;
    T = new slot[MaxSize];
    h = -1;
    csize = 0;
}

// Destructor
template <class keyType, class dataType>
hashTable<keyType, dataType>::~hashTable() {
    delete[] T;
}

// Empty all slots
template <class keyType, class dataType>
void hashTable<keyType, dataType>::emptyTable(const keyType &k) {
    Empty = k;
    for (int i = 0; i < MaxSize; i++) T[i].key = Empty;
    h = -1;
    csize = 0;
}

// return True if table is empty
template <class keyType, class dataType>
bool hashTable<keyType, dataType>::tableIsEmpty() const {
    return (csize == 0);
}

// return True if table is full
template <class keyType, class dataType>
bool hashTable<keyType, dataType>::tableIsFull() const {
    return (csize == MaxSize);
}

// to return the current occupancy of the table
template <class keyType, class dataType>
int hashTable<keyType, dataType>::occupancy() const {
    return csize;
}

// insert key and data at a hashed slot
template <class keyType, class dataType>
bool hashTable<keyType, dataType>::insert(const keyType &k, const dataType &d) {
    if (!tableIsFull()) {
        h = hash(k);
        while (T[h].key != Empty) h = (h + 1) % MaxSize;
        T[h].key = k;
        T[h].data = d;
        csize++;
        return true;
    } else
        return false;
}

// Search the table for the slot that matches key.
// If found, return True, set current position to slot
template <class keyType, class dataType>
bool hashTable<keyType, dataType>::search(const keyType &k) {
    if (!tableIsEmpty()) {
        h = hash(k);
        int start = h;
        for (;;) {
            if (T[h].key == Empty) return false;
            if (k == T[h].key) return true;
            h = (h + 1) % MaxSize;
            if (h == start) return false;
        }
    } else
        return false;
}

/* Remove given key from (make deleted) current slot
template <class keyType, class dataType>
void hashTable<keyType, dataType>::remove()
{
    T[h].key = Deleted;
}
*/

// Update the data part of the current slot
template <class keyType, class dataType>
void hashTable<keyType, dataType>::updateData(const dataType &d) {
    if ((h >= 0) && (h < MaxSize)) T[h].data = d;
}

// Retrieve the data part of the current slot
template <class keyType, class dataType>
void hashTable<keyType, dataType>::retrieveData(dataType &d) const {
    if ((h >= 0) && (h < MaxSize))
        d = T[h].data;
    else
        d = T[0].data;
}

// Traverse whole table
template <class keyType, class dataType>
void hashTable<keyType, dataType>::traverse() const {
    for (int i = 0; i < MaxSize; i++) cout << T[i].key << endl;
}

// Private Hashing Function
template <class keyType, class dataType>
int hashTable<keyType, dataType>::hash(const keyType &k) const {
    return (k % MaxSize);
}
