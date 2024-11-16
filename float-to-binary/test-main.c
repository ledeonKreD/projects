#include <stdio.h>
#include <stdlib.h>

#define LEN_ARRAY 32
#define LEN_EXPONENT 8
#define LEN_MANTISSA 23
#define BIAS 127

//sign bit: 31
//exponent: 30-23
//fraction: 22-0

//TODO:
//remove array assignment


void printArray(int *arr) {
	for(int i = 0; i < LEN_ARRAY; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int *floatToBinary(const float num) {
	int *arr = malloc(sizeof(int) * LEN_ARRAY);
	int arr_frac[LEN_ARRAY] = {0};
	int arr_int[LEN_ARRAY] = {0};
	float abs_num;
	if(num < 0) {
		abs_num -= num;
		arr[0] = 1;
	}
	else {
		abs_num = num;
		arr[0] = 0;
	}

	//split digits before and after decimal point respectively
	int i_num = abs_num;
	float f_num = num - i_num;
	
	//convert integer part to binary
	//read from front
	int len_int = 0;
	while(i_num > 0) {
		arr_int[len_int] = i_num % 2;
		i_num /= 2;
		len_int++;
	}
	printf("%s%d\n", "len_int: ", len_int);
	printArray(arr_int);

	//convert fractional part to binary
	//read from back
	int len_frac = 0;
	int lead_frac = 0;
	int IS_FOUND = 0;
	while(f_num > 0.0) {
		arr_frac[len_frac] = f_num * 2.0;
		f_num = (f_num * 2) - arr_frac[len_frac];
		if(arr_frac[len_frac] == 1 && IS_FOUND != 1) {
			lead_frac = len_frac;
			IS_FOUND = 1;
		}
		len_frac++;
	}
	printf("%s%d\n", "lead_frac: ", lead_frac);
	printArray(arr_frac);

	int exponent = 0;
	if(num < 1.0) {
		exponent = -lead_frac - 1;
	}
	else{
		exponent = len_int - 1;
		int point = exponent;
	}
	printf("%d\n", exponent);
	exponent += BIAS;

	for(int i = LEN_EXPONENT; i > 0; i--) {
		arr[i] = exponent % 2;
		exponent /= 2;
	}

	IS_FOUND = 0;
	int index = LEN_ARRAY - LEN_MANTISSA;
	for(int i = len_int - 1; i >= 0; i--) {
		if(arr_int[i] == 0 && IS_FOUND == 0) {
			continue;
		}
		else if(arr_int[i] == 1 && IS_FOUND == 0) {
			IS_FOUND = 1;
			continue;
		}
		arr[index] = arr_int[i];
		index++;
	}
	printf("%s%d\n", "IS_FOUND AFTER 1st loop: ", IS_FOUND);
	for(int i = 0; i < len_frac; i++) {
		if(arr_frac[i] == 0 && IS_FOUND == 0) {
			continue;
		}
		else if(arr_frac[i] == 1 && IS_FOUND == 0) {
			IS_FOUND = 1;
			continue;
		}
		arr[index] = arr_frac[i];
		index++;
	}
	printf("%s%d\n", "IS_FOUND AFTER 2nd loop: ", IS_FOUND);


	return arr;
}


int main(int argc, char **argv) {
	float num = atof(argv[1]);
	printf("%s%f\n", "Entered: ", num);
	int *bin = floatToBinary(num);
	printf("%s\n", "Returned:");
	for(int i = 0; i < 9; i++) {
		printf("%d ", bin[i]);
	}
	printf("%s", " | ");
	for(int i = 9; i < 32; i++) {
		printf("%d ", bin[i]);
	}

	return 0;
}
