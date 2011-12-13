#include <stdio.h>
#define ARRAY_SIZE 30000

char bf[ARRAY_SIZE];
char *p = bf;
char c;
long pos;

void doBF(FILE *);
void interpretBF(char);

/* TODO:
	- Most important (and all that I can think of right now): nested loops.
*/