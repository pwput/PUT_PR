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
    if (!validateProgramArguments(argc, argv,MIN,MAX,DEBUGMODE))
        return 0;
    auto startTime = std::chrono::steady_clock::now(),
            midTime = std::chrono::steady_clock::now(),
            endTime = std::chrono::steady_clock::now();

    ull midPoint = (MAX - MIN) / 2;
    ull count = 0;
    int lineBreak = 10;
    startTime = std::chrono::steady_clock::now();
    for (ull number = MIN; number <= MAX; ++number) {
        bool isPrime = true;
        if (number == midPoint) {
            midTime = std::chrono::steady_clock::now();
        }
        for (ull dev = 2; dev <= sqrt(number); ++dev) {
            if (number % dev == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime) {
            count++;
            if(DEBUGMODE){
                std::cout<<number;
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



    std::cout << std::endl<< "Time from start to Max/2:" << getTimeDuration(midTime, startTime) <<std::endl
    <<"Time from Max/2 to end:"<<getTimeDuration(endTime, midTime)<<std::endl
    <<"Time from start to end:"<<getTimeDuration(endTime, startTime)<<std::endl;

    std::cout <<std::endl<<"Found "<<count<<" prime numbers between "<<MIN<<" and "<<MAX<<std::endl;

}