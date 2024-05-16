// File:PQ.cpp
// PQ (min Heap) Class implementation
#include <iostream>
#include <cmath>
#include <iomanip>
#include "PQ.h"
using namespace std;

// Member Functions

// Constructor with argument. Max size is mVal elements
// not including a[0] which will receive -32767
// The constructor creates the heap array, initializes
// the end of the heap to N=0,and itmMin
template <class E>
PQ<E>::PQ(int mVal, std::function<bool(const E&, const E&)> com, E min) {
    compare = com;
    MaxSize = mVal;
    a = new E[MaxSize + 1];
    N = 0;
    itemMin = min;  // Minimum Heap
    a[0] = itemMin;
}

// Class Destructor
template <class E>
PQ<E>::~PQ() {
    delete[] a;
}

// Heap Adjustment Functions
// upheap element at location (k) in the heap
// as long as it is less than the parent

template <class E>
void PQ<E>::upheap(int k) {
    E v = a[k];
    while (compare(a[k / 2], v)) {
        a[k] = a[k / 2];
        k = k / 2;
    }
    a[k] = v;
}

template <class E>
int PQ<E>::size() {
    return N;
}

template <class E>
E PQ<E>::top() {
    return a[1];
}

// downheap element at (k) in the heap
template <class E>
void PQ<E>::downheap(int k) {
    int j = 2 * k;
    E v = a[k];
    while (j <= N) {
        if ((j < N) && compare(a[j], a[j + 1])) j++;
        if (compare(a[j], v)) break;
        a[j / 2] = a[j];
        j *= 2;
    }
    a[j / 2] = v;
}

// Insert element (v) in the heap and adjust heap
template <class E>
void PQ<E>::insert(E v) {
    if (v == NULL) return;

    a[++N] = v;

    upheap(N);
}

// remove and return top of the heap, then adjust heap
template <class E>
E PQ<E>::remove() {
    E v = a[1];
    a[1] = a[N--];
    downheap(1);
    return v;
}

template <class E>
void PQ<E>::dispHeap() {
    int s = 1, e = 1, rlength, k, Nlevels = int(ceil(log(float(N)) / log(2.0) + 0.01));
    for (int level = 0; level < Nlevels; level++) {
        disp_Level(Nlevels, level, s, e);
        rlength = e - s + 1;
        s = e + 1;
        k = e + 2 * rlength;
        e = (k < N) ? k : N;
    }
}

template <class E>
void PQ<E>::disp_Level(int Nrows, int level, int s, int e) {
    int skip = int(pow(2.0, Nrows - level) - 1);
    for (int i = s; i <= e; i++) {
        cout << setw(skip) << " ";
        cout << setw(2) << a[i];
        cout << setw(skip) << " ";
    }
    cout << "\n\n\n";
}