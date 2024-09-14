#ifndef fix_in_order_successor_c
#define fix_in_oredr_successor_c
#include <interface.c>
#include <stdlib.h>
#include <stdbool.h>
#include <fix_first.c>

/////////////////////////////////////////////////////////////////////////////
//
//	FixInOrderSuccessor()
//
//	If an in-order successor was found, InOrderSuccessor() will have modified
//	the contents of a node, leaving it in a broken state.  This method will
//	recurse down the tree and repair the damage using successive calls to
//	FixFirst().
//
bool fix_in_order_successor(ROOT)
{
	if (NULL == p_root->p_child1) {
		return true;
	}

	// If this call returns true, the first child needs to be removed from
	// the tree.
	if (fix_in_order_successor(p_root->p_child1)) {
		return fix_first(p_root);
	}

	return false;
}



#endif
