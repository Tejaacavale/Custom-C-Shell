#include "headers.h"
bool is_starting_part(const char *str1, const char *str2) {
    int length1 = strlen(str1);
    int length2 = strlen(str2);

    if (length1 > length2) {
        return false; // str1 is longer than str2, so it can't be a starting part
    }

    for (int i = 0; i < length1; i++) {
        if (str1[i] != str2[i]) {
            return false; // Mismatch found, not a starting part
        }
    }

    return true; // All characters matched, str1 is a starting part of str2
}
void find_relative_path(const char *from_path, const char *to_path,char relative_path[4096]) {
    const char *from = from_path;
    const char *to = to_path;

    // Find the common part of the paths
    while (*from && *to && *from == *to) {
        from++;
        to++;
    }

    // Count the remaining levels in 'from' path
    int levels_up = 0;
    while (*from) {
        if (*from == '/') {
            levels_up++;
        }
        from++;
    }

    // Calculate the length of the resulting relative path
    int relative_path_length = (levels_up * 3) + strlen(to) + 1;
    
    // Allocate memory for the relative path    
    relative_path[0] = '\0';
    for (int i = 0; i < levels_up; i++) {
        strcat(relative_path, "../");
    }
    strcat(relative_path, to);

}
void prompt(char* homedir) {
    // Do not hardcode the prmopt
    struct passwd *pw;
    uid_t uid;
    uid = geteuid();
    pw = getpwuid (uid);
    char sysname[4096];
    gethostname(sysname,sizeof(sysname));
    char cwd[4096];
    getcwd(cwd,sizeof(cwd));
    char dir[4096];
    int check = 0 ;
    if(is_starting_part(homedir,cwd)){       
        find_relative_path(homedir,cwd,dir);
    }
    else{
        strcpy(dir,cwd);
        check = 1;
    }
    int check2 =0;
    
    if(check==0){
        printf("<%s@%s:~%s",pw->pw_name,sysname,dir);
    }
    else{
        printf("<%s@%s:%s",pw->pw_name,sysname,dir);
    }

    if(timetaken>2){
        printf(":%s %ds",promptname,timetaken);
    }
    printf(">");
}
