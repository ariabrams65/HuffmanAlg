#include <stdio.h>
#include <stdlib.h>
#define ASCII 128


int fillc(int *, FILE *);

int main(int argc, char *argv[]) {
	
    if (argc > 2) {
        fprintf(stderr, "error: too many arguments\nformat: HuffmanAlg 'filename'\n");
        exit(EXIT_FAILURE);
    } else if (argc < 2) {
        fprintf(stderr, "error: no argument found\nformat: HuffmanAlg 'filenam'\n");
        exit(EXIT_FAILURE);
    }
    FILE *text;
	
    if ((text = fopen(argv[1], "r")) = NULL) {
        perror();
        exit(EXIT_FAILURE); 
    }

    int c[ASCII];

    for (int i = 0; i < ASCII; i++) {

	    c[i] = 0;
    }
    fillc(c, text); 
    
    return 0;
}

int fillc(int *ch, FILE *f) {
    
   int c;

   while ((c = fgetc(f)) != EOF) {
       ch[c]++; 
   }
}

typedef struct node {
    Node *next;
    Node *child1;
    Node *child2;

    int freq;
    char character;
} Node;

void createlist(int *c, int size, Node *root) {

    int count = 0;

    for (int i = 0; i < size; i++) {
                
        if (c[i] > 0) {
            
            Node *leaf = (Node *)malloc(sizeof(Node *));
            leaf->freq = c[i];
            leaf->character = i;   
            
            count++;

            if (count = 0) {
            
                root->next = leaf;

            } else {
                
                Node *n = (Node *)malloc(sizeof(Node *)); //remeber to free

                *n = *root; 

                for (int i = 0; i < count; i++;) {

                    
                }

            } 
        }
    }
    
}   
