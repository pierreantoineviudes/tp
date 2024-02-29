#include <iostream>
#include <vector>
#include <thread>
using namespace std;

void merge(vector<int>& array, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; ++i)
        L[i] = array[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = array[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            array[k] = L[i];
            ++i;
        } else {
            array[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        array[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        array[k] = R[j];
        ++j;
        ++k;
    }
}

void mergeSort(vector<int>& array, int left, int right, int depth) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;

    thread leftThread(mergeSort, ref(array), left, mid, depth - 1);
    thread rightThread(mergeSort, ref(array), mid + 1, right, depth - 1);

    leftThread.join();
    rightThread.join();

    merge(array, left, mid, right);
}

void parallelMergeSort(vector<int>& array) {
    int depth = thread::hardware_concurrency(); // Number of available threads
    mergeSort(array, 0, array.size() - 1, depth);
}

int main() {
    vector<int> arr = {12, 11, 13, 5, 6, 7};

    cout << "Original array:\n";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    parallelMergeSort(arr);

    cout << "Sorted array:\n";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
