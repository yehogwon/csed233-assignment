#include <iostream>
#include <string>
using namespace std;

class sortAlg {

public:
    sortAlg();  

    int arr_size;
    int *arr;   
    
    void printArray(ofstream &);
    void insertionSort(ofstream &); 
    void mergeSort(ofstream &, int left, int right);
    void merge(int left, int middle, int right);
};
