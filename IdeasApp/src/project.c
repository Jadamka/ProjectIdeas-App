#include "project.h"

int GetNumOfLines(FILE *fptr)
{
    char ch;
    int lines = 0;
    while((ch = fgetc(fptr)) != EOF){
        if(ch == '\n'){
            lines++;
        }
    }

    return lines - 3; // 3 difficulties (cant have empty lines, because i do line[strlen(line) - 1] = 0 
}

project_t *ReadProjects(const char *path, int *projectsCount)
{
    FILE *fptr;
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    fptr = fopen(path, "r");
    if(fptr == NULL){
        printf("fopen error\n");
        return NULL;
    }

    // Gets number of lines in a file, so i can allocate memory for Project array
    *projectsCount = GetNumOfLines(fptr);
    project_t *projects = (project_t *)malloc(sizeof(project_t) * (*projectsCount));

    // getNumOfLines moved pointer to the end of file. This sets it back
    rewind(fptr);

    int projectIndex = 0;
    while((nread = getline(&line, &len, fptr)) != -1){
        fwrite(line, nread, 1, stdin);

        // gets rid of '\n' character at the end of string, so i can comprate them easily
        line[strlen(line)-1] = 0;

        if(strcmp(line, "[beginner]") == 0){
            projects[projectIndex].type = BEGINNER;
            continue;
        }
        else if(strcmp(line, "[intermediate]") == 0){
            projects[projectIndex].type = INTERMEDIATE;
            continue;
        }
        else if(strcmp(line, "[advanced]") == 0){
            projects[projectIndex].type = ADVANCED;
            continue;
        }

        // Get name of the project
        char* token = strtok(line, DELIM);
        if(token != NULL){
            projects[projectIndex].name = (char*)malloc(sizeof(char) * (strlen(token) + 1));
            strcpy(projects[projectIndex].name, token);
        }

        // Get description of the project (moves to the next left side before another '=')
        token = strtok(NULL, DELIM);
        if(token != NULL){
            projects[projectIndex].desc = (char*)malloc(sizeof(char) * (strlen(token) + 1));
            strcpy(projects[projectIndex].desc, token);
        }

        projectIndex++;
    }

    free(line);
    fclose(fptr);

    return projects;
}

void FreeProjects(project_t *projects, int *projectsCount)
{
    if(projects != NULL){
        for(int i = 0; i < *projectsCount; i++){
            free(projects[i].name);
            free(projects[i].desc);
        }
        free(projects);
    }
}
















