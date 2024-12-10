#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1000


char *encrypt(char *text, char *key) {
	int index_key = 0, index_text = 0;
	
	//speicher zuweisen
	char *encrypted = malloc(strlen(text) * sizeof(char) + 1);

	//durch gesamten string durchgehen
	while(text[index_text] != '\0') {

		//wenn ende vom key erreicht wird wieder von vorne anfangen
		if(key[index_key] == '\0') {
			index_key = 0;
		}

		//bei neuer zeile mit key von vorne anfangen
		if(text[index_text] == '\n') {
			encrypted[index_text] = text[index_text];
			index_key = 0;
			index_text++;
			continue;
		}

		//steuerzeichen ignorieren
		if(text[index_text] < ' ') {
			encrypted[index_text] = text[index_text];
			index_text++;
			index_key++;
			continue;
		}

		//verschlüsseln / entschlüsseln
		encrypted[index_text] = text[index_text] ^ (0x0f & key[index_key]);
		index_text++;
		index_key++;
	}

	//verschlüsselten text null terminieren, da schleife davor endet
	encrypted[index_text] = '\0';

	//verschlüsselten text als pointer zurückgeben
	return encrypted;
}


int main(int argc, char **argv) {

	//key und dateiname als programm-parameter
	char *key = argv[1];
	char *filename = argv[2];

	//buffer für eingelesene datei
	//liest gesamte datei auf einmal
	char buffer[SIZE];

	//datei öffnen
	FILE *p_file = fopen(filename, "r");
	if(p_file == NULL) {
		printf("Error reading file\n");
		return 1;
	}

	//datei einlesen und null-terminieren
	int n = 0;
	while((buffer[n] = fgetc(p_file)) != EOF) {
		n++;
	}
	buffer[n] = '\0';
	printf("##########Read from file:##########\n");
	printf("%s\n", buffer);

	//funkion anwenden und per printf ausgeben, könnte man auch mit fwrite machen
	char *encrypted = encrypt(buffer, key);
	printf("##########Decrypted text:##########\n");
	printf("%s\n", encrypted);

	fclose(p_file);
	return 0;
}
		
