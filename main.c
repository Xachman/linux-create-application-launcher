#include <stdio.h>
#include <stdlib.h>


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
    char temp;
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

    char output[10000];
    sprintf(output,"#!/usr/bin/env xdg-open\n[Desktop Entry]\nVersion=%s\nType=%s\nTerminal=%s\nExec=%s\nName=%s\nComment=%s\nIcon=%s\n", version, type, terminal, command, name, comment, icon);
    sprintf(filepath, "%s/.local/share/applications/%s", homedir, filename);
    file = fopen(filepath, "w");
    fprintf(file, output);
    fclose(file);
    return 0;
    
}