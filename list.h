

//

/** ElemType may be changed for application
 * specific needs.
 *
 * However, it should be a numeric type.
 */

typedef int ElemType;

typedef struct node {
    ElemType val;
    struct node *next;
    struct node *prev;
    int inQueue;
} NODE;


struct list_struct {
    NODE *front;
    NODE *back;
    int size;
};


#define FORMAT " %i "
#define DEFAULT 0

// hidden implementation of list_struct
typedef struct list_struct LIST;

extern LIST *lst_create(); 
extern void lst_free(LIST *l);
extern void lst_print(LIST *l); 


extern void lst_push_front(LIST *l, NODE *newNode); 
extern void lst_push_back(LIST *l, NODE *newNode); 

/** TODO
 * function:  lst_length
 *
 * description:  returns the length of the given list.
 *
 * CONSTRAINTS:
 *
 *      runtime:  O(1)
 *		  (you will rewrite the THETA(n) version
 *		  already given to you).
 *
 * NOTES:
 *
 *      since the LIST struct is "hidden" in the .c file,
 *      you ARE free to change it; this will almost certainly
 *      be necessary to achive the O(1) runtime.
 *
 *      furthermore, the real work you do to make this work
 *	in O(1) time will be in _other_ functions which affect
 *	the length of lists.
*/
extern int lst_length(LIST *l);

extern int lst_is_empty(LIST *l);

extern NODE* lst_pop_front(LIST *l); 
