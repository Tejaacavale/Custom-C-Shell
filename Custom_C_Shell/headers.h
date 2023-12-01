#ifndef HEADERS_H_
#define HEADERS_H_

#define COLOR_RESET   "\033[0m"
#define COLOR_GREEN   "\033[1;32m" // Green for executables
#define COLOR_WHITE   "\033[0m"    // White for regular files
#define COLOR_BLUE    "\033[1;34m"
#define MAX_COMMANDS 15
#define MAX_COMMAND_LENGTH 100
typedef struct {
    char command[MAX_COMMAND_LENGTH];
} Command;
struct Node {
    char *processName;
    int pid;
    struct Node *next;
};
typedef struct Node Node;
#define MAX_PROCESSES 100 // Adjust the size as needed

struct ProcessInfo {
    char processName[100]; // Adjust the size as needed
    int pid;
};
extern int timetaken;
extern struct ProcessInfo processArray[MAX_PROCESSES];
extern int numProcesses;
extern char promptname[4096];
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdbool.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include "prompt.h"
#include "input.h"
#include "execute.h"
#include "warp.h"
#include "peek.h"
#include "pastevents.h"
#include "seek.h"
#include "systemcmds.h"
#include "linkedlist.h"
#include "proclore.h"
#include <time.h>
#endif