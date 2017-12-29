/*
 * Yiyuan Li
 * Student Id: 1230002
 * CSE 374
 * Homework 5
 *
 * This is the header file for the T9 trie node.
 *
 **/

#ifndef TRIE_NODE_H
#define TRIE_NODE_H

struct TrieNode {
    struct TrieNode* children[10];
    struct LinkedListNode* word_node;
};

struct TrieNode* makeTrieNode();
int addNode(struct TrieNode* node, char* word);
struct LinkedListNode*  search (struct TrieNode* root,
                                struct LinkedListNode*
                                link_node_current_ptr,
                                char* raw_input);
int deallocateTrieNode(struct TrieNode* node);

#endif
