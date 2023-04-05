#include <stdio.h>
#include <string>
#include <chrono>
#include <errno.h>
#include <math.h>
#include <iostream>
#include "tools.cpp"


ull MAX, MIN = 0;
bool DEBUGMODE = false;

int main(int argc, char *argv[]) {
    if (!validateProgramArguments(argc, argv, MIN, MAX, DEBUGMODE))
        return 0;
    auto startTime = std::chrono::steady_clock::now(),
            midTime = std::chrono::steady_clock::now(),
            endTime = std::chrono::steady_clock::now();

    ull midPoint = (MAX - MIN) / 2;
    ull count = 0;
    int lineBreak = 10;
    startTime = std::chrono::steady_clock::now();

    ull lastNumber = (ull) sqrt(MAX);
    bool *IsPrimeTable = new bool[MAX - 2];

    //ustawiam wszyskie liczyb w tablicy wynikowej na true
    for (int i = 0; i < MAX - 2; ++i) {
        IsPrimeTable[i] = true;
    }

    startTime = std::chrono::steady_clock::now();

    //główna petla sita
    for (int number = 2; number <= lastNumber; number++) {

        if (number == midPoint)
            midTime = std::chrono::steady_clock::now();

        //sprawdzam czy nie była wczesniej wykreślona
        if (!IsPrimeTable[number - 2])
            continue;

        //nie była wczesniej wykreslona i jest pierwsza
        //wykreslam wszystkie wielokrotnosci z tableli

        for (ull multi = number * 2; multi <= MAX; multi += number) {
            IsPrimeTable[multi - 2] = false;
        }

        //teraz sprawdzam cczy jest w interesujacym nas zakresie
        if (number >> MIN){
            count++;
            if (DEBUGMODE) {
                std::cout << number;
                if (lineBreak-- == 0){
                    lineBreak = 10;
                    std::cout << std::endl;
                }
                else {
                    std::cout << " ";
                }
            }
        }



    }
    endTime = std::chrono::steady_clock::now();

    for (int i = lastNumber; i <MAX ; ++i) {
        if(IsPrimeTable[i-2]){
            count++;
            if (DEBUGMODE) {
                std::cout << i;
                if (lineBreak-- == 0){
                    lineBreak = 10;
                    std::cout << std::endl;
                }
                else {
                    std::cout << " ";
                }
            }
        }

    }

    std::cout <<std::endl<< "Time from start to Max/2:" <<
              getTimeDuration(midTime, startTime) << std::endl
              << "Time from Max/2 to end:" <<
              getTimeDuration(endTime, midTime) << std::endl
              << "Time from start to end:" <<
              getTimeDuration(endTime, startTime) << std::endl;

    std::cout <<std::endl<<"Found "<<count<<" prime numbers between "<<MIN<<" and "<<MAX<<std::endl;
}