#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
	unsigned const int len_buffer = 500;
	char *filename = argv[1];
	FILE *p_file = fopen(filename, "r");
	if(p_file == NULL) {
		printf("Error opening file\n");
		return 1;
	}

	char buffer[len_buffer];
	int n = 0;
	while((buffer[n] = fgetc(p_file)) != EOF) {
		n++;
	}
	buffer[n] = '\0';
	if(feof(p_file)) {
		printf("end reached\n");
	}
	printf("read:\n");
	printf("%s", buffer);

	fclose(p_file);
	return 0;
}
