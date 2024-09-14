#ifndef traverse_c
#define traverse_c
#include <interface.c>
#include <stdlib.h>
#include <stdio.h>

/////////////////////////////////////////////////////////////////////////////
//
//	TraverseRec()
//
void traverse_rec(ROOT, u_int32_t *prev)
{

	if (NULL == p_root->p_child1) {
		*prev = p_root->ref_lo.key;
		printf("%4d", p_root->ref_lo.key);

		if (NULL != p_root->ref_hi.p_context) {
			*prev = p_root->ref_hi.key;
			printf("%4d", p_root->ref_hi.key);
		}

	}
	else {
		traverse_rec(p_root->p_child1, prev);

		*prev = p_root->ref_lo.key;
		printf("%4d", p_root->ref_lo.key);

		traverse_rec(p_root->p_child2, prev);

		if (NULL != p_root->p_child3) {
			*prev = p_root->ref_hi.key;
			printf("%4d", p_root->ref_hi.key);

			traverse_rec(p_root->p_child3, prev);
		}
	}
}


/////////////////////////////////////////////////////////////////////////////
//
//	Traverse()
//
void traverse(TREE)
{
	if (NULL != p_tree->data) {
		u_int32_t prev = 0;
		traverse_rec(p_tree->data, &prev);
		printf("\n\n");
	}
}

#endif
