#ifndef __LINKEDLIST_H
#define __LINKEDLIST_H


struct Node *createNode(char *processName, int pid);
struct Node* insertNode(struct Node **head, char *processName, int pid);
void deleteNodeByPid(struct Node **head, int pid);
void printList(struct Node *head);
void freeList(struct Node *head);
void checkAndDeleteCompleted(struct Node **head);
void insertProcess(const char *processName, int pid) ;
void deleteProcessByPid(int pid);
void checkAndDeleteCompletedProcesses() ;
#endif