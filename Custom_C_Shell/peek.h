#ifndef __PEEK_H
#define __PEEK_H
struct FileInfo {
    char name[256];
    struct stat stat_info;
};
int compareFileInfo(const void *a, const void *b);
int compareNames(const void *a, const void *b);
void peek(char *stringArray[], int count,char* prevdir,char* homedir);
#endif