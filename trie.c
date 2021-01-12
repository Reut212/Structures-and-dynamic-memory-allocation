#include <stdlib.h>
#include <stdio.h>
#include "trie.h"

#define LINE 256
#define NUM_LETTERS 26

//Get a line from a text and check each word
void textToTree(node *head) {
    char line[LINE] = {0};
    char *p = NULL;
    int run = 0;
    int sum = 0;
    while (!feof(stdin)) {
		if (fgets(line, LINE, stdin) == NULL) continue;
		p = &line[0];
		while (line[run] != ('\0')) {
			if (checkChar(line[run])) {
				sum++;
			} else if (sum != 0) {
				addWord(head, p, sum);
				p = p + sum + 1;
				sum = 0;
			} else {
				p = p + 1;
			}
			run++;
		}
		run = 0;
    }
    return;
}

//add a specific word after checking and converting it
void addWord(node *n, char* const p, int size) {
    if (size == 0) {
        n->count++;
    } else {
        char *p2 = p;
        int tempChar = ((convert(*(p2))) - 'a');
        if (n->children[tempChar] == NULL) {
            node *new = (node *) malloc(sizeof(node));
            new->letter = convert(*(p2));
            new->count = 0;
            for (int i = 0; i < MUN_ABC; i++) {
                new->children[i] = NULL;
            }
            n->children[tempChar] = new;
            addWord(new, p2 + 1, size - 1);
        } else {
            addWord(n->children[tempChar], p2 + 1, size - 1);
        }
        p2++;
    }
}

//check if the char is one of the AlphaBeit letters.
boolean checkChar(char index){
    if(('a' <= index && index >= 'z') || ('A' <= index && index >= 'Z')){
		return 1;
	}
    return 0;
}

//convert uppercase letters to smallcase
char convert(char index){
    if ('A' <= index && index <= 'Z'){
        return (index + ('a'-'A'));
    }
    return index;
}

//Inorder Traversal
void printInorder(node *node, char string[LINE], int indexChar ) {
	string[indexChar] = node->letter;
	string[indexChar+1] = '\0';
    if ( node->count > 0 ) {
		printf ("%s\t%ld \n", string, (node->count) );
	}
    for (int i = 0; i < MUN_ABC; i++) {
        if (node->children[i] != NULL) {
            printInorder(node->children[i], string, indexChar+1);
        }
    }
}

//Preorder Traversal
void printPreorder(node *node, char string[], int indexChar ) {
	string[indexChar] = node->letter;
	string[indexChar+1] = '\0';
	if (indexChar<LINE){
	    string[indexChar+1] = '\0';
	}
    else {string[indexChar] = '\0';}
    if ( node->count > 0 ) {
		printf ("%s\t%ld\n", string, node->count );
	}
    for (int i = MUN_ABC-1; i >= 0; i--) {
        if (node->children[i] != NULL) {
            printPreorder(node->children[i], string, indexChar+1);
        }
    }
}

//Destroy the tree
void destroyTree(node *head) {
    int i = 0;
    for (i = 0; i < MUN_ABC; i++) {
        if (head->children[i] != NULL) {
            destroyTree(head->children[i]);
        }
        free(head->children[i]);
    }
}