#include "Header.h"

FILE* createProfile(FILE* pointer) {
	PROFILE temp1 = { 0 };
	char txt[5] = { ".txt" };
	FILE* profilePointer = NULL;
	int id = 0;
	time_t now = time(NULL);


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
	fseek(pointer, 0, SEEK_SET);
	char name[30];
	strcpy(name, temp1.name);
	profilePointer=fopen(strcat(name, txt), "a+");
	if (profilePointer == NULL)
	{
		exit(EXIT_FAILURE);
	}

	fputs(temp1.name,profilePointer);
	fflush(profilePointer);
	return profilePointer;
}

void showMM(FILE* pP , FILE* pFL) {
	char profileName[30];
	int choice = 0;
	rewind(pP);
	fscanf(pP, "%s", profileName);

	printf("Profile selected: %s\n\n",profileName);
	
	printf("############################################\n");
	printf("\tSelect a option to continue\n");
	printf("1) create new account");

	do
	{
		scanf("%d", &choice);
	} while (choice <= 0 || choice >= 6);
	getchar();

	switch (choice)
	{
	
	case 1:
		createProfile(pFL); 
		break;
	
	default:
		break;
	}

}