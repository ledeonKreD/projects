#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//for float data type (4 bytes):
#define LEN_EXPONENT    8
#define LEN_MANTISSA    23
#define BIAS            127

//TODO: find out why the fuck first loop in floatToBinary() switches to 0 when 1 would be reached


//this sucks ass
int *floatToBinary(const float num) {
    int len = LEN_EXPONENT + LEN_MANTISSA + 1;
    int *arr = malloc((len * sizeof(int)));

    //digits before point
    int i_num = num;
    //digits after point
    float f_num = num - i_num;

    //convert numbers after decimal point to binary
    int i = len - 1;
    while(f_num < 1.0 && f_num != 0.0) {
        arr[i] = f_num * 2.0;
        f_num = f_num * 2.0;
        f_num -= arr[i];
        i--;
    }
    while(i_num > 0) {
       arr[i] = i_num % 2;
       i_num = i_num / 2;
       i--;
    }

    return arr;
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

int main(int argc, char **argv) {
    float numba = atof(argv[1]);
    int *bin = floatToBinary(numba);
    for(int i = 0; i < 32; i++) {
        printf("%d", bin[i]);
    }

    return 0;
}