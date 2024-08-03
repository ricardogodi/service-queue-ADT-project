#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "sq.h"

// Author: Ricardo Gonzalez
// Professor: John Lillis
// CS 211
// Program #5

/**
 * description:  simple implementation of the
 *        service queue ADT as specified
 *        in sq.h
 *
 *        (Believed to be) functionally correct,
 *        but does not meet all of the runtime
 *        requirements specified in sq.h
 *
 *        Acts as a client of the linked list
 *        ADT previously developed.
 */
struct service_queue {
    LIST * the_queue;
    LIST * buzzer_bucket;
    NODE **nodeArray;
    int nodeArraySize;  // number of elements in the array
    int nodeArrayCapacity;
};

/**
 * Function: sq_create()
 * Description: creates and intializes an empty service queue.
 *          It is returned as an SQ pointer.
 */
SQ * sq_create() {
    SQ *q;
    q = malloc(sizeof(SQ));
    q->the_queue = lst_create();
    q->buzzer_bucket = lst_create();
    q->nodeArray = malloc(2 * sizeof(NODE*));  // create list of size 2
    q->nodeArrayCapacity = 2;
    q->nodeArraySize = 0;
    return q;
}

/**
 * Function: sq_free()
 * Description:  see sq.h
 *
 * RUNTIME REQUIREMENT:  O(N_t)  where N_t is the number of buzzer
 *    IDs that have been used during the lifetime of the
 *    service queue; in general, at any particular instant
 *    the actual queue length may be less than N_t.

 */
void sq_free(SQ *q) {
    lst_free(q->the_queue);
    lst_free(q->buzzer_bucket);
    free(q->nodeArray);  // free the array!
    free(q);
}

/**
 * Function: sq_display()
 * Description:  see sq.h
 *
 * REQUIRED RUNTIME:  O(N)  (N is the current queue length).
 */
void sq_display(SQ *q) {
    printf("current-queue contents:\n    ");
    lst_print(q->the_queue);
    printf("\n");
}

/**
 * Function: sq_length()
 * Description:  see sq.h
 *
 * REQUIRED RUNTIME:  O(1)
 */
int sq_length(SQ *q) {
    return q->the_queue->size;
}

/**
 * Function: sq_give_buzzer()
 * Description:  see sq.h
 *
 * REQUIRED RUNTIME:  O(1)  ON AVERAGE or "AMORTIZED":  in other words, if
 *        there have been M calls to sq_give_buzzer, the total
 *        time taken for those M calls is O(M).
 *
 *        An individual call may therefore not be O(1) so long
 *        as when taken as a whole they average constant time.
 *
 *        (Hopefully this reminds you of an idea we employed in
 *        the array-based implementation of the stack ADT).
 *
 */
int sq_give_buzzer(SQ *q) {
    
    int buzzer;
    
    if(q->buzzer_bucket->front != NULL){  // If there is something at the Buzzer, we want to recycle
        NODE* recycledBuzzer = lst_pop_front(q->buzzer_bucket);  // get the buzzer
        recycledBuzzer->inQueue = 1;
        q->buzzer_bucket->size--;
        lst_push_back(q->the_queue, recycledBuzzer);  // push_back to the queue
        buzzer = recycledBuzzer->val;
        return buzzer;
    }
    
    if(q->nodeArrayCapacity == q->nodeArraySize) {      // RE-SIZE
        
        int newCapacity = 2 * (q->nodeArrayCapacity);
        NODE ** newArray = malloc(newCapacity*sizeof(NODE*));
        
        for (int i = 0; i < q->nodeArraySize; i++) {  // copy reference to newArray
            newArray[i] = q->nodeArray[i];
        }
        
        free(q->nodeArray);     // Free the previous array. NOT THE NODES.
        q->nodeArray = newArray;  // update nodeArray
        q->nodeArrayCapacity = newCapacity;  // Now we have a new capacity
    }
    
    // If we get here we are ready to create a new node and add to the queue
    int arraySize = q->nodeArraySize;
    NODE *newNode = malloc(sizeof(NODE));  // create the node
    newNode->val = arraySize;
    newNode->inQueue = 1;
    buzzer = newNode->val;
    q->nodeArray[arraySize] = newNode;  // create reference in the array to the new node
    lst_push_back(q->the_queue, newNode);  // push it to the queue
    q->nodeArraySize++;
    return buzzer;
}

/**
 * function: sq_seat()
 * description:  see sq.h
 *
 * REQUIRED RUNTIME:  O(1)
 */
int sq_seat(SQ *q) {
    
    if (sq_length(q) == 0) {
        return -1;
    }
    
    int buzzer;
    NODE* served = lst_pop_front(q->the_queue);  // pop from the front of the queue
    served->inQueue = 0;    // now served is NOT in the queue
    q->the_queue->size--;
    buzzer = served->val;
    lst_push_back(q->buzzer_bucket, served);  // push it to the buzzer bucket
    return buzzer;
}

/**
 * function: sq_kick_out()
 *
 * description:  see sq.h
 *
 * REQUIRED RUNTIME:  O(1)
 */
int sq_kick_out(SQ *q, int buzzer) {
    
    if (buzzer >= q->nodeArraySize) {  // buzzer does not exist
        return 0;
    }
    
    if (q->nodeArray[buzzer]->inQueue == 0) {  // buzzer exists but not in queue
        return 0;
    }
    
    NODE* kicked = q->nodeArray[buzzer];
    
    if (q->the_queue->front == q->the_queue->back) {  // There is only one node in the queue
        q->the_queue->front = NULL;
        q->the_queue->back = NULL;
        kicked->inQueue = 0;
        q->the_queue->size--;
        lst_push_back(q->buzzer_bucket, kicked);
        return 1;
        
    } else {
        
        if (q->the_queue->front == kicked) {  // Kickout at the beginning
            q->the_queue->front = kicked->next;
            q->the_queue->front->prev = NULL;
        } else if (q->the_queue->back == kicked) {  // Kickout at the end
            q->the_queue->back = kicked->prev;
            q->the_queue->back->next = NULL;
        } else {                                // Kickout in the middle
            kicked->prev->next = kicked->next;
            kicked->next->prev = kicked->prev;
        }
        
        kicked->inQueue = 0;
        q->the_queue->size--;
        lst_push_back(q->buzzer_bucket, kicked);
    }
    return 1;
}

/**
 * function:  sq_take_bribe()
 * description:  see sq.h
 *
 * REQUIRED RUNTIME:  O(1)
 */
int sq_take_bribe(SQ *q, int buzzer) {
    
    if (buzzer >= q->nodeArraySize) {  // buzzer does not exist
        return 0;
    }
    
    if(q->nodeArray[buzzer]->inQueue == 0) {  // buzzer exists but not in queue
        return 0;
    }
    
    NODE* briber = q->nodeArray[buzzer];
    
    if (q->the_queue->front == q->the_queue->back) {
        // do nothing, briber is already at the right spot
    } else {
        
        if(q->the_queue->front == briber) {  // Briber at the beginning
            // do nothing, briber is already at the right spot
        } else if (q->the_queue->back == briber) {  // Briber at the end
            q->the_queue->back = briber->prev;
            q->the_queue->back->next = NULL;
            lst_push_front(q->the_queue, briber);
            q->the_queue->size--;  // compensate for the size++ inside push_front. We don't wanna increase size!
        } else {                                // Briber in the middle
            briber->prev->next = briber->next;
            briber->next->prev = briber->prev;
            lst_push_front(q->the_queue, briber);
            q->the_queue->size--;  // compensate for the size++ inside push_front. We don't wanna increase size!
        }
    }
    return 1;
}
