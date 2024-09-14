#ifndef in_oredr_successor_c
#define in_order_successor_c
#include <interface.c>
#include <stdlib.h>
#include <stdbool.h>

/////////////////////////////////////////////////////////////////////////////
//
//	InOrderSuccessor()
//
//	Given a key value, find the smallest key that comes immediately after
//	this node.  This simply amounts to finding the leftmost child.
//
//	Since this code is used specifically for deletion, it will swap the
//	in-order successor into the given node, and place the old value of the
//	current node in ref.  This simplifies the swapping logic needed when
//	merging nodes.
//
bool in_order_successor(ROOT, void_ref_t *ref)
{
	// Keep traversing until we hit a leaf node.
	while (NULL != p_root->p_child1) {
		p_root = p_root->p_child1;
	}

	// Return the old value stored in p_root.
	*ref = p_root->ref_lo;

	p_root->ref_lo          = p_root->ref_hi;
	p_root->ref_hi.key      = 0;
	p_root->ref_hi.p_context = NULL;

	return (NULL == p_root->ref_lo.p_context);
}


#endif
