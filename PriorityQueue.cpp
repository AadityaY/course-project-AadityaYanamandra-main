#include "PriorityQueue.hpp"
#include <limits.h>

using namespace std;
//comment

void swap(ReviewInfo *a, ReviewInfo *b)
{
    ReviewInfo temp = *a;
    *a=*b;
    *b=temp;
    return;
}

/*
Constructor for our MinHeap implementation
*/
PriorityQ::PriorityQ(int cap)
{
    heapArr = new ReviewInfo[cap];
    capacity=cap;
    currentSize=0;
    return;
}

/*
Destructor
*/
PriorityQ::~PriorityQ()
{
    delete [] heapArr;
    capacity=0;
    currentSize=0;
    return;
}

/*
Finds the parent of a node, given its index.
*/
int PriorityQ::parent(int index)
{
    return (index-1)/2;
}

/*
Returns the left child of a node.
*/
int PriorityQ::leftChild(int index)
{
    return (2*(index)+1);
}

/*
Returns the right child of a node.
*/
int PriorityQ::rightChild(int index)
{
    return (2*(index)+2);
}

ReviewInfo PriorityQ::peek()
{
    if (currentSize==0) {
        cout << "The priority queue is empty, there is no first element to show you!" << endl;
    }
    return heapArr[0];
}

void PriorityQ::heapify(int i)
{
    if (i>currentSize) {
        cout << "This index is out of bounds!" << endl;
        return;
    }
    int left = leftChild(i);
    int right = rightChild(i);
    int largest=i;
    if (left<currentSize && heapArr[left].time>heapArr[i].time) {
        largest=left;
    }
    if (right<currentSize && heapArr[right].time>heapArr[largest].time) {
        largest=right;
    }
    if (largest!=i) {
        swap(&heapArr[i], &heapArr[largest]);
        heapify(largest);
    }
}

void PriorityQ::insertElement(ReviewInfo restaurant)
{
    if (currentSize==capacity) {
        cout << "The priority queue is full, nothing could be added!" << endl;
        return;
    }
    heapArr[currentSize]=restaurant;
    int index=currentSize;
    currentSize++;
    while (index>0 && heapArr[parent(index)].time<heapArr[index].time) {
        swap(&heapArr[index], &heapArr[parent(index)]);
        index=parent(index);
    }
}

/*
Prints the elements in the heap
*/
void PriorityQ::print()
{
    for (int i=0; i<currentSize; i++) {
        cout << "\t" << "Customer: " << heapArr[i].customer << endl;
        cout << "\t" << "Review: " << heapArr[i].review << endl;
        cout << "\t" << "Time: " << heapArr[i].time << endl;
        cout << "\t" << "=====" << endl;
    }
}

// Method to remove minimum element (or root) from min heap
void PriorityQ::pop()
{
    if (currentSize==0) {
        cout << "The priority queue is empty, nothing can be removed!" << endl;
        return;
    }
    heapArr[0]=heapArr[currentSize-1];
    currentSize--;
    heapify(0);
}
