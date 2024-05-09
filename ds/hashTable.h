// File: hashTable.h
// Definition of Hash Table Template Class

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

// Specification of the class

template <class keyType, class dataType>

class hashTable {
   public:
    // Member Functions
    hashTable(int nelements = 11);  // Constructor
    ~hashTable();                   // Destructor

    // Functions Prototype Definitions

    void emptyTable(const keyType &);
    bool tableIsEmpty() const;
    bool tableIsFull() const;
    int occupancy() const;
    bool insert(const keyType &, const dataType &);
    bool search(const keyType &);
    // void remove();
    void updateData(const dataType &);
    void retrieveData(dataType &) const;
    void traverse() const;

   private:
    // Slot Class
    class slot {
       public:
        keyType key;    // key
        dataType data;  // Data
    };  // end of class slot declaration

    slot *T;             // Pointer to Storage Array
    int h;               // Index to a slot
    int MaxSize, csize;  // Maximum and Current Sizes
    keyType Empty;       // empty symbol

    // Private Member function
    int hash(const keyType &) const;
};
#endif  // HASH_TABLE_H
#include "hashTable.cpp"