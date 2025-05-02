#include "Header.h"

FILE* createProfile(FILE* pointer) {
	PROFILE temp1 = { 0 };
	char txt[5] = { ".txt" };
	FILE* profilePointer = NULL;
	int id = 0;

	system("cls");
	printf("enter your alias\n");
	scanf("%29[^\n]",temp1.name);
	getchar();
	
	fseek(pointer, 0, SEEK_SET);
	fread(&id, sizeof(int), 1, pointer);
	fseek(pointer, (1+sizeof(temp1.name)*id), SEEK_SET);
	fwrite(&temp1.name, sizeof(temp1.name), 1, pointer);
	id++;
	temp1.id = id;
	fseek(pointer, 0, SEEK_SET);
	fwrite(&id, sizeof(int), 1, pointer);
	printf("%d", temp1.id);

	profilePointer=fopen(strcat(temp1.name, txt), "a+");
	if (profilePointer == NULL)
	{
		exit(EXIT_FAILURE);
	}

	return profilePointer;
}