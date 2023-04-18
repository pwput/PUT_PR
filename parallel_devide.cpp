#include <stdio.h>
#include <string>
#include <errno.h>
#include <omp.h>
#include <math.h>
#include <iostream>
#include "tools.cpp"


ull MAX, MIN = 0;
bool DEBUGMODE = false;

int main(int argc, char *argv[]) {
    if (!validateProgramArguments(argc, argv, MIN, MAX, DEBUGMODE))
        return 0;
    ull count = 0;
    int lineBreak = 10;
#pragma omp parallel for
    for (ull number = MIN; number <= MAX; ++number) {
        bool isPrime = true;
        for (ull dev = 2; dev <= sqrt(number); ++dev) {
            if (number % dev == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime) {
#pragma omp critical
            count++;
            if (DEBUGMODE) {
                std::cout << number;
                if (lineBreak-- == 0) {
                    lineBreak = 10;
                    std::cout << std::endl;
                } else {
                    std::cout << " ";
                }
            }
        }

    }
    std::cout << std::endl << "Found " << count << " prime numbers between " << MIN << " and " << MAX << std::endl;

}