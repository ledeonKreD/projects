#include <stdio.h>
#include <stdlib.h>


//pass as null-terminated strings
void encrypt(char* text, char* key) {
	size_t len_text = 0;
	size_t len_key = 0;	
	//printf("Size key: %d\n", sizeof(key));
	
	//this will NOT include the null-terminator
	for(size_t i = 0; text[i] != '\0'; i++) {
		len_text++;
	}

	//only this is really needed
	for(size_t i = 0; key[i] != '\0'; i++) {
		len_key++;
	}

	//printf("Len Key: %d\n", len_key);
	for(size_t i = 0; text[i] != '\0'; i++) {
		//skip control characters
		if(text[i] < ' ') {
			continue;
		}

		text[i] = text[i] ^ (0x0f & key[(i + len_key) % len_key]);
		printf("%c", text[i]);
	}
}


/*
void encrypt(char* text, char* key) {
	const int mask = 0x0f;
	size_t index_text = 0, index_key = 0;
	while(text[index_text] != '\0') {
		if(key[index_key] == '\0') {
			key[index_key] = 0;
		}
		text[index_text] = (mask & text[index_text]) ^ key[index_key];
		index_text++;
		index_key++;
	}
}
*/

int main(int argc, char** argv) {
	
	if(argc < 2) {
		printf("Specify 2 arguments:\n \
			1. The Key\n \
			2. The File\n");
		return 1;
	}

	char* key = argv[1];
	char* filename = argv[2];
	FILE *file = fopen(filename, "r");
	if(file == NULL) {
		printf("Error opening file\n");
		return 1;
	}

	char buffer[100] = {0};
	while(fgets(buffer, sizeof(buffer), file) != NULL) {
		encrypt(buffer, key);
	}
	fclose(file);
	return 0;
}
