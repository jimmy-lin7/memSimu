#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

static unsigned char *memory;
static BStree bst;

// Initialize an unsigned char array of size elements and initialize a binary search tree.
void mem_ini(unsigned int size) {
	memory = (unsigned char *) malloc(size);
	bst = bstree_ini(size/5); // size/5 is large enough
	bstree_insert(bst, 0, size);
}

// Allocate size bytes and return a pointer to the first byte allocated.
void *simu_malloc(unsigned int size) {
	Key *key = bstree_data_search(bst, size+4); // Get key
	Data *bytesTaken = bstree_search(bst, *key);
	bstree_delete(bst, *key);
	if (((*bytesTaken) - (size + 4)) != 0){
	bstree_insert(bst, (*key)+size+4, (*bytesTaken) - (size + 4));
	}
	*((int*)(memory +*key)) = size;
	return memory+(*key)+4;
}

// Put the allocated memory pointed by ptr back to be free memory.
void simu_free(void *ptr) {
	unsigned char * point = (unsigned char *) ptr;
	int*sizePtr = (int*)(ptr - 4);
	bstree_insert(bst, point - 4 - memory, (*sizePtr)+4);

}

// Print all the free memory blocks.
void mem_print(void) {
	bstree_traversal(bst);
}

// Free memory used for the array and the binary search tree.
void mem_free(void) {
	bstree_free(bst);
	free(memory);
}
