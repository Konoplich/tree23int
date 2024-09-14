#ifndef fix_first_c
#define fix_first_c
#include <stdlib.h>
#include <interface.c>
#include <stdbool.h>

/////////////////////////////////////////////////////////////////////////////
//
//	FixFirst()
//
//	This is called when p_root->p_child1 has ended up as a degenerate 1-node.
//
//	If p_root->p_child2 is a 3-node, the nodes can be rebalanced by rotating
//	one of the keys from p_child2 to p_child1.
//
//	Otherwise the code has to merge p_child1 and p_child2.  If p_root only
//	had two children before the merge, this will cause p_root to become a
//	degenerate 1-node.
//
//	Returns true if p_root ends up with only one child after the merge.
//
bool fix_first(ROOT)
{
	node_t *pC1 = p_root->p_child1;
	node_t *pC2 = p_root->p_child2;

	// If p_child2 is a 3-node, we rotate one of its children over to
	// p_child1.  No merge is needed, so the fix-up work on the tree is
	// now complete.
	if (NULL != pC2->ref_hi.p_context) {
		pC1->ref_lo   = p_root->ref_lo;
		p_root->ref_lo = pC2->ref_lo;
		pC2->ref_lo   = pC2->ref_hi;
		pC2->ref_hi.key      = 0;
		pC2->ref_hi.p_context = NULL;
		pC1->p_child2 = pC2->p_child1;
		pC2->p_child1 = pC2->p_child2;
		pC2->p_child2 = pC2->p_child3;
		pC2->p_child3 = NULL;

		return false;
	}

	// If we get to here, p_child2 is a 2-node.  We have no choice but to
	// merge p_child1 and p_child2.

	// The first key in p_root and the only key in p_child2 are moved into
	// p_child1, turning p_child1 into a 3-node.
	pC1->ref_lo = p_root->ref_lo;
	pC1->ref_hi = pC2->ref_lo;
	pC2->ref_lo.key      = 0;
	pC2->ref_lo.p_context = NULL;

	// The two children of p_child2 are moved into p_child1.
	pC1->p_child2 = pC2->p_child1;
	pC1->p_child3 = pC2->p_child2;

	// Clear out the pointers to avoid problems with freeing p_child2.
	pC2->p_child1 = NULL;
	pC2->p_child2 = NULL;
	pC2->p_child3 = NULL;

	// p_child3 becomes p_child2.  This may turn p_root into a degenerate
	// 1-node.
	p_root->ref_lo = p_root->ref_hi;
	p_root->ref_hi.key      = 0;
	p_root->ref_hi.p_context = NULL;
	p_root->p_child2 = p_root->p_child3;
	p_root->p_child3 = NULL;

	free(pC2);

	// Following the merge, p_root may have turned into a 1-node.  Return
	// true if the merge needs to propagate up the tree.
	return (NULL == p_root->ref_lo.p_context);
}


#endif
