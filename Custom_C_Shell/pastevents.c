#include "headers.h"
void pastevents(char* stringArray[], int counts,Command commands[], int* countc,char* homedir,char* previousdir,Node** LL){
    if (counts==1){
        printCommands(commands,*countc);
    }
    else if(strcmp(stringArray[1],"purge")==0){
        (*countc)=0;
        writeCommandsToFile(homedir,commands,*countc);
    }
    else if(strcmp(stringArray[1],"execute")==0){
        int number = atoi(stringArray[2]);
        if(number>*countc){
            printf("These many pastevents are not stored !\n");
            return;
        }
        char cmd[4096];
        int lol=0;
        strcpy(cmd,commands[(*countc)-number].command);
        if(cmd[strlen(cmd)-1]=='&'){
            lol=1;
        }
        execute_command(cmd,lol,homedir, previousdir,commands,countc,LL);
    }
}