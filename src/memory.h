#ifndef Memory_H
#define Memory_H

#include "bst.h"

void mem_ini(unsigned int size);
void mem_free(void);
void *simu_malloc(unsigned int size);
void simu_free(void *ptr);
void mem_print(void);

#endif
