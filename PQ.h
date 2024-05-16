#include <functional>

template <class E>
class PQ
{
public:

	// Class Constructor with input size parameter
	PQ(int, std::function<bool(const E&, const E&)>, E);
	// Class Destructor
	~PQ();
	// Member Functions
	void insert(E);	// insert element into heap
	E remove();			// remove & return the top of the heap
	void dispHeap();	// Display Heap Array as a tree
	int size();
	E top();

private:
	// Pointer to Storage Array
	E* a;
	// Maximum Size (not including a[0])
	int MaxSize;
	int N;					// index of last element in the array
	E itemMin;
	std::function<bool(const E&, const E&)> compare;
	// Heap Adjustment Functions
	void upheap(int k);
	void downheap(int k);
	void disp_Level(int Nrows, int level, int s, int e);

};