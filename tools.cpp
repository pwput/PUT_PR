#include <string>
#include <chrono>
#define ull unsigned long long

double getTimeDuration(std::chrono::time_point<std::chrono::steady_clock> end,
                       std::chrono::time_point<std::chrono::steady_clock> start) {
    return std::chrono::duration<double>(end - start).count();
}

bool isNumber(char number[]) {
    for (int i = 0; number[i] != 0; i++) {
        if (!isdigit(number[i]))
            return false;
    }
    return true;
}

void printPropperUse() {
    perror("Invalid arguments!\nProper use:\n"
           "./your_binary <min> <max> <-d>\n"
           "Note use '-d' only for debug.");
}
bool validateAndSetMinMax(ull min, ull max, ull& MIN, ull& MAX) {
    if (min >= max) {
        return false;
    }
    MAX = max;
    MIN = min;
    return true;
}

bool validateProgramArguments(int argc, char *argv[],ull& MIN, ull& MAX, bool& DEBUGMODE) {
    if (argc < 2 || argc > 4 || !isNumber(argv[1]) || !isNumber(argv[2])) {
        printPropperUse();
        return false;
    }
    if (!validateAndSetMinMax(std::stoull(argv[1]), std::stoull(argv[2]),MIN,MAX)) {
        perror("Invalid Min or Max\n");
        printPropperUse();
        return false;
    }
    std::string s(argv[3]);
    if (s == "-d"){
        DEBUGMODE = true;
    }
    return true;
}
