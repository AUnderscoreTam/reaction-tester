#include "Header.h"

extern const int zero = 0;

int main() {
	FILE* pPfList= NULL;
	FILE* pP = NULL;

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
		int choice = 0;
		fseek(pP, 0, SEEK_SET);
		fscanf(pP, "%29[^\n]", profileName);

		printf("Profile selected: %s\n\n", profileName);

		printf("############################################\n");
		printf("\tSelect a option to continue\n");
		printf("\n1) create new profile");
		printf("\n2) switch profile");
		printf("\n3) delete profile");

		printf("\n\n Option selected :  ");
		do
		{
			scanf("%d", &choice);
			getchar();
		} while (choice <= 0 || choice > 3);




		switch (choice)
		{

		case 1:
			pP = createProfile(pPfList, pP);
			break;

		case 2:
			pP = switchProfile(pP, pPfList);
			break;

		case 3:
			deleteProfile(pPfList, pP);
			break;

		default:
			break;
		}

	}
	
	return 0;
}