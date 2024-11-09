#ifndef DEF_PROJECT_H
#define DEF_PROJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DELIM "="

enum projectType_t 
{
    BEGINNER = 1,
    INTERMEDIATE = 2,
    ADVANCED = 3,
};

typedef struct project_t
{
    char *name; // name of the project
    char *desc; // description of the project
    enum projectType_t type;
} project_t;

int GetNumOfLines(FILE *fptr);
project_t *ReadProjects(const char *path, int *projectsCount);
void FreeProjects(project_t *projects, int *projectsCount);

#endif
