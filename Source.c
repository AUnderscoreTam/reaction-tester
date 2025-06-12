#include "Profile.h"

extern const int zero = 0;

enum choice
{
	play=1,
	display_all_times_in_profile,
	display_profile_time_leaderboard,
	
	create_new_profile,
	switch_profile,
	switch_profile_by_name,
	rename_profile,
	delete_profile,
	exit_program,
};

int main() {
	static FILE* pPfList= NULL;
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
			if (i>30)
			{
				fseek(pP, -32, SEEK_END);
				if (fscanf(pP, "%29[^\n]", lastRecordedSpeed) == 0) {
					fseek(pP, -31, SEEK_END);
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
		printf("\n2) display all times in profile");
		printf("\n3) display profile time leaderboard");
		printf("\n4) create new profile");
		printf("\n5) switch profile");
		printf("\n6) switch profile by name");
		printf("\n7) rename profile");
		printf("\n8) delete profile");
		printf("\n9) exit program")

		printf("\n\n Option selected :  ");
		do
		{
			scanf("%d", &choice);
			getchar();
		} while (choice <= 0 || choice > 9);


		switch (choice)
		{

		case play:
			reactionTest(pP);
			break;

		case display_all_times_in_profile :
			showProfileSpeed(pP);
			break;

		case display_profile_time_leaderboard :
			leaderboard(pP, pPfList);
			break;

		case create_new_profile:
			pP = createProfile(pPfList, pP);
			break;

		case switch_profile_by_name:
			pP = searchProfile(pP, pPfList);
			break;

		case switch_profile :
			pP = switchProfile(pP, pPfList);
			break;
		
		case rename_profile :
			pP = renameProfile(pPfList, pP);
			break;

		case delete_profile:
			deleteProfile(pPfList, pP);
			break;

		case exit_program:
			printf("are you sure you  want to quit?\ncofirm by typing y\n");
			if(getchar()=='y' || 'Y'){
			fclose(pP);
			pP=NULL;
			fclose(pPfList);
			pPfList=NULL;
			exit(EXIT_SUCCESS);
			}
		
		default:
			break;
		}

	}
	
	return 0;
}
