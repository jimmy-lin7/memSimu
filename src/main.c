#include <stdio.h>
#include <stdlib.h>
#include "memory.h"
#include "list.h"
#include "bst.h"

int main() {
	printf("Size of the dynamic memory system: ");
	// Ini memory
	unsigned int mem;
	scanf("%d", &mem);
	mem_ini(mem);
	// Ini linked list
	List list = list_ini();
	// Insert values and occurances into linked list
	int value;
	int *occurs;
	printf("Enter values:\n");
	scanf("%d", &value);
	while (!feof(stdin)) { // While not ctrl-d
		occurs = list_search(list, value);
		if (occurs == NULL) {
			list_add(list, value, 1);
		}
		else {
			list_delete(list, value);
			list_add(list, value, (*occurs) + 1);
		}
		scanf("%d", &value);
	}
	printf("integer   Occurance\n");
	list_print(list);
	list_free(list);
	mem_free();
}