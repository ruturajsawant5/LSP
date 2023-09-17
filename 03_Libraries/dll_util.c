#include "dll.h"
#include <memory.h>
#include <stdlib.h>

/*More functions*/
int /*return 0 on success and -1 on failure*/
remove_data_from_dll_by_data_ptr(dll_t *dll, void *data) {

    dll_node_t *node = NULL;

    if (dll == NULL)
        return -1;

    node = dll->head;
    while (node) {
        if (&(node->data) == data)
            return 0;
        node = node->right;
    }
    return -1;
}

/*return 0 if empty, -1 if not empty*/
int is_dll_empty(dll_t *dll) {
    if (dll && dll->head)
        return -1;
    return 0;
}

/* delete all nodes from a dll, but do not free appln data*/
void drain_dll(dll_t *dll) {
    dll_node_t *node = NULL, *temp = NULL;

    if (dll == NULL || (dll && dll->head == NULL))
        return;

    node = dll->head;
    while (node) {
        temp = node->right;
        free(node);
        node = temp;
    }
}
