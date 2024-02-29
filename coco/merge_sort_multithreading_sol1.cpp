#include <thread>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <mutex>
#include <random>


using namespace std;

// size of the array
#define NB_ELEM 4000
#define NB_THREADS 4

// La fonction merge pour fusionner deux tableau
void merge(int arr[], int left[], int right[], int Tab1size, int Tab2size, int start) {

    int totalSize = Tab1size + Tab2size;
    int temp[totalSize];

    int i = 0, j = 0, k = 0;
    while (i < Tab1size && j < Tab2size) {
        if (left[i] <= right[j]) {
            temp[k++] = left[i++]; //The k++ part means we place the element at the current position k and then increment k for the next operation
        } else {
            temp[k++] = right[j++];
        }
    }
    while (i < Tab1size) {
        temp[k++] = left[i++];
    }
    while (j < Tab2size) {
        temp[k++] = right[j++];
    }

    // On copie le tableau temporaire dans le tableau principal à partir de l'index 'start'
    // Ceci est nécéssaire pour que le tableau soit trié sur place
    for (i = 0; i < totalSize; i++) {
        arr[start + i] = temp[i];
    }
}



// Fonction récursive pour trier le tableau
void tri(int Tab[], int left, int right) {
    if (left >= right) { // condition d'arrêt pour sortir de la boucle si left >=right alors le tableu est vide
        return;
    }

    int middle = left + (right - left) / 2;
    tri(Tab, left, middle);
    tri(Tab, middle + 1, right);
    int Tab1[middle - left + 1], Tab2[right - middle];
    for (int i = 0; i <= middle - left; i++) {
        Tab1[i] = Tab[left + i];
    }
    for (int i = 0; i < right - middle; i++) {
        Tab2[i] = Tab[middle + 1 + i];
    }
    merge(Tab, Tab1, Tab2, middle - left + 1, right - middle, left);
}

int main() {
    // On utilise une seed pour fixer les valeurs provenant du générateur de nombre aléatoire
    int seed = 12345;
    srand(seed);

    
    int arr[NB_ELEM];
    // On remplit le tableau avec des valeurs aléatoires
    for (int i = 0; i < NB_ELEM; ++i) {
        arr[i] = rand() % 4000;  // Random numbers between 0 and 99
    }

    cout << "Tableau non trié:" << endl;
    for (int i = 0; i < NB_ELEM; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    //cut the array in 4

    // Calculate the size of each subarray
    int subarraySize = NB_ELEM / NB_THREADS;

    // Create pointers or indices to represent the subarrays
    int* subarray1 = arr;                               // Points to the start of the original array
    int* subarray2 = arr + subarraySize;                // Points to the second subarray
    int* subarray3 = arr + 2 * subarraySize;            // Points to the third subarray
    int* subarray4 = arr + 3 * subarraySize;            // Points to the fourth subarray

    // Print the subarrays
    cout << "Subarray 1: ";
    for (int i = 0; i < subarraySize; ++i) {
        cout << subarray1[i] << " ";
    }
    cout << endl;

    cout << "Subarray 2: ";
    for (int i = 0; i < subarraySize; ++i) {
        cout << subarray2[i] << " ";
    }
    cout << endl;

    cout << "Subarray 3: ";
    for (int i = 0; i < subarraySize; ++i) {
        cout << subarray3[i] << " ";
    }
    cout << endl;

    cout << "Subarray 4: ";
    for (int i = 0; i < subarraySize; ++i) {
        cout << subarray4[i] << " ";
    }
    cout << endl;

    // Début du chrono
    auto start = chrono::high_resolution_clock::now();
    
    thread threads[NB_THREADS];

    for (int k = 0; k < NB_THREADS; k++) {
        threads[k] = thread(calculate_partial_pi, k);
    }

    for (int k = 0; k < NB_THREADS; k++) {
        threads[k].join();
    }

    // Fin du chrono et mesure du temps d'éxecution
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);


    cout << "Tableau trié:" << endl;
    for (int i = 0; i < NB_ELEM; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    cout << "Temps total: " << duration.count() << " microsecond" << endl;


    return 0;
}


