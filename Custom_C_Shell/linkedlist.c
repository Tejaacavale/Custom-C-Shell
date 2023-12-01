#include "headers.h"
struct Node *createNode(char *processName, int pid) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->processName = processName;
        newNode->pid = pid;
        newNode->next = NULL;
    return newNode;
}

struct Node* insertNode(struct Node **head, char *processName, int pid) {
    if (*head == NULL) {
        *head = createNode(processName, pid);
        return *head;
    } else {
        struct Node *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        struct Node *temp = createNode(processName, pid);
        current->next = temp;
        return *head;
    }
}
void insertProcess(const char *processName, int pid) {
    if (numProcesses < MAX_PROCESSES) {
        strcpy(processArray[numProcesses].processName, processName);
        processArray[numProcesses].pid = pid;
        numProcesses++;
    } else {
        printf("Process array is full\n");
    }
}
void deleteProcessByPid(int pid) {
    for (int i = 0; i < numProcesses; i++) {
        if (processArray[i].pid == pid) {
            for (int j = i; j < numProcesses - 1; j++) {
                processArray[j] = processArray[j + 1];
            }
            numProcesses--;
            return;
        }
    }
}
void checkAndDeleteCompletedProcesses() {
    for (int i = 0; i < numProcesses; i++) {
        int status;
        if (waitpid(processArray[i].pid, &status, WNOHANG) != 0) {
            if (WIFEXITED(status)) {
                printf("%s exited normally (%d)\n", processArray[i].processName,processArray[i].pid);
                deleteProcessByPid(processArray[i].pid);
                i--; // To recheck the current index
            }
        }
    }
}

void deleteNodeByPid(struct Node **head, int pid) {
    if (*head == NULL) {
        return; // List is empty
    }

    if ((*head)->pid == pid) {
        struct Node *temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }

    struct Node *current = *head;
    while (current->next != NULL && current->next->pid != pid) {
        current = current->next;
    }

    if (current->next != NULL) {
        struct Node *temp = current->next;
        current->next = current->next->next;
        free(temp);
    }
}

void printList(struct Node *head) {
    struct Node *current = head;
    while (current != NULL) {
        printf("Process: %s, PID: %d\n", current->processName, current->pid);
        current = current->next;
    }
}

void freeList(struct Node *head) {
    while (head != NULL) {
        struct Node *temp = head;
        head = head->next;
        free(temp);
    }
}
void checkAndDeleteCompleted(struct Node **head) {
    struct Node *current = *head;
    struct Node *prev = NULL;

    while (current != NULL) {
        int status;
        if (waitpid(current->pid, &status, WNOHANG) != 0) {
            if (WIFEXITED(status)) {
                if (prev == NULL) {
                    *head = current->next;
                } else {
                    prev->next = current->next;
                }
                printf("%s exited normally (%d)\n", current->processName,current->pid);
                struct Node *temp = current;
                current = current->next;
                free(temp);
                continue;
            }
        }
        prev = current;
        current = current->next;
    }
}