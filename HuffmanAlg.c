#include "Huffman.h"

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
    fill_c(c, text);
    Node *s = create_list(c, ASCII);
    Node *t = create_tree(s);

    Code *codes[ASCII];

    Code g;
    g.size = 0;
    for (int i = 0; i < ASCII; i++) {
        codes[i] = NULL;
    }
    create_codes(codes, t, g);

    int lnodes = 0;
    for (int i = 0; i < ASCII; i++) {
        if (codes[i] != NULL) {
            lnodes++; 
        }
    }
    int inodes = lnodes - 1;
   
    int tsize = inodes + (9 * lnodes); 
   
    uint32_t bsize; 
    if (tsize % 8 != 0) {
        bsize = (tsize / 8) + 1;
    } else {
        bsize = tsize / 8; 
    }
    print_header(t, bsize); 
    return 0;
}

int fill_c(int *ch, FILE *f) {
    
   int c;

   while ((c = fgetc(f)) != EOF) {
    
       ch[c]++; 
   }
}

Node *create_list(int *c, int size) {          /*returns the initial node of a linked list*/

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
                
                initial = put_node(initial, leaf); 
            }
        }
    }   
    return initial;
} 

Node *put_node(Node *initial, Node *leaf) {        /*puts leaf node within linked list starting at initial in ascending order based on frequency*/     
                                                
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

Node *combine_nodes(Node *a, Node *b) {

    Node *p;
    if ((p = malloc(sizeof(Node))) == NULL) {
        perror(NULL);
        exit(EXIT_FAILURE);    
    }
    p->next = NULL;
    p->child1 = a;
    p->child2 = b;
    p->freq = a->freq + b->freq;

    return p;
}

Node *create_tree(Node *initial) {  

    while (1) {
        
        Node *parent = combine_nodes(initial, initial->next); 
        if (parent->child1 == NULL) {
            printf("error");
        }
        
        initial = initial->next->next;
        
        if (initial == NULL) { 
            return parent;
        }
        initial = put_node(initial, parent);
    }
}

void create_codes(Code **table, Node *tree, Code c) {
    
    if (tree->child1 == NULL) {
        if ((table[tree->character] = malloc(sizeof(Code))) == NULL) {
            perror(NULL);
            exit(EXIT_FAILURE);
        }
        *table[tree->character] = c;
    } else {
        c.size++;    
        c.code <<= 1;
        create_codes(table, tree->child1, c);
        c.code += 1;
        create_codes(table, tree->child2, c);
    }
}

void print_header(Node *tree, uint32_t hsize) {
    
    uint32_t chars = tree->freq;
    FILE *a = fopen("test11", "wb+"); 

    fwrite(&hsize, sizeof(uint32_t), 1, a);
    fwrite(&chars, sizeof(uint32_t), 1, a);

    int ptr;
printf("%d\n", ptr);
   
  int x = fread(&ptr, sizeof(int), 1, a); //returns eof
  int b = feof(a); 
  printf("%d\n", b);
  printf("%d\n", x);
   
    printf("%d", ptr);
     
    print_tree(tree);
}

void print_tree(Node *tree) {

}
