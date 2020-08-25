#include <stdio.h>                                                              
#include <stdlib.h>                                                             
#include <stdint.h>                                                             
#define ASCII 256                                                               
                                                                                
int fill_c(int *, FILE *);                                                      
                                                                                
typedef struct Node {                                                           
                                                                                
    struct Node *next;                                                          
    struct Node *child1;                                                        
    struct Node *child2;                                                        
                                                                                
    int freq;                                                                   
    char character;                                                             
} Node;                                                                         
                                                                                
typedef struct Code {                                                           
                                                                                
    unsigned char size;                                                         
    uint32_t code;                                                              
} Code;                                                                         
                                                                                
Node *create_list(int *, int);                                                  

Node *create_tree(Node *);                                                                                                       

Node *put_node(Node *, Node *);

void create_codes(Code **, Node *, Code);

void print_header(Node *, uint32_t);

void print_tree(Node *);
