#ifndef public_c
#define public_c
#include <interface.c>
#include <stdlib.h>
#include <stdbool.h>

bool new(TREE)
{
    p_tree = malloc(sizeof(tree23int_t));
    return NULL != p_tree;
}

void free_node(ROOT)
{
	if (NULL != p_root) {
		if (NULL != p_root->p_child1) {
			free_node(p_root->p_child1);
		}
		if (NULL != p_root->p_child2) {
			free_node(p_root->p_child2);
		}
		if (NULL != p_root->p_child3) {
			free_node(p_root->p_child3);
		}

		SafeDelete(p_root);
	}
}

void destructor(TREE)
{
    free_node(p_tree->data);
    free(p_tree);
    p_tree = NULL;
}

#endif
