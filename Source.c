#include "Header.h"

extern const int zero = 0;

int main() {
	FILE* pPfList= NULL;
	FILE* pP = NULL;

	srand((unsigned)time(NULL));

	pPfList = fopen("Profile_List", "rb+");
	if (pPfList == NULL)
	{
		fopen("Profile_List", "wb+");
		pPfList = fopen("Profile_List", "rb+");
		if (pPfList == NULL) {
			exit(EXIT_FAILURE);
		}
		fseek(pPfList,0,SEEK_SET);
		fwrite(&zero, sizeof(int), 1, pPfList);
		pP = createProfile(pPfList,pP);
	}
	if (pP == NULL)
	{
		pP=switchProfile(pP, pPfList);
	}

	while (1) {
		char profileName[30];
		char c=8;
		char lastRecordedSpeed[30] = {0};
		int choice = 0;
		int i = 0;
		int bN = 0;
		fseek(pP, 0, SEEK_SET);
		fscanf(pP, "%29[^\n]", profileName);
		fseek(pP, 0, SEEK_SET);
		while ((c=fgetc(pP)) != EOF) {
			if (i>=32)
			{
				fseek(pP, -29, SEEK_END);
				if (fscanf(pP, "%29[^\n]", lastRecordedSpeed) == 0) {
					fseek(pP, -28, SEEK_END);
					fscanf(pP, "%29[^\n]", lastRecordedSpeed);
				};
				break;
			}
			i++;
		}

		printf("Profile selected: %s\nLast recorded speed: %s\n", profileName,lastRecordedSpeed);

		printf("############################################\n");
		printf("\tSelect a option to continue\n");
		printf("\n1) play");
		printf("\n2) create new profile");
		printf("\n3) switch profile");
		printf("\n4) delete profile");
		printf("\n5) rename profile");
		

		printf("\n\n Option selected :  ");
		do
		{
			scanf("%d", &choice);
			getchar();
		} while (choice <= 0 || choice > 5);


		switch (choice)
		{

		case 1:
			reactionTest(pP);
			break;

		case 2:
			pP = createProfile(pPfList, pP);
			break;

		case 3:
			pP = switchProfile(pP, pPfList);
			break;

		case 4:
			deleteProfile(pPfList, pP);
			break;
		
		case 5:
			pP = renameProfile(pPfList, pP);
			break;

		default:
			break;
		}

	}
	
	return 0;
}