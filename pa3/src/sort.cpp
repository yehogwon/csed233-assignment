#include "sort.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cmath>

sortAlg::sortAlg() {
    arr_size = 0;
    arr = new int[100]; // Each test case will be less than 100 values
}

using namespace std;

void sortAlg::printArray(ofstream &fout) {
    string answer;
    for (int i = 0; i < arr_size - 1; i++)
        answer += to_string(arr[i]) + " ";
    answer += to_string(arr[arr_size - 1]);
    fout << answer << endl;
}

void sortAlg::insertionSort(ofstream &fout) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    int i = 1;
    for (int i = 1; i < arr_size; i++) {
        int j = i;
        bool no = true;
        while (j > 0 && arr[j] < arr[j - 1]) {
            std::swap(arr[j], arr[j - 1]);
            no = false;
            j--;
        }
        if (!no) {
            printArray(fout);
        }
    }
  
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

void sortAlg::merge(int left, int middle, int right) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    // merge [left, middle) and [middle, right]

    if (left == middle) return;
    
    int i = left;
    int j = middle;
    int k = 0;

    int *temp = new int[right - left + 1];
    
    while (i < middle && j <= right) {
        if (arr[i] < arr[j]) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    }

    while (i < middle) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];
    
    for (int i = 0; i < k; i++) arr[left + i] = temp[i];

    delete[] temp;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

void sortAlg::mergeSort(ofstream &fout, int left, int right) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    // length 8
    // [0, 1, 1], [2, 3, 3], [4, 5, 5], [6, 7, 7] // 1
    // [0, 2, 3], [4, 6, 7] // 2
    // [0, 4, 7] // 3

    // length 9
    // [0, 1, 1], [2, 3, 3], [4, 5, 5], [6, 7, 7], [8, 8, 8] // 1
    // [0, 2, 3], [4, 6, 7], [8, 8, 8] // 2
    // [0, 4, 7], [8, 8, 8] // 3
    // [0, 8, 8] // 4

    // length 10
    // [0, 1, 1], [2, 3, 3], [4, 5, 5], [6, 7, 7], [8, 9, 9] // 1
    // [0, 2, 3], [4, 6, 7], [8, 9, 9] // 2
    // [0, 4, 7], [8, 9, 9] // 3
    // [0, 8, 9] // 4
    
    // prevBlockSize = 2 ** i -> i = 0, ...
    // 0 <= i < log_2 n
    // 1 <= 2 ** i = prevBlockSize < n
    for (int prevBlockSize = 1; prevBlockSize < arr_size; prevBlockSize *= 2) {
        int curBlockSize = prevBlockSize * 2;
        for (int i = 0; i < arr_size; i += curBlockSize) {
            int left = i;
            int middle = std::min(i + prevBlockSize, arr_size - 1);
            int right = std::min(i + curBlockSize - 1, arr_size - 1);
            merge(left, middle, right);
        }
        printArray(fout);
    }

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}
