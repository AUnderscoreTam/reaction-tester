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
		if(fopen("Profile_List", "wb+") == NULL) {
			perror("Error at line 28 (Source.c):");
	};
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
		char choiExit  = 0;
		fseek(pP, 0, SEEK_SET);
		if(fscanf(pP, "%29[^\n]", profileName) == 0) {
			perror("Error at line 53:");
		}
		fseek(pP, 0, SEEK_SET);
		while ((c=fgetc(pP)) != EOF) {
			if (i>30)
			{
				fseek(pP, -32, SEEK_END);
				if (fscanf(pP, "%29[^\n]", lastRecordedSpeed) == 0) {
					fseek(pP, -31, SEEK_END);
					if(fscanf(pP, "%29[^\n]", lastRecordedSpeed) == 0) {
						perror("Error at line 62 (Source.c):");
					}
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
		printf("\n9) exit program");

		printf("\n\n Option selected :  ");
		do
		{
			if(scanf("%d", &choice) == 0) {
				perror("Error at line 88 (Source.c):");
			}
			getchar();
		} while (choice <= 0 || choice > 9);


		switch (choice)
		{

		case play:
			system("cls");
			reactionTest(pP);
			system("cls");
			break;

		case display_all_times_in_profile :
			system("cls");
			showProfileSpeed(pP);
			break;

		case display_profile_time_leaderboard :
			system("cls");
			leaderboard(pP, pPfList);
			break;

		case create_new_profile:
			system("cls");
			pP = createProfile(pPfList, pP);
			break;

		case switch_profile_by_name:
			system("cls");
			pP = searchProfile(pP, pPfList);
			break;

		case switch_profile :
			pP = switchProfile(pP, pPfList);
			system("cls");
			break;
		
		case rename_profile :
			system("cls");
			pP = renameProfile(pPfList, pP);
			system("cls");
			break;

		case delete_profile:
			system("cls");
			deleteProfile(pPfList, pP);
			break;

		case exit_program:
			printf("are you sure you  want to quit?\nConfirm by typing y\n");
			choiExit = getchar();
			if(choiExit=='y' || choiExit == 'Y'){
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
