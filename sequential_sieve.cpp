#include <stdio.h>
#include <string>
#include <errno.h>
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

    ull lastNumber = (ull) sqrt(MAX);
    bool *IsPrimeTable = new bool[MAX - 2];

    //ustawiam wszyskie liczyb w tablicy wynikowej na true
    for (int i = 0; i < MAX - 2; ++i) {
        IsPrimeTable[i] = true;
    }

    //główna petla sita
    for (int number = 2; number <= lastNumber; number++) {


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
    std::cout <<std::endl<<"Found "<<count<<" prime numbers between "<<MIN<<" and "<<MAX<<std::endl;
}