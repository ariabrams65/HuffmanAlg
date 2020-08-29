#include "Huffman.h"

int main(int argc, char *argv[]) {	

    if (argc > 2) {
     
        fprintf(stderr, "error: too many arguments\nformat: HuffmanAlg 'filename'\n");
        exit(EXIT_FAILURE);
    } else if (argc < 2) {
     
        fprintf(stderr, "error: no argument found\nformat: HuffmanAlg 'filename'\n");
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
    int lnodes = fill_c(c, text);
    Node *s = create_list(c, ASCII);
    Node *t = create_tree(s);

    Code *codes[ASCII];
    Code g;
    g.size = 0;
    create_codes(codes, t, g);

    print_header(t, get_header_size(lnodes)); 
    print_char_codes(codes);


    return 0;
}

int fill_c(int *ch, FILE *f) {
    
    int i = 0;
    int c;

    while ((c = fgetc(f)) != EOF) {
         
        if (ch[c] == 0) {
            
            i++; 
        }
        ch[c]++; 
    }
    return i;
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

    fwrite(&hsize, sizeof(uint32_t), 1, stdout);
    fwrite(&chars, sizeof(uint32_t), 1, stdout);

    print_tree(tree);
    flush_bits();
}

Code c0 = {1, 0};
Code c1 = {1, 1};

void print_tree(Node *tree) {
    
    if (tree->child1 == NULL) {
        
        print_code(c1);
        Code c = {8 , tree->character};
        print_code(c);
    } else {
        
        print_code(c0);
        print_tree(tree->child1);
        print_tree(tree->child2);
    }
}

uint32_t get_header_size(int l) {
    
    int inodes = l - 1;
   
    int tsize = inodes + (9 * l); 

    uint32_t bsize;
    bsize = tsize % 8 != 0 ? (tsize / 8) + 1 : tsize / 8; 

    return bsize;
}

char buf = 0;
int space = 8;

void print_code(Code c) {
    
    if (c.size - space >= 0) {
         
        Code d = c;
        c.code >>= c.size - space;
        buf |= c.code;
        c = d;
        c.size -= space;
        printf("%c", buf);
        buf = 0;
        space = 8;

        if (c.size > 0) {
            
            print_code(c);
        }
    } else {
         
        c.code <<= space - c.size;
        buf |= c.code;
        space -= c.size;
    }
}

void flush_bits() {
    
    if (space < 8) {
        
        printf("%c", buf);
    }
}

void print_char_codes(Code ** table) {
    
    
}
