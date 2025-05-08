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
	fseek(pointer, ((int)sizeof(int) + (int)sizeof(temp1.name) * id), SEEK_SET);
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
	fscanf(pP, "%29[^\n]", profileName);

	printf("Profile selected: %s\n\n",profileName);
	
	printf("############################################\n");
	printf("\tSelect a option to continue\n");
	printf("\n1) create new profile");
	printf("\n2) switch profile");


	printf("\n\n Option selected :  ");
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
	
	case 2:
		listAllProfiles(pFL);
		//return switchProfile(pP,pFL);
		break;

	default:
		break;
	}

}

FILE* switchProfile(FILE* pP, FILE* pFL) {
	fclose(pP);
		




}

void listAllProfiles(FILE* pFL) {
	system("cls");
	int n = 0;
	char name[30];
	fseek(pFL, 0, SEEK_SET);
	fread(&n, sizeof(int), 1, pFL);
	
	for (int i = 0; i < n; i++)
	{
 	fread(name, 30, 1, pFL);
	printf("%s\n", name);
	}
}