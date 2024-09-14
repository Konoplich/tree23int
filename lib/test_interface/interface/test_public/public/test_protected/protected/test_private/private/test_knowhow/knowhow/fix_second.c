#ifndef fix_second_c
#define fix_second_c
#include <interface.c>
#include <stdlib.h>
#include <stdbool.h>

/////////////////////////////////////////////////////////////////////////////
//
//	FixSecond()
//
//	This is called when p_root->p_child2 has ended up as a degenerate 1-node.
//
//	This is the most complex of the fix-up routines.  If either p_child1 or
//	p_child3 is a 3-node, the extra node can be rotated into p_child2 to turn
//	it back into a 2-node.  If we cannot rotate a value in from a sibling,
//	we will be forced to merge p_child1 and p_child2.
//
//	Returns true if p_root ends up as a 1-node, which forces the fix-up
//	operation to propagate up to the next level of the tree.
//
//	NOTE: This p_root is never a leaf node.  Before this call, the node is
//	legal and has at least two children.
//
bool fix_second(ROOT)

{
	node_t *pC1 = p_root->p_child1;
	node_t *pC2 = p_root->p_child2;
	node_t *pC3 = p_root->p_child3;

	// If p_child3 exists and is a 3-node, rotate a value over to p_child2.
	if ((NULL != pC3) && (NULL != pC3->ref_hi.p_context)) {
		pC2->ref_lo   = p_root->ref_hi;
		p_root->ref_hi = pC3->ref_lo;
		pC3->ref_lo   = pC3->ref_hi;
		pC3->ref_hi.key      = 0;
		pC3->ref_hi.p_context = NULL;

		pC2->p_child2 = pC3->p_child1;
		pC3->p_child1 = pC3->p_child2;
		pC3->p_child2 = pC3->p_child3;
		pC3->p_child3 = NULL;

		return false;
	}
	
	// If p_child1 is a 3-node, rotate its extra child over to p_child2.
	if (NULL != pC1->ref_hi.p_context) {
		pC2->ref_lo   = p_root->ref_lo;
		p_root->ref_lo = pC1->ref_hi;
		pC1->ref_hi.key      = 0;
		pC1->ref_hi.p_context = NULL;

		pC2->p_child2 = pC2->p_child1;
		pC2->p_child1 = pC1->p_child3;
		pC1->p_child3 = NULL;

		return false;
	}
	
	// If p_child3 exists, merge it with p_child2.
	if (NULL != p_root->ref_hi.p_context) {
		pC2->ref_lo = p_root->ref_hi;
		pC2->ref_hi = pC3->ref_lo;
		p_root->ref_hi.key      = 0;
		p_root->ref_hi.p_context = NULL;
		pC3->ref_lo.key        = 0;
		pC3->ref_lo.p_context   = NULL;

		pC2->p_child2 = pC3->p_child1;
		pC2->p_child3 = pC3->p_child2;
		pC3->p_child1 = NULL;
		pC3->p_child2 = NULL;

		p_root->p_child3= NULL;

		free(pC3);

		return false;
	}

	// The last resort is to merge p_child1 and p_child2.
	// This will turn p_root into a degenerate 1-node.
	pC1->ref_hi = p_root->ref_lo;
	p_root->ref_lo.key      = 0;
	p_root->ref_lo.p_context = NULL;

	pC1->p_child3   = pC2->p_child1;
	pC2->p_child1   = NULL;
	p_root->p_child2 = NULL;

	free(pC2);

	// Return true since p_root is degenerate and the fix-up operation
	// must propagate up to the next level of the tree.
	return true;
}


#endif
