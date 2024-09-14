#ifndef leaf_depth_c
#define leaf_depth_c
#include <interface.c>
#include <stdlib.h>
#include <stdio.h>

/////////////////////////////////////////////////////////////////////////////
//
//	LeafDepthRec()
//
//	Recurse through the tree to locate all leaf nodes.  This will track the
//	depth of every leaf node.  In a balanced tree, every leaf node should be
//	at exactly the same depth.  This method is used to verify that the tree
//	has not ended up unbalanced.
//
u_int32_t leaf_depth_rec(ROOT, u_int32_t depth, u_int32_t ary[], u_int32_t depthLimit)
{
	ary[depth] += 1;

	if (NULL != p_root->ref_hi.p_context) {
		ary[depth] += 1;
	}

	if (NULL == p_root->p_child1) {
		return depth + 1;
	}

	if (depth >= depthLimit) {
		return depth;
	}

	u_int32_t d1 = leaf_depth_rec(p_root->p_child1, depth + 1, ary, depthLimit);
	u_int32_t d2 = leaf_depth_rec(p_root->p_child2, depth + 1, ary, depthLimit);

	u_int32_t maxDepth = Max(d1, d2);

	if (NULL != p_root->ref_hi.p_context) {
		u_int32_t d3 = leaf_depth_rec(p_root->p_child3, depth + 1, ary, depthLimit);

		maxDepth = Max(maxDepth, d3);
	}

	return maxDepth;
}



/////////////////////////////////////////////////////////////////////////////
//
//	LeafDepth()
//
//	This is a sanity-checking routine.  It will figure out the depth of every
//	leaf node, then print out the resulting count.  Unless the tree has ended
//	up corrupted in some way, every leaf should be at the exact same depth.
//
void leaf_depth(TREE)
{
	u_int32_t ary[64];
	for (u_int32_t i = 0; i < ArraySize(ary); ++i) {
		ary[i] = 0;
	}

	u_int32_t maxDepth = leaf_depth_rec(p_tree->data, 0, ary, ArraySize(ary));

	u_int32_t tally = 0;

	for (u_int32_t i = 0; i < maxDepth; ++i) {
		tally += ary[i];

		printf("%3d: %5d = %5d\n", i, ary[i], tally);
	}
}


#endif
