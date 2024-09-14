#ifndef public_c
#define public_c
#include <interface.c>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

bool new(PTREE)
{
    *p_tree = malloc(sizeof(tree23int_t));
    if(NULL !=*p_tree)
    {
        memset(*p_tree, 0, sizeof(tree23int_t));
        return true;
    }
    return false;
}

void free_node(ROOT)
{
    p("free node %p\n", p_root);
	if (NULL != p_root) {
		if (NULL != p_root->p_child1) {
			free_node(p_root->p_child1);
		}
		if (NULL != p_root->p_child2) {
			free_node(p_root->p_child2);
		}
		if (NULL != p_root->p_child3) {
			free_node(p_root->p_child3);
		}

		SafeDelete(p_root);
	}
}

void destructor(PTREE)
{
    p("destructor enter\n");
    p("destructor: %p\n", (*p_tree));
    free_node((*p_tree)->data);
    free(*p_tree);
    p_tree = NULL;
}

void print_rec(ROOT)
{
    printf("root: %p ", p_root);
	if (NULL != p_root->ref_lo.p_context) {
		printf("lo[%d-%s] ", p_root->ref_lo.key, (char*)p_root->ref_lo.p_context);
	}
	if (NULL != p_root->ref_hi.p_context) {
		printf("hi[%d-%s] ", p_root->ref_hi.key, (char*)p_root->ref_hi.p_context);
	}

	if (NULL != p_root->p_child1) {
		printf("child1 %p ", p_root->p_child1);
		print_rec(p_root->p_child1);
		printf("child2 %p ", p_root->p_child2);
        print_rec(p_root->p_child2);

		if (NULL != p_root->p_child3) {
		    printf(" child3 %p\n", p_root->p_child3);
			print_rec(p_root->p_child3);
		}
	}
    printf("\n");
}



void print(TREE)
{
    if(NULL != p_tree && NULL !=p_tree->data)
	    print_rec(p_tree->data);
}

#endif
