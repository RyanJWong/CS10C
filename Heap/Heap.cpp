#include "Heap.h"
#include <iostream>

/*Initializes an empty heap.*/
Heap::Heap() {
    numItems = 0;
}

/*Inserts a PrintJob to the heap without
violating max-heap properties.*/
void Heap::enqueue ( PrintJob* job) {
    if (numItems < MAX_HEAP_SIZE) {
        arr[numItems] = job;
        // add to end of heap and percolate appropriately
        percolateUp(numItems);
        numItems++;
    }
}

/*Removes the node with highest priority from the heap. 
Follow the algorithm on priority-queue slides. */
void Heap::dequeue() {
    if (numItems <= 1) {
        arr[0] = 0;
        numItems = 0;
    }
    else {
        arr[0] = arr[numItems -1]; //replace root w/ last item and percolate new root down
        numItems--;
        arr[numItems] = 0;
        trickleDown(0); // trickle down root
    }
}


/*Returns the node with highest priority.*/
PrintJob* Heap::highest () {
    if (numItems == 0) {
        return 0;
    }
    return arr[0];
}

/*Prints the PrintJob with highest priority in the following format:
Priority: priority, Job Number: jobNum, Number of Pages: numPages
(Add a new line at the end.)*/
void Heap::print () {
    if (numItems > 0) {
        std::cout << "Priority: " << arr[0]->getPriority() << ", Job Number: " << arr[0]->getJobNumber() << ", Number of Pages: " << arr[0]->getPages() << std::endl;
    }
}


/*This function is called by dequeue function
to move the new root down the heap to the 
appropriate location.*/
void Heap::trickleDown(int nodeIndex) {
    for (int index = 0; index < numItems; index++) {
        if (arr[index]->getPriority() > arr[nodeIndex]->getPriority() ) { // keep moving the node down until its in the right spot
            swap(arr[index], arr[nodeIndex]);
        }
    }
}

void Heap::percolateUp(int nodeIndex) {
    while (nodeIndex >= 1 and arr[nodeIndex]->getPriority() > arr[(nodeIndex-2)/2]->getPriority()) { // repeat until last node is at the head or follows maxheap properties
        swap(arr[nodeIndex], arr[(nodeIndex-2)/2]); // swap parent and current node;
        // set current value to swapped node's index
        nodeIndex = (nodeIndex-2)/2;
    }
}
