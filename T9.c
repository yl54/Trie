/*
 * Yiyuan Li
 * Student Id: 1230002
 * CSE 374
 * Homework 5
 * 
 * This program ingests a dictionary text file, builds a T9 trie
 *   of those words, and allows the user to find words that match
 *   key sequence inputs.
 * 
 **/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "TrieNode.h"
#include "LinkedListNode.h"

#define MAX_WORD_LENGTH 40

struct TrieNode* makeTrieFromDict(char* file_name);
int interact(struct TrieNode* root);

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Error: wrong number of arguments.\n");
        return EXIT_FAILURE;
    }

    struct TrieNode* root_ptr = makeTrieFromDict(argv[1]);
    if (root_ptr == NULL) {
        fprintf(stderr, "Error: failed to create trie.\n");
        return EXIT_FAILURE;
    }

    int interact_status = interact(root_ptr);
    deallocateTrieNode(root_ptr);
    fprintf(stdout, "\n");
    return EXIT_SUCCESS;
}

/*
 * Summary: This function creates and returns a T9 Trie from the 
 *            dictionary of words.
 * Variables: file_name is the name of the file to open. 
 *
 * */
struct TrieNode* makeTrieFromDict(char* file_name) {
    // Attempt to open the file. Check if it works.
    FILE* f = fopen(file_name, "r");
    if (f == NULL) {
        fprintf(stderr, "Error: file failed to open.\n");
        return NULL;
    }

    // Read each line.
    char line[MAX_WORD_LENGTH] = "";

    // This will serve as the empty root node.
    struct TrieNode* root_ptr = makeTrieNode();
    if (root_ptr == NULL) {
        fprintf(stderr, "Error: failed to allocate space to create node.\n");
        return NULL;
    }

    // For each line/word, add to the trie.
    while (fgets(line, MAX_WORD_LENGTH, f) != NULL) {
        int add_node_status = addNode(root_ptr, line);
        if (add_node_status != 0) {
            fprintf(stderr, "Error: failed to add node to root.\n");
            return NULL;
        }
    }

    return root_ptr;
}

/*
 * Summary: This function takes a T9 Trie and provides an interaction 
 *            sequence with the user, who is typing in key sequences.
 *            Returns 0 if successful operation, else returns 1.
 * Variables: root is the root TrieNode to search through.
 *
 * */
int interact(struct TrieNode* root_ptr) {
    // Check if root is valid.
    if (root_ptr == NULL) {
        fprintf(stderr, "Error: provided root node is invalid.");
        return EXIT_FAILURE;
    }

    struct LinkedListNode* link_node_current_ptr = NULL;
    char raw_input[MAX_WORD_LENGTH];
    char stop_message[4] = "exit";
    while (1 == 1) {
        fprintf(stdout, "Please type in your key sequence, '#' for next "
                        "word, or 'exit' to quit: ");
        if (fgets(raw_input, MAX_WORD_LENGTH, stdin) == NULL) {
            fprintf(stderr, "Error: invalid input.");
            continue;
        }

        if (strncmp(stop_message, raw_input, 4) == 0) {
            fprintf(stdout, "End interaction.");
            return 0;
        }

        link_node_current_ptr = search(root_ptr,
                                       link_node_current_ptr,
                                       raw_input);
    }
}
