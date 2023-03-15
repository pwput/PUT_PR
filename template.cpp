#include <stdio.h>
#include <string>
#include <errno.h>

int MAX,MIN = 0;


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

bool validateAndSetMinMax(int min, int max){
    if(min>=max){
        return false;
    }
    MAX = max;
    MIN = MIN;
    return true;
}

bool validateProgramArguments(int argc, char *argv[]) {
    if (argc < 2 || argc > 4 || !isNumber(argv[1]) || !isNumber(argv[2])) {
        printPropperUse();
        return false;
    }
    if (!validateAndSetMinMax(std::stoi(argv[1]),std::stoi(argv[2]))){
        perror("Invalid Min or Max\n");
        printPropperUse();
        return false;
    }
    return true;
}

int main(int argc, char *argv[]) {
    if (!validateProgramArguments(argc, argv))
        return 0;

}