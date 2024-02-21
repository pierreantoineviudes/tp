/**
 * @file testgpt.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-01-29
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <iostream>
#include <vector>
#include <random>

/**
 * @brief
 *
 * @param arr1
 * @param arr2
 * @return std::vector<int>
 */
std::vector<int> merge(const std::vector<int> &arr1, const std::vector<int> &arr2)

{

    std::vector<int> mergedArr;
    int i = 0, j = 0;

    while (i < arr1.size() && j < arr2.size())
    {
        if (arr1[i] < arr2[j])
        {
            mergedArr.push_back(arr1[i]);
            ++i;
        }
        else
        {
            mergedArr.push_back(arr2[j]);
            ++j;
        }
    }

    while (i < arr1.size())
    {
        mergedArr.push_back(arr1[i]);
        ++i;
    }

    while (j < arr2.size())
    {
        mergedArr.push_back(arr2[j]);
        ++j;
    }

    return mergedArr;
}

/**
 * @brief
 *
 * @param arr
 * @return std::vector<int>
 */
std::vector<int> mergeSort(const std::vector<int> &arr)
{
    if (arr.size() <= 1)
    {
        return arr;
    }

    int middle = arr.size() / 2;
    std::vector<int> left(arr.begin(), arr.begin() + middle);
    std::vector<int> right(arr.begin() + middle, arr.end());

    left = mergeSort(left);
    right = mergeSort(right);

    return merge(left, right);
}

/**
 * @brief
 *
 * @param size
 * @param minValue
 * @param maxValue
 * @return std::vector<int>
 */
std::vector<int> generateRandomArray(int size, int minValue, int maxValue)
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(minValue, maxValue);

    std::vector<int> randomArray(size);
    for (int &value : randomArray)
    {
        value = distribution(generator);
    }

    return randomArray;
}

int main()
{
    // Creating a random array of integers
    std::vector<int> arr = generateRandomArray(std::pow(10, 6), 0, 100);

    // Sorting the array using merge sort
    arr = mergeSort(arr);

    return 0;
}
