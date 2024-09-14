#ifndef key_count_c
#define key_count_c
#include <interface.c>
#include <stdlib.h>
/////////////////////////////////////////////////////////////////////////////
//
//	KeyCountRec()
//
//	Recurse through all child nodes, counting the total number of keys in the
//	tree.
//
u_int32_t key_count_rec(ROOT)
{
	u_int32_t tally = 0;

	if (NULL != p_root->ref_lo.p_context) {
		tally += 1;
	}
	if (NULL != p_root->ref_hi.p_context) {
		tally += 1;
	}

	if (NULL != p_root->p_child1) {
		tally += key_count_rec(p_root->p_child1) + key_count_rec(p_root->p_child2);

		if (NULL != p_root->p_child3) {
			tally += key_count_rec(p_root->p_child3);
		}
	}

	return tally;
}


/////////////////////////////////////////////////////////////////////////////
//
//	KeyCount()
//
//	This is just a wrapper function for the recursive routine that counts
//	all keys in the tree.
//
u_int32_t key_count(TREE)
{
	return key_count_rec(p_tree->data);
}

#endif
