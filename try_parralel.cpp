#include <iostream>
#include <vector>
#include <thread>

void merge(std::vector<int>& array, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> L(n1), R(n2);

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

void mergeSort(std::vector<int>& array, int left, int right, int depth) {
    if (left >= right) return;

    if (depth <= 0 || right - left <= 1000) { // Limit for number of threads or size of sub-array
        for (int i = left; i <= right; ++i) {
            for (int j = i + 1; j <= right; ++j) {
                if (array[i] > array[j]) {
                    std::swap(array[i], array[j]);
                }
            }
        }
        return;
    }

    int mid = left + (right - left) / 2;

    std::thread leftThread(mergeSort, std::ref(array), left, mid, depth - 1);
    std::thread rightThread(mergeSort, std::ref(array), mid + 1, right, depth - 1);

    leftThread.join();
    rightThread.join();

    merge(array, left, mid, right);
}

void parallelMergeSort(std::vector<int>& array) {
    int depth = std::thread::hardware_concurrency(); // Number of available threads
    mergeSort(array, 0, array.size() - 1, depth);
}

int main() {
    std::vector<int> arr = {12, 11, 13, 5, 6, 7};

    std::cout << "Original array:\n";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    parallelMergeSort(arr);

    std::cout << "Sorted array:\n";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
