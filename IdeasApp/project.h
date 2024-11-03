#ifndef DEF_PROJECT_H
#define DEF_PROJECT_H

#include <stdlib.h>
#include <string.h>

enum PROJECT_TYPE 
{
    BEGINNER,
    INTERMEDIATE,
    ADVANCED,
};

typedef struct Project 
{
    char* name;
    char** project_desc;
    enum PROJECT_TYPE type;
} Project;

Project** initProjects();
Project* loadProject(enum PROJECT_TYPE type);

#endif
