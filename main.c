#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <cjson/cJSON.h>



int main( int argc, const char* argv[] )
{
    const char *homedir;
    homedir = getenv("HOME");

    FILE* file;
    char version[10];
    char type[50];
    char terminal[5];
    char command[4096];
    char name[255];
    char comment[255];
    char icon[4096];
    char filename[255];
    char filepath[4096] = "tester.txt";
    char appLocation[4096];
    char *repo = NULL;
    char temp;
    char fullRepo[1000];
    char ch;

    int c;
    int optionsCount = 0;
    while ((c = getopt (argc, argv, "a:")) != -1) 
        switch(c) {
            case 'a':
                optionsCount++;

                FILE *repoFile;

                repo = optarg;

                repoFile = fopen("repo.json", "r");

                if (repoFile == NULL)
                {
                    perror("Error while opening the file.\n");
                    exit(EXIT_FAILURE);
                }
                char buffer[150];
                while(fgets(buffer,150,repoFile)){
                    strcat(fullRepo,buffer);
                }

                fclose(repoFile);

                cJSON *json = cJSON_Parse(fullRepo);

                if (json == NULL)
                {
                    const char *error_ptr = cJSON_GetErrorPtr();
                    if (error_ptr != NULL)
                    {
                        fprintf(stderr, "Error before: %s\n", error_ptr);
                    }
                    cJSON_Delete(json);
                    return 0;
                }
                cJSON *item = NULL;

                cJSON_ArrayForEach(item, json) {
                    cJSON *jLabel = cJSON_GetObjectItemCaseSensitive(item, "label");
                    if (cJSON_IsString(jLabel) && (jLabel->valuestring != NULL))
                    {
                        if(strcmp(repo, jLabel->valuestring) == 0) {
                            printf("is this one \n");
                            cJSON *jName = cJSON_GetObjectItemCaseSensitive(item, "name");
                            cJSON *jVersion = cJSON_GetObjectItemCaseSensitive(item, "version");
                            cJSON *jType = cJSON_GetObjectItemCaseSensitive(item, "type");
                            cJSON *jTerminal = cJSON_GetObjectItemCaseSensitive(item, "terminal");
                            cJSON *jCommand = cJSON_GetObjectItemCaseSensitive(item, "exec");
                            cJSON *jComment = cJSON_GetObjectItemCaseSensitive(item, "comment");
                            cJSON *jIcon = cJSON_GetObjectItemCaseSensitive(item, "icon");
                            printf( "%s location: ", jName->valuestring );
                            char appPath[4096];
                            scanf("%[^\n]", &appPath);
                            scanf("%c",&temp); // temp statement to clear buffer

                            strcpy(version, jVersion->valuestring);
                            strcpy(command, sprintf("%s/%s",appPath, jCommand->valuestring));
                            strcpy(terminal, jTerminal->valuestring);
                            strcpy(filename, sprintf("%s%s",jLabel->valuestring, ".desktop"));
                            strcpy(comment, jComment->valuestring);
                            strcpy(icon, sprintf("%s/%s", appPath, jIcon->valuestring));
                            strcpy(type, jType->valuestring);
                            strcpy(name, jName->valuestring);

                        }
                    }

                }
                break;
        }
    if(optionsCount == 0) {
        printf( "Version: " );
        scanf("%[^\n]", &version);
        scanf("%c",&temp); // temp statement to clear buffer
        printf( "Type: " );
        scanf("%[^\n]", &type);
        scanf("%c",&temp); // temp statement to clear buffer
        printf( "Terminal (true,false): " );
        scanf("%[^\n]", &terminal);
        scanf("%c",&temp); // temp statement to clear buffer
        printf( "Command to execute: " );
        scanf("%[^\n]", &command);
        scanf("%c",&temp); // temp statement to clear buffer
        printf( "Name: " );
        scanf("%[^\n]", &name);
        scanf("%c",&temp); // temp statement to clear buffer
        printf( "Comment: " );
        scanf("%[^\n]", &comment);
        scanf("%c",&temp); // temp statement to clear buffer
        printf( "Icon path: " );
        scanf("%[^\n]", &icon);
        scanf("%c",&temp); // temp statement to clear buffer
        printf( "File name: " );
        scanf("%[^\n]", &filename);
        scanf("%c",&temp); // temp statement to clear buffer
    }

    char output[10000];
    sprintf(output,"#!/usr/bin/env xdg-open\n[Desktop Entry]\nVersion=%s\nType=%s\nTerminal=%s\nExec=%s\nName=%s\nComment=%s\nIcon=%s\n", version, type, terminal, command, name, comment, icon);
    sprintf(filepath, "%s/.local/share/applications/%s", homedir, filename);
    file = fopen(filepath, "w");
    fprintf(file, output);
    fclose(file);
    return 0;
    
}