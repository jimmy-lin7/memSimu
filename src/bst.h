#ifndef Bst_H
#define Bst_H

#include "datatype.h"

typedef struct {
	Node *tree_nodes;
	unsigned int *free_nodes;
	int size, top, root;
} BStree_struct;
typedef BStree_struct* BStree;

BStree bstree_ini(int size);
void bstree_insert(BStree bst, Key key, Data data);
void bstree_traversal(BStree bst);
void bstree_free(BStree bst);
void bstree_delete(BStree bst, Key key);
Data *bstree_search(BStree bst, Key key);
Key *bstree_data_search(BStree bst, Data data);
//void bstree_pre_suc(BStree bst, Key key, Key **pre, Key **suc);
//void bstree_traversal_all(BStree bst);

#endif
