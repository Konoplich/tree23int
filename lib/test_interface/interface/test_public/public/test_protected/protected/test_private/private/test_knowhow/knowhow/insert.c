#ifndef insert_c
#define insert_c
#include <interface.c>
#include <new_node.c>
#include <stdbool.h>
#include <stdio.h>

/////////////////////////////////////////////////////////////////////////////
//
//	InsertRec()
//
//	This is a recursive method that does all of the work for locating the
//	position where the insertion should occur, rearranging the contents of
//	the tree, and returning info needed by the parent to perform a split.
//
//	If the node ends up being split, this method will return true, so the
//	caller knows it needs to finish the splitting logic.  This method cannot
//	do the split itself, since it does not have a reference to the parent
//	node.  This is a necessity to generalize the code to also handle the
//	root of the tree.  Because the root does not have a parent, it is more
//	simple to create a new node (if necessary), return that in ppN2, and
//	let the caller handle creating a new node to contain the split.
//
//	If a split is required, this code will rearrange data to guarantee
//	that all values stored in ppN1 and ppN2 are sorted, that ppN1 will
//	be positioned to the left (less-than) of ppN2, and that ref will be
//	modified to hold the key that falls between ppN1 and ppN2.
//
//	This means that the contents of p_root will be changed when a split is
//	required.  Technically, this operation could be considered destructive,
//	but it is necessary to assure that the two sibling nodes at this level
//	are organized correctly.  It also makes it easy for the caller to
//	finish the split by allocating a new node, making ppN1 and ppN2 its
//	two children, and setting returned value of ref as the key that comes
//	between the two modified nodes.
//
bool insert_rec(ROOT, void_ref_t *ref, node_t **ppN1, node_t **ppN2)
{
	node_t *pN1  = NULL;
	node_t *pN2  = NULL;
	node_t *pNew = NULL;

	void_ref_t key[3];

	// If a split operation occurs, we'll have to turn a 3-node into a
	// 4-node.  However, there is no such thing as a 4-node in a 2-3
	// tree.  This array is used as a placeholder while rearranging the
	// four nodes in the correct order.
	node_t *pC[4];

    p("%s\n", "insert_rec");
	// This is an internal node.  We need to start off by recursing down
	// to the appropriate child.  If the recursion caused a split, we
	// need to finish the split logic here.
	if (NULL != p_root->p_child1) {

        p("%s\n", "insert_rec");
		// Recurse down the first child.
		if (ref->key < p_root->ref_lo.key) {
			if (false == insert_rec(p_root->p_child1, ref, &pN1, &pN2)) {
				return false;
			}

			// A split of the child nodes was performed.  Figure out what
			// work is needed to clean up at this level.

			// If this is a 2-node, we just need to rearrange the keys and
			// child pointers.
			//
			// Since we recursed down the left, the second child remains
			// unchanged.  All we need to do for it is shift it over to
			// become the third child.
			//
			// Then we poke the returned values in as the first and second
			// child.
			//
			// In this case, the splitting is now contained, so we return
			// false.
			//

            p("%s\n", "insert_rec");
			if (NULL == p_root->ref_hi.p_context) {
				p_root->ref_hi   = p_root->ref_lo;
				p_root->ref_lo   = *ref;
				p_root->p_child3 = p_root->p_child2;
				p_root->p_child2 = pN2;
				p_root->p_child1 = pN1;

				return false;
			}

			// Otherwise we need to convert this 3-node into a 4-node.
			// Poke the values into the arrays so the clean-up logic can
			// split this node.
			else {
                p("%s\n", "insert_rec");
				key[0] = *ref;
				key[1] = p_root->ref_lo;
				key[2] = p_root->ref_hi;
				pC[0]  = pN1;
				pC[1]  = pN2;
				pC[2]  = p_root->p_child2;
				pC[3]  = p_root->p_child3;
			}
		}

		// If this is a 3-node, we need to decide whether to recurse down
		// the second or third child.
		else if (NULL != p_root->ref_hi.p_context) {
 
            p("%s\n", "insert_rec");
			// Recurse down the middle child.
			if (ref->key < p_root->ref_hi.key) {
				if (false == insert_rec(p_root->p_child2, ref, &pN1, &pN2)) {
					return false;
				}

				// The recursive call caused a split.  Since we now have a
				// 4-node, we have no choice but to split this node as well.
				key[0] = p_root->ref_lo;
				key[1] = *ref;
				key[2] = p_root->ref_hi;
				pC[0]  = p_root->p_child1;
				pC[1]  = pN1;
				pC[2]  = pN2;
				pC[3]  = p_root->p_child3;
			}

			// Recurse down the third child.
			else if (ref->key > p_root->ref_hi.key) {
                p("%s\n", "insert_rec");
				if (false == insert_rec(p_root->p_child3, ref, &pN1, &pN2)) {
					return false;
				}

				key[0] = p_root->ref_lo;
				key[1] = p_root->ref_hi;
				key[2] = *ref;
				pC[0]  = p_root->p_child1;
				pC[1]  = p_root->p_child2;
				pC[2]  = pN1;
				pC[3]  = pN2;
			}

			else {
				p_root->ref_hi = *ref;
				return false;
			}
		}

		// Otherwise this is a 2-node, so we can only recurse down the
		// middle child.
		else if (ref->key > p_root->ref_lo.key) {
            p("%s\n", "insert_rec");
			if (false == insert_rec(p_root->p_child2, ref, &pN1, &pN2)) {
				return false;
			}

			// A split occurred.  However, since this is a 2-node, the split
			// is contained to this level of the tree.  Since the recursive
			// call did all of the rearranging work, we replace the current
			// key and pointers with the values returned from the recursive
			// call.
			p_root->ref_hi   = *ref;
			p_root->p_child2 = pN1;
			p_root->p_child3 = pN2;

			return false;
		}

		else {
            p("%s\n", "insert_rec");
			p_root->ref_lo = *ref;
			return false;
		}
	}

	// Recursive base case:  This is where we hit a leaf node.  Unless
	// the key value is found in this node, we will try to insert the new
	// key in this node, possibly causing a split.
	else {
		// This leaf only contains one key.  No split is required, we just
		// need to insert the new key into the correct place (or replace
		// an existing value).
        p("%s\n", "insert_rec");
		if (NULL == p_root->ref_hi.p_context) {

			// If the new key is bigger than the one key in this node,
			// it becomes the second key.
			if (ref->key > p_root->ref_lo.key) {
				p_root->ref_hi = *ref;
			}

			// Otherwise we need to shift the existing key over to be
			// the second key, then drop the new key in as the first key.
			else if (ref->key < p_root->ref_lo.key) {
				p_root->ref_hi = p_root->ref_lo;
				p_root->ref_lo = *ref;
			}

			// Otherwise we're replacing an existing key with a new value.
			// This does not insert a new value, it only replaces the
			// existing value.  
			else {
				p_root->ref_lo = *ref;
			}

			// No split was required, so no fix-up operations will be
			// required as we back out of the recursion.
			return false;
		}

		// Otherwise splitting is required.  We don't need to deal with
		// any pointers, since there are no child nodes, but we do need to
		// rearrange the existing keys so that they are correctly sorted.
		//
		// Note the special cases where the key being replaced matches a
		// key already present.  Here we just need to replace the old key,
		// under the assumption that its value has been updated.
        p("%s\n", "insert_rec");
		if (ref->key < p_root->ref_lo.key) {
			key[0] = *ref;
			key[1] = p_root->ref_lo;
			key[2] = p_root->ref_hi;
		}

		// Special case: replace an existing value.
		else if (ref->key == p_root->ref_lo.key) {
			p_root->ref_lo = *ref;
			return false;
		}

		else if (ref->key < p_root->ref_hi.key) {
			key[0] = p_root->ref_lo;
			key[1] = *ref;
			key[2] = p_root->ref_hi;
		}

		// Special case: replace an existing value.
		else if (ref->key == p_root->ref_hi.key) {
			p_root->ref_hi = *ref;
			return false;
		}

		else {
			key[0] = p_root->ref_lo;
			key[1] = p_root->ref_hi;
			key[2] = *ref;
		}

        p("%s\n", "insert_rec");
		// Since this is a leaf node, leave all child pointers NULL.
		pC[0] = NULL;
		pC[1] = NULL;
		pC[2] = NULL;
		pC[3] = NULL;
	}


	// The remaining code is only executed if we have created a 4-node.
	// This forces p_root to be split.  The code above has already stored
	// the keys and child pointers in the correct order.

	// Destructively replace the contents of p_root to contain the first
	// two child nodes.
    p("%s\n", "insert_rec");
	p_root->ref_lo          = key[0];
	p_root->ref_hi.key      = 0;
	p_root->ref_hi.p_context = NULL;
	p_root->p_child1        = pC[0];
	p_root->p_child2        = pC[1];
	p_root->p_child3        = NULL;

	// Create a new node to contain the last two child pointers.
    p("%s\n", "insert_rec");
	pNew = new_node();
	pNew->ref_lo           = key[2];
	pNew->p_child1         = pC[2];
	pNew->p_child2         = pC[3];
	pNew->p_child3         = NULL;

	// Return the info about these two sibling nodes so the caller can
	// handle the split at its level.
    p("%s\n", "insert_rec");
	*ref   = key[1];
	*ppN1 = p_root;
	*ppN2 = pNew;

	return true;
}


