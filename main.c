#include <stdlib.h>
#include <stdio.h>
#include <libtree23int.h>
#include <stdbool.h>

void ins(PTREE, int key, char *val)
{
    void_ref_t v1 = {.key=key, .p_context=val};
    insert(*p_tree, v1);
}

int main(int argc, char** argv)
{
    
    TREE;
    bool res = new(&p_tree);
    printf("p_tree-%p\n", p_tree);
    if(false == res)
    {
        printf("error 1\n");
	    exit(1);
    }
    ins(&p_tree, 2, "2");
    ins(&p_tree, 3, "3");
/*
    2 3
*/
    print(p_tree);
    ins(&p_tree, 5, "5");
/*
      3
    2   5
*/
    print(p_tree);
/*
      3
    2   5 7
*/
    ins(&p_tree, 7, "7");
    print(p_tree);

/*
      3 6
     2   5 7 
*/

    ins(&p_tree, 6, "6");
    print(p_tree);
    printf("--------\n");
    printf("insert\n");
/*
      3 6
    2   4 5   7
*/
    ins(&p_tree, 4, "4");
    print(p_tree);

    ins(&p_tree, 1, "1");
    ins(&p_tree, 2, "2");
    ins(&p_tree, 8, "8");
/*
      3 6
    1 2   4 5   7 8
*/
    print(p_tree);
;

    ins(&p_tree, 9, "9");
/*
        6
     3        8
  1 2,4 5    7,9 
*/
    print(p_tree);
    printf("depth\n");
    leaf_depth(p_tree);
    printf("traverse\n");
    traverse(p_tree);
    printf("key count: %d\n", key_count(p_tree));
    sanity_check(p_tree);

    char *v;
    char *msg[] = {"found %d %s\n", "not found %d\n"};

    v = lookup(p_tree, 4);
    printf(msg[!((size_t)v | (size_t)0)], 4, v);

    v = lookup(p_tree, 5);
    printf(msg[!((size_t)v | (size_t)0)], 5, v);

    v = lookup(p_tree, 99);
    printf(msg[!((size_t)v | (size_t)0)], 99, v);


    printf("delete %p \n",p_tree);

    delete(p_tree, 1);
    //delete(p_tree, 2);
    delete(p_tree, 8);
    delete(p_tree, 9);
    delete(p_tree, 4);
    print(p_tree);

    printf("depth\n");
    leaf_depth(p_tree);
    printf("traverse\n");
    traverse(p_tree);
    printf("key count: %d\n", key_count(p_tree));
    sanity_check(p_tree);
    destructor(&p_tree);
    printf("ok\n");
    return 0;
}
