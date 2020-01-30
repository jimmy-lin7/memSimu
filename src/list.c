#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "memory.h"

// Return a pointer to a dynamically allocated and initialized List.
List list_ini(void) {
	List_node *head= (List_node *) simu_malloc( sizeof(List_node) ); 
	head->next = NULL;
	return head;
}

// If key is in list, return the address of key’s associated data. If key is not in list, return NULL.
Data *list_search(List list, Key key) {
	List_node *head = list->next;
	for(; head != NULL; head = head->next){
		if (head->key == key) {
			return &(head->data);
		}
	}
	return NULL;
}

// Add key with data into the front of list. If key is in lsit, then do nothing.
void list_add(List list, Key key, Data data) {
	if (list_search(list, key) != NULL) {
		return;
	}
	else {
		List_node *node = (List_node *)simu_malloc(sizeof(List_node));
		node->key = key;
		node->data = data;
		node->next = list->next;
		list->next = node;
	}
}

// Delete the node in list with its key equals to key. If no such node in list, do nothing.
void list_delete(List list, Key key) {
	if (list->next == NULL) { // Indicates end of list, haven't found node so do nothing
		return;
	}
	else if (list->next->key == key) { // Delete and free node
		List_node *node = list->next;
		list->next = list->next->next;
		simu_free(node);
		return;
	}
	list_delete(list->next, key); // Check next node
}

// Linearly traversal the list and print each node’s key and data.
void list_print(List list) {
	List_node *head = list->next;
	while (head != NULL) {
		print_list_node(head);
		head = head->next;
	}
}

// Free all the dynamically allocated memory of list.
void list_free(List list) {
	if (list != NULL) {
		list_free(list->next);
		simu_free(list);
	}
}
