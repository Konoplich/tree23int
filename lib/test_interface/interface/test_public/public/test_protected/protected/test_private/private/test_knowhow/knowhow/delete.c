#ifndef delete_c
#define delete_c
#include <interface.c>
#include <stdlib.h>
#include <stdbool.h>
#include <fix_first.c>
#include <fix_second.c>
#include <fix_third.c>
#include <fix_in_order_successor.c>
#include <in_order_successor.c>

/////////////////////////////////////////////////////////////////////////////
//
//	DeleteRec()
//
//	Recursively locate the node to delete (if it even exists in the tree),
//	then remove the node.  If this causes a degenerate 1-node, we need to
//	start merging this node with one of its siblings.
//
//	Returns true if the node needs to be merged.  The caller is responsible
//	for completing the merge (or in the case of the root, deleting the old
//	root of the tree).
//
bool delete_rec(ROOT, const u_int32_t key)
{
	// This is an interior node.  Determine which child should be recursed.
	// If the recursive call returned true, the node need to be merged.
	if (NULL != p_root->p_child1) {
		// Recurse down the leftmost child.
		if (key < p_root->ref_lo.key) {
			if (delete_rec(p_root->p_child1, key)) {
				// p_child1 was turned into a 1-node.  Perform a fix-up
				// operation to turn p_child1 into a 2-node.
				return fix_first(p_root);
			}
		}

		// The key to delete is the first key in p_root.
		else if (key == p_root->ref_lo.key) {
			void_ref_t succ;

			// Find the smallest key that is larger than the key being
			// deleted.  This will replace the first key in p_root.
			if (in_order_successor(p_root->p_child2, &succ)) {
				p_root->ref_lo = succ;

				// If InOrderSuccessor() returned true, the node that used
				// to contain the successor key was turned into a 1-node,
				// so we need to apply a fix-up operation to that node,
				// which in turn may cause merging operation to progress up
				// the tree.
				if (fix_in_order_successor(p_root->p_child2)) {
					return fix_second(p_root);
				}
			}
			else {
				p_root->ref_lo = succ;
			}
		}

		// If p_root is a 3-node, we need to recurse down either p_child2 or
		// p_child3.
		else if (NULL != p_root->ref_hi.p_context) {

			// Recurse down the second child.
			if (key < p_root->ref_hi.key) {
				if (delete_rec(p_root->p_child2, key)) {
					return fix_second(p_root);
				}
			}

			// Recurse down the third child.
			else if (key > p_root->ref_hi.key) {
				if (delete_rec(p_root->p_child3, key)) {
					fix_third(p_root);
					return false;
				}
			}

			// If we get here, p_root's second key is the one that needs to
			// be deleted.  That key needs to be replaced by the in-order
			// successor to the key being deleted.
			else {
				void_ref_t succ;

				// Find the smallest key that is larger than the key being
				// deleted.  This will replace the first key in p_root.
				if (in_order_successor(p_root->p_child3, &succ)) {
					p_root->ref_hi = succ;

					// If InOrderSuccessor() returned true, the node that
					// used to contain the successor key was turned into a
					// 1-node, so we need to apply a fix-up operation to
					// that node, which in turn may cause merging operations
					// to progress up the tree.
					if (fix_in_order_successor(p_root->p_child3)) {
						fix_third(p_root);
						return false;
					}
				}
				else {
					p_root->ref_hi = succ;
				}
			}
		}

		// Otherwise p_root is a 2-node, so the only option is to recurse
		// down the second child in search of the key to delete.
		else {
			if (delete_rec(p_root->p_child2, key)) {
				return fix_second(p_root);
			}
		}
	}

	// Special case for hitting a leaf node.
	else {
		// If the key to remove is the first key, we try to replace the
		// first key with the second.
		if (key == p_root->ref_lo.key) {

			// Assume there is a second key and replace the first with it.
			// If not, we have at least succeeded in NULLing out the first
			// node.
			p_root->ref_lo          = p_root->ref_hi;
			p_root->ref_hi.key      = 0;
			p_root->ref_hi.p_context = NULL;

			// Return true if we ended up with a node that contains no keys.
			// The parent will need to handle merging the node.
			return (NULL == p_root->ref_lo.p_context);
		}

		// If there is a second node, check to see if it is the key we need
		// to remove.  If so, we only need to NULL out the reference.
		// Always return false, since no merge is needed in this case.
		else if ((NULL != p_root->ref_hi.p_context) && (key == p_root->ref_hi.key)) {
			p_root->ref_hi.key      = 0;
			p_root->ref_hi.p_context = NULL;
		}
	}

	return false;
}




/////////////////////////////////////////////////////////////////////////////
//
//	Delete()
//
//	This is the main routine for deleting a key from the tree.  
//
void delete(TREE, const u_int32_t key)
{
	if (delete_rec(p_tree->data, key)) {

		// If a merge propagated all the way to the root, we need to delete
		// the root of the tree.
		//
		// Note that this is the only way that the depth of the tree can
		// change.  By deleting the root, the depth of every leaf node has
		// just decreased by 1.

		node_t *pTemp = p_tree->data;

		p_tree->data = p_tree->data->p_child1;

		pTemp->p_child1 = NULL;

		free(pTemp);
	}
}


#endif
