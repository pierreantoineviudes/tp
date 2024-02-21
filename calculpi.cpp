#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <atomic>

std::atomic<int> insideCircleCount(0);
const int totalPoints = 100000000;

void monteCarloSimulation(int points)
{
    int insideCircle = 0;
    double x, y, distance;

    for (int i = 0; i < points; ++i)
    {
        x = (double)rand() / RAND_MAX; // Random number between 0 and 1
        y = (double)rand() / RAND_MAX; // Random number between 0 and 1

        distance = x * x + y * y;

        if (distance <= 1)
        {
            ++insideCircle;
        }
    }

    insideCircleCount += insideCircle;
}

int main()
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    int numThreads = std::thread::hardware_concurrency();
    int pointsPerThread = totalPoints / numThreads;

    std::thread *threads = new std::thread[numThreads];

    // Start threads
    for (int i = 0; i < numThreads; ++i)
    {
        threads[i] = std::thread(monteCarloSimulation, pointsPerThread);
    }

    // Wait for threads to finish
    for (int i = 0; i < numThreads; ++i)
    {
        threads[i].join();
    }

    // Calculate pi
    double piApproximation = 4.0 * insideCircleCount / totalPoints;

    std::cout << "Approximated value of pi: " << std::setprecision(8) << piApproximation << std::endl;

    delete[] threads;

    return 0;
}
