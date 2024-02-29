#include <thread>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <mutex>
#include <random>
#include <chrono> 

using namespace std;

#define NB_POINTS 10000000L
#define NB_THREADS 4

double totalSum = 0.0;
int iterationsThread = NB_POINTS / NB_THREADS;

void partialCircle(int threadNumber) {
    cout << "Thread Number :" << threadNumber << " started\n";

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0, 1);

    double localSum = 0.0;
    for (int i = 0; i < iterationsThread; ++i) {
        double x = dis(gen);
        double y = dis(gen);
        if (x * x + y * y <= 1) {
            localSum += 1;
        }
    }
    totalSum += localSum/iterationsThread;
}

int main() {
    auto start_time = chrono::high_resolution_clock::now();

    thread threads[NB_THREADS];

    for (int k = 0; k < NB_THREADS; k++) {
        threads[k] = thread(partialCircle, k);
    }

    for (int k = 0; k < NB_THREADS; k++) {
        threads[k].join();
    }

    auto end_time = chrono::high_resolution_clock::now(); // Arrêter le compteur de temps
    chrono::duration<double, std::milli> duration_ms = end_time - start_time; // Calculer la durée en millisecondes


    cout << "Approximated value of Pi: " << totalSum << endl;
    cout << "Time taken: " << duration_ms.count() << " ms\n";
    return 0;
}