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
	int runs;
}PROFILE;



FILE* createProfile(FILE* pointer,FILE* pP);
FILE* switchProfile(FILE* pP, FILE* pFL);
void listAllProfiles(FILE* pFL);
char* listProfile(FILE* pFL, int n);
int scanId(FILE* pFL);
void deleteProfile(FILE* pFL, FILE* pP);
FILE* renameProfile(FILE* pFL, FILE* pP);
void writeToFile(FILE* pP, char* string);
void reactionTest(FILE* pP);
