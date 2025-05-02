#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>


typedef struct {
	int id;
	char name[30];
	int runs;
}PROFILE;

int isPListempty(FILE* pointer);
FILE* createProfile(FILE* pointer);