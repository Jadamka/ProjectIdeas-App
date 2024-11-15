#ifndef DEF_PROJECT_H
#define DEF_PROJECT_H

#include <stdio.h>

#define DELIM "="

typedef enum projectType 
{
    BEGINNER = 1,
    INTERMEDIATE = 2,
    ADVANCED = 3,
} projectType_t;

typedef struct project_t
{
    char *name; // name of the project
    char *desc; // description of the project
    projectType_t type;
} project_t;

int get_num_of_lines(FILE *fptr);
project_t *read_projects(const char *path, int *projectsCount);
void free_projects(project_t *projects, int *projectsCount);

#endif
