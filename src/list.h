#ifndef List_H
#define List_H

#include "datatype.h"

typedef List_node *List;

List list_ini(void);
Data *list_search(List list, Key key);
void list_add(List list, Key key, Data data);
void list_delete(List list, Key key);
void list_print(List list);
void list_free(List list);

#endif
