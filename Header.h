#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>


typedef struct {
	int id;
	char name[30];
	int runs;
}PROFILE;



FILE* createProfile(FILE* pointer);
void showMM(FILE* pP, FILE* pFL);
