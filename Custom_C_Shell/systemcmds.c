#include "headers.h"
void systemcalls(char *stringArray[], int background, int count,Node** deLL)
{
    Node* LL = *deLL;
    stringArray[count] = NULL;
    if (background)
    {
        pid_t childPid;
        childPid = fork();
        if (childPid == 0)
        {
            // Child process
            if (execvp(stringArray[0], stringArray)==-1)
            {
               printf("No such command found!\n");
                return;
            }
            exit(1);
        }
        else if (childPid > 0)
        {
            // Parent process
            printf("%d\n", childPid);
            LL = insertNode(&LL,stringArray[0],childPid);
            insertProcess(stringArray[0],childPid);

        }
        else
        {
            perror("Fork error");
        }
    }
    else
    {
        pid_t childPid;
        int status;

        childPid = fork();
        struct timespec start_time, end_time;
        clock_gettime(CLOCK_MONOTONIC, &start_time);


        if (childPid == 0)
        {
            // Child process
            if (execvp(stringArray[0], stringArray)==-1)
            {
              printf("No such command found!\n");
                return;
            }
            exit(1);
        }
        else if (childPid > 0)
        {
            // Parent process
            waitpid(childPid, &status, 0);
            clock_gettime(CLOCK_MONOTONIC, &end_time); 
            long long time_taken = (end_time.tv_sec - start_time.tv_sec) +
                   (end_time.tv_nsec - start_time.tv_nsec) / 1.0e9;
            timetaken = time_taken;
            strcpy(promptname,stringArray[0]);
            // printf("%s exited normally\n", stringArray[0]);
        }
        else
        {
            perror("Fork error");
        }
    }
}