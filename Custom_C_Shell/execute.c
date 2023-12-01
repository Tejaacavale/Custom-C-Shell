#include "headers.h"
void execute_command(char *cmd, int background,char* homedir,char* previousdir,Command commands[], int* countc,Node** deLL)
{
    
    char* stringArray[100];
    int count = 0 ;
    splitString(cmd,stringArray,&count);
    if(strcmp(stringArray[count-1],"&")==0){
        count--;
    }
    // for (int i = 0; i < count; i++) {
    //     printf("%s\n", stringArray[i]);
    // }
    checkAndDeleteCompletedProcesses();
    if(strcmp(stringArray[0],"warp")==0){
        warp(stringArray,count,homedir,previousdir);
    }
    else if(strcmp(stringArray[0],"peek")==0){
        peek(stringArray,count,previousdir,homedir);
    }
    else if(strcmp(stringArray[0],"pastevents")==0){
        pastevents(stringArray,count,commands,countc,homedir,previousdir,deLL);
        }
    else if (strcmp(stringArray[0],"seek")==0){
        seek(stringArray,count,homedir);
    }
    else if (strcmp(stringArray[0],"proclore")==0){
        proclore(stringArray,count);
    }
    else if(strcmp(stringArray[0],"exit")==0){
        addCommand(commands,countc,"exit");
        writeCommandsToFile(homedir,commands,*countc);
        exit(0);
    }
    else{
        systemcalls(stringArray,background,count,deLL);
    }
}
void splitString(char *inputString, char *stringArray[], int *count) {
    char *token = strtok(inputString, " ");
    while (token != NULL) {
        stringArray[*count] = token;
        (*count)++;
        token = strtok(NULL, " ");
    }
}