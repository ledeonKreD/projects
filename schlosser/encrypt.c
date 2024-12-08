#include <stdio.h>
#include <stdlib.h>

#define BUFFER 50

char* encrypt(char* text, char* key) {
	char* encrypted = malloc(BUFFER * sizeof(char));
	size_t index_key = 0, index_text = 0;
	
	while(index_text < BUFFER && text[index_text] != '\0') {
		if(key[index_key] == '\0') {
			index_key = 0;
		}
		if(text[index_text] < ' ') {
			encrypted[index_text] = text[index_text];
			index_text++;
			index_key++;
			continue;
		}

		//"00001111"
		encrypted[index_text] = (text[index_text] & 0x0f) ^ key[index_key];
		printf("%c", encrypted[index_text]);
		index_text++;
		index_key++;
	}
	return encrypted;
}


int main(int argc, char** argv) {
	char *test = "ligma balls";
	if(argc != 4) {
		//PLEASE change that to stdout so you can redirect the output
		printf("Expected 3 arguments:\n \
			1. Key\n \
			2. path to file\n \
			3. path to out\n");
		return 1;
	}
	char buffer[BUFFER];
	char *encrypted;
	char *key = argv[1];

	char *filename = argv[2];
	FILE *file = fopen(filename, "r");
	if(file == NULL) {
		printf("Error opening file\n");
		return 1;
	}
	char *file_out = argv[3];
	FILE *result = fopen(file_out, "w");
	if(result == NULL) {
		printf("Error writing to file\n");
		return 1;
	}

	while(fgets(buffer, BUFFER, file) != NULL) {
		encrypted = encrypt(buffer, key);
		fwrite(encrypted, sizeof(char), BUFFER, result); 
	}
	if(feof(file)) {
		printf("End of file reached\n");
	}
	fclose(file);
	test = encrypt(test, key);
	test = encrypt(test, key);
	return 0;
}
