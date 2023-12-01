#include "headers.h"

void readCommandsFromFile(const char *filename, Command commands[], int *count) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Unable to open file");
        return;
    }

    char line[256]; // Adjust the size as needed

    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = '\0'; // Remove newline character
        addCommand(commands, count, line);
    }

    fclose(file);
}
void addCommand(Command commands[], int *count, const char *command) {
    char cmd[4096]; // Allocate memory for the command
    strcpy(cmd, command);
            // puts(cmd);
    trim_spaces(cmd);
            // puts(cmd);
    trimSpacesAndTabs(cmd);
    char* stringArray[100];
    int counts =0;
    splitString(cmd,stringArray,&counts);
    if(strcmp(stringArray[0],"pastevents")==0){
        return;
    }
    if (*count < MAX_COMMANDS) {
        // Check if the command is the same as the previous one
        if (*count == 0 || strcmp(commands[*count - 1].command, command) != 0) {
            strcpy(commands[*count].command, command);
            (*count)++;
        }
    } else {
        // Overwrite the oldest command
        for (int i = 0; i < MAX_COMMANDS - 1; i++) {
            strcpy(commands[i].command, commands[i + 1].command);
        }
        strcpy(commands[MAX_COMMANDS - 1].command, command);
    }
}
void writeCommandsToFile(const char *homedir, Command commands[], int count) {
    char filename[256];
    snprintf(filename, sizeof(filename), "%s/pastevents.txt", homedir);

    int file_descriptor = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (file_descriptor == -1) {
        perror("Unable to open file");
        return;
    }

    for (int i = 0; i < count; i++) {
        ssize_t bytes_written = write(file_descriptor, commands[i].command, strlen(commands[i].command));
        if (bytes_written == -1) {
            perror("Error writing to file");
            close(file_descriptor);
            return;
        }
        
        write(file_descriptor, "\n", 1); // Write newline after each command
    }

    close(file_descriptor);
}

void printCommands(Command commands[], int count) {
    for (int i = 0; i < count; i++) {
        printf("%d: %s\n", i + 1, commands[i].command);
    }
}
void trim_spaces(char *str)
{
    int len = strlen(str);
    int i, j = 0;
    int inside_space = 0;

    // Remove leading spaces and tabs
    while (str[j] == ' ' || str[j] == '\t')
    {
        j++;
    }

    // Process the rest of the string
    for (i = j; i < len; i++)
    {
        if (str[i] != ' ' && str[i] != '\t')
        {
            str[j++] = str[i];
            inside_space = 0;
        }
        else if (!inside_space)
        {
            str[j++] = ' ';
            inside_space = 1;
        }
    }

    // Remove trailing spaces
    if (j > 0 && str[j - 1] == ' ')
    {
        j--;
    }
    str[j] = '\0';
}
void trimSpacesAndTabs(char *str)
{
    // Find the first non-space/tab character
    char *start = str;
    while (*start && (isspace(*start) || *start == '\t'))
    {
        start++;
    }

    // Find the last non-space/tab character
    char *end = str + strlen(str) - 1;
    while (end > start && (isspace(*end) || *end == '\t'))
    {
        end--;
    }

    // Move the characters to the beginning of the string
    memmove(str, start, end - start + 1);
    str[end - start + 1] = '\0';
}
void tokenise_input(char* homedir,char* previousdir,Command commands[], int *count,Node** deLL)
{
    Node* LL = *deLL;
    char input[4096];
    fgets(input, 4096, stdin);
    input[strcspn(input, "\n")] = '\0';
    // Tokenize input based on semicolon to separate command groups
    char *group_token;
    char *group_saveptr = NULL;
    group_token = strtok_r(input, ";", &group_saveptr);
    // puts(group_saveptr);
    while (group_token != NULL)
    {
        // Tokenize each group based on ampersand to separate commands within the group
        // puts(group_saveptr);
        char *cmd_token;
        char *cmd_saveptr = NULL;
        cmd_token = strtok_r(group_token, "&", &cmd_saveptr);
        // puts(cmd_saveptr);
        // puts(cmd_token);
        while (cmd_token != NULL)
        {
            int background;
            // puts(cmd_token);
            // puts(cmd_saveptr);
            if (cmd_saveptr == NULL)
            {
                background = 0;
            }
            else
            {
                background = 1;
            }
            // char *last_char = cmd_token + strlen(cmd_token) - 1;
            // if (background)
            // {
            //     *last_char = '\0'; // Remove the '&' character
            // }
            char cmd[4096]; // Allocate memory for the command
            strcpy(cmd, cmd_token);
            // puts(cmd);
            trim_spaces(cmd);
            // puts(cmd);
            trimSpacesAndTabs(cmd);
            
            execute_command(cmd, background,homedir,previousdir,commands,count,&LL);
            
            char random[4096];
            strcpy(random,cmd_token);
            if(background){
            strcat(random," &");
            }
            addCommand(commands,count,random);
            writeCommandsToFile(homedir,commands,*count);
            cmd_token = strtok_r(NULL, "&", &cmd_saveptr);

        }

        group_token = strtok_r(NULL, ";", &group_saveptr);
    }
}