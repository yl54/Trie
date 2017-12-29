/*
 * Yiyuan Li
 * Student Id: 1230002
 * CSE 374
 * Homework 5
 * 
 * This is an implementation of a T9 trie node.
 * 
 **/

#include "LinkedListNode.h"
#include "TrieNode.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define NUMBER_TRIE_NODE_CHILDREN 10

struct TrieNode* makeTrieNode();
int addNode(struct TrieNode* node, char* word);
int addWord(struct TrieNode* node, char* word);
struct LinkedListNode* search(struct TrieNode* root,
                              struct LinkedListNode*
                              link_node_current_ptr,
                              char* raw_input);
struct LinkedListNode* getNextWord(struct LinkedListNode*
                                   link_node_current_ptr);
char* convertWordToDigits(char* word, int length);
int deallocateTrieNode(struct TrieNode* node);

/*
 * Summary: This function allocates memory and returns a new trie node.
 * Variables: n_data is the data for this node.
 *
 * */
struct TrieNode* makeTrieNode() {
    struct TrieNode* n_node = (struct TrieNode*)
                               malloc(sizeof(struct TrieNode));
    if (n_node != NULL) {
        n_node->word_node = NULL;
        for (int i = 0; i < NUMBER_TRIE_NODE_CHILDREN; i++) {
            n_node->children[i] = NULL;
        }
    }

    return n_node;
}

/*
 * Summary: This function takes the root of a trie and adds the new data
 *            to its respective node. Return 0 if its a successful 
 *            operation, 1 if its a failure.
 * Variables: root is the root trie node to add to.
 *            word is the new word to add to the t9 trie.
 *
 * */
int addNode(struct TrieNode* root, char* word) {
    if (root == NULL) {
        fprintf(stderr, "Error: node_ptr is NULL.\n");
        return 1;
    }

    struct TrieNode* node_ptr = root;
    int length = strlen(word) - 1;
    char* digits = convertWordToDigits(word, length);
    for (int i = 0; i < length; i++) {
        int digit = digits[i] - '0';
        if (node_ptr->children[digit] == NULL) {
            node_ptr->children[digit] = makeTrieNode();
            if (node_ptr->children[digit] == NULL) {
                fprintf(stderr, "Error: failed to allocate space.\n");
                return 1;
            }
        }

        node_ptr = node_ptr->children[digit];
    }

    int end_status = addWord(node_ptr, word);
    return end_status;
}

/*
 * Summary: This function takes some TrieNode and adds the new word to 
 *            the end of the TrieNode's current list. Return 0 if its
 *            a successful operation, 1 if its a failure.
 * Variables: node is the root trie node to add the word to.
 *            word is the new word to add to the TrieNode.
 *
 * */
int addWord(struct TrieNode* node, char* word) {
    if (node->word_node == NULL) {
        node->word_node = makeLinkedListNode(word);
        if (node != NULL) {
            return 0;
        } else {
            return 1;
        }
    }

    struct LinkedListNode* current = node->word_node;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = makeLinkedListNode(word);
    if (current->next != NULL) {
        return 0;
    } else {
        return 1;
    }
}

/*
 * Summary: This function takes the root of a trie and returns a TrieNode
 *            for that particular key sequence, if it exists.
 * Variables: root is the root trie node to search through.
 *            digits is the key sequence to traverse in the Trie.
 *
 * */
struct LinkedListNode* search(struct TrieNode* root,
                              struct LinkedListNode*
                              link_node_current_ptr,
                              char* raw_input) {
    struct TrieNode* node_ptr = root;
    int length = strlen(raw_input) - 1;
    char hash_tag[1] = "#";
    for (int i = 0; i < length; i++) {
        if (strncmp(hash_tag, &raw_input[i], 1) == 0) {
            link_node_current_ptr = getNextWord(link_node_current_ptr);
            if (link_node_current_ptr == NULL) {
                return NULL;
            }
        } else {
            int digit = raw_input[i] - '0';
            if (digit < 2 || digit > 9) {
                return NULL;
            }

            if (node_ptr->children[digit] == NULL) {
                fprintf(stdout, "Not found in current dictionary.\n");
                return NULL;
            }

            node_ptr = node_ptr->children[digit];
            link_node_current_ptr = node_ptr->word_node;
        }
    }

    if (link_node_current_ptr == NULL) {
        fprintf(stdout, "Not found in current dictionary.\n");
    } else {
        fprintf(stdout, "%s", link_node_current_ptr->data);
    }

    return link_node_current_ptr;
}

/*
 * Summary: This function helps retrieve the next word value, if it exists.
 * Variables: link_node_current_ptr is the pointer to the word node.
 *
 * */
struct LinkedListNode* getNextWord(struct LinkedListNode*
                                   link_node_current_ptr) {
    if (link_node_current_ptr == NULL) {
        fprintf(stdout, "Not found in current dictionary.\n");
        return NULL;
    }

    link_node_current_ptr = link_node_current_ptr->next;
    if (link_node_current_ptr == NULL) {
        fprintf(stdout, "There are no more T9onyms.\n");
        return NULL;
    }

    return link_node_current_ptr;
}

/*
 * Summary: This function converts the string value and converts it
 *            to its respective key sequence.
 * Variables: word is the  word to convert to a key sequence.
 *
 * */
char* convertWordToDigits(char* word, int length) {
    char* digits = (char*) malloc(sizeof(word) * length);
    for (int i = 0; i < length; i++) {
        if (word[i] >= 'a' && word[i] <= 'c') {
            digits[i] = '2';
        } else if (word[i] >= 'd' && word[i] <= 'f') {
            digits[i] = '3';
        } else if (word[i] >= 'g' && word[i] <= 'i') {
            digits[i] = '4';
        } else if (word[i] >= 'j' && word[i] <= 'l') {
            digits[i] = '5';
        } else if (word[i] >= 'm' && word[i] <= 'o') {
            digits[i] = '6';
        } else if (word[i] >= 'p' && word[i] <= 's') {
            digits[i] = '7';
        } else if (word[i] >= 't' && word[i] <= 'v') {
            digits[i] = '8';
        } else if (word[i] >= 'w' && word[i] <= 'z') {
            digits[i] = '9';
        }
    }

    return digits;
}

/*
 * Summary: This function takes the root of a trie and frees the memory
 *            used by the trie. Return 0 if its succesful.
 * Variables: root is the root trie node to deallocate.
 *
 * */
int deallocateTrieNode(struct TrieNode* node) {
    // Check if this current pointer is null or not.
    if (node == NULL) {
        return 0;
    }

    for (int i = 0; i < NUMBER_TRIE_NODE_CHILDREN; i++) {
        deallocateTrieNode(node->children[i]);
    }

    // Free the node and its elements.
    int deallocate_status = deallocateLinkedListNode(node->word_node);
    free(node);
    return 0;
}

