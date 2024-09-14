/****************************************

* File Name : lookup.c

* Creation Date : 14-09-2024

* Last Modified : Сб 14 сен 2024 13:34:39

* Created By :  Sergey Konoplich

*****************************************/
#ifndef lookup_c
#define lookup_c
#include <stdlib.h>
#include <interface.c>

/////////////////////////////////////////////////////////////////////////////
//
//	LookUp()
//
//	Iteratively traverses the tree looking for the given search key.
//	Returns the context pointer if the key exists within the tree.
//	Returns NULL if the key cannot be found.
//
void* lookup(TREE, const u_int32_t key)
{
	if (NULL == p_tree) {
		return NULL;
	}

    p("lookup enter %p %d\n", p_tree->data, key);
	node_t *pScan = p_tree->data;
    p("lookup\n");
	while (NULL != pScan) {
		if (key < pScan->ref_lo.key) {
			pScan = pScan->p_child1;
		}
		else if (key == pScan->ref_lo.key) {
			return pScan->ref_lo.p_context;
		}

		// If this is a 2-node, iterate down to the second child.
		else if (NULL == pScan->ref_hi.p_context) {
    p("lookup\n");
			pScan = pScan->p_child2;
		}

		// Otherwise we need to compare against the higher key to
		// determine whether we traverse the second or third child.
		else if (key < pScan->ref_hi.key) {
			pScan = pScan->p_child2;
		}
		else if (key > pScan->ref_hi.key) {
			pScan = pScan->p_child3;
		}
		else {
    p("lookup\n");
			return pScan->ref_hi.p_context;
		}
	}

	return NULL;
}

#endif

