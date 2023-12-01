#include "headers.h"
int compareFileInfo(const void *a, const void *b)
{
    return strcmp(((struct FileInfo *)a)->name, ((struct FileInfo *)b)->name);
}
int compareNames(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}
void peek(char *stringArray[], int count,char* prevdir,char* homedir)
{
    int a = 0;
    int l = 0;
    char address[4096];
    if (count == 1)
    {
        strcpy(address, ".");
    }
    else if (count == 2)
    {
        if (strcmp(stringArray[1], "-a") == 0)
        {
            a = 1;
            strcpy(address, ".");
        }
        else if (strcmp(stringArray[1], "-l") == 0)
        {
            l = 1;
            strcpy(address, ".");
        }
        else if (strcmp(stringArray[1], "-la") == 0 || strcmp(stringArray[1], "-al") == 0)
        {
            a = 1;
            l = 1;
            strcpy(address, ".");
        }
        else
        {
            strcpy(address, stringArray[count - 1]);
        }
    }
    else if (count == 3)
    {
        if (strcmp(stringArray[1], "-a") == 0)
        {
            a = 1;
        }
        if (strcmp(stringArray[1], "-l") == 0)
        {
            l = 1;
        }
        if (strcmp(stringArray[1], "-la") == 0 || strcmp(stringArray[1], "-al") == 0)
        {
            a = 1;
            l = 1;
        }
        strcpy(address, stringArray[2]);
        if (strcmp(stringArray[2], "-l") == 0 || strcmp(stringArray[2], "-a") == 0)
        {
            l = 1;
            a = 1;
            strcpy(address, ".");
        }
    }
    else if (count == 4)
    {
        a = 1;
        l = 1;
        strcpy(address, stringArray[3]);
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
    if(strcmp(address,"-")==0){
        strcpy(address,prevdir);
    }
    if (l == 0)
    {
        DIR *dir = opendir(address);
        if (dir == NULL)
        {
            perror("opendir");
            return;
        }

        struct FileInfo *files = NULL;
        int num_entries = 0;

        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL)
        {
            if (!a && entry->d_name[0] == '.')
            {
                continue;
            }

            struct stat file_stat;
            char full_path[4096];
            snprintf(full_path, sizeof(full_path), "%s/%s", address, entry->d_name);

            if (stat(full_path, &file_stat) == -1)
            {
                perror("stat");
                continue;
            }

            struct FileInfo fileInfo;
            strcpy(fileInfo.name, entry->d_name);
            fileInfo.stat_info = file_stat;

            files = realloc(files, (num_entries + 1) * sizeof(struct FileInfo));
            files[num_entries++] = fileInfo;
        }

        closedir(dir);

        qsort(files, num_entries, sizeof(struct FileInfo), compareFileInfo);
        for (int i = 0; i < num_entries; i++)
        {
            struct FileInfo fileInfo = files[i];
            struct stat file_stat = fileInfo.stat_info;

            if (S_ISDIR(file_stat.st_mode))
            {
                printf(COLOR_BLUE "%s" COLOR_RESET "\n", fileInfo.name);
                
            }
            else if (file_stat.st_mode & S_IXUSR)
            {
                printf(COLOR_GREEN "%s" COLOR_RESET "\n", fileInfo.name);
                
            }
            else
            {
                printf(COLOR_WHITE "%s" COLOR_RESET "\n", fileInfo.name);
                
            }
        }
        free(files);
    }
    else
    {
        DIR *dir = opendir(address);
        if (dir == NULL)
        {
            perror("opendir");
            return;
        }

        struct FileInfo *files = NULL;
        int num_entries = 0;

        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL)
        {
            if (!a && entry->d_name[0] == '.')
            {
                continue;
            }

            struct stat file_stat;
            char full_path[4096];
            snprintf(full_path, sizeof(full_path), "%s/%s", address, entry->d_name);

            if (stat(full_path, &file_stat) == -1)
            {
                perror("stat");
                continue;
            }

            struct FileInfo fileInfo;
            strcpy(fileInfo.name, entry->d_name);
            fileInfo.stat_info = file_stat;

            files = realloc(files, (num_entries + 1) * sizeof(struct FileInfo));
            files[num_entries++] = fileInfo;
        }

        closedir(dir);

        qsort(files, num_entries, sizeof(struct FileInfo), compareFileInfo);
        printf("total %d\n", num_entries);
        for (int i = 0; i < num_entries; i++)
        {
            struct FileInfo fileInfo = files[i];
            struct stat file_stat = fileInfo.stat_info;
            if (l == 0)
            {
                printf("%s\n", fileInfo.name);
                
            }
            else
            {
                struct passwd *pw = getpwuid(file_stat.st_uid);
                struct group *gr = getgrgid(file_stat.st_gid);
                struct tm *timeinfo = localtime(&file_stat.st_mtime);

                char time_str[80];
                strftime(time_str, sizeof(time_str), "%b %d %H:%M", timeinfo);
                if (S_ISDIR(file_stat.st_mode))
                {
                    printf(COLOR_BLUE);
                }
                else if (file_stat.st_mode & S_IXUSR)
                {
                    printf(COLOR_GREEN);
                }
                else
                {
                    printf(COLOR_WHITE);
                }
                printf("%c%c%c%c%c%c%c%c%c%c %-4lu %-8s %-8s %-10lld %-15s %s\n",
                       S_ISDIR(file_stat.st_mode) ? 'd' : '-',
                       (file_stat.st_mode & S_IRUSR) ? 'r' : '-',
                       (file_stat.st_mode & S_IWUSR) ? 'w' : '-',
                       (file_stat.st_mode & S_IXUSR) ? 'x' : '-',
                       (file_stat.st_mode & S_IRGRP) ? 'r' : '-',
                       (file_stat.st_mode & S_IWGRP) ? 'w' : '-',
                       (file_stat.st_mode & S_IXGRP) ? 'x' : '-',
                       (file_stat.st_mode & S_IROTH) ? 'r' : '-',
                       (file_stat.st_mode & S_IWOTH) ? 'w' : '-',
                       (file_stat.st_mode & S_IXOTH) ? 'x' : '-',
                       (unsigned long)file_stat.st_nlink,
                       (pw) ? pw->pw_name : "",
                       (gr) ? gr->gr_name : "",
                       (long long)file_stat.st_size,
                       time_str,
                       fileInfo.name);
                
                printf(COLOR_RESET);
            }
        }

        free(files);
    }
}
