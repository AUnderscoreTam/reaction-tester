#include "Header.h"

extern char txt[5] = { ".txt" };

FILE* createProfile(FILE* pointer,FILE* pP) {
	PROFILE temp1 = { 0 };
	char txt[5] = { ".txt" };
	FILE* profilePointer = NULL;
	int id = 0;
	time_t now = time(NULL);

	if (pP != NULL)
	{
		fclose(pP);
	}


	printf("enter your alias\n");
	scanf("%29[^\n]", temp1.name);

	while ((getchar()) != '\n');
	
	if (temp1.name[0] == '\0') {return createProfile(pointer, pP);}

	char name[35];
	strcpy(name, temp1.name);

	if ((fopen(strcat(name, txt), "r")) == NULL)
	{
		profilePointer = fopen(name, "a+");
		if (profilePointer == NULL)
		{
			exit(EXIT_FAILURE);
		}

		fputs(temp1.name, profilePointer);
		fflush(profilePointer);

		fseek(pointer, 0, SEEK_SET);
		fread(&id, sizeof(int), 1, pointer);
		fseek(pointer, ((int)sizeof(int) + (int)sizeof(temp1.name) * id), SEEK_SET);
		fwrite(&temp1.name, sizeof(temp1.name), 1, pointer);
		id++;
		temp1.id = id;
		fseek(pointer, 0, SEEK_SET);
		fwrite(&id, sizeof(int), 1, pointer);
		fseek(pointer, 0, SEEK_SET);
		return profilePointer;
	}
	else
	{
		printf("alias already taken");
		Sleep(3500);
		createProfile(pointer, pP);
	}
}

FILE* switchProfile(FILE* pP, FILE* pFL) {
	
	FILE* profilePointer = NULL;
	int n = scanId(pFL);
	int choice = 0;
	listAllProfiles(pFL);

	if (pP != NULL)
	{
		fclose(pP);
	}

	do
	{
		scanf("%d", &choice);
		getchar();
	} while (choice <= 0 || choice > n);

	char name[35];
	fseek(pFL, ((int)sizeof(int) + 30 * (choice-1)), SEEK_SET);
	fread(name, 30, 1, pFL);
	profilePointer = fopen(strcat(name, txt), "a+");
	if (profilePointer == NULL)
	{
		exit(EXIT_FAILURE);
	}
	return profilePointer;
	
}

char* listProfile(FILE* pFL,int n) {
	/*
		char name[30];
	fseek(pFL, (sizeof(int) + 30 * n), SEEK_SET);
	fread(name, 30, 1, pFL);

	return name;
	*/
} // NAUCI KORISTITI RETURNATI STRINGOVE 

void listAllProfiles(FILE* pFL) {
	char name[30];
	int n = scanId(pFL);
	
	for (int i = 0; i < n; i++)
	{
	fread(name, 30, 1, pFL);
	printf("%d)%s\t", i+1 ,name);
	}
}

int scanId(FILE* pFL) {
	int n = 0;
	fseek(pFL, 0, SEEK_SET);
	fread(&n, sizeof(int), 1, pFL);
	return n;
}

void deleteProfile(FILE* pFL, FILE* pP) {
	FILE* profilePointer = NULL;
	int n = scanId(pFL);
	int choice = 0;
	listAllProfiles(pFL);
	char name[30] = {0};
	char emtpy[30] = {0};


	do
	{
		scanf("%d", &choice);
		getchar();
	} while (choice <= 0 || choice > n);

	char namet[35];
	fseek(pFL, ((int)sizeof(int) + 30 * (choice - 1)), SEEK_SET);
	fread(namet, 30, 1, pFL);
	strcat(namet, txt);
	if ((remove(namet)) != 0){
		fclose(pP);
		remove(namet);

		if (n == choice) {
			fseek(pFL, ((int)sizeof(int) + 30 * (choice-1)), SEEK_SET);
			fwrite(emtpy, 30, 1, pFL);
		}

		for (int i = 0; i < (n - choice); i++)
		{
		fseek(pFL, ((int)sizeof(int) + 30 * (choice + i)), SEEK_SET);
		fread(name, 30, 1, pFL);
		fseek(pFL, ((int)sizeof(int) + 30 * (choice + i)), SEEK_SET);
		fwrite(emtpy, 30, 1, pFL);
		fseek(pFL, ((int)sizeof(int) + 30 * ((choice + i) - 1)), SEEK_SET);
		fwrite(name, 30, 1, pFL);
		}

		fseek(pFL, 0, SEEK_SET);
		n -= 1;
		fwrite(&n, sizeof(int), 1, pFL);

		if (n==0)
		{
			pP = createProfile(pFL,pP);
		}
		else
		{
			pP = switchProfile(pP, pFL);
		}
		return;
	};
	
	if (n == choice) {
		fseek(pFL, ((int)sizeof(int) + 30 * (choice-1)), SEEK_SET);
		fwrite(emtpy, 30, 1, pFL);
	}

	for (int i = 0; i < (n - choice); i++)
	{
		fseek(pFL, ((int)sizeof(int) + 30 * (choice + i)), SEEK_SET);
		fread(name, 30, 1, pFL);
		fseek(pFL, ((int)sizeof(int) + 30 * (choice + i)), SEEK_SET);
		fwrite(emtpy, 30, 1, pFL);
		fseek(pFL, ((int)sizeof(int) + 30 * ((choice + i) - 1)), SEEK_SET);
		fwrite(name, 30, 1, pFL);
	}
	
	fseek(pFL,0,SEEK_SET);
	n -= 1;
	fwrite(&n,sizeof(int), 1, pFL);
}