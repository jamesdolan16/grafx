#ifndef lcthw_list_algos_h
#define lcthw_list_algos_h

#include "list.h"
#include "dbg.h"

typedef int (*List_compare)(const void *x, const void *y);

int List_bubble_sort(List *list, List_compare cmp);
List *List_merge_sort(List *list, List_compare cmp);

#endif