/////////////////////////////////////////////////////////////////////////////
//
//	Insert()
//
//	Insertions are moderately complex, since various special cases must be
//	addressed to rebalance the tree following the insertion.  Insertion is
//	a recursive operation (though it could be made iterative if a stack is
//	used), so most of the complexity resides in the recursive sub-function.
//
void insert(TREE,void_ref_t ref)
{
    p("insert enter tree; %p key: %d\n", p_tree, ref.key);
    p("%s %p\n", "insert", p_tree->data);
	// In the normal case, the tree is not empty.
	if (NULL != p_tree->data) {
        p("%s\n", "insert");
		node_t *pN1  = NULL;
		node_t *pN2  = NULL;

		// If the recursive operation returns true, we need to split the
		// root of the tree.  The existing root node has already been
		// changed to maintain sorting order (the current root pointer is
		// returned in pN1), and a new node is returned in pN2.  Since
		// all conditioning was done by the recursive routine, all we
		// need to do is create a new root node and make the two pointers
		// the children of the new root node.
		//
		// Also note that ref is pass-by-reference, so upon exiting the
		// recursive function, ref will now contain the correct key for
		// the new root node.
		//

		if (insert_rec(p_tree->data, &ref, &pN1, &pN2)) {
            p("%s\n", "insert");
			p_tree->data = new_node();

			p_tree->data->ref_lo   = ref;
			p_tree->data->p_child1 = pN1;
			p_tree->data->p_child2 = pN2;
		}
	}

	// Special case for inserting into an empty tree.
	else {
        p("%s\n", "insert");
		p_tree->data = new_node();
		p_tree->data->ref_lo  = ref;
	}
    p("insert leave \n");
}


#endif
