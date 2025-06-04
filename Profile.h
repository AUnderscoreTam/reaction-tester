#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <sys/timeb.h>
#include <conio.h>


typedef struct {
	int id;
	char name[30];
}PROFILE;



FILE* createProfile(FILE* const pFL, FILE* pP);
FILE* switchProfile(const FILE* pP, const FILE* const pFL);
void listAllProfiles(const FILE* const pFL);
int scanId(const FILE* const pFL);
void deleteProfile(FILE* const pFL, FILE* pP);
FILE* renameProfile(FILE* const pFL, FILE* pP);
void writeToFile(FILE* const pP, char* string);
void reactionTest(FILE* const pP);
void showProfileSpeed(const FILE* const pP);
void leaderboard(const FILE* const pP, const FILE* const pFL);
int compare(const void* a, const void* b);
int numberOfTrys(const FILE* const pP);
int readspeed(FILE* const pP, int i);
FILE* searchProfile(const FILE* pP, const FILE* const pFL);
int strCompare(const void* a, const void* b);


