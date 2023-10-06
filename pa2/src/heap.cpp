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

    if (empty()) return false;
    heap[0] = heap[--size];
    int index = 0;
    while (index < size && !is_leaf(index)) {
        int higher_child_index = higher_child(index);
        if (heap[index].priority >= heap[higher_child_index].priority) break;
        pq_element tmp = heap[index];
        heap[index] = heap[higher_child_index];
        heap[higher_child_index] = tmp;
        index = higher_child_index;
    }
    return true;

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

int PriorityQueue::higher_child(int i) {
    if (is_leaf(i)) return -1;
    
    int left_index = left(i), right_index = right(i);
    if (no_right_child(i)) return left_index; // have only left child
    return heap[left_index].priority > heap[right_index].priority ? left_index : right_index; // have both children
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
