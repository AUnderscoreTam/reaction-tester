#include "Header.h"

extern const int zero = 0;

int main() {
	FILE* pPfList= NULL;

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
		createProfile(pPfList); 
	}



	return 0;
}