#ifndef interface_c
#define interface_c
#include <stdlib.h>
#include <sys/types.h>

#define TREE tree23int_t *p_tree
#define PTREE tree23int_t **p_tree
#define ROOT node_t *p_root
#define SafeDelete(x)		{ if (NULL != (x)) { free(x);     (x) = NULL; } }

//#define DEBUG

#ifdef DEBUG
    #define p(...) printf("line %d ", __LINE__); printf(__VA_ARGS__);
#else
    #define p /**/
#endif


typedef struct _void_ref
{
	u_int32_t  key;
	void* p_context;
} void_ref_t;

typedef struct _node
{
	struct _node *p_child1;
	struct _node *p_child2;
	struct _node *p_child3;

	void_ref_t ref_lo;
	void_ref_t ref_hi;
} node_t;

typedef struct _tree23int
{
    node_t *data;
} tree23int_t;

void insert(TREE, void_ref_t ref);
void delete(TREE, const u_int32_t key);
void* lookup(TREE, const u_int32_t key);

#endif
