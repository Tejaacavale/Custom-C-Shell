#include "headers.h"
int numProcesses = 0;
struct ProcessInfo processArray[MAX_PROCESSES];
char promptname[4096];
int timetaken = 0 ; 
int main()
{
    char homedir[4096];
    char previousdir[4096];
    getcwd(homedir,sizeof(homedir));
    strcpy(previousdir,homedir);
    const char *filename = "pastevents.txt";
    Command pastEvents[MAX_COMMANDS];
    int numCommands = 0;
    Node *LL = NULL;
    

  
    readCommandsFromFile(filename, pastEvents, &numCommands);
    while (1)
    {
        prompt(homedir);
        timetaken = 0;
        tokenise_input(homedir,previousdir,pastEvents,&numCommands,&LL);
    }
}
