#ifndef fix_third_c
#define fix_third_c
#include <interface.c>

/////////////////////////////////////////////////////////////////////////////
//
//	FixThird()
//
//	This is called when p_root->p_child3 has ended up as a degenerate 1-node.
//
//	In this case, p_root is a 3-node, so we have enough values to safely
//	contain the merging.  At worst, we may delete p_child3.
//
//	Note that in this case, since merging is contained to this node, this
//	function does not need to return anything.
//
void fix_third(ROOT)
{
	node_t *pC2 = p_root->p_child2;
	node_t *pC3 = p_root->p_child3;

	// If p_child2 is a 3-node, we need to perform a rotation.
	if (NULL != pC2->ref_hi.p_context) {
		pC3->ref_lo   = p_root->ref_hi;
		p_root->ref_hi = pC2->ref_hi;
		pC2->ref_hi.key    = 0;
		pC2->ref_hi.p_context = NULL;

		pC3->p_child2 = pC3->p_child1;
		pC3->p_child1 = pC2->p_child3;
		pC2->p_child3 = NULL;
	}

	// Otherwise p_child2 is a 2-node.  We have to fix p_child3 by merging it
	// with p_child2, making p_root a 2-node.
	else {
		pC2->ref_hi = p_root->ref_hi;
		p_root->ref_hi.key      = 0;
		p_root->ref_hi.p_context = NULL;

		pC2->p_child3 = pC3->p_child1;
		pC3->p_child1 = NULL;

		p_root->p_child3 = NULL;

		free(pC3);
	}
}

#endif
