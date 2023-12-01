
#ifndef __EXECUTE_H
#define __EXECUTE_H
void execute_command(char *cmd, int background,char* homedir,char* previousdir,Command commands[], int* countc,Node** LL);
void splitString(char *inputString, char *stringArray[], int *count);
#endif