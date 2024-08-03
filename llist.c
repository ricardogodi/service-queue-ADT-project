#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/*
* returns pointer to newly created empty list
*/
LIST *lst_create() {
    LIST *l = malloc(sizeof(LIST));
    l->front = NULL;
    l->back = NULL;
    l->size = 0;
    return l;
}

void lst_free(LIST *l) {
    NODE *p = l->front;
    NODE *pnext;
    while(p != NULL) {
        pnext = p->next;   // keeps us from de-referencing a freed ptr
        free(p);
        p = pnext;
    }
    free(l);
}

void lst_print(LIST *l) {
NODE *p = l->front;

  printf("[");
  while(p != NULL) {
    printf(FORMAT, p->val);
    p = p->next;
  }
  printf("]\n");
}

void lst_push_front(LIST *l, NODE *newNode) {
    newNode->next = l->front;
    newNode->prev = NULL;
    if (l->front != NULL) {
        l->front->prev = newNode;
    }
    l->front = newNode;
    if(l->back == NULL)  { // was empty, now one elem
        l->back = newNode;
    }
    l->size++;
}

void lst_push_back(LIST *l, NODE * newNode) {
    if(l->back == NULL)   // list empty - same as push_front
        lst_push_front(l, newNode);
    else {  // at least one element before push
        newNode->next = NULL;
        l->back->next = newNode;
        newNode->prev = l->back;
        l->back = newNode;
        l->size++;
    }
}

int lst_is_empty(LIST *l) {
  return l->front == NULL;
}

NODE* lst_pop_front(LIST *l) {
    NODE* ret = l->front;
    if(lst_is_empty(l))
        return 0;                // no-op
    if(l->front == l->back) {  // one element
        //free(l->front);
        l->front = NULL;
        l->back = NULL;
    } else {
        l->front = l->front->next;  // hop over
        l->front->prev = NULL;
    }
    return ret;
}

