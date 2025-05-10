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


	system("cls");
	printf("enter your alias\n");
	scanf("%29[^\n]",temp1.name);
	while ((getchar()) != '\n');
	
	fseek(pointer, 0, SEEK_SET);
	fread(&id, sizeof(int), 1, pointer);
	fseek(pointer, ((int)sizeof(int) + (int)sizeof(temp1.name) * id), SEEK_SET);
	fwrite(&temp1.name, sizeof(temp1.name), 1, pointer);
	id++;
	temp1.id = id;
	fseek(pointer, 0, SEEK_SET);
	fwrite(&id, sizeof(int), 1, pointer);
	fseek(pointer, 0, SEEK_SET);

	char name[35];
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
	printf("\n3) delete profile");

	printf("\n\n Option selected :  ");
	do
	{
		scanf("%d", &choice);
	} while (choice <= 0 || choice >3 );
	getchar();

	switch (choice)
	{
	
	case 1:
		pP = createProfile(pFL,pP); 
		break;
	
	case 2:
		pP = switchProfile(pP,pFL);
		break;
	
	case 3:
		deleteProfile(pFL, pP);
		break;

	default:
		break;
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
	} while (choice <= 0 || choice > n);

	char name[35];
	fseek(pFL, ((int)sizeof(int) + 30 * (choice-1)), SEEK_SET);
	fread(name, 30, 1, pFL);
	profilePointer = fopen(strcat(name, txt), "a+");
	if (profilePointer == NULL)
	{
		exit(EXIT_FAILURE);
	}
	
	system("cls");

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
	system("cls");
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
	char name[35] = { "\0" };

	do
	{
		scanf("%d", &choice);
	} while (choice <= 0 || choice > n);


	char namet[35];
	fseek(pFL, ((int)sizeof(int) + 30 * (choice - 1)), SEEK_SET);
	fread(namet, 30, 1, pFL);
	strcat(namet, txt);
	if ((remove(namet)) != 0){
	fclose(pP);
	remove(namet);

	for (int i = 0; i < (n - choice); i++)
	{
		fseek(pFL, ((int)sizeof(int) + 30 * (choice + i)), SEEK_SET);
		fread(name, 30, 1, pFL);
		fseek(pFL, ((int)sizeof(int) + 30 * (choice + i)), SEEK_SET);
		fwrite("\0", 30, 1, pFL);
		fseek(pFL, ((int)sizeof(int) + 30 * ((choice + i) - 1)), SEEK_SET);
		fwrite(name, 30, 1, pFL);
	}

	fseek(pFL, 0, SEEK_SET);
	n -= 1;
	fwrite(&n, sizeof(int), 1, pFL);


	pP = switchProfile(pP, pFL);
	return;
	};
	

	for (int i = 0; i < (n - choice); i++)
	{
		fseek(pFL, ((int)sizeof(int) + 30 * (choice + i)), SEEK_SET);
		fread(name, 30, 1, pFL);
		fseek(pFL, ((int)sizeof(int) + 30 * (choice + i)), SEEK_SET);
		fwrite("\0", 30, 1, pFL);
		fseek(pFL, ((int)sizeof(int) + 30 * ((choice + i) - 1)), SEEK_SET);
		fwrite(name, 30, 1, pFL);
	}
	
	fseek(pFL,0,SEEK_SET);
	n -= 1;
	fwrite(&n,sizeof(int), 1, pFL);
}