#ifndef new_node_c
#define new_node_c
#include <interface.c>
#include <stdlib.h>

node_t *new_node(void)
{
	node_t *p_new = malloc(sizeof(node_t));

	p_new->ref_lo.key      = 0;
	p_new->ref_lo.p_context = NULL;
	p_new->ref_hi.key      = 0;
	p_new->ref_hi.p_context = NULL;
	p_new->p_child1        = NULL;
	p_new->p_child2        = NULL;
	p_new->p_child3        = NULL;

	return p_new;
}

#endif
