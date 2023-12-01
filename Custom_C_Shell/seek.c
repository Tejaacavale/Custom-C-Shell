#include "headers.h"
void split_at_last_period(char *input, char *before_period, char *after_period)
{
    char *last_period = strrchr(input, '.');
    if (last_period != NULL)
    {
        *last_period = '\0'; // Replace the last period with a null terminator
        strcpy(before_period, input);
        strcpy(after_period, last_period + 1); // Skip the period
    }
    else
    {
        strcpy(before_period, input);
        strcpy(after_period, ""); // No period found, set after_period to an empty string
    }
}
void print_file_contents(const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("fopen");
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    printf("\n");
    fclose(file);
}

void seek_recursive_e_found(const char *target, const char *path, int d, int f, int e, int *match_found, char *currentpath)
{
    if ((*match_found))
    {
        return;
    }
    DIR *dir = opendir(path);
    if (dir == NULL)
    {
        perror("opendir");
        return;
    }
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_name[0] == '.') {
            continue;
        }
        if ((*match_found))
        {
            return;
        }
        struct stat file_stat;
        char full_path[4096];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        if (stat(full_path, &file_stat) == -1)
        {
            perror("stat");
            continue;
        }
        char filename[4096];
        char extension[4096];
        char tempname[4096];
        strcpy(tempname,entry->d_name);
        split_at_last_period(tempname, filename, extension);
        if (f == 1)
        {
            if (!S_ISDIR(file_stat.st_mode))
            {
                if (strcmp(filename, target) == 0)
                {
                    (*match_found) += 1;
                    if (access(path, R_OK) == 0)
                    {
                        char newpath[4096];
                        snprintf(newpath, sizeof(newpath), "%s/%s", currentpath,entry->d_name);
                        printf(COLOR_GREEN);
                        printf("%s\n", newpath);
                        printf(COLOR_RESET);
                        print_file_contents(full_path);
                        
                        
                    }
                    else
                    {
                        printf("Missing permissions for task!\n");
                        
                    }
                }
            }
        }
        else if (d == 1)
        {
            if (S_ISDIR(file_stat.st_mode))
            {
                if (strcmp(filename, target) == 0)
                {
                    (*match_found) += 1;
                    if (access(path, R_OK) == 0)
                    {
                       
                        char newpath[4096];
                        snprintf(newpath, sizeof(newpath), "%s/%s", currentpath,entry->d_name);
                        printf(COLOR_BLUE);
                        printf("%s\n", newpath);
                        printf(COLOR_RESET);
                        chdir(full_path);
                        
                    }
                    else
                    {
                        printf("Missing permissions for task!\n");
                        
                    }
                }
            }
        }
        else
        {
            if (strcmp(filename, target) == 0)
            {
                (*match_found) += 1;
                if (S_ISDIR(file_stat.st_mode))
            {
                if (strcmp(filename, target) == 0)
                {
                    (*match_found) += 1;
                    if (access(path, R_OK) == 0)
                    {
                        chdir(path);
                        char newpath[4096];
                        snprintf(newpath, sizeof(newpath), "%s/%s", currentpath,entry->d_name);
                        printf(COLOR_BLUE);
                        printf("%s\n", newpath);
                        printf(COLOR_RESET);
                        chdir(full_path);
                        
                    }
                    else
                    {
                        printf("Missing permissions for task!\n");
                        
                    }
                }
            }
                else{
                    if (strcmp(filename, target) == 0)
                {
                    (*match_found) += 1;
                    if (access(path, R_OK) == 0)
                    {
                        char newpath[4096];
                        snprintf(newpath, sizeof(newpath), "%s/%s", currentpath,entry->d_name);
                        printf(COLOR_GREEN);
                        printf("%s\n", newpath);
                        printf(COLOR_RESET);
                        print_file_contents(full_path);
                        
                        
                    }
                    else
                    {
                        printf("Missing permissions for task!\n");
                    }
                }
                }
                
            }
        }
        if (S_ISDIR(file_stat.st_mode))
        {
            char newpath[4096];
            snprintf(newpath, sizeof(newpath), "%s/%s", currentpath,entry->d_name);
            seek_recursive_e_found(target, full_path, d, f, e, match_found, newpath);
        }
    }
}
void seek_recursive_e(const char *target, const char *path, int d, int f, int e, int *match_found, char *currentpath)
{
    DIR *dir = opendir(path);
    if (dir == NULL)
    {
        perror("opendir");
        return;
    }
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_name[0] == '.') {
            continue;
        }
        struct stat file_stat;
        char full_path[4096];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        if (stat(full_path, &file_stat) == -1)
        {
            perror("stat");
            continue;
        }
        char filename[4096];
        char extension[4096];
        char tempname[4096];
        strcpy(tempname,entry->d_name);
        split_at_last_period(tempname, filename, extension);

        if (f == 1)
        {
            if (!S_ISDIR(file_stat.st_mode))
            {
                if (strcmp(filename, target) == 0)
                {
                    (*match_found) += 1;
                }
            }
        }
        else if (d == 1)
        {
            if (S_ISDIR(file_stat.st_mode))
            {
                if (strcmp(filename, target) == 0)
                {
                    (*match_found) += 1;
                }
            }
        }
        else
        {
            if (strcmp(filename, target) == 0)
            {
                (*match_found) += 1;
            }
        }
        if (S_ISDIR(file_stat.st_mode))
        {
            char newpath[4096];
            snprintf(newpath, sizeof(newpath), "%s/%s", currentpath,entry->d_name);
            seek_recursive_e(target, full_path, d, f, e, match_found, newpath);
        }
    }
}
void seek_recursive(const char *target, const char *path, int d, int f, int e, int *match_found, char *currentpath)
{
    DIR *dir = opendir(path);
    if (dir == NULL)
    {
        perror("opendir");
        return;
    }
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_name[0] == '.') {
            continue;
        }
        struct stat file_stat;
        char full_path[4096];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        if (stat(full_path, &file_stat) == -1)
        {
            perror("stat");
            continue;
        }
        char filename[4096];
        char extension[4096];
        char tempname[4096];
        strcpy(tempname,entry->d_name);
        split_at_last_period(tempname, filename, extension);

        if (f == 1)
        {
            if (!S_ISDIR(file_stat.st_mode))
            {
                if (strcmp(filename, target) == 0)
                {
                    (*match_found) += 1;
                    printf(COLOR_GREEN);
                    printf("%s/%s\n", currentpath, entry->d_name);
                    printf(COLOR_RESET);
                    
                }
            }
        }
        else if (d == 1)
        {
            if (S_ISDIR(file_stat.st_mode))
            {
                if (strcmp(filename, target) == 0)
                {
                    (*match_found) += 1;
                    printf(COLOR_BLUE);
                    printf("%s/%s\n", currentpath, entry->d_name);
                    printf(COLOR_RESET);
                    
                }
            }
        }
        else
        {
            if (S_ISDIR(file_stat.st_mode)){
                printf(COLOR_BLUE);
                
            }
            else{
                printf(COLOR_GREEN);
            }
            if (strcmp(filename, target) == 0)
            {
                (*match_found) += 1;
                printf("%s/%s\n", currentpath, entry->d_name);
                
            }
            printf(COLOR_RESET); 

        }
        if (S_ISDIR(file_stat.st_mode))
        {
        
            char newpath[4096];
            snprintf(newpath, sizeof(newpath), "%s/%s", currentpath,entry->d_name);
            seek_recursive(target, full_path, d, f, e, match_found, newpath);
        }
    }
}
void seek(char *stringArray[], int count,char* homedir)
{

    int f = 0;
    int d = 0;
    int e = 0;
    int match_found = 0;
    char address[4096];
    char filename[4096];
    char currentpath[4096];
    for ( int i = 1 ; i < count ; i++){
        if(strcmp(stringArray[i],"-d")==0){
            d++;
        }
        if(strcmp(stringArray[i],"-f")==0){
            f++;
        }
        if(strcmp(stringArray[i],"-e")==0){
            e++;
        }
    }
    int add = d+f+e;
    if(count==add+2){
        strcpy(filename,stringArray[count-1]);
        strcpy(address,".");
    }
    else{
        strcpy(address,stringArray[count-1]);
        strcpy(filename,stringArray[count-2]);
    }
    if(address[0]=='~'){
        if(strlen(address)==1 || strcmp(address,"~/")==0){
            strcpy(address,homedir);
        }
        else{
            char result[4096];
            strcpy(result,homedir);
            strcat(result,address+1);
            strcpy(address,result);
        }
    }
    // strcpy(filename,stringArray[1]);
    strcpy(currentpath, ".");
    // strcpy(address,"./test");
    if (d == 1 && f == 1)
    {
        printf("Invalid flags!\n");
        
        return;
    }
    if (e == 0)
    {
        seek_recursive(filename, address, d, f, e, &match_found, currentpath);
        if (match_found == 0)
        {
            printf("No match found!\n");
            
        }
    }
    if (e == 1)
    {
        seek_recursive_e(filename, address, d, f, e, &match_found, currentpath);
        if (match_found == 0)
        {
            printf("No match found!\n");
            
        }
        else if (match_found == 1)
        {
            match_found = 0;
            seek_recursive_e_found(filename, address, d, f, e, &match_found, currentpath);
            
        }
        else
        {
            printf("More than one match found!\n");
        }
    }
}