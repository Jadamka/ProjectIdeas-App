#ifndef DEF_PROJECT_H
#define DEF_PROJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DELIM "="

enum PROJECT_TYPE 
{
    BEGINNER = 1,
    INTERMEDIATE = 2,
    ADVANCED = 3,
};

typedef struct Project 
{
    char* name; // name of the project
    char* desc; // description of the project
    enum PROJECT_TYPE type;
} Project;

int GetNumOfLines(FILE* fptr);
Project* ReadProjects(const char* path, int* projectsCount);
void FreeProjects(Project* projects, int* projectsCount);

#endif
