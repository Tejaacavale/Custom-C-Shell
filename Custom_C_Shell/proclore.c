#include "headers.h"
void proclore(char* stringArray[],int count){
    int target_pid = getpid();  // Replace with the actual PID
    if(count==2){
        int number = atoi(stringArray[1]);
        target_pid = number;
    }
    char target_pid_string[16];
    sprintf(target_pid_string, "%d", target_pid);

    char path_stat[256];
    sprintf(path_stat, "/proc/%s/stat", target_pid_string);

    FILE* file_ptr = fopen(path_stat, "r");
    if (file_ptr == NULL) {
        printf("\033[1;31mERROR: Couldn't open the file\n");
        printf("\033[0m");
        return ;
    }

    char process_info[4096];
    int process_info_size = 0;
    int ch;

    while ((ch = fgetc(file_ptr)) != EOF && process_info_size < sizeof(process_info) - 1) {
        process_info[process_info_size++] = ch;
    }
    process_info[process_info_size] = '\0';  // Null-terminate the string

    fclose(file_ptr);

    char info_array[52][1024];  // Using character arrays directly
    int array_index = 0;
    int info_index = 0;

    for (int i = 0; process_info[i] != '\0'; i++) {
        if (process_info[i] == ' ') {
            info_array[array_index][info_index] = '\0';
            array_index++;
            info_index = 0;
        } else {
            info_array[array_index][info_index++] = process_info[i];
        }
    }
    info_array[array_index][info_index] = '\0';
    int check=0;
    if(info_array[4]==info_array[7])
    {
        check = 43;
    }

    // Printing the info_array values for demonstration
   

    // Get the executable path
    char executable[1024];
    sprintf(executable, "/proc/%s/exe", target_pid_string);
    char path[1024];
    readlink(executable, path, sizeof(path));

    // Printing the info_array values for demonstration
    printf("pid : %s\n", info_array[0]);
    printf("Process Status: %s%c\n", info_array[2],(char)check);
    printf("Process Group : %s\n", info_array[4]);
    printf("Virtual memory : %s\n", info_array[22]);
    printf("executable path : %s\n", path);
}