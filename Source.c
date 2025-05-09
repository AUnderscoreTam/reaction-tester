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
		showMM(pP, pPfList);
	}
	
	return 0;
}