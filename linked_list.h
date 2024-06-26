#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct Node {
    int id;
    int data;
    struct Node* next;
} Node;

Node* createNode(int data);
void insertAtBeginning(Node** head, int data);
void insertAtEnd(Node** head, int data);
void printList(Node* head);
void deleteNode(Node** head, int key);
void freeList(Node* head);

#endif