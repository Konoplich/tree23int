#ifndef sanity_check_c
#define sanity_check_c
#include <interface.c>
#include <stdlib.h>
#include <stdio.h>

/////////////////////////////////////////////////////////////////////////////
//
//	SanityCheckRec()
//
//	Recurse through the tree and verify that the state of the tree meets all
//	of the requirements of an interior 2-3 tree.
//
void sanity_check_rec(ROOT)
{
    
	printf("%d %s\n", __LINE__, (NULL != p_root)? "Ok":"Error");
	// A leaf node cannot have any child pointers.
	if (NULL == p_root->p_child1) {
		printf("%d %s\n", __LINE__, (NULL == p_root->p_child1)? "Ok":"Error");
		printf("%d %s\n", __LINE__, (NULL == p_root->p_child2)? "Ok":"Error");
		printf("%d %s\n", __LINE__, (NULL == p_root->p_child3)? "Ok":"Error");
	}

	// A non-leaf node must have at least two child pointers.
	else {
		printf("%d %s\n", __LINE__, (NULL != p_root->p_child1)? "Ok":"Error");
		printf("%d %s\n", __LINE__, (NULL != p_root->p_child2)? "Ok":"Error");

		// If there is a second key, there must also be a third child.
		if (NULL != p_root->ref_hi.p_context) {
			printf("%d %s\n", __LINE__, (p_root->ref_lo.key < p_root->ref_hi.key)? "Ok":"Error");
			printf("%d %s\n", __LINE__, (NULL != p_root->p_child3)? "Ok":"Error");
		}

		// If the first child is a leaf, all children must be a leaf.
		if (NULL == p_root->p_child1->p_child1) {
			printf("%d %s\n", __LINE__, (NULL == p_root->p_child2->p_child1)? "Ok":"Error");

			if (NULL != p_root->ref_hi.p_context) {
			    printf("%d %s\n", __LINE__, (NULL == p_root->p_child3->p_child1)? "Ok":"Error");
			}
		}

		// If the first child is not a leaf, none of the children can be
		// leaves.
		else {
			printf("%d %s\n", __LINE__, (NULL != p_root->p_child2->p_child1)? "Ok":"Error");

			if (NULL != p_root->ref_hi.p_context) {
			    printf("%d %s\n", __LINE__, (NULL != p_root->p_child3->p_child1)? "Ok":"Error");
			}
		}

		// Recurse over all of the children.
		sanity_check_rec(p_root->p_child1);
		sanity_check_rec(p_root->p_child2);

		if (NULL != p_root->ref_hi.p_context) {
			sanity_check_rec(p_root->p_child3);
		}
	}
}


/////////////////////////////////////////////////////////////////////////////
//
//	SanityCheck()
//
//	Wrapper function around the code for recursively validating the contents
//	of the tree.
//
void sanity_check(TREE)
{
	if (NULL != p_tree->data) {
		sanity_check_rec(p_tree->data);
	}
}

#endif
