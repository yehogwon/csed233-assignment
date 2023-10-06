#include "heap.h"
#include <iostream>
#include <string>

using namespace std;

string PriorityQueue::printPQ()
{
    string answer;
    for (int i = 0; i < size; i++)
        answer += to_string(heap[i].value) + " ";
    return answer;
}

bool PriorityQueue::insert(int priority, int value)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    if (size == MAX_SIZE) return false;
    if (size == 0) {
        heap[size++] = pq_element{priority, value};
        return true;
    }

    int index = size++;
    pq_element elem{priority, value};
    while (index > 0 && elem.priority > heap[parent(index)].priority) {
        heap[index] = heap[parent(index)];
        index = parent(index);
    }
    heap[index] = elem;
    return true;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

bool PriorityQueue::removeMax()
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

pq_element PriorityQueue::getMax()
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    return heap[0];

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

bool PriorityQueue::empty()
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    return size == 0;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  You can implement any other functions ////////


int PriorityQueue::left(int i) {
    return 2 * i + 1;
}

int PriorityQueue::right(int i) {
    return left(i) + 1;
}

bool PriorityQueue::is_leaf(int i) {
    return left(i) >= size;
}

bool PriorityQueue::no_right_child(int i) {
    return right(i) >= size;
}

int PriorityQueue::parent(int i) {
    return (i - 1) / 2;
}

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////
