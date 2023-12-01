#include "headers.h"
void warp(char *stringArray[], int count, char *homedir, char *previousdir)
{
    char printdir[4096];
    if(count == 1){
        char address[4096];
        char newprev[4096];
        getcwd(newprev,sizeof(newprev));
        if (chdir(homedir) == 0)
                {
                    strcpy(printdir, homedir);
                    strcpy(previousdir, newprev);
                    
                }
                else
                {
                    perror("chdir");
                }

    }
    for (int i = 0; i < count; i++)
    {
        if (i == 0)
        {
            continue;
        }
        char address[4096];
        char newprev[4096];
        getcwd(newprev,sizeof(newprev));
        strcpy(address, stringArray[i]);
        if (strcmp(address, "-") == 0)
        {

            if (chdir(previousdir) == 0)
            {
                strcpy(printdir, previousdir);
                char currentdir[4096];
                getcwd(currentdir, sizeof(currentdir));
                strcpy(previousdir, newprev);
                
            }
            else
            {
                perror("chdir");
            }
        }
        else if (address[0] == '~' )
        {
            if (strlen(address) == 1 || strcmp(address,"~/")==0 )
            {
                if (chdir(homedir) == 0)
                {
                    strcpy(printdir, homedir);
                    strcpy(previousdir, newprev);
                    
                }
                else
                {
                    perror("chdir");
                }
            }
            else
            {
                if (chdir(homedir) == 0)
                {
                }
                else
                {
                    perror("chdir");
                }
                char new[4096];
                strcpy(new, address + 2);
                if (chdir(new) == 0)
                {
                    char currentdir[4096];
                    getcwd(currentdir, sizeof(currentdir));
                    strcpy(previousdir,newprev);
                    strcpy(printdir, currentdir);
                    
                }
                else
                {
                    perror("chdir");
                }
            }
        }

        else
        {
            if (chdir(address) == 0)
            {
                char currentdir[4096];
                getcwd(currentdir, sizeof(currentdir));
                strcpy(previousdir, newprev);
                strcpy(printdir, currentdir);
                
            }
            else
            {
                perror("chdir");
            }
        }
    }
    puts(printdir);
}