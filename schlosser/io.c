#include <stdio.h>
#include <stdlib.h>


void encrypt(char *text, char *key) {
	unsigned int index_text, index_key = 0;
	while(text[index_text] != '\0' && index_text < 1000) {
		if(key[index_key] == '\0' || text[index_text] == '\n') {
			index_key = 0;
		}
		if(text[index_text] < ' ') {
			index_text++;
			index_key++;
			continue;
		}
		text[index_text] = text[index_text] ^ (0x0f & key[index_key]);
		index_text++;
		index_key++;
	}
}


int main(int argc, char **argv) {
	char *key = argv[1];
	char *filename = argv[2];
	FILE *file = fopen(filename, "r");
	
	char buffer[1000];
	int i = 0;
	int c;
	while((c = fgetc(file)) != EOF) {
		buffer[i] = c;
		i++;
	}
	buffer[i] = '\0';

	encrypt(buffer, key);
	i = 0;
	while(buffer[i] != '\0') {
		printf("%c", buffer[i]);
	}
	printf("\n");
	fclose(file);
	return 0;
}
