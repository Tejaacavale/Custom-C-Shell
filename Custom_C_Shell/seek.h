#ifndef __SEEK_H
#define __SEEK_H
void seek(char* stringArray[],int count,char* homedir);
void seek_recursive(const char *target, const char *path, int d, int f, int e,int* match_found,char* currentpath) ;
void split_at_last_period(char *input, char *before_period, char *after_period) ;
void seek_recursive_e(const char *target, const char *path, int d, int f, int e, int *match_found, char *currentpath);
void print_file_contents(const char *file_path) ;
#endif