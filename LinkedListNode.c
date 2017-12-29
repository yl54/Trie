/*
 * Yiyuan Li
 * Student Id: 1230002
 * CSE 374 
 * Homework 5
 * 
 * This is an implementation of a linked list node that stores words.
 * 
 **/

#include "LinkedListNode.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

struct LinkedListNode* makeLinkedListNode(char* n_data);
int deallocateLinkedListNode(struct LinkedListNode* node);

/*
 * Summary: This function allocates and returns a new linked list node.
 * Variables: n_data is this node's word.
 *
 * */
struct LinkedListNode* makeLinkedListNode(char* n_data) {
    struct LinkedListNode* n_node = (struct LinkedListNode*)
                                     malloc(sizeof(struct LinkedListNode));
    if (n_node != NULL) {
        n_node->next = NULL;
        int len = strlen(n_data) + 1;
        char* node_data = (char*) malloc(sizeof(n_data) * len);
        if (node_data == NULL) {
            return NULL;
        }
        strncpy(node_data, n_data, len);
        n_node->data = node_data;
    }

    return n_node;
}

/*
 * Summary: This function deallocates the linked list node. Returns 0
 *            if its a successful operation, 1 if its a failure.
 * Variables: node is the node to deallocate.
 *
 * */
int deallocateLinkedListNode(struct LinkedListNode* node) {
    if (node == NULL) {
        return 0;
    }

    struct LinkedListNode* current = node;
    while (node != NULL) {
        current = node->next;
        free(node->data);
        free(node);
        node = current;
    }

    return 0;
}
