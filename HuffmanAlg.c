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
	
    text = fopen(argv[1], "r");

    int c[ASCII + 1];

    for (int i = 0; i <= ASCII; i++) {

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

struct node {
    node *next;
    node *child1;
    node *child2;

    int freq;
    char character;
};
