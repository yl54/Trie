/*
 * Yiyuan Li
 * Student Id: 1230002
 * CSE 374 
 * Homework 5
 * 
 * This is the header file for the linked list node.
 * 
 **/

#ifndef LINKED_LIST_NODE_H
#define LINKED_LIST_NODE_H

struct LinkedListNode {
    struct LinkedListNode* next;
    char* data;
};

struct LinkedListNode* makeLinkedListNode(char* n_data);
int deallocateLinkedListNode(struct LinkedListNode* node);

#endif
