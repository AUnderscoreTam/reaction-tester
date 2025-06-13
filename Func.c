#include "Profile.h"

extern char txt[5] = { ".txt" };

FILE* createProfile(FILE* const pFL,FILE* pP) {
	PROFILE temp1 = { 0 };
	FILE* profilePointer = NULL;
	int id = 0;
	time_t now = time(NULL);

	if (pP != NULL)
	{
		fclose(pP);
	}


	printf("enter your alias\n");
	if (scanf("%29[^\n]", temp1.name) == 0) {
		perror("Error at line 20:");
	}

	while ((getchar()) != '\n');
	
	if (temp1.name[0] == '\0') {return createProfile(pFL, pP);}

	char name[35];
	strcpy(name, temp1.name);

	if ((fopen(strcat(name, txt), "r")) == NULL)
	{
		FILE* Temp=fopen(name, "w");
		fclose(Temp);
		profilePointer = fopen(name, "r+");
		if (profilePointer == NULL)
		{
			exit(EXIT_FAILURE);
		}
		for (int i = 0; i < 30; i++)
		{
			fputs(" ", profilePointer);
		}
		rewind(profilePointer);
		fputs(temp1.name, profilePointer);
		fseek(profilePointer, 0, SEEK_END);
		fputs("\n", profilePointer);
		fflush(profilePointer);

		fseek(pFL, 0, SEEK_SET);
		fread(&id, sizeof(int), 1, pFL);
		fseek(pFL, ((int)sizeof(int) + (int)sizeof(temp1.name) * id), SEEK_SET);
		fwrite(&temp1.name, sizeof(temp1.name), 1, pFL);
		id++;
		temp1.id = id;
		fseek(pFL, 0, SEEK_SET);
		fwrite(&id, sizeof(int), 1, pFL);
		fseek(pFL, 0, SEEK_SET);
		return profilePointer;
	}
	else
	{
		printf("alias already taken");
		Sleep(3500);
		createProfile(pFL, pP);
	}
}

