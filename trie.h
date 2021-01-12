#define EX4_FREQUENCY_LIB_H
#define  MUN_ABC 26
#define  LINE 256

typedef enum {
    FALSE=0,
    TRUE=1
} boolean;

typedef struct node {
    char letter;
    long unsigned int count;
    struct node* children [MUN_ABC];
} node;

void textToTree(node *head);
void printInorder(node *node, char string[LINE], int indexChar );
void printPreorder(node *node, char string[LINE], int indexChar );
void addWord(node *head,  char* const p, int size);
boolean checkChar(char index);
char convert(char index);
void destroyTree(node *head);

