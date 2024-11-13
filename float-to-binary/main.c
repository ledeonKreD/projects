#include <stdio.h>
#include <stdlib.h>

//for float data type (4 bytes):
#define LEN_EXPONENT    8
#define LEN_MANTISSA    23
#define LEN_ARRAY       32
#define BIAS            127


//TODO:
//  align the bits "to the left"
//  fix printNumba function
//  make some nice output
//  convert function needs to add 1 after conversion
//  find out why the fuck first loop in floatToBinary() switches to 0 when 1 would be reached

//Formula for Representing a Floating-Point Number in IEEE Format:
//(-1)^(S) * (2^(B - bias)) * (1.f^(N) ... f^(0))
//________   ______________   ___________________
//SIGN       EXPONENT         SIGNIFICAND
//S=0 (pos)  B=Biased-        N=23 (float=24) digits
//S=1 (neg)  Exponent

//this sucks ass
int *floatToBinary(const float num) {

    int *arr = malloc((LEN_ARRAY * sizeof(int)));

    //digits before point
    int i_num = num;
    //digits after point
    float f_num = num - i_num;
    //da place where the period would be
    int point;
    //place of MSB
    int msb = 0;
    //exponent
    int exp = 0;

    //convert numbers after decimal point to binary
    //-1 to leave space for the sign bit
    int index = LEN_ARRAY - 1;
    while(f_num < 1.0 && f_num != 0.0) {
        arr[index] = f_num * 2.0;
        f_num = f_num * 2.0;
        f_num -= arr[index];
        index--;
    }
    index--;
    point = index;

    //convert numbers before decimal point
    while(i_num > 0) {
       arr[index] = i_num % 2;
       i_num = i_num / 2;
       index--;
    }

    //identify most significant bit
    for(int i = 0; arr[i] != 1; i++) {
       msb++;
    }

    //get exponent and apply bias,
    //set the msb 0 as the byte is not needed for representation
    //printf("%d\n", msb);
    exp = point - msb;
    exp += BIAS;
    arr[msb] = 0;

    //convert exponent to binary and prepend
    for(int i = msb; i > msb - 8; i--) {
        arr[i] = exp % 2;
        exp = exp / 2;
    }

    return arr;
}

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
    int *bin = floatToBinary(numba);
    for(int i = 0; i < 32; i++) {
        printf("%d", bin[i]);
    }
    //printNumba(bin);

    return 0;
}
