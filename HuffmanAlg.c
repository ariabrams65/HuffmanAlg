#include <stdio.h>
#include <stdlib.h>
#define ASCII 128

int fillc(int *, FILE *);

typedef struct Node
{ 
    struct Node *next;
    struct Node *child1;
    struct Node *child2;
    struct Node *parent;

    int freq;
    char character;
} Node;

Node *createlist(int *, int);
Node *createtree(Node *);
void compress(Node *, FILE *);

int main(int argc, char *argv[]) {
	
    if (argc > 2) {
     
        fprintf(stderr, "error: too many arguments\nformat: HuffmanAlg 'filename'\n");
        exit(EXIT_FAILURE);
    } else if (argc < 2) {
     
        fprintf(stderr, "error: no argument found\nformat: HuffmanAlg 'filenam'\n");
        exit(EXIT_FAILURE);
    }
    FILE *text;
	
    if ((text = fopen(argv[1], "r")) == NULL) {
     
        perror(NULL);
        exit(EXIT_FAILURE); 
    }
    int c[ASCII];

    for (int i = 0; i < ASCII; i++) {
     
	    c[i] = 0;
    }
    fillc(c, text);
    Node *s = createlist(c, sizeof(c) / sizeof(c[0]));
    Node *t = createtree(s);

    compress(t, text);

    return 0;
}

int fillc(int *ch, FILE *f) {
    
   int c;

   while ((c = fgetc(f)) != EOF) {
    
       ch[c]++; 
   }
}

Node *putnode(Node *, Node *);

Node *createlist(int *c, int size) {          /*returns the initial node of a linked list*/

    int count = 0;
    Node *initial;

    for (int i = 0; i < size; i++) {
    
        if (c[i] > 0) {
         
            Node *leaf;
            if ((leaf = malloc(sizeof(Node))) == NULL) {
            
                perror(NULL);
                exit(EXIT_FAILURE);
            }
            leaf->freq = c[i];
            leaf->character = i;
            leaf->next = NULL; 
            leaf->child1 = NULL;
            leaf->child2 = NULL;

            count++;     

            if (count == 1) {
            
                initial = leaf;
            } else {
                
                initial = putnode(initial, leaf); 
            }
        }
    }   
    return initial;
} 

Node *putnode(Node *initial, Node *leaf) {        /*puts leaf node within linked list starting at initial in ascending order based on frequency*/     
                                                
    Node *cur = initial;
    Node *prev = initial; 

    while (cur != NULL) {                        /*while we are not at end of linked list*/ 
    
        if (cur->freq >= leaf->freq) { 
                                    
            if (cur == initial) {
            
            initial = leaf; 
            } else {
            
            prev->next = leaf;
            }
            
            leaf->next = cur;

            return initial;
        }

        prev = cur; 
        cur = cur-> next; 
    }
    prev->next = leaf; 
    return initial;                                                                                          
}

Node *combinenodes(Node *a, Node *b) {

    Node *p;
    if ((p = malloc(sizeof(Node))) == NULL) {
        perror(NULL);
        exit(EXIT_FAILURE);    
    }
    p->next = NULL;
    p->child1 = a;
    p->child2 = b;
    p->freq = a->freq + b->freq;

    a->parent = p;
    b->parent = p;

    return p;
}

Node *createtree(Node *initial) {  

    while (1) {
        
        Node *parent = combinenodes(initial, initial->next); 
        if (parent->child1 == NULL) {
            printf("error");
        }
        
        initial = (initial->next)->next;
        
        if (initial == NULL) { 
            return parent;
        }
        initial = putnode(initial, parent);
    }
}

void compress(Node *tree, FILE *file) {

}
