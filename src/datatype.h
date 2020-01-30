#ifndef Datatype_H
#define Datatype_H

typedef int Key;
typedef int Data;
typedef struct {
	Key key; 
	Data data; 
	int left, right;
} Node;
typedef struct List_node {
	Key key;
	Data data;
	struct List_node *next;
} List_node;

int key_comp(Key key1, Key key2);
int data_comp(Data data1, Data data2);
void key_print(Key key);
void data_print(Data data);
void print_node(Node node);
void print_list_node(List_node *node);

#endif
