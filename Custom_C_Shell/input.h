#ifndef __INPUT_H
#define __INPUT_H

void trim_spaces(char *str);
void trimSpacesAndTabs(char *str);
void tokenise_input(char* homedir,char* previousdir,Command commands[], int *count,Node** LL);
void addCommand(Command commands[], int *count, const char *command);
void writeCommandsToFile(const char *homedir, Command commands[], int count);
void printCommands(Command commands[], int count);
void readCommandsFromFile(const char *filename, Command commands[], int *count);
#endif