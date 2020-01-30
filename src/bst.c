#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

//	Input: ’size’: size of an array
//	Output: a pointer of type BStree,
//				i.e. a pointer to an allocated memory of BStree_struct type
//	Effect: dynamically allocate memory of type BStree_struct
//			allocate memory for a Node array of size+1 for member tree_nodes
//			allocate memory for an unsigned int array of size+1 for member is_free
//			set entry i of is_free to i
//			set member size to ’size’
//			set member top to 1 
//			set member root to 0 
BStree bstree_ini(int size) {
	BStree bst;
	int i;

	bst = (BStree) malloc( sizeof(BStree_struct) );
	bst->tree_nodes = (Node *) malloc( (size+1)*sizeof(Node) );
	bst->free_nodes = (unsigned int *) malloc( (size+1)*sizeof(unsigned int) );
	bst->size = size;
	for (i=0; i<=size; i++) {
		bst->free_nodes[i] = i;
	}
	bst->top = 1;
	bst->root = 0;
	return bst;
}

//	Input: ’bst’: a binary search tree
//					’key’: a Key
//					’data’: a Data
//	Effect: get a free tree_nodes index from free_nodes[top]
//	        ’key’ with ’data’ is assigned into the free tree_nodes
//					left and right are assigned to 0
static int new_node(BStree bst, Key key, Data data) {
	int index;
	if (bst->top > bst->size) {
		return 0;
	}
	index = bst->free_nodes[bst->top];
	bst->top++;
	bst->tree_nodes[index].key = key;
	bst->tree_nodes[index].data = data;
	bst->tree_nodes[index].left = 0;
	bst->tree_nodes[index].right = 0;
	return index;
}

//	Input: ’bst’: a binary search tree
//					’key’:  a Key
//					’data’: a Data
//					'index': pointer to current tree node index
//	Effect: ’key’ with ’data’ is inserted into ’bst’
//					if ’key’ is already in ’bst’, do nothing
static void bst_insert(BStree bst, int *index, Key key, Data data) {
	if (*index == 0 ) {
		*index = new_node(bst, key, data);
		return;
	}
	else {
		int i=*index;
		int comp = key_comp( bst->tree_nodes[i].key, key );
		if ( comp < 0 ) {
			bst_insert(bst, &bst->tree_nodes[i].right, key, data);
		}
		else if ( comp > 0 ) {
			bst_insert(bst, &bst->tree_nodes[i].left, key, data);
		}
		else
			return;
	}
}

//	Input: ’bst’: a binary search tree
//					’key’:  a Key
//					’data’: a Data
//	Effect: ’key’ with ’data’ is inserted into ’bst’
//					if ’key’ is already in ’bst’, do nothing
void bstree_insert(BStree bst, Key key, Data data) {
	bst_insert(bst, &bst->root, key, data);
}

//	Input: ’bst’: a binary search tree
//					’key’:  a Key
//					'index': pointer to current tree node index
//	Effect: delete the tree node who's key is ’key’ from ’bst’
//					if ’key’ is not ’bst’, do nothing
static void bst_delete(BStree bst, int *index, Key key) {
	int ind = *index;
  if (ind == 0) {
    return;
  }
  int comp = key_comp(key, bst->tree_nodes[ind].key);
  if ( comp < 0 )
    bst_delete(bst, &bst->tree_nodes[ind].left, key);
  else if ( comp > 0 )
    bst_delete(bst, &bst->tree_nodes[ind].right, key);
  else { //comp==0
    if (bst->tree_nodes[ind].left == 0) {
      *index = bst->tree_nodes[ind].right;
    }
    else if (bst->tree_nodes[ind].right == 0) {
      *index = bst->tree_nodes[ind].left;
    }
    else {
      int *index1=&bst->tree_nodes[ind].right;
			int ind1 = *index1;
			while ( bst->tree_nodes[ind1].left != 0 ) {
        index1 = &bst->tree_nodes[ind1].left;
        ind1 = *index1;
      }
			*index1 = bst->tree_nodes[ind1].right;
      *index = ind1;
      bst->tree_nodes[ind1].left = bst->tree_nodes[ind].left;
      bst->tree_nodes[ind1].right = bst->tree_nodes[ind].right;
    }
    bst->top--;
		bst->free_nodes[bst->top] = ind;
  }
}

//	Input: ’bst’: a binary search tree
//					’key’:  a Key
//	Effect: delete the tree node who's key is ’key’ from ’bst’
//					if ’key’ is not ’bst’, do nothing
void bstree_delete(BStree bst, Key key) {
	bst_delete(bst, &bst->root, key);
}

// Input: ’bst’: a binary search tree
//        'index': index of current tree node
// Effect: print all the nodes in bst using in order traversal
static void bst_traversal(BStree bst, int index) {
	if ( index == 0 ) {
		return;
	}
	else {
		bst_traversal(bst, bst->tree_nodes[index].left);
		print_node( bst->tree_nodes[index]);
		bst_traversal(bst, bst->tree_nodes[index].right);
	}
}

// Input: ’bst’: a binary search tree
// Effect: print all the nodes in bst using in order traversal
void bstree_traversal(BStree bst) {
  bst_traversal(bst, bst->root);
}

// Input: ’bst’: a binary search tree
// Effect: free all dynamic allocated memory for bst
void bstree_free(BStree bst) {
	free( bst->tree_nodes );
	free( bst->free_nodes );
	free( bst );
}

// If key is in bst, return the address of key’s associated data. If key is not in bst, return NULL.
static Data *bst_search(BStree bst, int index, Key key) {
	if (index == 0) {
		return NULL;
	}
	int comp = key_comp(bst->tree_nodes[index].key, key);
	if (comp == 0) {
		return &bst->tree_nodes[index].data;
	}
	else if (comp < 0) {
		if (bst->tree_nodes[index].right == 0) {
			return NULL;
		}
		return bst_search(bst, bst->tree_nodes[index].right, key);
	}
	else {
		if (bst->tree_nodes[index].left == 0) {
			return NULL;
		}
		return bst_search(bst, bst->tree_nodes[index].left, key);
	}
}

// If key is in bst, return the address of key’s associated data. If key is not in bst, return NULL.
Data *bstree_search(BStree bst, Key key) {
	return bst_search(bst, bst->root, key);
}

// Return the address of the key of the first node, in order of the keys in bst, such that the
// data of the node is greater than or equals to data. If there is no such node, return NULL.
static Key *bst_data_search(BStree bst, int index, Data data) {
	if (index == 0) {
		return NULL;
	}
	Key * key = bst_data_search(bst, bst->tree_nodes[index].left, data);
	if (key != NULL) {
		return key;
	}
	int comp = data_comp(bst->tree_nodes[index].data, data);
	if (comp >= 0) {
		return &bst->tree_nodes[index].key;
	}
	key = bst_data_search(bst, bst->tree_nodes[index].right, data);
	if (key != NULL) {
		return key;
	}
}

// Return the address of the key of the first node, in order of the keys in bst, such that the
// data of the node is greater than or equals to data If there is no such node, return NULL.
Key *bstree_data_search(BStree bst, Data data) {
	return bst_data_search(bst, bst->root, data);
}

