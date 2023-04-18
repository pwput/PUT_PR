#include <stdio.h>
#include <string>
#include <errno.h>
#include <math.h>
#include <iostream>
#include <omp.h>
#include "tools.cpp"

//Algorytm ten sekwencyjnie wyznacza liczby pierwsze.
// W tej wersji algorytmu zrównoleglenie polega na podzieleniu zakresu liczb do wykreślenia na przedziały

ull MAX, MIN = 0;
bool DEBUGMODE = false;
#define threads 4
#define sizes 50000

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

        omp_set_num_threads(threads);

#pragma omp parallel{
        int rank = omp_get_thread_num();
        int start = MIN + rank * sizes;


        while (start <= MIN)
        {

            for (int i = 0; i < count; i++)
            {
                int begin;
                int x = start % IsPrimeTable[i];
                if (!x)
                    begin = start;
                else
                    begin = start + IsPrimeTable[i] - x;
                if (begin == IsPrimeTable[i])
                    begin = IsPrimeTable[i] + IsPrimeTable[i];
                int end = start + sizes + 1;
                for (int k = begin; k <= end && k <= MIN; k += IsPrimeTable[i])
                {
                    IsPrimeTable[k] = false;
                }
            }
            start += (threads * sizes);
        }
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