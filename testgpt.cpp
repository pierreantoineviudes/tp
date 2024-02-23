/**
 * @file testgpt.cpp
 * @author Pierre-Antoine Viudès (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-01-29
 *
 * @copyright Copyright (c) 2024
 *
 */

#define taille_tableau 1000000L
#define MAX_THREADS 15

#include <iostream>
#include <vector>
#include <random>
#include <thread>
using namespace std;

/**
 * @brief function to sort/merge an array
 *
 * @param arr1
 * @param arr2
 * @return vector<int>
 */
vector<int> merge(const vector<int> &arr1, const vector<int> &arr2)

{

    vector<int> mergedArr;
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
 * @brief fnction to compute the merge of two sorted arrays
 *
 * @param arr
 * @return vector<int>
 */
vector<int> mergeSort(const vector<int> &arr)
{
    if (arr.size() <= 1)
    {
        return arr;
    }

    int middle = arr.size() / 2;
    vector<int> left(arr.begin(), arr.begin() + middle);
    vector<int> right(arr.begin() + middle, arr.end());

    left = mergeSort(left);
    right = mergeSort(right);

    return merge(left, right);
}

/**
 * @brief function to generate random array in order to test the program
 *
 * @param size
 * @param minValue
 * @param maxValue
 * @return vector<int>
 */
vector<int> generateRandomArray(int size, int minValue, int maxValue)
{
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(minValue, maxValue);

    vector<int> randomArray(size);
    for (int &value : randomArray)
    {
        value = distribution(generator);
    }

    return randomArray;
}

int main()
{
    // Creating a random array of integers
    // vector<int> arr = generateRandomArray(pow(10, 6), 0, 100);
    vector<int> arr = generateRandomArray(taille_tableau, 0, 100);

    // Print original array
    cout << "Original Array:\n";
    for (const auto &num : arr)
    {
        cout << num << " ";
    }
    cout << endl;

    // Sorting the array using merge sort
    arr = mergeSort(arr);

    // Print sorted array
    cout << "\nSorted Array:\n";
    for (const auto &num : arr)
    {
        cout << num << " ";
    }
    cout << endl;

    // pour les threads, je pense qu'il faut diviser le tableau en
    // parties égales dépendant du nb de threads
    // et finalement, re-merge tout ça en ré-utilisant la fonction merge

    // boucle sur les différents nb de threads
    for (int nb_threads = 1; nb_threads < MAX_THREADS; nb_threads++)
    {
        thread lds[nb_threads];

        // création du tableau qui va recevoir le sorted Arr
        vector<int> sortedArr(taille_tableau);

        // diviser le tableau en nb_threads parties
        int size_tranche = ceil(taille_tableau * 1.0 / nb_threads);

        int taille_deja_fait = 0;
        for (int k = 0; k < nb_threads - 1; k++, taille_deja_fait += size_tranche)
        {
            lds[k] = thread(sort_une_tranche, tab, k * size_tranche, (k + 1) * size_tranche, ref(somme_globale));
        }
    }

    return 0;
}