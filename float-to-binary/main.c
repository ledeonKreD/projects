#include <stdio.h>
#include <stdlib.h>

//for float data type:
#define LEN_EXPONENT    8
#define LEN_MANTISSA    23


int main(int argc, char **argv) {
    float numba = atof(argv[1]);
    int float_binary[32];
    unsigned int sign = 0;
    if (numba < 0.0) {
        sign = 1;
    }

    return 0;
}

//Convert integer number to binary
//returns pointer to array containing the binary number
int *manToBinary(int number) {
    int *array = malloc(LEN_MANTISSA * sizeof(int));
    int quotient = number;

    for (int i = LEN_MANTISSA - 1; i >= 0 ; i--) {
        array[i] = quotient % 2;
        quotient /= 2;
    }

    return array;
}

int *expToBinary(int number) {
    int *array = malloc(LEN_EXPONENT * sizeof(int));
    int quotient = number;

    for (int i = LEN_EXPONENT; i >= 0 ; i--) {
        array[i] = quotient % 2;
        quotient /= 2;
    }

    return array;
}

void printMan(int *array) {
    for(int i = 0; i < LEN_MANTISSA; i++) {
        printf("%d", array[i]);
    }
}

void printExp(int *array) {
    for(int i = 0; i < LEN_EXPONENT; i++) {
        printf("%d", array[i]);
    }
}

void invert(int *array, int len) {
    for(int i = 0; i < len; i ++) {
        if(array[i] = 1) {
            array[i] = 0;
        }
        else {
            array[i] = 1;
        }
    }
}