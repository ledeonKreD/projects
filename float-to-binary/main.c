#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//for float data type (4 bytes):
#define LEN_EXPONENT    8
#define LEN_MANTISSA    23
#define LEN_ARRAY       32
#define BIAS            127


//TODO:
//  align the bits "to the left"
//  make some nice output
//  convert function needs to add 1 after conversion
//  find out why the fuck first loop in floatToBinary() switches to 0 when 1 would be reached

//Formula for Representing a Floating-Point Number in IEEE Format:
//(-1)^(S) * (2^(B - bias)) * (1.f^(N) ... f^(0))
//________   ______________   ___________________
//SIGN       EXPONENT         SIGNIFICAND
//S=0 (pos)  B=Biased-        N=23 (float=24) digits
//S=1 (neg)  Exponent

int *floatToBinary(const float num) {
    //initialize array
    int *arr = malloc((LEN_ARRAY * sizeof(int)));

    float abs_num;
    if(num < 0) {
        abs_num -= num;
        arr[0] = 1;
    }
    else {
        abs_num = num;
        arr[0] = 1;
    }

    //split the passed number into the part before and after decimal point respectively
    int i_num = abs_num;
    float f_num = abs_num - i_num;

    //convert ass of number to binary
    int index = 0;
    while(f_num < 1.0 && f_num != 0.0) {
        arr[index] = f_num * 2.0;
        f_num = (f_num * 2.0) - arr[index];
        index++;
    }

    int point = index;

    //convert front of number to binary
    while(i_num > 0.0) {
        arr[index] = i_num % 2;
        i_num /= 2;
        index++;
    }
    //set index to place of most significant bit
    arr[index] = 0;
    int exponent = index - point;
    exponent += BIAS;

    //convert exponent to binary
    while(exponent > 0) {
        arr[index] = exponent % 2;
        exponent /= 2;
        index++;
    }

    return arr;
}
//this sucks ass
/*
int *floatToBinary(const float num) {

    int *arr = malloc((LEN_ARRAY * sizeof(int)));

    //truncate digits before point
    int i_num = num;
    //digits after point
    float f_num = num - i_num;
    //da place where the period would be
    int point;
    //place of MSB
    //at least at pos. 1 since sign bit is pos. 0
    int msb = 1;
    //exponent
    int exp = 0;

    //convert numbers after decimal point to binary
    //boundaries not necessary since floating point numbers have size limits set by C
    int index = LEN_ARRAY - 1;
    while(f_num < 1.0 && f_num != 0.0) {
        arr[index] = f_num * 2.0;
        f_num = f_num * 2.0;
        f_num -= arr[index];
        index--;
    }
    point = index;

    //convert numbers before decimal point
    while(i_num > 0) {
       arr[index] = i_num % 2;
       i_num /= 2;
       index--;
    }

    //identify most significant bit
    for(int i = 1; arr[i] != 1; i++) {
       msb++;
    }

    //get exponent and apply bias,
    //set the msb 0 as the byte is not needed for representation
    exp = point - msb;
    printf("%d\n", exp);
    exp += BIAS;
    arr[msb] = 0;

    //convert exponent to binary and prepend
    for(int i = msb; i > msb - 8; i--) {
        arr[i] = exp % 2;
        exp = exp / 2;
    }

    return arr;
}
*/

void printNumba(int *arr) {
    int pos = 0;

    //sign bit
    printf("%d ", arr[pos]);
    pos++;

    //exponent
    for(; pos < pos + LEN_EXPONENT; pos++) {
        printf("%d", arr[pos]);
    }
    printf(" . ");

    //mantissa
    for(; pos < pos + LEN_MANTISSA; pos++) {
        printf("%d", arr[pos]);
    }
}


int main(int argc, char **argv) {
    float numba = atof(argv[1]);
    printf("%f\n", numba);
    int *bin = floatToBinary(numba);
    for(int i = 0; i < LEN_ARRAY; i++) {
        printf("%d", bin[i]);
    }
    printf("\n");
    free(bin);
    return 0;
}