FILE* switchProfile(const FILE* pP, const FILE* const pFL) {
	
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
		if(scanf("%d", &choice) == 0) {
			perror("Error at line 82:");
	}
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

void listAllProfiles(const FILE* const pFL) {
	char name[30];
	int n = scanId(pFL);
	
	for (int i = 0; i < n; i++)
	{
	fread(name, 30, 1, pFL);
	printf("%d)%s\t", i+1 ,name);
	}
}

int scanId(FILE* const pFL) {
	int n = 0;
	fseek(pFL, 0, SEEK_SET);
	fread(&n, sizeof(int), 1, pFL);
	return n;
}

void deleteProfile(FILE* const pFL, FILE* pP) {
	FILE* profilePointer = NULL;
	int n = scanId(pFL);
	int choice = 0;
	listAllProfiles(pFL);
	char name[30] = {0};
	char emtpy[30] = {0};


	do
	{
		if(scanf("%d", &choice) == 0) {
			perror("Error at line 129:");
	}
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

FILE* renameProfile(FILE* const pFL, FILE* pP) {
	int n = scanId(pFL);
	int choice = 0;
	listAllProfiles(pFL);
	char name[30] = { 0 };
	char emtpy[30] = { 0 };
	char namet[35] = { 0 };
	char namet2[35] = { 0 };
	char namet3[35] = { 0 };
	int warning = 0;
	char c = 0;
	int i=0;
	



	fclose(pP);

	do
	{
		if(scanf("%d", &choice) == 0) {
			perror("Error at line 213:");
	};
		getchar();
	} while (choice <= 0 || choice > n);

	fseek(pFL, ((int)sizeof(int) + 30 * (choice - 1)), SEEK_SET);
	fread(namet, 30, 1, pFL);
	strcat(namet, txt);

	do
	{
		if (warning>=1)
		{
			printf("alias already taken\n");
		}
		printf("enter new alias\n");
		if(scanf("%29[^\n]", name) == 0) {
			perror("Error at line 230:");
		}
		while ((getchar()) != '\n');
		strcpy(namet2, name);
		warning++;
	} while ((fopen(strcat(namet2, txt), "r")) != NULL);
	
	
	fseek(pFL, ((int)sizeof(int) + 30 * (choice - 1)), SEEK_SET);
	fwrite(emtpy, 30, 1, pFL);
	fseek(pFL, ((int)sizeof(int) + 30 * (choice - 1)), SEEK_SET);
	fwrite(name, 30, 1, pFL);
	fflush(pFL);
	pP = fopen(namet, "r+");
	if (pP==NULL)
	{
		exit(EXIT_FAILURE);
	}
	rewind(pP);
	while((c=fgetc(pP))!='\n')
	{
		if (c==EOF)
		{
			break;
		}
		i++;
	}
	for (int y = 0; y < i; y++)
	{
		fseek(pP, y, SEEK_SET);
		fprintf(pP, "%s", " ");
	}
	fseek(pP, 0, SEEK_SET);
	fprintf(pP, "%s", name);
	fclose(pP);

	if(rename(namet, namet2) != 0) {
		perror("Error at line 267:");
	}


	if ((pP=fopen(namet2,"r+"))==NULL)
	{
		exit(EXIT_FAILURE);
	}
	return pP;
		 
}

void writeToFile(FILE* const pP, char* string) {
	struct tm* tim;
	time_t t;
	char temp[30];
	t = time(NULL);
	tim = localtime(&t);
	strftime(temp, sizeof(temp), "%d/%B/%y - %I:%M%p",tim);
	fseek(pP, 0, SEEK_END);
	fprintf(pP, "%s\t%s     \n", string,temp);
}

void reactionTest(FILE* const pP) {
	int offset = 0;
	struct timeb time1 = { NULL };
	struct timeb time2 = { NULL };
	char buf = '!';
	int rez=0;
	char buffer[245] = { '0' };
	offset = 1000 + (float)rand() / RAND_MAX * (7000 - 1000);

	system("cls");
	printf("press any key when the hashtags turn green\n");
	printf("\033[0;31m############\n############\n############\n############\n\033[0m");
	Sleep((1000 + offset));
	system("cls");
	printf("wait for the hashtags to turn green\n");
	printf("\033[0;32m############\n############\n############\n############\n\033[0m");
	Sleep(60);
	ftime(&time1);
	while (buf=='!')
	{
		buf = _getch();
	}
	ftime(&time2);
	rez = ((time2.time - time1.time)*1000 + time2.millitm) - time1.millitm;
	if (rez<60)
	{
		rez = 0;
	}
	if (rez == 0)
	{
		printf("pressed too early\n");
		Sleep(3000);
	}
	else if(rez >=9999)
	{
		printf("pressed too late\n");
		Sleep(3000);
	}
	else {
		printf("%d\n", rez);
		sprintf(buffer, "%d", rez);
		writeToFile(pP, buffer);
	}
}

void showProfileSpeed(const FILE* const pP) {
	char c = 0;
	rewind(pP);
	printf("\n");
	while (fgetc(pP) != '\n') {
	}
	while ((c=fgetc(pP)) != EOF) {
		printf("%c",c);
	}
	printf("\n");
}


void leaderboard(const FILE* const pP, const FILE* const pFL){
	int y = numberOfTrys(pP);
	int* array = (int*)calloc(y, sizeof(int));
	if (array==NULL)
	{
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < y; i++)
	{
		array[i] = readspeed(pP, i);
	}

	qsort(array, y, sizeof(int), compare);
	for (int i = 0; i < y; i++)
	{
		printf("%d\n", array[i]);
	}
	if (array != NULL) {
		free(array);
		array = NULL;
	}
}

int compare(const void* a, const void* b) { return (*(int*)a - *(int*)b); }

int numberOfTrys(const FILE* const pP) {
	char c;
	int rez=0;
	rewind(pP);
	while (fgetc(pP) != '\n') {
	}
	while ((c = fgetc(pP)) != EOF) {
		if (c=='\n')
		{
			rez++;
		};
	}
	return rez;
}

int readspeed(FILE* const pP, int i) {
	char c = 0;
	int rez = 0;
	rewind(pP);
	while (fgetc(pP) != '\n') {
	}
	fseek(pP, 30 * i, SEEK_CUR);
	if(fscanf(pP, "%d", &rez) == 0) {
		perror("Error at line 390:");
	}
	return rez;
}

FILE* searchProfile(const FILE* pP, const FILE* const pFL) {
	int n = scanId(pFL);
	FILE* profilePointer = NULL;
	char* chosen = NULL;
	char* array = (char*)calloc(n, sizeof(char)*30);
	if (array==NULL)
	{
		exit(EXIT_FAILURE);
	}
	char key[30] = { 0 };

	printf("enter your alias\n");
	if(scanf("%29[^\n]",key) == 0) {
		perror("Error at line 487:");
	}

	while ((getchar()) != '\n');

	for (int i = 0; i < scanId(pFL); i++)
	{
		fseek(pFL, ((int)sizeof(int) + 30 * i), SEEK_SET);
		fread((array+30*i), 30, 1, pFL);
	}

	qsort(array, n, 30, strCompare);
	
	if ((chosen=(char*)bsearch(&key, array, scanId(pFL), 30, strCompare)) == NULL) {
		printf("no profile matching name found\n");
		return pP;
	}
	else
	{
		if (pP != NULL)
		{
			fclose(pP);
		}

		profilePointer = fopen(strcat(chosen, txt), "a+");
		if (profilePointer == NULL)
		{
			exit(EXIT_FAILURE);
		}
		return profilePointer;
	}
}

int strCompare(const void* a, const void* b) {return strcmp((const char*)a, (const char*)b);}